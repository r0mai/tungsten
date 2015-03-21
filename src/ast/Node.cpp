
#include "Node.hpp"

#include <cassert>
#include <sstream>
#include <algorithm>

#include "io/NodeToInputForm.hpp"
#include "eval/Identifiers.hpp"

namespace tungsten { namespace ast {

void Node::detach() {
	if( storagePtr && !storagePtr.unique() ) {
		storagePtr = std::make_shared<Storage>( *storagePtr );
	}
}

Node::Node(const StoragePtr& storagePtr) : storagePtr(storagePtr) {
	assert(!is<math::Real>() || boost::math::isfinite(get<math::Real>()));
}

Node::Node(const Node& other) : storagePtr(other.storagePtr) {}

Node& Node::operator=(const Node& other) {
	storagePtr = other.storagePtr;
	return *this;
}

bool Node::isFunctionCall(const Identifier& head) const {
	return is<FunctionCall>() &&
			get<FunctionCall>().getFunction().is<Identifier>() &&
			get<FunctionCall>().getFunction().get<Identifier>() == head;
}

bool Node::isFunctionCall(const Node& head) const {
	return is<FunctionCall>() &&
			get<FunctionCall>().getFunction() == head;
}

bool Node::isNumeric() const {
	return is<math::Real>() || is<math::Rational>();
}

bool Node::isNumeric(const math::Real& test) {
	return isNumeric() && getNumeric() == test;
}

bool Node::isInteger() const {
	return is<math::Rational>() && math::isInteger(get<math::Rational>());
}

math::Integer Node::getInteger() const {
	assert( isInteger() );
	return math::asInteger(get<math::Rational>());
}

math::Real Node::getNumeric() const {
	assert( isNumeric() );
	if ( is<math::Real>() ) {
		return get<math::Real>();
	}
	return get<math::Rational>();
}

bool Node::operator==(const Node& other) const {
	return *storagePtr == *other.storagePtr;
}

//These are used by operator<
template<class T> struct NodeTypeToInt;

template<> struct NodeTypeToInt<math::Rational> {
	static const int value = 1;
};
template<> struct NodeTypeToInt<math::Real> {
	static const int value = 2;
};
template<> struct NodeTypeToInt<math::ComplexReal> {
	static const int value = 3;
};
template<> struct NodeTypeToInt<math::ComplexRational> {
	static const int value = 4;
};
template<> struct NodeTypeToInt<String> {
	static const int value = 5;
};
template<> struct NodeTypeToInt<Identifier> {
	static const int value = 6;
};
template<> struct NodeTypeToInt<FunctionCall> {
	static const int value = 7;
};


struct CompareLessVisitor : boost::static_visitor<bool> {

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
	return applyVisitor( *this, other, CompareLessVisitor{} );
}

struct ToStringVisitor : boost::static_visitor<std::string> {
	template<class T>
	std::string operator()(const T& t) const { return t.toString(); }

	std::string operator()(const math::Rational& rational) const { return math::toString(rational); }
	std::string operator()(const math::Real& real) const { return math::toString(real); }
};

std::string Node::toString() const {
	return io::NodeToInputForm( *this );
//	return applyVisitor( *this, ToStringVisitor{} );
}

std::ostream& operator<<(std::ostream& os, const Node& node) {
	os << node.toString();
	return os;
}

struct GetByteCountVisitor : boost::static_visitor<std::size_t> {
	template<class T>
	std::size_t operator()(const T& t) const {
		return t.getByteCount();
   	}
	std::size_t operator()(const math::Rational& rational) const { return math::getByteCount(rational); }
	std::size_t operator()(const math::Real& real) const { return math::getByteCount(real); }
	std::size_t operator()(const math::ComplexRational& rational) const { return math::getByteCount(rational); }
	std::size_t operator()(const math::ComplexReal& real) const { return math::getByteCount(real); }
};

std::size_t Node::getByteCount() const {
	return applyVisitor(*this, GetByteCountVisitor{});
}

}} //namespace tungsten::ast
