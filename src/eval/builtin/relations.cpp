
#include "functions.hpp"
#include "eval/SessionEnvironment.hpp"

namespace tungsten { namespace eval { namespace builtin {

OptionalNode Less(const ast::Operands& /*operands*/, eval::SessionEnvironment& /*sessionEnvironment*/) {
	return EvaluationFailure();
}

OptionalNode LessEqual(const ast::Operands& /*operands*/, eval::SessionEnvironment& /*sessionEnvironment*/) {
	return EvaluationFailure();
}


OptionalNode Greater(const ast::Operands& /*operands*/, eval::SessionEnvironment& /*sessionEnvironment*/) {
	return EvaluationFailure();
}


OptionalNode GreaterEqual(const ast::Operands& /*operands*/, eval::SessionEnvironment& /*sessionEnvironment*/) {
	return EvaluationFailure();
}


}}}; // tungsten::eval::builtin;
