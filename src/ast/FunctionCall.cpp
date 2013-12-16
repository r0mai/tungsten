
#include <sstream>

#include <boost/bind/mem_fn.hpp>
#include <boost/algorithm/string/join.hpp>
#include <boost/range/adaptor/transformed.hpp>
#include <boost/range/algorithm/lexicographical_compare.hpp>

#include "eval/Identifiers.hpp"
#include "FunctionCall.hpp"
#include "Node.hpp"

namespace tungsten { namespace ast {

namespace ids = eval::ids;

FunctionCall::FunctionCall() : function(nullptr) {}

FunctionCall::FunctionCall(const FunctionCall& other) :
		function( new Node(*other.function) ), operands(other.operands) {}

FunctionCall::FunctionCall(const Identifier& name) :
		function( new Node(Node::make<Identifier>(name)) ) {}

FunctionCall::FunctionCall(const Identifier& name, const Operands& operands) :
		function( new Node(Node::make<Identifier>(name)) ), operands(operands) {}

FunctionCall::FunctionCall(const Identifier& name, std::initializer_list<Node> operands) :
		function( new Node(Node::make<Identifier>(name)) ), operands(operands) {}

FunctionCall::FunctionCall(const Node& function) :
		function( new Node(function) ) {}

FunctionCall::FunctionCall(const Node& function, const Operands& operands) :
		function( new Node(function) ), operands(operands) {}

FunctionCall::FunctionCall(const Node& function, std::initializer_list<Node> operands) :
		function( new Node(function) ), operands(operands) {}

FunctionCall& FunctionCall::operator=(FunctionCall other) {
	swap(*this, other);
	return *this;
}

bool FunctionCall::operator==(const FunctionCall& other) const {
	return *function == *other.function && operands == other.operands;
}

bool FunctionCall::operator<(const FunctionCall& rhs) const {

	const ast::Node& lhsFunction = getFunction();
	const ast::Node& rhsFunction = rhs.getFunction();
	const ast::Operands& lhsOperands = getOperands();
	const ast::Operands& rhsOperands = rhs.getOperands();

	//default case
	if ( lhsFunction != rhsFunction ) {
		return lhsFunction < rhsFunction;
	}

	if ( lhsOperands.size() != rhsOperands.size() ) {
		return lhsOperands.size() < rhsOperands.size();
	}

	return std::lexicographical_compare( lhsOperands.begin(), lhsOperands.end(), rhsOperands.begin(), rhsOperands.end() );
}

Node& FunctionCall::getFunction() {
	assert( function );
	return *function;
}

const Node& FunctionCall::getFunction() const {
	assert( function );
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
	assert( function );

	std::stringstream ss;
	ss << function->toString() << '[';
	ss << boost::join( operands | boost::adaptors::transformed( boost::mem_fn(&Node::toString) ), ", " );
	ss << ']';
	return ss.str();
}

std::ostream& operator<<(std::ostream& os, const FunctionCall& fc) {
	os << fc.toString();
	return os;
}

}} //namespace tungsten::ast


