


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

std::vector<std::string> builtinFunctionCompletions(const std::string& textSoFar);

//TODO this has to remain there (for now)
OptionalNode evaluateFunction(const ast::Operands& functionOperands, const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment);

}}} //namespace tungsten::eval::builtin

#endif /* EVAL_BUILTIN_FUNCTIONS_HPP_ */
