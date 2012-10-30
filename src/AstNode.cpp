
#include "AstNode.hpp"

#include <cassert>
#include <sstream>

#include "AstNodeVisitor.hpp"
#include "rangeToString.hpp"

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


AstNode& AstNode::operator[](unsigned index) {
	assert( type_ == Type::Function );
	assert( function.operands.size() > index );

	return function.operands[index];
}

const AstNode& AstNode::operator[](unsigned index) const {
	assert( type_ == Type::Function );
	assert( function.operands.size() > index );

	return function.operands[index];
}

//TODO optimize this to use a single stream to stringize the whole tree
std::string AstNode::toString() const {
	struct ToStringVisitor : AstNodeVisitor<> {

		ToStringVisitor(std::stringstream& ss) : sstream(ss) {}
		std::stringstream& sstream;

		void operator()(const Real& real) { sstream << real; }
		void operator()(const Rational& rational) { sstream << rational; }
		void operator()(const String& string) { sstream << '"' << string << '"'; } //TODO escape chars
		void operator()(const Identifier& identifier) { sstream << identifier; }

		void operator()(const Function& function) {
			sstream << function.name << '[';
			rangeToStream(sstream, function.operands, [](const AstNode& node) { return node.toString(); }, ", " );
			sstream << ']';
		}

	};

	std::stringstream ss;

	applyVisitor( ToStringVisitor{ss} );

	return ss.str();

}

} //namespace tungsten
