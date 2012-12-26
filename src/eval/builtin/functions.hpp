

#ifndef EVAL_BUILTIN_FUNCTIONS_HPP_
#define EVAL_BUILTIN_FUNCTIONS_HPP_

#include "ast/Node.hpp"
#include "eval/EnvironmentFwd.hpp"

#include <map>

namespace tungsten { namespace eval { namespace builtin {

typedef ast::Node(*FunctionPtr)(const ast::Operands& node, eval::Environment& environment);
typedef std::map<ast::Identifier, FunctionPtr> Functions;

Functions createFunctions();

ast::Node Plus(const ast::Operands& operands, eval::Environment& environment);

}}} //namespace tungsten::eval::builtin

#endif /* EVAL_BUILTIN_FUNCTIONS_HPP_ */
