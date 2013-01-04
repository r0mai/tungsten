
#include "functions.hpp"

#include <iostream>

#include "eval/SessionEnvironment.hpp"

namespace tungsten { namespace eval { namespace builtin {

ast::Node Plus(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment) {
	if ( operands.size() == 0 ) {
		return ast::Node::makeRational(0);
	}

	if ( operands.size() == 1 ) {
		return operands[0];
	}

	return ast::Node::makeFunctionCall("Plus", operands);
}

}}} //namespace tungsten::eval::builtin

