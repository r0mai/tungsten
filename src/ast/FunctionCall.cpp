
#include <sstream>

#include "FunctionCall.hpp"
#include "Node.hpp"

#include "util/rangeToString.hpp"

namespace tungsten { namespace ast {

FunctionCall::FunctionCall() {}

FunctionCall::FunctionCall(const FunctionCall& other) :
		function( new Node(*other.function) ), operands(other.operands) {}

FunctionCall::FunctionCall(const Identifier& name) :
		function( new Node(Node::makeIdentifier(name)) ) {}

FunctionCall::FunctionCall(const Identifier& name, const Operands& operands) :
		function( new Node(Node::makeIdentifier(name)) ), operands(operands) {}

FunctionCall::FunctionCall(const Node& function) :
		function( new Node(function) ) {}

FunctionCall::FunctionCall(const Node& function, const Operands& operands) :
		function( new Node(function) ), operands(operands) {}

FunctionCall& FunctionCall::operator=(FunctionCall other) {
	swap(*this, other);
	return *this;
}

bool FunctionCall::operator==(const FunctionCall& other) const {
	return *function == *other.function && operands == other.operands;
}

Node& FunctionCall::getFunction() {
	return *function;
}

const Node& FunctionCall::getFunction() const {
	return *function;
}

Operands& FunctionCall::getOperands() {
	return operands;
}

const Operands& FunctionCall::getOperands() const {
	return operands;
}

void swap(FunctionCall& fc1, FunctionCall& fc2) {
	std::swap( fc1.function, fc2.function );
	std::swap( fc1.operands, fc2.operands );
}

std::string FunctionCall::toString() const {
	std::stringstream ss;
	ss << function->toString() << '[';
	util::rangeToStream(ss, operands, [](const Node& node) { return node.toString(); }, ", " );
	ss << ']';
	return ss.str();
}

std::ostream& operator<<(std::ostream& os, const FunctionCall& fc) {
	os << fc.toString();
	return os;
}

}} //namespace tungsten::ast


