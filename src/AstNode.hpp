
#ifndef ASTNODE_HPP_
#define ASTNODE_HPP_

#include <cassert>
#include <initializer_list>

#include <boost/variant.hpp>
#include <boost/operators.hpp>

#include "AstNodeTypes.hpp"

namespace tungsten {


//Immutable (so far)
class AstNode : boost::equality_comparable<AstNode> {
public:

	enum class Type { Real, Rational, Function, String, Identifier };

	//TODO Make these use perfect forwarding, this requires partially template specializing constructors
	template<class... Ts> static AstNode makeReal(const Ts&... args);
	template<class... Ts> static AstNode makeRational(const Ts&... args);
	template<class... Ts> static AstNode makeFunction(const Ts&... args);
	static AstNode makeFunction(const FunctionName& name, std::initializer_list<Operands::value_type> init_list);
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

	const AstNode& operator[](unsigned index) const;

	bool operator==(const AstNode& other) const;

	//string representation of an AstNode
	std::string toString() const;

	template<class Visitor>
	typename Visitor::result_type applyVisitor(Visitor&& visitor) const;

	//Totally arbitrary. default constructed AstNode should never be used
	AstNode() : type_(Type::Rational) {}

private:

	Type type_;

	typedef boost::variant<Real, Rational, Function, String, Identifier> Storage;

	Storage storage;


};

std::ostream& operator<<(std::ostream& os, const AstNode& node);

//Template impl
template<class... Ts>
AstNode AstNode::makeReal(const Ts&... args) {
	AstNode node;
	node.type_ = Type::Real;
	node.storage = Real(args...);
	return node;
}

template<class... Ts>
AstNode AstNode::makeRational(const Ts&... args) {
	AstNode node;
	node.type_ = Type::Rational;
	node.storage = Rational(args...);
	return node;
}

template<class... Ts>
AstNode AstNode::makeFunction(const Ts&... args) {
	AstNode node;
	node.type_ = Type::Function;
	node.storage = Function(args...);
	return node;
}

inline
AstNode AstNode::makeFunction(const FunctionName& name, std::initializer_list<Operands::value_type> init_list) {
	AstNode node;
	node.type_ = Type::Function;
	node.storage = Function(name, Operands(init_list));
	return node;

}

template<class... Ts>
AstNode AstNode::makeString(const Ts&... args) {
	AstNode node;
	node.type_ = Type::String;
	node.storage = String(args...);
	return node;
}

template<class... Ts>
AstNode AstNode::makeIdentifier(const Ts&... args) {
	AstNode node;
	node.type_ = Type::Identifier;
	node.storage = Identifier(args...);
	return node;
}

template<class Visitor>
typename Visitor::result_type AstNode::applyVisitor(Visitor&& visitor) const {
	return boost::apply_visitor(std::forward<Visitor>(visitor), storage);
}

} //namespace tungsten

#endif /* ASTNODE_HPP_ */
