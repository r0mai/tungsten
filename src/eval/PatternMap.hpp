

#ifndef EVAL_PATTERNMAP_HPP_
#define EVAL_PATTERNMAP_HPP_

#include <map>

#include "ast/Node.hpp"

namespace tungsten { namespace eval {

class PatternMap {
public:

	static PatternMap makeDefault();

	PatternMap();

	void addPattern(const ast::Node& pattern, const ast::Node& replacement);

	ast::Node applyPatterns(const ast::Node& node) const;
private:
	typedef std::map<ast::Node, ast::Node> Storage;
	Storage storage;
};

}} //namespace tungsten::eval

#endif /* EVAL_PATTERNMAP_HPP_ */
