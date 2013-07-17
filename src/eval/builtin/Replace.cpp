
#include "functions.hpp"
#include "eval/SessionEnvironment.hpp"
#include "eval/patternMatching.hpp"

#include <stack>

namespace tungsten { namespace eval { namespace builtin {

OptionalNode Replace(const ast::Operands& operands, eval::SessionEnvironment& /*sessionEnvironment*/) {
	return ast::Node::make<ast::FunctionCall>( ids::Replace, operands );
}

typedef std::pair<const ast::Node*, const ast::Node*> RulePtr;

//returns false if none of the patterns matched
bool applyRulePtrs(ast::Node& expression, const std::vector<RulePtr>& rules, eval::SessionEnvironment& sessionEnvironment) {

	bool result = false;

	std::stack<ast::Node*> todoStack;
	todoStack.push(&expression);

	while ( !todoStack.empty() ) {

		ast::Node& current = *todoStack.top();
		todoStack.pop();

		MatchedPatternMap patternMap;
		bool matched = false;
		for ( const RulePtr& rulePtr : rules ) {
			const ast::Node& pattern = *rulePtr.first;
			const ast::Node& replacement = *rulePtr.second;
			if ( doesPatternMatch( current, pattern, patternMap, sessionEnvironment ) ) {
				result = true;
				matched = true;
				current = applyPatternMapImmutable( replacement, patternMap );
				break;
			}
		}
		if ( !matched && current.is<ast::FunctionCall>() ) {
			ast::FunctionCall& functionCall = current.getM<ast::FunctionCall>();
			todoStack.push(&functionCall.getFunction());
			for ( ast::Node& operand : functionCall.getOperands() ) {
				todoStack.push(&operand);
			}
		}
	}
	
	return result;
}

//returns false when a error message is raised
bool applyRules(ast::Node& expression, const ast::Node& rules, eval::SessionEnvironment& sessionEnvironment, const ast::Identifier& caller) {

	if ( rules.isFunctionCall(ids::List) ) {
		const ast::Operands& listOperands = rules.get<ast::FunctionCall>().getOperands();
		if ( std::all_of( listOperands.begin(), listOperands.end(), [](const ast::Node& node) { return node.isFunctionCall(ids::List); } ) ) {

			ast::Operands expressionList = ast::Operands( listOperands.size(), expression );

			for ( unsigned i = 0; i < listOperands.size(); ++i ) {
				if ( !applyRules( expressionList[i], listOperands[i], sessionEnvironment, caller ) ) {
					return false;
				}
			}
			expression = ast::Node::make<ast::FunctionCall>(ids::List, expressionList);
			
		} else if ( std::all_of( listOperands.begin(), listOperands.end(), [](const ast::Node& node) { 
				return (node.isFunctionCall(ids::Rule) || node.isFunctionCall(ids::RuleDelayed)) && node.get<ast::FunctionCall>().getOperands().size() == 2;
			} ) )
		{
			std::vector<RulePtr> rulePtrs(listOperands.size());
			std::transform( listOperands.begin(), listOperands.end(), rulePtrs.begin(), [](const ast::Node& rule) {
				return std::make_pair(&rule.get<ast::FunctionCall>().getOperands()[0], &rule.get<ast::FunctionCall>().getOperands()[1]);
			} );
			applyRulePtrs(expression, rulePtrs, sessionEnvironment);
		} else {
			sessionEnvironment.raiseMessage( Message(caller, ids::rmix, {rules}) );
			return false;
		}
	
	} else if ((rules.isFunctionCall(ids::Rule) || rules.isFunctionCall(ids::RuleDelayed)) && rules.get<ast::FunctionCall>().getOperands().size() == 2 ) {
		applyRulePtrs(expression, std::vector<RulePtr>(1, std::make_pair(&rules.get<ast::FunctionCall>().getOperands()[0], &rules.get<ast::FunctionCall>().getOperands()[1])), sessionEnvironment);
	} else {
		sessionEnvironment.raiseMessage( Message(caller, ids::reps, {rules}) );
		return false;
	}
	return true;
}

OptionalNode ReplaceAll(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment) {
	if ( operands.size() != 2 ) {
		sessionEnvironment.raiseMessage( Message(ids::ReplaceAll, ids::argrx, {
				ast::Node::make<ast::Identifier>( ids::ReplaceAll ),
				ast::Node::make<math::Rational>( operands.size() ),
				ast::Node::make<math::Rational>( 2 )
		} ));
		return EvaluationFailure();
	}

	const ast::Node& expression = operands.front();
	const ast::Node& rules = operands.back();

	ast::Node result = expression;
	if ( !applyRules( result, rules, sessionEnvironment, ids::ReplaceAll ) ) {
		return EvaluationFailure();
	}
	return sessionEnvironment.recursiveEvaluate(result);
}

OptionalNode ReplaceRepeated(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment) {
	if ( operands.size() != 2 ) {
		sessionEnvironment.raiseMessage( Message(ids::ReplaceRepeated, ids::argrx, {
				ast::Node::make<ast::Identifier>( ids::ReplaceRepeated ),
				ast::Node::make<math::Rational>( operands.size() ),
				ast::Node::make<math::Rational>( 2 )
		} ));
		return EvaluationFailure();
	}
		
	const ast::Node& expression = operands.front();
	const ast::Node& rules = operands.back();

	ast::Node result = expression;
	while ( true ) {
		ast::Node last = result; 
		if ( !applyRules( result, rules, sessionEnvironment, ids::ReplaceRepeated ) ) {
			return EvaluationFailure();
		}
		result = sessionEnvironment.recursiveEvaluate(result);
		if ( result == last ) {
			break;
		}
	}
	return result;
}

}}} //namespace tungsten::eval::builtin


