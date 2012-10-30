
#ifndef ASTNODE_HPP_
#define ASTNODE_HPP_

#include "AstNodeTypes.hpp"

#include <utility>

namespace tungsten {

class AstNode {
public:

	enum class Type { Real, Rational, Function, String, Identifier };

	//TODO Make these use perfect forwarding, this requires partially template specializing constructors
	template<class... Ts> static AstNode makeReal(const Ts&... args);
	template<class... Ts> static AstNode makeRational(const Ts&... args);
	template<class... Ts> static AstNode makeFunction(const Ts&... args);
	template<class... Ts> static AstNode makeString(const Ts&... args);
	template<class... Ts> static AstNode makeIdentifier(const Ts&... args);

	bool isReal() const;
	bool isRational() const;
	bool isFunction() const;
	bool isString() const;
	bool isIdentifier() const;

	Type type() const;

	const Real& getReal() const;
	const Rational& getRational() const;
	const Function& getFunction() const;
	const String& getString() const;
	const Identifier& getIdentifier() const;

	//Returns nth operand
	AstNode& operator[](unsigned index);
	const AstNode& operator[](unsigned index) const;

	AstNode() : type_(Type::Rational) {}

private:

	Type type_;

	//TODO put these into union or boost::variant to save space
	Real real;
	Rational rational;
	Function function;
	String string;
	Identifier identifier;

};

//Template impl
template<class... Ts> AstNode AstNode::makeReal(const Ts&... args) {
	AstNode node;
	node.type_ = Type::Real;
	node.real = Real(args...);
	return node;
}

template<class... Ts> AstNode AstNode::makeRational(const Ts&... args) {
	AstNode node;
	node.type_ = Type::Rational;
	node.rational = Rational(args...);
	return node;
}

template<class... Ts> AstNode AstNode::makeFunction(const Ts&... args) {
	AstNode node;
	node.type_ = Type::Function;
	node.function = Function(args...);
	return node;
}

template<class... Ts> AstNode AstNode::makeString(const Ts&... args) {
	AstNode node;
	node.type_ = Type::String;
	node.string = String(args...);
	return node;
}

template<class... Ts> AstNode AstNode::makeIdentifier(const Ts&... args) {
	AstNode node;
	node.type_ = Type::Identifier;
	node.identifier = Identifier(args...);
	return node;
}


} //namespace tungsten

#endif /* ASTNODE_HPP_ */
