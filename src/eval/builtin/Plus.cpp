
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
#include "eval/flattenOperands.hpp"
#include "eval/SessionEnvironment.hpp"

namespace tungsten { namespace eval { namespace builtin {

struct PlusVisitor : boost::static_visitor<void> {

	PlusVisitor(eval::SessionEnvironment& sessionEnvironment) : sessionEnvironment(sessionEnvironment) {}

	void operator()(const math::Real& real) {
		constant = RealRationalNumber::doOperation( constant, real, rationalPlus, realPlus );
	}

	void operator()(const math::Rational& rational) {
		constant = RealRationalNumber::doOperation( constant, rational, rationalPlus, realPlus );
	}

	void operator()(const ast::String& string) {
		coefficientMap[ast::Node::makeString(string)] =
				RealRationalNumber::doOperation( coefficientMap[ast::Node::makeString(string)], ast::Node::makeRational(1), rationalPlus, realPlus );
	}

	void operator()(const ast::Identifier& identifier) {
		coefficientMap[ast::Node::makeIdentifier(identifier)] =
				RealRationalNumber::doOperation( coefficientMap[ast::Node::makeIdentifier(identifier)], ast::Node::makeRational(1), rationalPlus, realPlus );
	}

	void operator()(const ast::FunctionCall& functionCall) {
		assert( functionCall.getFunction() != ast::Node::makeIdentifier("Plus") );

		ast::Node key = ast::Node::makeFunctionCall(functionCall);
		RealRationalNumber coefficient = math::Rational(1);

		if ( functionCall.getFunction() == ast::Node::makeIdentifier("Times") ) {

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
					key = toMultiply[0];
				} else {
					key = ast::Node::makeFunctionCall("Times", toMultiply);
				}
			}
		}
		coefficientMap[key] =
				RealRationalNumber::doOperation( coefficientMap[key], coefficient, rationalPlus, realPlus );
	}


	ast::Node resultToNode() const {

//		for ( const std::pair<ast::Node, RealRationalNumber>& term : coefficientMap ) {
//			std::cout << term.first << " : " << term.second.toNode() << std::endl;
//		}


		ast::Operands operands;

		for ( const std::pair<ast::Node, RealRationalNumber>& term : coefficientMap ) {
			ast::Node coefficient = term.second.toNode();
			if ( coefficient == ast::Node::makeRational(0) ) {
				/*this space is intentionally left blank*/
			} else if ( coefficient == ast::Node::makeRational(1) ) {
				operands.push_back( term.first );
			} else {
				operands.push_back( sessionEnvironment.recursiveEvaluate(ast::Node::makeFunctionCall("Times", {coefficient, term.first})) );
			}
		}

		ast::Node constantTerm = constant.toNode();
		if ( constantTerm != ast::Node::makeRational(0) ) {
			operands.push_back( constantTerm );
		}

		if ( operands.empty() ) {
			return ast::Node::makeRational(0);
		}

		if ( operands.size() == 1 ) {
			return operands[0];
		}

		return ast::Node::makeFunctionCall("Plus", operands);

	}

	RealRationalNumber constant;

	typedef std::map<ast::Node, RealRationalNumber> CoefficientMap;
	CoefficientMap coefficientMap;

	static const RealRationalNumber::RationalOperation rationalPlus;
	static const RealRationalNumber::RealOperation realPlus;

	eval::SessionEnvironment& sessionEnvironment;
};

const RealRationalNumber::RationalOperation PlusVisitor::rationalPlus = [](const math::Rational& x, const math::Rational& y) { return x+y; };
const RealRationalNumber::RealOperation PlusVisitor::realPlus = [](const math::Real& x, const math::Real& y) { return x+y; };

ast::Node Plus(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment) {

	ast::Operands flatOperands = flattenOperands("Plus", operands);

	PlusVisitor plusVisitor(sessionEnvironment);
	for ( const ast::Node& node : flatOperands ) {
		ast::applyVisitor( node, plusVisitor );
	}

	return plusVisitor.resultToNode();
}

}}} //namespace tungsten::eval::builtin

