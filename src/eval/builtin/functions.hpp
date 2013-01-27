

#ifndef EVAL_BUILTIN_FUNCTIONS_HPP_
#define EVAL_BUILTIN_FUNCTIONS_HPP_

#include "ast/Node.hpp"
#include "eval/SessionEnvironmentFwd.hpp"
#include "eval/Identifiers.hpp"

#include <map>
#include <functional>

namespace tungsten { namespace eval { namespace builtin {

typedef std::function<ast::Node(const ast::Operands&, eval::SessionEnvironment&)> FunctionPtr;

typedef std::map<ast::Identifier, FunctionPtr> Functions;

Functions createFunctions();

ast::Node Plus(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment);
ast::Node Times(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment);
ast::Node Power(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment);
ast::Node Abs(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment);
ast::Node Numerator(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment);
ast::Node Denominator(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment);
ast::Node Replace(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment);

}}} //namespace tungsten::eval::builtin

#endif /* EVAL_BUILTIN_FUNCTIONS_HPP_ */
