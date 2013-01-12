
#include <sstream>

#include <boost/bind/mem_fn.hpp>
#include <boost/algorithm/string/join.hpp>
#include <boost/range/adaptor/transformed.hpp>
#include <boost/range/algorithm/lexicographical_compare.hpp>

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

FunctionCall::FunctionCall(const Identifier& name, std::initializer_list<Node> operands) :
		function( new Node(Node::makeIdentifier(name)) ), operands(operands) {}

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
/* Default behaviour by r0
	if ( *function != *rhs.function ) {
		return *function < *rhs.function;
	}

	return boost::lexicographical_compare( operands, rhs.operands );
*/ // End default behaviour by r0
// Start new behaviour by ph
/**
Canonical-like ordering

Special ordering relation to mimic WM like output (for eg. Polynomials)
Please see http://reference.wolfram.com/mathematica/ref/Sort.html
for more details on how/why. This operator deals with case 4-5:
	(...)
	4: Sort usually orders expressions by putting shorter ones first, and then
	comparing parts in a depth-first manner. 
	5: Sort treats powers and products specially, ordering them to correspond 
	to terms in a polynomial.
	(...)
**/


if(this->getFunction().getIdentifier() == rhs.getFunction().getIdentifier()) {
	// if functions have same name, one with less parameters is smaller (4)
	if(this->getOperands().size() < rhs.getOperands().size()){ return true; }
	if(this->getOperands().size() > rhs.getOperands().size()){ return false; }
	
	return boost::lexicographical_compare(this->getOperands(), rhs.getOperands());
	// depth based lexicographical compare.
	
}
// Functions are of different name (and different objects) now.
// Handle the special cases now. Hopefully no more will arise

if(this->getFunction().getIdentifier() == "Power") {
// I hope that's what it's called. :S
	if(rhs.getFunction().getIdentifier() == "Times") {
	// left pow, right times example: (x^3) * 5. Verdict: Swap.
		return false;
	}
}

if(this->getFunction().getIdentifier() == "Times") {
	if(rhs.getFunction().getIdentifier() == "Power") {
	// right pow, left times example: 5 * (x^3) . Verdict: Do not swap.
		return true;
	}
}

return this->getOperands().size() <= rhs.getOperands().size(); // as above.
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
	ss << boost::join( operands | boost::adaptors::transformed( boost::mem_fn(&Node::toString) ), ", " );
	ss << ']';
	return ss.str();
}

std::ostream& operator<<(std::ostream& os, const FunctionCall& fc) {
	os << fc.toString();
	return os;
}

}} //namespace tungsten::ast


