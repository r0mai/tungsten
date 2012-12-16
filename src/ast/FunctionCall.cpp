
#include "FunctionCall.hpp"
#include "Node.hpp"

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
	std::swap(*this, other);
	return *this;
}

bool FunctionCall::operator==(const FunctionCall& other) const {
	return *function == *other.function && operands == other.operands;
}

const Node& FunctionCall::getFunction() const {
	return *function;
}

const Operands& FunctionCall::getOperands() const {
	return operands;
}

}} //namespace tungsten::ast

