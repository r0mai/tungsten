
#include "SessionEnvironment.hpp"

#include <iterator>
#include <vector>
#include <functional>

#include <boost/bind.hpp>
#include <boost/range/algorithm/find.hpp>
#include <boost/range/algorithm/transform.hpp>

#include "Identifiers.hpp"
#include "threadListableOperands.hpp"
#include "flattenOperands.hpp"

namespace tungsten { namespace eval {

SessionEnvironment::SessionEnvironment() :
		attributeMap(AttributeMap::makeDefault()), builtinFunctions(builtin::createFunctions()), patternMap(PatternMap::makeDefault()) {}

SessionEnvironment::~SessionEnvironment() {}

ast::Node SessionEnvironment::evaluate(const ast::Node& node) {
	//TODO update history
	return recursiveEvaluate(node);
}

void SessionEnvironment::addPattern(const ast::Node& pattern, const ast::Node& replacement) {
	patternMap.addPattern(pattern, replacement);
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
		ast::Operands operands(functionCall.getOperands().size());

		//TODO Hold*

		boost::transform(
				functionCall.getOperands(),
				operands.begin(),
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

			ThreadListableOperandsReturnType returnValue = threadListableOperands( functionCall, listOperands );
			if ( returnValue == ThreadListableOperandsReturnType::UNSUCCESSFUL ) {
				std::cout << "Thread::tdlen UNSUCCESSFUL" << std::endl;
				//TODO issue Thread::tdlen
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

		return ast::Node::make<ast::FunctionCall>(function, operands);

	}

	ast::Node operator()(const ast::String& string) {
		return ast::Node::make<ast::String>(string);
	}

	ast::Node operator()(const ast::Identifier& identifier) {
		//TODO this should go to FunctionCall-s branch as well
		return sessionEnvironment.patternMap.applyPatterns(ast::Node::make<ast::Identifier>(identifier));
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


