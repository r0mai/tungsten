
#include "functions.hpp"
#include "eval/SessionEnvironment.hpp"

namespace tungsten { namespace eval { namespace builtin {

OptionalNode CompoundExpression(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment) {
	if ( operands.empty() ) {
		return ast::Node::make<ast::Identifier>(ids::Null);
	}
	for ( auto it = operands.begin(), end = std::prev(operands.end()); it != end; ++it ) {
		sessionEnvironment.recursiveEvaluate(*it);
	}

	return sessionEnvironment.recursiveEvaluate(operands.back());
}

}}} //namespace tungsten::eval::builtin

