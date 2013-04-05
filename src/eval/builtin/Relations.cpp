#include "functions.hpp"
#include "eval/SessionEnvironment.hpp"
#include "eval/IterationSpecifier.hpp"

#include <algorithm>
#include <cassert>

namespace tungsten { namespace eval { namespace builtin {

OptionalNode Less(const ast::Operands& /*operands*/, eval::SessionEnvironment& /*sessionEnvironment*/) {
	return EvaluationFailure();
}

OptionalNode LessOrEqual(const ast::Operands& /*operands*/, eval::SessionEnvironment& /*sessionEnvironment*/) {
	return EvaluationFailure();
}


OptionalNode Greater(const ast::Operands& /*operands*/, eval::SessionEnvironment& /*sessionEnvironment*/) {
	return EvaluationFailure();
}


OptionalNode GreaterOrEqual(const ast::Operands& /*operands*/, eval::SessionEnvironment& /*sessionEnvironment*/) {
	return EvaluationFailure();
}


}}}; // tungsten::eval::builtin;
