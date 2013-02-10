
#ifndef AST_NODE_HPP_
#define AST_NODE_HPP_

#include <cassert>
#include <initializer_list>
#include <memory>
#include <type_traits>

#include <boost/variant.hpp>
#include <boost/operators.hpp>

#include "NodeFwd.hpp"
#include "FunctionCall.hpp"
#include "NodeTypes.hpp"
#include "util/make_unique.hpp"

namespace tungsten { namespace ast {

class Node :
		boost::less_than_comparable<Node,
		boost::equality_comparable<Node>> {
public:

	//partially obsolete: TODO Make these use perfect forwarding, this requires partially template specializing constructors
	template<class T, class... Args>
	static Node make(const Args&... args);

	//Workaround to accept syntax Node::make<FunctionCall>("f", {...});
	template<class T, class U>
	static Node make(const U& arg, std::initializer_list<Node> initializerList);

	template<class T>
	bool is() const;

	template<class T>
	bool is(const T& test) const;

	bool isNumeric() const; //isReal() || isRational()
	bool isNumeric(const math::Real& test);
	math::Real getNumeric() const; //returns Real when isNumeric() is true

	template<class T>
	T& get();

	template<class T>
	const T& get() const;

	bool operator==(const Node& other) const;
	bool operator<(const Node& other) const;

	//string representation of an Node
	std::string toString() const;

	//Totally arbitrary. default constructed Node should never be used
	Node() : storage(Identifier("???")) {}

	template<class Visitor>
	friend typename std::remove_reference<Visitor>::type::result_type
	applyVisitor(const Node& node, Visitor&& visitor);

	template<class Visitor>
	friend typename std::remove_reference<Visitor>::type::result_type
	applyVisitor(const Node& lhs, const Node& rhs, Visitor&& visitor);

private:
	typedef boost::variant<math::Real, math::Rational, FunctionCall, String, Identifier> Storage;
	Storage storage;

	Node(const Storage& storage) : storage(storage) {}
};

std::ostream& operator<<(std::ostream& os, const Node& node);

template<class Visitor>
typename std::remove_reference<Visitor>::type::result_type
applyVisitor(const Node& node, Visitor&& visitor) {
	return boost::apply_visitor(
			std::forward<Visitor>(visitor),
			node.storage);
}

template<class Visitor>
typename std::remove_reference<Visitor>::type::result_type
applyVisitor(const Node& lhs, const Node& rhs, Visitor&& visitor) {
	return boost::apply_visitor(
			std::forward<Visitor>(visitor),
			lhs.storage,
			rhs.storage);
}

//Template implementation:
template<class T, class... Args>
Node Node::make(const Args&... args) {
	return Node{T(args...)};
}


template<class T, class U>
Node Node::make(const U& arg, std::initializer_list<Node> initializerList) {
	return Node{T(arg, initializerList)};
}

template<class T>
bool Node::is() const {
	return boost::get<T>(&storage) != nullptr;
}

template<class T>
bool Node::is(const T& test) const {
	return is<T>() && get<T>() == test;
}

template<class T>
T& Node::get() {
	assert( is<T>() );
	return boost::get<T>(storage);
}

template<class T>
const T& Node::get() const {
	assert( is<T>() );
	return boost::get<T>(storage);
}

}} //namespace tungsten::ast

#endif /* AST_NODE_HPP_ */
