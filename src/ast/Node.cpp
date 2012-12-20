
#include "Node.hpp"

#include <cassert>
#include <sstream>

#include "util/rangeToString.hpp"

namespace tungsten { namespace ast {

bool Node::isReal() const { return type_ == Type::Real; }
bool Node::isRational() const { return type_ == Type::Rational; }
bool Node::isFunctionCall() const { return type_ == Type::FunctionCall; }
bool Node::isString() const { return type_ == Type::String; }
bool Node::isIdentifier() const { return type_ == Type::Identifier; }

Node::Type Node::type() const {
	return type_;
}

math::Real& Node::getReal() {
	assert( type_ == Type::Real );
	return boost::get<math::Real>(storage);
}

const math::Real& Node::getReal() const {
	assert( type_ == Type::Real );
	return boost::get<math::Real>(storage);
}

math::Rational& Node::getRational() {
	assert( type_ == Type::Rational );
	return boost::get<math::Rational>(storage);
}

const math::Rational& Node::getRational() const {
	assert( type_ == Type::Rational );
	return boost::get<math::Rational>(storage);
}

FunctionCall& Node::getFunctionCall() {
	assert( type_ == Type::FunctionCall );
	return boost::get<FunctionCall>(storage);
}

const FunctionCall& Node::getFunctionCall() const {
	assert( type_ == Type::FunctionCall );
	return boost::get<FunctionCall>(storage);
}

String& Node::getString() {
	assert( type_ == Type::String );
	return boost::get<String>(storage);
}


const String& Node::getString() const {
	assert( type_ == Type::String );
	return boost::get<String>(storage);
}

Identifier& Node::getIdentifier() {
	assert( type_ == Type::Identifier );
	return boost::get<Identifier>(storage);
}

const Identifier& Node::getIdentifier() const {
	assert( type_ == Type::Identifier );
	return boost::get<Identifier>(storage);
}

bool Node::operator==(const Node& other) const {
	bool result = storage == other.storage;
	if ( result ) {
		assert( type_ == other.type_ );
	}
	return result;
}

bool Node::operator<(const Node& other) const {
	return false; //TODO
}

//TODO optimize this to use a single stream to stringize the whole tree
std::string Node::toString() const {

	struct ToStringVisitor : boost::static_visitor<std::string> {
		template<class T>
		std::string operator()(const T& t) const { return t.toString(); }
	};

	return applyVisitor( ToStringVisitor{} );

}

std::ostream& operator<<(std::ostream& os, const Node& node) {
	os << node.toString();
	return os;
}

}} //namespace tungsten::ast
