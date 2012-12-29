
#include "functions.hpp"

#include <iostream>

#include "eval/SessionEnvironment.hpp"

namespace tungsten { namespace eval { namespace builtin {

ast::Node Plus(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment, eval::EvaluationEnvironment& evaluationEnvironment) {
	if ( operands.size() == 0 ) {
		return ast::Node::makeRational(0);
	}

	if ( operands.size() == 1 ) {
		return operands[0];
	}
}

ast::Node Plus_N(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment, eval::EvaluationEnvironment& evaluationEnvironment) {
	return Plus(operands, sessionEnvironment, evaluationEnvironment);
}

}}} //namespace tungsten::eval::builtin

