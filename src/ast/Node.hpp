
#ifndef AST_NODE_HPP_
#define AST_NODE_HPP_

#include <cassert>
#include <initializer_list>
#include <memory>
#include <type_traits>
#include <memory>

#include <boost/variant.hpp>

#include "NodeFwd.hpp"
#include "FunctionCall.hpp"
#include "NodeTypes.hpp"
#include "util/make_unique.hpp"

namespace tungsten { namespace ast {

class Node {
public:

	Node(const Node& other);
	Node& operator=(const Node& other);

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

	//These returns true, if this is a FunctionCall, and it's function is 'head'
	//Doesn't do anything with the operands
	bool isFunctionCall(const Identifier& head) const;
	bool isFunctionCall(const Node& head) const;

	bool isNumeric() const; //isReal() || isRational()
	bool isNumeric(const math::Real& test);
	math::Real getNumeric() const; //returns Real when isNumeric() is true

	//Using this potentially causes a copy. This is why it has a differnt name
	template<class T>
	T& getM();

	template<class T>
	const T& get() const;

	bool operator==(const Node& other) const;
	inline bool operator!=(const Node& other) const { return !(*this == other); }
	//Fast operator< to be used in sets, maps
	//For correct comparsion operator, which correctly implements OrderedQ[] see eval/orderNode.hpp
	bool operator<(const Node& other) const;
	inline bool operator>(const Node& other) const { return other < *this; }
	inline bool operator<=(const Node& other) const { return !(other < *this); }
	inline bool operator>=(const Node& other) const { return !(*this < other); }

	//string representation of an Node
	std::string toString() const;

	//Totally arbitrary. default constructed Node should never be used
	Node() : storagePtr(nullptr) {}

	template<class Visitor>
	friend typename std::remove_reference<Visitor>::type::result_type
	applyVisitor(const Node& node, Visitor&& visitor);

	template<class Visitor>
	friend typename std::remove_reference<Visitor>::type::result_type
	applyVisitor(const Node& lhs, const Node& rhs, Visitor&& visitor);

private:
	typedef boost::variant<math::Real, math::Rational, FunctionCall, String, Identifier> Storage;
	typedef std::shared_ptr<Storage> StoragePtr;
	StoragePtr storagePtr;

	void detach();

	Node(const StoragePtr& storagePtr);
};

std::ostream& operator<<(std::ostream& os, const Node& node);

template<class Visitor>
typename std::remove_reference<Visitor>::type::result_type
applyVisitor(const Node& node, Visitor&& visitor) {
	return boost::apply_visitor(
			std::forward<Visitor>(visitor),
			*node.storagePtr);
}

template<class Visitor>
typename std::remove_reference<Visitor>::type::result_type
applyVisitor(const Node& lhs, const Node& rhs, Visitor&& visitor) {
	return boost::apply_visitor(
			std::forward<Visitor>(visitor),
			*lhs.storagePtr,
			*rhs.storagePtr);
}

//Template implementation:
template<class T, class... Args>
Node Node::make(const Args&... args) {
    static_assert( 
        std::is_same<T, math::Real>::value ||
        std::is_same<T, math::Rational>::value ||
        std::is_same<T, ast::FunctionCall>::value ||
        std::is_same<T, ast::String>::value ||
        std::is_same<T, ast::Identifier>::value, "invalid Node type" );
	return Node{StoragePtr{new Storage(T(args...))}};
}

template<class T, class U>
Node Node::make(const U& arg, std::initializer_list<Node> initializerList) {
    static_assert( 
        std::is_same<T, ast::FunctionCall>::value, "init list version can only be called for FunctionCall" );
	return Node{StoragePtr{new Storage(T(arg, initializerList))}};
}

template<class T>
bool Node::is() const {
    static_assert( 
        std::is_same<T, math::Real>::value ||
        std::is_same<T, math::Rational>::value ||
        std::is_same<T, ast::FunctionCall>::value ||
        std::is_same<T, ast::String>::value ||
        std::is_same<T, ast::Identifier>::value, "invalid Node type" );
	return boost::get<T>(&*storagePtr) != nullptr;
}

template<class T>
bool Node::is(const T& test) const {
    static_assert( 
        std::is_same<T, math::Real>::value ||
        std::is_same<T, math::Rational>::value ||
        std::is_same<T, ast::FunctionCall>::value ||
        std::is_same<T, ast::String>::value ||
        std::is_same<T, ast::Identifier>::value, "invalid Node type" );
	return is<T>() && get<T>() == test;
}

template<class T>
T& Node::getM() {
    static_assert( 
        std::is_same<T, math::Real>::value ||
        std::is_same<T, math::Rational>::value ||
        std::is_same<T, ast::FunctionCall>::value ||
        std::is_same<T, ast::String>::value ||
        std::is_same<T, ast::Identifier>::value, "invalid Node type" );
	assert( is<T>() );
	detach();
	return boost::get<T>(*storagePtr);
}

template<class T>
const T& Node::get() const {
    static_assert( 
        std::is_same<T, math::Real>::value ||
        std::is_same<T, math::Rational>::value ||
        std::is_same<T, ast::FunctionCall>::value ||
        std::is_same<T, ast::String>::value ||
        std::is_same<T, ast::Identifier>::value, "invalid Node type" );
	assert( is<T>() );
	return boost::get<T>(*storagePtr);
}

}} //namespace tungsten::ast

#endif /* AST_NODE_HPP_ */
