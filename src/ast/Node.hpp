
#ifndef AST_NODE_HPP_
#define AST_NODE_HPP_

#include <cassert>
#include <initializer_list>
#include <memory>

#include <boost/variant.hpp>
#include <boost/operators.hpp>

#include "NodeFwd.hpp"
#include "FunctionCall.hpp"
#include "NodeTypes.hpp"
#include "util/make_unique.hpp"

namespace tungsten { namespace ast {


//Immutable (so far)
class Node : boost::equality_comparable<Node> {
public:

	enum class Type { Real, Rational, FunctionCall, String, Identifier };

	//TODO Make these use perfect forwarding, this requires partially template specializing constructors
	template<class... Ts> static Node makeReal(const Ts&... args);
	template<class... Ts> static Node makeRational(const Ts&... args);
	template<class... Ts> static Node makeFunctionCall(const Ts&... args);
	static Node makeFunctionCall(const Identifier& name, std::initializer_list<Operands::value_type> init_list);
	static Node makeFunctionCall(const Node& function, std::initializer_list<Operands::value_type> init_list);
	template<class... Ts> static Node makeString(const Ts&... args);
	template<class... Ts> static Node makeIdentifier(const Ts&... args);

	bool isReal() const;
	bool isRational() const;
	bool isFunction() const;
	bool isString() const;
	bool isIdentifier() const;

	Type type() const;

	const math::Real& getReal() const;
	const math::Rational& getRational() const;
	const FunctionCall& getFunctionCall() const;
	const String& getString() const;
	const Identifier& getIdentifier() const;

	const Node& operator[](unsigned index) const;

	bool operator==(const Node& other) const;

	//string representation of an Node
	std::string toString() const;

	template<class Visitor>
	typename Visitor::result_type applyVisitor(Visitor&& visitor) const;

	//Totally arbitrary. default constructed Node should never be used
	Node() : type_(Type::Rational) {}

private:

	Type type_;

	typedef boost::variant<math::Real, math::Rational, FunctionCall, String, Identifier> Storage;

	Storage storage;


};

std::ostream& operator<<(std::ostream& os, const Node& node);

//Template impl
template<class... Ts>
Node Node::makeReal(const Ts&... args) {
	Node node;
	node.type_ = Type::Real;
	node.storage = math::Real(args...);
	return node;
}

template<class... Ts>
Node Node::makeRational(const Ts&... args) {
	Node node;
	node.type_ = Type::Rational;
	node.storage = math::Rational(args...);
	return node;
}

template<class... Ts>
Node Node::makeFunctionCall(const Ts&... args) {
	Node node;
	node.type_ = Type::FunctionCall;
	node.storage = FunctionCall(args...);
	return node;
}

inline
Node Node::makeFunctionCall(const Identifier& name, std::initializer_list<Operands::value_type> init_list) {
	Node node;
	node.type_ = Type::FunctionCall;
	node.storage = FunctionCall(name, Operands(init_list));
	return node;

}

inline
Node Node::makeFunctionCall(const Node& function, std::initializer_list<Operands::value_type> init_list) {
	Node node;
	node.type_ = Type::FunctionCall;
	node.storage = FunctionCall(function, Operands(init_list));
	return node;
}

template<class... Ts>
Node Node::makeString(const Ts&... args) {
	Node node;
	node.type_ = Type::String;
	node.storage = String(args...);
	return node;
}

template<class... Ts>
Node Node::makeIdentifier(const Ts&... args) {
	Node node;
	node.type_ = Type::Identifier;
	node.storage = Identifier(args...);
	return node;
}

template<class Visitor>
typename Visitor::result_type Node::applyVisitor(Visitor&& visitor) const {
	return boost::apply_visitor(std::forward<Visitor>(visitor), storage);
}

}} //namespace tungsten::ast

#endif /* AST_NODE_HPP_ */
