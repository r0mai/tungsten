
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

#include "eval/RealRationalNumber.hpp"
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

	void operator()(const ast::String& string) {
		insertOrMultiplyInMap(ast::Node::make<ast::String>(string), math::Rational(1));
	}

	void operator()(const ast::Identifier& identifier) {
		insertOrMultiplyInMap(ast::Node::make<ast::Identifier>(identifier), math::Rational(1));
	}

	void operator()(const ast::FunctionCall& functionCall) {
		assert( functionCall.getFunction() != ast::Node::make<ast::Identifier>(ids::Times) );

		ast::Node factor = ast::Node::make<ast::FunctionCall>(functionCall);
		RealRationalNumber exponent = math::Rational(1);

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
	void insertOrMultiplyInMap(const ast::Node& key, const RealRationalNumber& toMultiply) {
		ExponentMap::iterator it = exponentMap.find(key);
		if ( it == exponentMap.end() ) {
			exponentMap[key] = ast::Node::make<math::Rational>(0);
		}
		doAddition( exponentMap[key], toMultiply );
	}

	void doMultiplication(RealRationalNumber& value, const RealRationalNumber& toMultiply) {
		value = RealRationalNumber::doOperation( value, toMultiply,
						[](const math::Rational& x, const math::Rational& y) { return x*y; },
						[](const math::Real& x, const math::Real& y) { return x*y; } );
	}

	void doAddition(RealRationalNumber& value, const RealRationalNumber& toMultiply) {
		value = RealRationalNumber::doOperation( value, toMultiply,
						[](const math::Rational& x, const math::Rational& y) { return x+y; },
						[](const math::Real& x, const math::Real& y) { return x+y; } );
	}

	ast::Node resultToNode() const {

//		for ( const std::pair<ast::Node, RealRationalNumber>& factor : exponentMap ) {
//			std::cout << factor.first << " : " << factor.second.toNode() << std::endl;
//		}

		ast::Operands operands;

		//TODO this could be moved to operator()(const math::Rational& rational) when rational == 0
		ast::Node constantFactorNode = constantFactor.toNode();
		if ( constantFactorNode == ast::Node::make<math::Rational>(0) || constantFactorNode == ast::Node::make<math::Real>(0) ) {
			return constantFactorNode;
		}

		if ( constantFactorNode != ast::Node::make<math::Rational>(1) ) {
			operands.push_back( constantFactorNode );
		}


		for ( const std::pair<ast::Node, RealRationalNumber>& factor : exponentMap ) {
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

		ast::Operands prunedOperands;

		for(auto& node: operands) {
			if(node.isFunctionCall(ids::Power) && node.get<ast::FunctionCall>().getOperands()[0].isFunctionCall(ids::DirectedInfinity)) {
				const auto infinityPower = node.get<ast::FunctionCall>();
				const auto infinity = infinityPower.getOperands()[0].get<ast::FunctionCall>();
				const auto power = infinityPower.getOperands()[1].getNumeric();
				if(!infinity.getOperands().empty()) {
					prunedOperands.push_back(ast::Node::make<ast::FunctionCall>(ids::DirectedInfinity, {
								ast::Node::make<math::Real>(math::power(infinity.getOperands()[0].getNumeric(), power))
					}));
				} else {
					prunedOperands.push_back(ast::Node::make<ast::FunctionCall>(ids::DirectedInfinity, { }));
				}
			} else {
				prunedOperands.push_back(std::move(node));
			}
		}

		std::swap(operands, prunedOperands);

		std::vector<ast::Node> infinities;
		std::copy_if(operands.begin(), operands.end(), std::back_inserter(infinities), [](const ast::Node& node) {
				return node.isFunctionCall(ids::DirectedInfinity);
		});

		if (!infinities.empty()) {
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

		if ( operands.size() == 1 ) {
			return operands[0];
		}

		return ast::Node::make<ast::FunctionCall>(ids::Times, operands);

	}

	RealRationalNumber constantFactor;

	typedef std::map<ast::Node, RealRationalNumber> ExponentMap;
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

