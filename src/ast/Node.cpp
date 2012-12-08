
#include "Node.hpp"

#include <cassert>
#include <sstream>

#include "util/rangeToString.hpp"

namespace tungsten { namespace ast {

bool Node::isReal() const { return type_ == Type::Real; }
bool Node::isRational() const { return type_ == Type::Rational; }
bool Node::isFunction() const { return type_ == Type::Function; }
bool Node::isString() const { return type_ == Type::String; }
bool Node::isIdentifier() const { return type_ == Type::Identifier; }

Node::Type Node::type() const {
	return type_;
}

const math::Real& Node::getReal() const {
	assert( type_ == Type::Real );
	return boost::get<math::Real>(storage);
}

const math::Rational& Node::getRational() const {
	assert( type_ == Type::Rational );
	return boost::get<math::Rational>(storage);
}

const Function& Node::getFunction() const {
	assert( type_ == Type::Function );
	return boost::get<Function>(storage);
}

const String& Node::getString() const {
	assert( type_ == Type::String );
	return boost::get<String>(storage);
}

const Identifier& Node::getIdentifier() const {
	assert( type_ == Type::Identifier );
	return boost::get<Identifier>(storage);
}

const Node& Node::operator[](unsigned index) const {
	assert( type_ == Type::Function );

	const Function& function = getFunction();
	assert( function.operands.size() > index );

	return function.operands[index];
}

bool Node::operator==(const Node& other) const {
	bool result = storage == other.storage;
	if ( result ) {
		assert( type_ == other.type_ );
	}
	return result;
}

//TODO optimize this to use a single stream to stringize the whole tree
std::string Node::toString() const {
	struct ToStringVisitor : boost::static_visitor<> {

		ToStringVisitor(std::stringstream& ss) : sstream(ss) {}
		std::stringstream& sstream;

		void operator()(const math::Real& real) const { sstream << real; }
		void operator()(const math::Rational& rational) const { sstream << rational; }
		void operator()(const String& string) const { sstream << '"' << string << '"'; } //TODO escape chars
		void operator()(const Identifier& identifier) const { sstream << identifier; }

		void operator()(const Function& function) const {
			sstream << function.name << '[';
			util::rangeToStream(sstream, function.operands, [](const Node& node) { return node.toString(); }, ", " );
			sstream << ']';
		}

	};

	std::stringstream ss;

	applyVisitor( ToStringVisitor{ss} );

	return ss.str();

}

std::ostream& operator<<(std::ostream& os, const Node& node) {
	os << node.toString();
	return os;
}

}} //namespace tungsten::ast
