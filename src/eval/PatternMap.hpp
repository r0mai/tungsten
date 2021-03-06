
#ifndef EVAL_PATTERNMAP_HPP_
#define EVAL_PATTERNMAP_HPP_

#include <list>
#include <utility>
#include <boost/optional.hpp>

#include "ast/Node.hpp"


namespace tungsten { namespace eval {

class SessionEnvironment;

class PatternMap {
public:

	static PatternMap makeDefault();

	PatternMap();

	void addPattern(const ast::Node& pattern, const ast::Node& replacement);
	boost::optional<ast::Node> getPatternReplacement(const ast::Node& pattern) const;
	void removePattern(const ast::Node& pattern);

	//Returns true, if a patterns matches node; result will be set to it's new value
	//Otherwise, result == node
	bool applyPatterns(const ast::Node& node, ast::Node& result, eval::SessionEnvironment& sessionEnvironment) const;
	// Returns a vector of assigned variables
	std::vector<ast::Identifier> getSetVariables() const;
private:
	//<pattern, replacement>
	typedef std::vector<std::pair<ast::Node, ast::Node>> Storage;
	Storage storage;
};

}} //namespace tungsten::eval

#endif /* EVAL_PATTERNMAP_HPP_ */

