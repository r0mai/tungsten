
#include "functions.hpp"

#include <iostream>

#include "eval/Environment.hpp"

namespace tungsten { namespace eval { namespace builtin {

ast::Node Plus(const ast::Operands& operands, eval::Environment& environment) {
	std::cout << "Plus called" << std::endl;
	return ast::Node::makeFunctionCall("Plus", operands);
}

}}} //namespace tungsten::eval::builtin

