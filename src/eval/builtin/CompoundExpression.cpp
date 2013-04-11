
#include "functions.hpp"
#include "eval/SessionEnvironment.hpp"

namespace tungsten { namespace eval { namespace builtin {

OptionalNode CompoundExpression(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment) {
	if ( operands.empty() ) {
		return ast::Node::make<ast::Identifier>(ids::Null);
	}
	for ( unsigned i = 0; i < operands.size()-1; ++i ) {
		sessionEnvironment.recursiveEvaluate(operands[i]);
	}

	return sessionEnvironment.recursiveEvaluate(operands.back());
}

}}} //namespace tungsten::eval::builtin

