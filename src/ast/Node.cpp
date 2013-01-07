
#include "Node.hpp"

#include <cassert>
#include <sstream>

namespace tungsten { namespace ast {

bool Node::isReal() const { return type_ == Type::Real; }
bool Node::isRational() const { return type_ == Type::Rational; }
bool Node::isFunctionCall() const { return type_ == Type::FunctionCall; }
bool Node::isString() const { return type_ == Type::String; }
bool Node::isIdentifier() const { return type_ == Type::Identifier; }

bool Node::isNumeric() const { return type_ == Type::Real || type_ == Type::Rational; }

math::Real Node::getNumeric() const {
	assert( isNumeric() );
	if ( type_ == Type::Real ) {
		return getReal();
	}
	return getRational();
}

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

//These are used by operator<
template<class T> struct NodeTypeToInt;

template<> struct NodeTypeToInt<math::Rational> {
	static const int value = 1;
};
template<> struct NodeTypeToInt<math::Real> {
	static const int value = 2;
};
template<> struct NodeTypeToInt<String> {
	static const int value = 3;
};
template<> struct NodeTypeToInt<Identifier> {
	static const int value = 4;
};
template<> struct NodeTypeToInt<FunctionCall> {
	static const int value = 5;
};


struct CompareVisitor : boost::static_visitor<bool> {

	template<class T>
	bool operator()(const T& lhs, const T& rhs) const {
		return lhs < rhs;
	}

	template<class T, class U>
	bool operator()(const T& /*lhs*/, const U& /*rhs*/) const {
		return NodeTypeToInt<T>::value < NodeTypeToInt<U>::value;
	}

	bool operator()(const math::Rational& lhs, const math::Real& rhs) const {
		if ( lhs != rhs ) {
			return lhs < rhs;
		}
		return operator()<math::Rational, math::Real>(lhs, rhs);
	}

	bool operator()(const math::Real& lhs, const math::Rational& rhs) const {
		if ( lhs != rhs ) {
			return lhs < rhs;
		}
		return operator()<math::Real, math::Rational>(lhs, rhs);
	}
	
	bool operator()(const FunctionCall& lhs, const Identifier& rhs) const {
		/** Ordering relation
		
		When Pow[x, 3] encounters a regular x, place x in front.
		**/		
		return false;
	}
	
	bool operator()(const Identifier& lhs, const FunctionCall& rhs) const {
		/** Ordering relation
		
		When regular x encounters a Pow[x, 3], leave x in front.
		**/		
		return true;
	}

};

bool Node::operator<(const Node& other) const {
	return applyVisitor( *this, other, CompareVisitor{} );
}



struct ToStringVisitor : boost::static_visitor<std::string> {
	template<class T>
	std::string operator()(const T& t) const { return t.toString(); }
};

std::string Node::toString() const {
	return applyVisitor( *this, ToStringVisitor{} );
}

std::ostream& operator<<(std::ostream& os, const Node& node) {
	os << node.toString();
	return os;
}

}} //namespace tungsten::ast
