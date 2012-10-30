
#include "AstNode.hpp"

#include <cassert>

namespace tungsten {

bool AstNode::isReal() const {
	return type_ == Type::Real;
}

bool AstNode::isRational() const {
	return type_ == Type::Rational;
}

bool AstNode::isFunction() const {
	return type_ == Type::Function;
}

bool AstNode::isString() const {
	return type_ == Type::String;
}

bool AstNode::isIdentifier() const {
	return type_ == Type::Identifier;
}

AstNode::Type AstNode::type() const {
	return type_;
}

const Real& AstNode::getReal() const {
	assert( type_ == Type::Real );
	return real;
}

const Rational& AstNode::getRational() const {
	assert( type_ == Type::Rational );
	return rational;
}

const Function& AstNode::getFunction() const {
	assert( type_ == Type::Function );
	return function;
}

const String& AstNode::getString() const {
	assert( type_ == Type::String );
	return string;
}

const Identifier& AstNode::getIdentifier() const {
	assert( type_ == Type::Identifier );
	return identifier;
}


AstNode& AstNode::operator[](unsigned /*index*/) {
	return *this;
}

const AstNode& AstNode::operator[](unsigned /*index*/) const {
	return *this;
}

} //namespace tungsten
