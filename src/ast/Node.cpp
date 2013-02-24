
#include "Node.hpp"

#include <cassert>
#include <sstream>
#include <algorithm>

#include "io/NodeToInputForm.hpp"
#include "eval/Identifiers.hpp"

namespace tungsten { namespace ast {

bool Node::isFunctionCall(const Identifier& head) {
	return is<FunctionCall>() &&
			get<FunctionCall>().getFunction().is<Identifier>() &&
			get<FunctionCall>().getFunction().get<Identifier>() == head;
}

bool Node::isFunctionCall(const Node& head) {
	return is<FunctionCall>() &&
			get<FunctionCall>().getFunction() == head;
}

bool Node::isNumeric() const {
	return is<math::Real>() || is<math::Rational>();
}

bool Node::isNumeric(const math::Real& test) {
	return isNumeric() && getNumeric() == test;
}

math::Real Node::getNumeric() const {
	assert( isNumeric() );
	if ( is<math::Real>() ) {
		return get<math::Real>();
	}
	return get<math::Rational>();
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

	std::string operator()(const math::Rational& rational) const { return math::toString(rational); }
	std::string operator()(const math::Real& real) const { return math::toString(real); }
};

std::string Node::toString() const {
	return io::NodeToInputForm( *this );
	return applyVisitor( *this, ToStringVisitor{} );
}

std::ostream& operator<<(std::ostream& os, const Node& node) {
	os << node.toString();
	return os;
}

}} //namespace tungsten::ast
