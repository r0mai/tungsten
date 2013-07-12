
#ifndef AST_OPERANDS_HPP_
#define AST_OPERANDS_HPP_

#include <list>

#include "NodeFwd.hpp"

namespace tungsten { namespace ast {

template<class T, class A = std::allocator<T>>
class IndexableList : public std::list<T, A> {
public:
	using std::list<T, A>::list;
	T& operator[](typename std::list<T, A>::size_type index) {
		return *std::next(std::list<T, A>::begin(), index);
	}
	const T& operator[](typename std::list<T, A>::size_type index) const {
		return *std::next(std::list<T, A>::cbegin(), index);
	}
};

typedef IndexableList<Node> Operands;

}} //namespace tungsten::ast

#endif //AST_OPERANDS_HPP_

