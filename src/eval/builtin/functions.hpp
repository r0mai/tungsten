

#ifndef EVAL_BUILTIN_FUNCTIONS_HPP_
#define EVAL_BUILTIN_FUNCTIONS_HPP_

#include "ast/Node.hpp"
#include "eval/SessionEnvironmentFwd.hpp"

#include <map>

namespace tungsten { namespace eval { namespace builtin {

//TODO make this an std::function
typedef ast::Node(*FunctionPtr)(
		const ast::Operands& node,
		eval::SessionEnvironment& sessionEnvironment);


typedef std::map<ast::Identifier, FunctionPtr> Functions;

Functions createFunctions();

ast::Node Plus(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment);

}}} //namespace tungsten::eval::builtin

#endif /* EVAL_BUILTIN_FUNCTIONS_HPP_ */
