
#ifndef EVAL_PATTERN_MATCHING_HPP_
#define EVAL_PATTERN_MATCHING_HPP_

#include "ast/Node.hpp"
#include "SessionEnvironment.hpp"

#include <map>

namespace tungsten { namespace eval {

typedef std::map<ast::Identifier, ast::Node> MatchedPatternMap;

bool doesPatternMatch(const ast::Node& expression, const ast::Node& pattern, eval::SessionEnvironment& sessionEnvironment);
bool doesPatternMatch(const ast::Node& expression, const ast::Node& pattern, MatchedPatternMap& patternMap, eval::SessionEnvironment& sessionEnvironment);

}} //namespace tungsten::eval

#endif // EVAL_PATTERN_MATCHING_HPP_

