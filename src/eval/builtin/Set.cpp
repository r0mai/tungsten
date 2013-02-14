
#include "functions.hpp"
#include "eval/SessionEnvironment.hpp"

namespace tungsten { namespace eval { namespace builtin {

OptionalNode Set(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment) {
	if ( operands.size() != 2 ) {

		sessionEnvironment.raiseMessage( Message(ids::Set, ids::argx, {
				ast::Node::make<ast::Identifier>( ids::Set ),
				ast::Node::make<math::Rational>( operands.size() )
		} ));

		return EvaluationFailure();
	}

	sessionEnvironment.addPattern(operands[0], operands[1]);
	return operands[1];
}

}}} //namespace tungsten::eval::builtin

