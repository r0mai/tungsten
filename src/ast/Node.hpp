
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
	bool isFunctionCall() const;
	bool isString() const;
	bool isIdentifier() const;

	bool isNumeric() const; //isReal() || isRational()
	math::Real getNumeric() const; //returns Real when isNumeric() is true

	Type type() const;

	math::Real& getReal();
	const math::Real& getReal() const;

	math::Rational& getRational();
	const math::Rational& getRational() const;

	FunctionCall& getFunctionCall();
	const FunctionCall& getFunctionCall() const;

	String& getString();
	const String& getString() const;

	Identifier& getIdentifier();
	const Identifier& getIdentifier() const;

	bool operator==(const Node& other) const;
	bool operator<(const Node& other) const;

	//string representation of an Node
	std::string toString() const;

	//Totally arbitrary. default constructed Node should never be used
	Node() : type_(Type::Identifier), storage(Identifier("???")) {}

	template<class Visitor>
	friend typename std::remove_reference<Visitor>::type::result_type
	applyVisitor(const Node& node, Visitor&& visitor);

	template<class Visitor>
	friend typename std::remove_reference<Visitor>::type::result_type
	applyVisitor(const Node& lhs, const Node& rhs, Visitor&& visitor);

private:

	Type type_;

	typedef boost::variant<math::Real, math::Rational, FunctionCall, String, Identifier> Storage;

	Storage storage;


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

}} //namespace tungsten::ast

#endif /* AST_NODE_HPP_ */
