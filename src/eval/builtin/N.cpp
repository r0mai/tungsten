
#include <stack>

#include "functions.hpp"
#include "eval/numericNodeEvaluation.hpp"
#include "eval/SessionEnvironment.hpp"

namespace tungsten { namespace eval { namespace builtin {

OptionalNode N(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment) {
	if ( operands.size() != 1 ) {
		sessionEnvironment.raiseMessage( Message(ids::N, ids::argx, {
				ast::Node::make<ast::Identifier>( ids::N ),
				ast::Node::make<math::Rational>( operands.size() )
		} ));
		return EvaluationFailure();
	}

	return sessionEnvironment.recursiveEvaluate( numericNodeEvaluation(operands.front(), sessionEnvironment) );
}

}}} //namespace tungsten::eval::builtin





