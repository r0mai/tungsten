
#include "functions.hpp"
#include "eval/SessionEnvironment.hpp"

namespace tungsten { namespace eval { namespace builtin {

OptionalNode SetDelayed(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment) {
	if ( operands.size() != 2 ) {

		sessionEnvironment.raiseMessage( Message(ids::SetDelayed, ids::argx, {
				ast::Node::make<ast::Identifier>( ids::SetDelayed ),
				ast::Node::make<math::Rational>( operands.size() )
		} ));

		return EvaluationFailure();
	}

	sessionEnvironment.addPattern(operands.front(), operands.back());
	return ast::Node::make<ast::Identifier>(ids::Null);
}

}}} //namespace tungsten::eval::builtin
