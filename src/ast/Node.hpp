
#ifndef AST_NODE_HPP_
#define AST_NODE_HPP_

#include <cassert>
#include <initializer_list>

#include <boost/variant.hpp>
#include <boost/operators.hpp>

#include "NodeTypes.hpp"

namespace tungsten { namespace ast {


//Immutable (so far)
class Node : boost::equality_comparable<Node> {
public:

	enum class Type { Real, Rational, Function, String, Identifier };

	//TODO Make these use perfect forwarding, this requires partially template specializing constructors
	template<class... Ts> static Node makeReal(const Ts&... args);
	template<class... Ts> static Node makeRational(const Ts&... args);
	template<class... Ts> static Node makeFunction(const Ts&... args);
	static Node makeFunction(const FunctionName& name, std::initializer_list<Operands::value_type> init_list);
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
	const Function& getFunction() const;
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

	typedef boost::variant<math::Real, math::Rational, Function, String, Identifier> Storage;

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
Node Node::makeFunction(const Ts&... args) {
	Node node;
	node.type_ = Type::Function;
	node.storage = Function(args...);
	return node;
}

inline
Node Node::makeFunction(const FunctionName& name, std::initializer_list<Operands::value_type> init_list) {
	Node node;
	node.type_ = Type::Function;
	node.storage = Function(name, Operands(init_list));
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
