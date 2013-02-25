
#include "functions.hpp"
#include "eval/SessionEnvironment.hpp"

namespace tungsten { namespace eval { namespace builtin {

OptionalNode Minus(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment) {
	if ( operands.size() != 1 ) {
		sessionEnvironment.raiseMessage( Message(ids::Minus, ids::argx, {
				ast::Node::make<ast::Identifier>( ids::Minus ),
				ast::Node::make<math::Rational>( operands.size() )
		} ));
		return EvaluationFailure();
	}

	return sessionEnvironment.recursiveEvaluate( ast::Node::make<ast::FunctionCall>(ids::Times, {
			ast::Node::make<math::Rational>(-1),
			operands[0]
	}) );
}

}}} //namespace tungsten::eval::builtin





