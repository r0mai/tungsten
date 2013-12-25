
#include "functions.hpp"
#include "eval/SessionEnvironment.hpp"

namespace tungsten { namespace eval { namespace builtin {

OptionalNode ByteCount(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment) {
	if ( operands.size() != 1 ) {
		sessionEnvironment.raiseMessage( Message(ids::ByteCount, ids::argx, {
				ast::Node::make<ast::Identifier>( ids::ByteCount ),
				ast::Node::make<math::Rational>( operands.size() )
		} ));

		return EvaluationFailure();
	}

	return ast::Node::make<math::Rational>(operands[0].getByteCount());
}

}}} //namespace tungsten::eval::builtin
