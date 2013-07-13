
#include "functions.hpp"
#include "eval/SessionEnvironment.hpp"

namespace tungsten { namespace eval { namespace builtin {

OptionalNode Subtract(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment) {
	if ( operands.size() != 2 ) {
		sessionEnvironment.raiseMessage( Message(ids::Subtract, ids::argrx, {
				ast::Node::make<ast::Identifier>( ids::Subtract ),
				ast::Node::make<math::Rational>( operands.size() ),
				ast::Node::make<math::Rational>( 2 )
		} ));
		return EvaluationFailure();
	}

	return sessionEnvironment.recursiveEvaluate(
			ast::Node::make<ast::FunctionCall>(ids::Plus, {
					operands.front(),
					ast::Node::make<ast::FunctionCall>(ids::Times, {
						operands.back(),
						ast::Node::make<math::Rational>(-1)
					})
			})
	);
}

}}} //namespace tungsten::eval::builtin
