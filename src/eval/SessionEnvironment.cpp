
#include "SessionEnvironment.hpp"

#include <iterator>
#include <vector>
#include <functional>

#include <boost/bind.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/range/algorithm/find.hpp>
#include <boost/range/algorithm/transform.hpp>

#include "Identifiers.hpp"
#include "threadListableOperands.hpp"
#include "flattenOperands.hpp"

namespace tungsten { namespace eval {

SessionEnvironment::SessionEnvironment() :
		attributeMap(AttributeMap::makeDefault()), builtinFunctions(builtin::createFunctions()), patternMap(PatternMap::makeDefault()) {}

SessionEnvironment::~SessionEnvironment() {}

void SessionEnvironment::raiseMessage(const Message& message) {
	//TODO add to list
	handleMessageString( message.getSymbol() + "::" + message.getTag() );
}

void SessionEnvironment::addPattern(const ast::Node& pattern, const ast::Node& replacement) {
	patternMap.addPattern(pattern, replacement);
}

RandomEngine& SessionEnvironment::getRandomEngine() {
	return randomEngine;
}

ast::Node SessionEnvironment::evaluate(const ast::Node& node) {
	//TODO update history
	return recursiveEvaluate(node);
}

/*
 * This Visitor in the future will probably work like this:
 * Try matching the input Node, with the symbol (pattern) table
 * if we found a match, replace it with the key for the match,
 * otherwise return the original node
 */

struct SessionEnvironment::EvaluateVisitor : boost::static_visitor<ast::Node> {

	EvaluateVisitor(SessionEnvironment& sessionEnvironment) :
		sessionEnvironment(sessionEnvironment) {}

	ast::Node operator()(const math::Real& real) {
		return ast::Node::make<math::Real>(real);
	}

	ast::Node operator()(const math::Rational& rational) {
		return ast::Node::make<math::Rational>(rational);
	}

	ast::Node operator()(const ast::FunctionCall& functionCall) {
		ast::Node function = sessionEnvironment.recursiveEvaluate(functionCall.getFunction());
		ast::Operands operands(functionCall.getOperands());

		//Attribute Hold*
		bool hasHoldFirst = false;
		bool hasHoldRest = false;
		bool hasHoldAll = false;

		if ( function.is<ast::Identifier>() ) {
			hasHoldFirst = sessionEnvironment.attributeMap.hasAttribute(function.get<ast::Identifier>(), ids::HoldFirst);
			hasHoldRest = sessionEnvironment.attributeMap.hasAttribute(function.get<ast::Identifier>(), ids::HoldRest);
			hasHoldAll = sessionEnvironment.attributeMap.hasAttribute(function.get<ast::Identifier>(), ids::HoldAll);
		}

		//Do we evaluate
		bool doHoldFirst = hasHoldFirst || hasHoldAll;
		bool doHoldRest = hasHoldRest || hasHoldAll;

		boost::iterator_range<ast::Operands::iterator> evaluationRange(operands);

		if ( doHoldRest && !evaluationRange.empty() ) {
			evaluationRange.advance_end( -(evaluationRange.size() - 1) );
		}
		if ( doHoldFirst && !evaluationRange.empty() ) {
			evaluationRange.advance_begin( 1 );
		}

		boost::transform(
				evaluationRange,
				evaluationRange.begin(),
				boost::bind(&SessionEnvironment::recursiveEvaluate, boost::ref(sessionEnvironment), _1) );


		//Attribute Flat:
		if (
			function.is<ast::Identifier>() &&
			sessionEnvironment.attributeMap.hasAttribute(function.get<ast::Identifier>(), ids::Flat) )
		{
			operands = flattenOperands( function.get<ast::Identifier>(), operands );
		}


		if ( function.is<ast::Identifier>() &&
			sessionEnvironment.attributeMap.hasAttribute(function.get<ast::Identifier>(), ids::Listable) )
		{

			ast::Operands listOperands;

			ThreadListableOperandsReturnType returnValue = threadListableOperands(
					ast::FunctionCall(function, operands),
					listOperands
				);

			if ( returnValue == ThreadListableOperandsReturnType::UNSUCCESSFUL ) {
				sessionEnvironment.raiseMessage( Message(ids::Thread, ids::tdlen, {ast::Node::make<ast::FunctionCall>(functionCall)}) );
			} else if ( returnValue == ThreadListableOperandsReturnType::NOT_APPLICABLE ) {
				//Fallthrough
			} else {
				assert( returnValue == ThreadListableOperandsReturnType::SUCCESSFUL );
				return sessionEnvironment.recursiveEvaluate( ast::Node::make<ast::FunctionCall>(ids::List, listOperands) );
			}
		}

		//If it is a numeric function and it has at least one Indeterminate argument, then the result is Indeterminate
		if ( function.is<ast::Identifier>() &&
				sessionEnvironment.attributeMap.hasAttribute(function.get<ast::Identifier>(), ids::NumericFunction) &&
				boost::find(operands, ast::Node::make<ast::Identifier>(ids::Indeterminate)) != operands.end() ) {
			return ast::Node::make<ast::Identifier>(ids::Indeterminate);
		}

		//If it is a builtin function => evaulate
		if ( function.is<ast::Identifier>() ) {
			builtin::Functions::const_iterator it = sessionEnvironment.builtinFunctions.find(function.get<ast::Identifier>());
			if ( it != sessionEnvironment.builtinFunctions.end() ) {
				return (it->second)(operands, sessionEnvironment);
			}
		}

		//Check for used defined rules in patternMap
		ast::Node result;
		if (sessionEnvironment.patternMap.applyPatterns(ast::Node::make<ast::FunctionCall>(function, operands), result)) {
			std::cout << "sesresult = " << result << std::endl;
			return sessionEnvironment.recursiveEvaluate(result);
		}

		//If no rules are defined, simply return
		return ast::Node::make<ast::FunctionCall>(function, operands);

	}

	ast::Node operator()(const ast::String& string) {
		return ast::Node::make<ast::String>(string);
	}

	ast::Node operator()(const ast::Identifier& identifier) {
		//TODO this should go to FunctionCall-s branch as well
		ast::Node result;
		if (sessionEnvironment.patternMap.applyPatterns(ast::Node::make<ast::Identifier>(identifier), result)) {
			return sessionEnvironment.recursiveEvaluate(result);
		}
		return result;
	}

private:
	SessionEnvironment& sessionEnvironment;
};

ast::Node SessionEnvironment::recursiveEvaluate(const ast::Node& node) {
	EvaluateVisitor evaluateVisitor{*this};
	ast::Node result = ast::applyVisitor(node, evaluateVisitor);

	//Sort if the result is Orderless function
	//Maybe this should be in FunctionCall branch of the Visitor
	if (
			result.is<ast::FunctionCall>() &&
			result.get<ast::FunctionCall>().getFunction().is<ast::Identifier>() &&
			attributeMap.hasAttribute(result.get<ast::FunctionCall>().getFunction().get<ast::Identifier>(), ids::Orderless) )
	{
		ast::Operands& operands = result.get<ast::FunctionCall>().getOperands();
		std::sort( operands.begin(), operands.end() );
	}

	return result;
}

}} //namespace tungsten::eval


