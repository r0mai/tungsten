
#include "functions.hpp"

#include <map>
#include <iostream>
#include <iterator>
#include <functional>
#include <vector>

#include <boost/range/adaptor/filtered.hpp>
#include <boost/range/algorithm/copy.hpp>
#include <boost/range/algorithm/count_if.hpp>
#include <boost/range/algorithm/find_if.hpp>

#include "eval/TypedNumber.hpp"
#include "eval/SessionEnvironment.hpp"
#include "eval/classifyOperands.hpp"

namespace tungsten { namespace eval { namespace builtin {

struct TimesVisitor : boost::static_visitor<void> {

	TimesVisitor(eval::SessionEnvironment& sessionEnvironment) : constantFactor(math::Rational(1)), sessionEnvironment(sessionEnvironment) {}

	void operator()(const math::Real& real) {
		doMultiplication(constantFactor, real);
	}

	void operator()(const math::Rational& rational) {
		doMultiplication(constantFactor, rational);
	}

	void operator()(const math::ComplexReal& real) {
		doMultiplication(constantFactor, real);
	}

	void operator()(const math::ComplexRational& rational) {
		doMultiplication(constantFactor, rational);
	}

	void operator()(const ast::String& string) {
		insertOrMultiplyInMap(ast::Node::make<ast::String>(string), math::Rational(1));
	}

	void operator()(const ast::Identifier& identifier) {
		insertOrMultiplyInMap(ast::Node::make<ast::Identifier>(identifier), math::Rational(1));
	}

	void operator()(const ast::FunctionCall& functionCall) {
		assert( functionCall.getFunction() != ast::Node::make<ast::Identifier>(ids::Times) );

		ast::Node factor = ast::Node::make<ast::FunctionCall>(functionCall);
		TypedNumber exponent = math::Rational(1);

		if ( functionCall.getFunction() == ast::Node::make<ast::Identifier>(ids::Power) ) {

			assert( functionCall.getOperands().size() == 2 );

			if ( functionCall.getOperands()[1].isNumeric() ) {
				//Issue 1: 2^(1/2) stays in symbolic format, so both operands can be numeric
				factor = functionCall.getOperands()[0];
				exponent = functionCall.getOperands()[1];
			}

		}
		insertOrMultiplyInMap(factor, exponent);
	}

	//TODO optimalization
	void insertOrMultiplyInMap(const ast::Node& key, const TypedNumber& toMultiply) {
		ExponentMap::iterator it = exponentMap.find(key);
		if ( it == exponentMap.end() ) {
			exponentMap[key] = ast::Node::make<math::Rational>(0);
		}
		doAddition( exponentMap[key], toMultiply );
	}

	void doMultiplication(TypedNumber& value, const TypedNumber& toMultiply) {
		value = TypedNumber::doTimes( value, toMultiply );
	}

	void doAddition(TypedNumber& value, const TypedNumber& toMultiply) {
		value = TypedNumber::doPlus( value, toMultiply );
	}

	ast::Node resultToNode() const {

//		for ( const std::pair<ast::Node, TypedNumber>& factor : exponentMap ) {
//			std::cout << factor.first << " : " << factor.second.toNode() << std::endl;
//		}

		ast::Operands operands;

		//TODO this could be moved to operator()(const math::Rational& rational) when rational == 0
		ast::Node constantFactorNode = constantFactor.toNode();

		auto isSpecial = [](const ast::Node& node) { return node.isFunctionCall(ids::DirectedInfinity); };
		bool areSpecialsPresent = std::find_if(exponentMap.begin(), exponentMap.end(), [&isSpecial](const std::pair<const ast::Node, TypedNumber> p) {
				return isSpecial(p.first);
		}) != exponentMap.end();

		if ( !areSpecialsPresent ) {
			if ( constantFactorNode == ast::Node::make<math::Rational>(0) || constantFactorNode == ast::Node::make<math::Real>(0) ) {
				return constantFactorNode;
			}
		}

		if ( constantFactorNode != ast::Node::make<math::Rational>(1) ) {
			operands.push_back( constantFactorNode );
		}


		for ( const std::pair<ast::Node, TypedNumber>& factor : exponentMap ) {
			ast::Node exponent = factor.second.toNode();
			if ( exponent == ast::Node::make<math::Rational>(0) ) {
				/*this space is intentionally left blank*/
			} else if ( exponent == ast::Node::make<math::Rational>(1) ) {
				operands.push_back( factor.first );
			} else {
				operands.push_back( sessionEnvironment.recursiveEvaluate(ast::Node::make<ast::FunctionCall>(ids::Power, {factor.first, exponent})) );
			}
		}

		if ( operands.empty() ) {
			return ast::Node::make<math::Rational>(1);
		}

		if ( operands.size() == 1 ) {
			return operands[0];
		}

		std::vector<ast::Node> infinities;
		std::copy_if(operands.begin(), operands.end(), std::back_inserter(infinities), [](const ast::Node& node) {
				return node.isFunctionCall(ids::DirectedInfinity);
		});

		if (!infinities.empty()) {

			if(std::find_if(operands.begin(), operands.end(), [](const ast::Node& node) {
				return node.isNumeric() && node.getNumeric() == math::Real(0);
			}) != operands.end()) {
				return ast::Node::make<ast::Identifier>(ids::Indeterminate);
			}
			auto prod = ast::Node::make<math::Real>(1);
			for(const auto& infinity: infinities) {
				const auto& infOperands = infinity.get<ast::FunctionCall>().getOperands();
				if ( !infOperands.empty() ) {
					const auto& direction = infOperands[0];
					prod =  ast::Node::make<math::Real>( prod.getNumeric() * direction.getNumeric() );
				} else {
					return ast::Node::make<ast::FunctionCall>(ids::DirectedInfinity, { } );
				}
			}
			return ast::Node::make<ast::FunctionCall>(ids::DirectedInfinity, { prod });
		}

		return ast::Node::make<ast::FunctionCall>(ids::Times, operands);

	}

	TypedNumber constantFactor;

	typedef std::map<ast::Node, TypedNumber> ExponentMap;
	ExponentMap exponentMap;

	eval::SessionEnvironment& sessionEnvironment;
};

OptionalNode Times(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment) {
	eval::NumericalClassification numericalClassification =
		eval::classifyNumerically(operands);

	switch (numericalClassification) {
		default:
			assert(false);
			return EvaluationFailure();
		case NumericalClassification::HAS_SYMBOLIC:
			{
				TimesVisitor timesVisitor(sessionEnvironment);
				for ( const ast::Node& node : operands ) {
					ast::applyVisitor( node, timesVisitor );
				}

				return timesVisitor.resultToNode();
			}
		case NumericalClassification::ALL_RATIONAL:
			{
				math::Rational result = 1;
				for ( const ast::Node& node : operands ) {
					result *= node.get<math::Rational>();
				}
				return ast::Node::make<math::Rational>(result);
			}
		case NumericalClassification::ALL_REAL:
			{
				math::Real result = 1;
				for ( const ast::Node& node : operands ) {
					result *= node.get<math::Real>();
				}
				return ast::Node::make<math::Real>(result);
			}
		case NumericalClassification::ALL_NUMERIC:
			{
				math::Real result = 1;
				for ( const ast::Node& node : operands ) {
					result *= node.getNumeric();
				}
				return ast::Node::make<math::Real>(result);
			}
	}
}

}}} //namespace tungsten::eval::builtin

