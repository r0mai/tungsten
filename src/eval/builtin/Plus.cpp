
#include "functions.hpp"

#include <iostream>

#include "eval/flattenOperands.hpp"
#include "eval/SessionEnvironment.hpp"

namespace tungsten { namespace eval { namespace builtin {

ast::Node Plus(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment) {
	if ( operands.size() == 0 ) {
		return ast::Node::makeRational(0);
	}

	ast::Operands flatOperands = flattenOperands("Plus", operands);

	if ( flatOperands.size() == 1 ) {
		return operands[0];
	}

	return ast::Node::makeFunctionCall("Plus", flatOperands);
}

}}} //namespace tungsten::eval::builtin

