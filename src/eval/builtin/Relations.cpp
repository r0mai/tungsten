#include "functions.hpp"
#include "eval/SessionEnvironment.hpp"
#include "eval/IterationSpecifier.hpp"

#include <algorithm>
#include <cassert>

namespace tungsten { namespace eval { namespace builtin {

OptionalNode Less(const ast::Operands& /*operands*/, eval::SessionEnvironment& /*sessionEnvironment*/) {
	std::cout<<"Unimplemented Less called"<<std::endl;
	return EvaluationFailure();
}

OptionalNode LessOrEqual(const ast::Operands& /*operands*/, eval::SessionEnvironment& /*sessionEnvironment*/) {
	std::cout<<"Unimplemented LessOrEqual called"<<std::endl;
	return EvaluationFailure();
}


OptionalNode Greater(const ast::Operands& /*operands*/, eval::SessionEnvironment& /*sessionEnvironment*/) {
	std::cout<<"Unimplemented Greater called"<<std::endl;
	return EvaluationFailure();
}


OptionalNode GreaterOrEqual(const ast::Operands& /*operands*/, eval::SessionEnvironment& /*sessionEnvironment*/) {
	std::cout<<"Unimplemented GreaterOrEqual called"<<std::endl;
	return EvaluationFailure();
}


}}}; // tungsten::eval::builtin;
