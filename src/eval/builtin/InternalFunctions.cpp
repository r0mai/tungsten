
#include "functions.hpp"
#include "eval/CLISessionEnvironment.hpp"

#include <algorithm>

namespace tungsten { namespace eval { namespace builtin {

OptionalNode Out(const ast::Operands& operands, SessionEnvironment& sessionEnvironment) {
	if(!std::all_of(operands.begin(), operands.end(), [](const ast::Node& node) {
		return node.isInteger();
	})) {
		return EvaluationFailure();
	}

	int index = 0;
	if(operands.size() == 1) {
		index = operands.front().getInteger().convert_to<int>();
	}
	const auto& result = sessionEnvironment.nthPreviousOutput(index);
	if(!result) {
		return EvaluationFailure();
	}

	return *result;
}

}}} // namespace tungsten::eval::builtin

