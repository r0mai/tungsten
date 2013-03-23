
#ifndef EVAL_ORDERNODE_HPP_
#define EVAL_ORDERNODE_HPP_

#include "ast/Node.hpp"

namespace tungsten { namespace eval {

bool nodeLess(const ast::Node& lhs, const ast::Node& rhs);

struct NodeComparatorLess {
	bool operator()(const ast::Node& lhs, const ast::Node& rhs) const {
		return nodeLess(lhs, rhs);
	}
};

bool dictionaryStringLess(const std::string& lhs, const std::string& rhs);

struct DictionaryStringComparatorLess {
	bool operator()(const std::string& lhs, const std::string& rhs) const {
		return dictionaryStringLess(lhs, rhs);
	}
};

}} //namespace tungsten::eval

#endif /* EVAL_ORDERNODE_HPP_ */
