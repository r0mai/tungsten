

#ifndef EVAL_BUILTIN_FUNCTIONS_HPP_
#define EVAL_BUILTIN_FUNCTIONS_HPP_

#include "ast/Node.hpp"
#include "eval/SessionEnvironmentFwd.hpp"
#include "eval/Identifiers.hpp"

#include <map>
#include <functional>

#include <boost/optional.hpp>

namespace tungsten { namespace eval { namespace builtin {

typedef boost::optional<ast::Node> OptionalNode;
typedef boost::none_t EvaluationFailure;

typedef std::function<OptionalNode(const ast::Operands&, eval::SessionEnvironment&)> FunctionPtr;

typedef std::map<ast::Identifier, FunctionPtr> Functions;

Functions createFunctions();

OptionalNode Plus(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment);
OptionalNode Times(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment);
OptionalNode Power(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment);
OptionalNode Abs(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment);
OptionalNode Numerator(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment);
OptionalNode Denominator(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment);
OptionalNode Replace(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment);
OptionalNode Set(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment);
OptionalNode SetDelayed(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment);
OptionalNode RandomReal(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment);
OptionalNode Divide(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment);
OptionalNode Head(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment);

}}} //namespace tungsten::eval::builtin

#endif /* EVAL_BUILTIN_FUNCTIONS_HPP_ */
