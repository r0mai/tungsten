
#include "patternMatching.hpp"
#include "getHead.hpp"

namespace tungsten { namespace eval {

bool doesPatternMatchRecursive(const ast::Node& expression, const ast::Node& pattern, MatchedPatternMap& patternMap, eval::SessionEnvironment& sessionEnvironment);

struct DoesPatternMatchRecursive2Visitor : boost::static_visitor<bool> {

	DoesPatternMatchRecursive2Visitor(MatchedPatternMap& patternMap, eval::SessionEnvironment& sessionEnvironment) : patternMap(patternMap), sessionEnvironment(sessionEnvironment) {}

	template<class T, class U>
	bool operator()(const T& /*expression*/, const U& /*pattern*/) {
		return false;
	}
	template<class T>
	bool operator()(const T& expression, const T& pattern) {
		return expression == pattern;
	}
	bool operator()(const ast::FunctionCall& expression, const ast::FunctionCall& pattern) {
		return expression.getOperands().size() == pattern.getOperands().size() &&
			doesPatternMatchRecursive(expression.getFunction(), pattern.getFunction(), patternMap, sessionEnvironment) &&
			std::equal(expression.getOperands().begin(), expression.getOperands().end(), pattern.getOperands().begin(),
			[&](const ast::Node& subExpression, const ast::Node& subPattern) {
				return doesPatternMatchRecursive(subExpression, subPattern, patternMap, sessionEnvironment);
			});
	}

	MatchedPatternMap& patternMap;
	SessionEnvironment& sessionEnvironment;
};

//doesPatternMatchRecursive takes care of pattern naming
bool doesPatternMatchRecursive2(const ast::Node& expression, 
	const ast::Node& pattern,
	MatchedPatternMap& patternMap,
	eval::SessionEnvironment& sessionEnvironment)
{
	if ( pattern.isFunctionCall(ids::Blank) ) {
		const ast::Operands& blankOperands = pattern.get<ast::FunctionCall>().getOperands();
		switch ( blankOperands.size() ) {
			case 0:
				return true;
			case 1:
				return doesPatternMatchRecursive(getHead(expression), blankOperands[0], patternMap, sessionEnvironment);
			default:
				sessionEnvironment.raiseMessage( Message(ids::Blank, ids::argt, {
						ast::Node::make<ast::Identifier>( ids::Blank ),
						ast::Node::make<math::Rational>( blankOperands.size() ),
						ast::Node::make<math::Rational>( 0 ),
						ast::Node::make<math::Rational>( 1 )
				} ));
				return false;
		}
		assert(false);
	}
	
	DoesPatternMatchRecursive2Visitor patternMatchVisitor(patternMap, sessionEnvironment);
	return ast::applyVisitor(expression, pattern, patternMatchVisitor);
}

bool doesPatternMatchRecursive(const ast::Node& expression, const ast::Node& pattern, MatchedPatternMap& patternMap, eval::SessionEnvironment& sessionEnvironment) {

	boost::optional<ast::Identifier> patternName;
	const ast::Node *patternPtr = &pattern; //using pointer to avoid copying

	if ( pattern.isFunctionCall(ids::Pattern) ) {
		const ast::Operands& patternOperands = pattern.get<ast::FunctionCall>().getOperands();
		if ( patternOperands.size() == 2 && patternOperands[0].is<ast::Identifier>() ) {
			patternName = patternOperands[0].get<ast::Identifier>();
			patternPtr = &patternOperands[1];
		} else {
			sessionEnvironment.raiseMessage(Message(ids::Pattern, ids::patvar, {pattern}));
			return false;
		}
	}
	
	if ( doesPatternMatchRecursive2(expression, *patternPtr, patternMap, sessionEnvironment) ) {
		if ( patternName ) {
			patternMap[*patternName] = expression;
		}
		return true;
	}
	return false;
}

bool doesPatternMatch(const ast::Node& expression, const ast::Node& pattern, eval::SessionEnvironment& sessionEnvironment) {
	MatchedPatternMap patternMap;
	return doesPatternMatch(expression, pattern, patternMap, sessionEnvironment);
}

bool doesPatternMatch(const ast::Node& expression, const ast::Node& pattern, MatchedPatternMap& patternMap, eval::SessionEnvironment& sessionEnvironment) {
	bool res =  doesPatternMatchRecursive(expression, pattern, patternMap, sessionEnvironment);
	for ( auto x : patternMap ) {
		//std::cout << x.first << " : " << x.second << std::endl;
	}
	return res;
}


}} //namespace tungsten::eval

