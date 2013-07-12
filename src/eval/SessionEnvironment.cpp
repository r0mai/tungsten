
#include "SessionEnvironment.hpp"

#include <iterator>
#include <vector>
#include <functional>
#include <iostream>

#include <boost/bind.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/range/algorithm/find.hpp>

#include "io/Parser.hpp"
#include "Identifiers.hpp"
#include "threadListableOperands.hpp"
#include "flattenOperands.hpp"
#include "orderNode.hpp"

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

boost::optional<ast::Node> SessionEnvironment::getPatternReplacement(const ast::Node& pattern) {
	return patternMap.getPatternReplacement(pattern);
}

void SessionEnvironment::removePattern(const ast::Node& pattern) {
	patternMap.removePattern(pattern);
}

RandomEngine& SessionEnvironment::getRandomEngine() {
	return randomEngine;
}

AttributeMap& SessionEnvironment::getAttributeMap() {
	return attributeMap;
}

const AttributeMap& SessionEnvironment::getAttributeMap() const {
	return attributeMap;
}

AttributeSet SessionEnvironment::getAttributeSetForFunction(const ast::Node& node) const {
	if ( node.is<ast::Identifier>() ) {
		return attributeMap.getAttributeSet( node.get<ast::Identifier>() );
	}
	return AttributeSet{};
}

ast::Node SessionEnvironment::evaluate(const std::string& inputString) {

	boost::optional<ast::Node> expression = io::parseInput(inputString);

	if ( !expression ) {
		raiseMessage(Message(ids::Syntax, ids::Syntax, {}));
		return ast::Node::make<ast::Identifier>(ids::Null);
	}

	return evaluate(*expression);
}

ast::Node SessionEnvironment::evaluate(const ast::Node& node) {
	//TODO history
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

		AttributeSet functionAttributes = sessionEnvironment.getAttributeSetForFunction(function);

		bool hasHoldAllComplete = functionAttributes.count( ids::HoldAllComplete );

		if ( hasHoldAllComplete ) {
			return ast::Node::make<ast::FunctionCall>(function, operands);
		}

		bool hasHoldFirst = functionAttributes.count( ids::HoldFirst );
		bool hasHoldRest = functionAttributes.count( ids::HoldRest );
		bool hasHoldAll = functionAttributes.count( ids::HoldAll );
		bool hasSequenceHold = functionAttributes.count( ids::SequenceHold );
		bool hasFlat = functionAttributes.count( ids::Flat );
		bool hasListable = functionAttributes.count( ids::Listable );
		bool hasNumericFunction = functionAttributes.count( ids::NumericFunction );

		//Attribute Hold*
		//Do we evaluate
		bool doHoldFirst = hasHoldFirst || hasHoldAll;
		bool doHoldRest = hasHoldRest || hasHoldAll;
		{	
			bool first = true;
			for ( auto it = operands.begin();  it != operands.end(); ++it, first = false ) {
				if ( ((!first || !doHoldFirst) && (first || !doHoldRest)) || it->isFunctionCall(ids::Evaluate) ) {
					*it = sessionEnvironment.recursiveEvaluate( *it );
				}

			}
		}

		//Sequence[] Parameter and Attribute SequenceHold
		if ( !hasSequenceHold )
		{
			for ( auto it = operands.begin(); it != operands.end(); ) {
				if ( it->isFunctionCall(ids::Sequence) ) {
					ast::Operands sequenceOperands = std::move(it->get<ast::FunctionCall>().getOperands());
					ast::Operands::iterator sequenceElementPosition = operands.erase( it++ ); 
					operands.splice( sequenceElementPosition, std::move(sequenceOperands) );
				} else {
					++it;
				}
			}
		}

		//Attribute Flat:
		if ( hasFlat ) {
			operands = flattenOperands( function, operands );
		}

		//Attribute Listable:
		if ( hasListable ) {

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
		if ( hasNumericFunction &&
				boost::find(operands, ast::Node::make<ast::Identifier>(ids::Indeterminate)) != operands.end() )
		{
			return ast::Node::make<ast::Identifier>(ids::Indeterminate);
		}

		//Check for user defined rules in patternMap
		ast::Node result;
		if (sessionEnvironment.patternMap.applyPatterns(ast::Node::make<ast::FunctionCall>(function, operands), result, sessionEnvironment)) {
			return sessionEnvironment.recursiveEvaluate(result);
		}

		//If it is a builtin function => evaulate
		if ( function.is<ast::Identifier>() ) {
			builtin::Functions::const_iterator it = sessionEnvironment.builtinFunctions.find(function.get<ast::Identifier>());
			if ( it != sessionEnvironment.builtinFunctions.end() ) {
				builtin::OptionalNode evaluationResult = (it->second)(operands, sessionEnvironment);
				if ( !evaluationResult ) { //Evaluation failed => return the expression untouched
					return ast::Node::make<ast::FunctionCall>(function, operands);
				}
				return *evaluationResult;
			}
		//pure function
		} else if ( function.isFunctionCall(ids::Function) ) {
			builtin::OptionalNode evaluationResult = builtin::evaluateFunction( function.get<ast::FunctionCall>().getOperands(), operands, sessionEnvironment );
			//TODO code repetition
			if ( !evaluationResult ) { //Evaluation failed => return the expression untouched
				return ast::Node::make<ast::FunctionCall>(function, operands);
			}
			return *evaluationResult;
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
		if (sessionEnvironment.patternMap.applyPatterns(ast::Node::make<ast::Identifier>(identifier), result, sessionEnvironment)) {
			return sessionEnvironment.recursiveEvaluate(result);
		}
		return ast::Node::make<ast::Identifier>(identifier);
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
		operands.sort(NodeComparatorLess{});
	}

	return result;
}

}} //namespace tungsten::eval


