
#include "functions.hpp"
#include "eval/CLISessionEnvironment.hpp"

#include <algorithm>
#include <iostream>
namespace tungsten { namespace eval { namespace builtin {

OptionalNode Out(const ast::Operands& operands, SessionEnvironment& sessionEnvironment) {
	if(!std::all_of(operands.begin(), operands.end(), [](const ast::Node& node) {
		return node.isInteger();
	})) {
		return EvaluationFailure();
	}

	int index = -1;
	if(operands.size() == 1) {
		index = operands.front().getInteger().convert_to<int>();
	}
	const auto& result = sessionEnvironment.nthOutput(index);
	if(!result) {
		return EvaluationFailure();
	}

	return *result;
}

OptionalNode In(const ast::Operands& operands, SessionEnvironment& sessionEnvironment) {
	if(!std::all_of(operands.begin(), operands.end(), [](const ast::Node& node) {
		return node.isInteger();
	})) {
		return EvaluationFailure();
	}

	int index = -1;
	if(operands.size() == 1) {
		index = operands.front().getInteger().convert_to<int>();
	}
	const auto& result = sessionEnvironment.nthInput(index+1);
	// As we under evaluatiuon, the 0th element points to In[]
	if(!result) {
		return EvaluationFailure();
	}

	return *result;
}

}}} // namespace tungsten::eval::builtin

