
#include "functions.hpp"
#include "eval/getNodeNumerator.hpp"

namespace tungsten { namespace eval { namespace builtin {

OptionalNode Numerator(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment) {
	if ( operands.size() != 1 ) {
		sessionEnvironment.raiseMessage( Message(ids::Numerator, ids::argx, {
				ast::Node::make<ast::Identifier>( ids::Numerator ),
				ast::Node::make<math::Rational>( operands.size() )
		} ));

		return EvaluationFailure();
	}

	return getNodeNumerator(operands[0], sessionEnvironment);
}

}}} //namespace tungsten::eval::builtin
