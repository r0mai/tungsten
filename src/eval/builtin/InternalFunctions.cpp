
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

	if(!dynamic_cast<CLISessionEnvironment*>(&sessionEnvironment)) {
		return EvaluationFailure();
	}

	int index = 0;
	if(operands.size() == 1) {
		index = operands.front().getInteger().convert_to<int>();
	}

	const auto& result = dynamic_cast<CLISessionEnvironment*>(&sessionEnvironment)->getNthLatestLine(index+1);
	// As Out is now at the end of the history, get one before it

	return sessionEnvironment.evaluate(result);
}

}}} // namespace tungsten::eval::builtin

