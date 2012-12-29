

#ifndef EVAL_BUILTIN_FUNCTIONS_HPP_
#define EVAL_BUILTIN_FUNCTIONS_HPP_

#include "ast/Node.hpp"
#include "eval/SessionEnvironmentFwd.hpp"
#include "eval/EvaluationEnvironment.hpp"

#include <map>

namespace tungsten { namespace eval { namespace builtin {

typedef ast::Node(*FunctionPtr)(
		const ast::Operands& node,
		eval::SessionEnvironment& sessionEnvironment,
		eval::EvaluationEnvironment& evaluationEnvironment);

//Holds a refular and an optinal numeric version of a builtin function
struct BuiltinFunctionPair {
	BuiltinFunctionPair(FunctionPtr regular = 0, FunctionPtr numeric = 0);

	FunctionPtr regular;
	FunctionPtr numeric;
};

typedef std::map<ast::Identifier, BuiltinFunctionPair> Functions;

Functions createFunctions();

ast::Node Plus(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment, eval::EvaluationEnvironment& evaluationEnvironment);
ast::Node Plus_N(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment, eval::EvaluationEnvironment& evaluationEnvironment);

}}} //namespace tungsten::eval::builtin

#endif /* EVAL_BUILTIN_FUNCTIONS_HPP_ */
