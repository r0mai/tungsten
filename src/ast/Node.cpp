
#include "Node.hpp"

#include <cassert>
#include <sstream>
#include <algorithm>

namespace tungsten { namespace ast {

bool Node::isReal() const { return is<math::Real>(); }
bool Node::isRational() const { return is<math::Rational>(); }
bool Node::isFunctionCall() const { return is<FunctionCall>(); }
bool Node::isString() const { return is<String>(); }
bool Node::isIdentifier() const { return is<Identifier>(); }

bool Node::isNumeric() const { return is<math::Real>() || is<math::Rational>(); }

math::Real Node::getNumeric() const {
	assert( isNumeric() );
	if ( is<math::Real>() ) {
		return getReal();
	}
	return getRational();
}

math::Real& Node::getReal() {
	assert( is<math::Real>() );
	return boost::get<math::Real>(storage);
}

const math::Real& Node::getReal() const {
	assert( is<math::Real>() );
	return boost::get<math::Real>(storage);
}

math::Rational& Node::getRational() {
	assert( is<math::Rational>() );
	return boost::get<math::Rational>(storage);
}

const math::Rational& Node::getRational() const {
	assert( is<math::Rational>() );
	return boost::get<math::Rational>(storage);
}

FunctionCall& Node::getFunctionCall() {
	assert( is<FunctionCall>() );
	return boost::get<FunctionCall>(storage);
}

const FunctionCall& Node::getFunctionCall() const {
	assert( is<FunctionCall>() );
	return boost::get<FunctionCall>(storage);
}

String& Node::getString() {
	assert( is<String>() );
	return boost::get<String>(storage);
}

const String& Node::getString() const {
	assert( is<String>() );
	return boost::get<String>(storage);
}

Identifier& Node::getIdentifier() {
	assert( is<Identifier>() );
	return boost::get<Identifier>(storage);
}

const Identifier& Node::getIdentifier() const {
	assert( is<Identifier>() );
	return boost::get<Identifier>(storage);
}

bool Node::operator==(const Node& other) const {
	return storage == other.storage;
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

struct LengthVisitor : boost::static_visitor<unsigned> {
	unsigned operator()(const math::Rational& /*r*/) const {
		return 1;
	}
	
	unsigned operator()(const math::Real& /*r*/) const {
		return 1;
	}
	
	unsigned operator()(const String& s) const {
		return s.length();
	}
	
	unsigned operator()(const Identifier& i) const {
		return i.length();
	}
	
	unsigned operator()(const FunctionCall& f) const {
		return 1+
		std::accumulate(f.getOperands().begin(), f.getOperands().end(), 
		0u, [](unsigned& u, const Node& n) 
		{return u+applyVisitor(n, LengthVisitor{});});
	}
	
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
