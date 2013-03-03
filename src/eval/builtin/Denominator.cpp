
#include "functions.hpp"
#include "eval/getNodeDenominator.hpp"

namespace tungsten { namespace eval { namespace builtin {

OptionalNode Denominator(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment) {
	if ( operands.size() != 1 ) {

		sessionEnvironment.raiseMessage( Message(ids::Denominator, ids::argx, {
				ast::Node::make<ast::Identifier>( ids::Denominator ),
				ast::Node::make<math::Rational>( operands.size() )
		} ));

		return EvaluationFailure();
	}

	return sessionEnvironment.recursiveEvaluate(getNodeDenominator(operands[0]));
}

}}} //namespace tungsten::eval::builtin
