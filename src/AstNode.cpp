
#include "AstNode.hpp"

#include <cassert>
#include <sstream>

#include "AstNodeVisitor.hpp"
#include "rangeToString.hpp"

namespace tungsten {

bool AstNode::isReal() const { return type_ == Type::Real; }
bool AstNode::isRational() const { return type_ == Type::Rational; }
bool AstNode::isFunction() const { return type_ == Type::Function; }
bool AstNode::isString() const { return type_ == Type::String; }
bool AstNode::isIdentifier() const { return type_ == Type::Identifier; }

AstNode::Type AstNode::type() const {
	return type_;
}

const Real& AstNode::getReal() const {
	assert( type_ == Type::Real );
	return boost::get<Real>(storage);
}

const Rational& AstNode::getRational() const {
	assert( type_ == Type::Rational );
	return boost::get<Rational>(storage);
}

const Function& AstNode::getFunction() const {
	assert( type_ == Type::Function );
	return boost::get<Function>(storage);
}

const String& AstNode::getString() const {
	assert( type_ == Type::String );
	return boost::get<String>(storage);
}

const Identifier& AstNode::getIdentifier() const {
	assert( type_ == Type::Identifier );
	return boost::get<Identifier>(storage);
}

const AstNode& AstNode::operator[](unsigned index) const {
	assert( type_ == Type::Function );

	const Function& function = getFunction();
	assert( function.operands.size() > index );

	return function.operands[index];
}

bool AstNode::operator==(const AstNode& other) const {
	bool result = storage == other.storage;
	if ( result ) {
		assert( type_ == other.type_ );
	}
	return result;
}

//TODO optimize this to use a single stream to stringize the whole tree
std::string AstNode::toString() const {
	struct ToStringVisitor : boost::static_visitor<> {

		ToStringVisitor(std::stringstream& ss) : sstream(ss) {}
		std::stringstream& sstream;

		void operator()(const Real& real) const { sstream << real; }
		void operator()(const Rational& rational) const { sstream << rational; }
		void operator()(const String& string) const { sstream << '"' << string << '"'; } //TODO escape chars
		void operator()(const Identifier& identifier) const { sstream << identifier; }

		void operator()(const Function& function) const {
			sstream << function.name << '[';
			rangeToStream(sstream, function.operands, [](const AstNode& node) { return node.toString(); }, ", " );
			sstream << ']';
		}

	};

	std::stringstream ss;

	applyVisitor( ToStringVisitor{ss} );

	return ss.str();

}

std::ostream& operator<<(std::ostream& os, const AstNode& node) {
	os << node.toString();
	return os;
}

} //namespace tungsten
