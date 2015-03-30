
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

struct PlusVisitor : boost::static_visitor<void> {

	PlusVisitor(eval::SessionEnvironment& sessionEnvironment) : constantTerm(math::Rational(0)), sessionEnvironment(sessionEnvironment) {}

	void operator()(const math::Real& real) {
		doAddition(constantTerm, real);
	}

	void operator()(const math::Rational& rational) {
		doAddition(constantTerm, rational);
	}

	void operator()(const math::ComplexReal& real) {
		doAddition(constantTerm, real);
	}

	void operator()(const math::ComplexRational rational) {
		doAddition(constantTerm, rational);
	}

	void operator()(const ast::String& string) {
		insertOrAddInMap(ast::Node::make<ast::String>(string), math::Rational(1));
	}

	void operator()(const ast::Identifier& identifier) {
		if(identifier == eval::ids::I) {
			math::ComplexRational i;
			i.real(0);
			i.imag(1);
			doAddition(constantTerm, i);
		} else {
			insertOrAddInMap(ast::Node::make<ast::Identifier>(identifier), math::Rational(1));
		}
	}

	void operator()(const ast::FunctionCall& functionCall) {
		assert( functionCall.getFunction() != ast::Node::make<ast::Identifier>(ids::Plus) );

		ast::Node term = ast::Node::make<ast::FunctionCall>(functionCall);
		RealRationalNumber coefficient = math::Rational(1);

		if ( functionCall.getFunction() == ast::Node::make<ast::Identifier>(ids::Times) ) {

			auto isNodeNumeric = [](const ast::Node& node) { return node.isNumeric(); };
			auto notIsNodeNumeric = [](const ast::Node& node) { return !node.isNumeric(); };

			//It is assumed, that there is at most a single numeric Node in Times's operands
			assert( boost::count_if( functionCall.getOperands(), isNodeNumeric ) <= 1 );

			ast::Operands::const_iterator numericLocation = boost::find_if( functionCall.getOperands(), isNodeNumeric );

			if ( numericLocation != functionCall.getOperands().end() ) {
				coefficient = *numericLocation;

				ast::Operands toMultiply;
				boost::copy( functionCall.getOperands() | boost::adaptors::filtered( notIsNodeNumeric ),
						std::back_inserter( toMultiply ) );

				assert( !toMultiply.empty() );

				if ( toMultiply.size() == 1 ) {
					term = toMultiply[0];
				} else {
					term = ast::Node::make<ast::FunctionCall>(ids::Times, toMultiply);
				}
			}
		}

		insertOrAddInMap(term, coefficient);
	}

	//TODO optimalization
	void insertOrAddInMap(const ast::Node& key, const RealRationalNumber& toAdd) {
		CoefficientMap::iterator it = coefficientMap.find(key);
		if ( it == coefficientMap.end() ) {
			coefficientMap[key] = ast::Node::make<math::Rational>(0);
		}
		doAddition( coefficientMap[key], toAdd );
	}

	void doAddition(RealRationalNumber& value, const RealRationalNumber& toAdd) {
		value = RealRationalNumber::doPlus( value, toAdd );
	}

	ast::Node resultToNode() const {

//		for ( const std::pair<ast::Node, RealRationalNumber>& term : coefficientMap ) {
//			std::cout << term.first << " : " << term.second.toNode() << std::endl;
//		}


		ast::Operands operands;

		for ( const std::pair<ast::Node, RealRationalNumber>& term : coefficientMap ) {
			ast::Node coefficient = term.second.toNode();
			if ( coefficient == ast::Node::make<math::Rational>(0) ) {
				/*this space is intentionally left blank*/
			} else if ( coefficient == ast::Node::make<math::Rational>(1) ) {
				operands.push_back( term.first );
			} else {
				operands.push_back( sessionEnvironment.recursiveEvaluate(ast::Node::make<ast::FunctionCall>(ids::Times, {coefficient, term.first})) );
			}
		}

		ast::Node constantTermNode = constantTerm.toNode();
		if ( constantTermNode != ast::Node::make<math::Rational>(0) ) {
			operands.push_back( constantTermNode );
		}

		if ( operands.empty() ) {
			return ast::Node::make<math::Rational>(0);
		}

		if ( operands.size() == 1 ) {
			return operands[0];
		}

		return ast::Node::make<ast::FunctionCall>(ids::Plus, operands);

	}

	RealRationalNumber constantTerm;

	typedef std::map<ast::Node, RealRationalNumber> CoefficientMap;
	CoefficientMap coefficientMap;

	eval::SessionEnvironment& sessionEnvironment;
};

OptionalNode Plus(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment) {
	eval::NumericalClassification numericalClassification =
		eval::classifyNumerically(operands);

	switch (numericalClassification) {
		default:
			assert(false);
			return EvaluationFailure();
		case NumericalClassification::HAS_SYMBOLIC:
			{
				PlusVisitor plusVisitor(sessionEnvironment);
				for ( const ast::Node& node : operands ) {
					ast::applyVisitor( node, plusVisitor );
				}
				return plusVisitor.resultToNode();
			}
		case NumericalClassification::ALL_RATIONAL:
			{
				math::Rational result = 0;
				for ( const ast::Node& node : operands ) {
					result += node.get<math::Rational>();
				}
				return ast::Node::make<math::Rational>(result);
			}
		case NumericalClassification::ALL_REAL:
			{
				math::Real result = 0;
				for ( const ast::Node& node : operands ) {
					result += node.get<math::Real>();
				}
				return ast::Node::make<math::Real>(result);
			}
		case NumericalClassification::ALL_NUMERIC:
			{
				math::Real result = 0;
				for ( const ast::Node& node : operands ) {
					result += node.getNumeric();
				}
				return ast::Node::make<math::Real>(result);
			}
	}
}

}}} //namespace tungsten::eval::builtin

