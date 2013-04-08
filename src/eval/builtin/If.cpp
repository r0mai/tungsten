
#include "functions.hpp"
#include "eval/SessionEnvironment.hpp"

namespace tungsten { namespace eval { namespace builtin {

OptionalNode If(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment) {
	if ( operands.size() < 2 || operands.size() > 4 ) {
		sessionEnvironment.raiseMessage( Message(ids::If, ids::argbu, {
				ast::Node::make<ast::Identifier>( ids::Set ),
				ast::Node::make<math::Rational>( operands.size() ),
				ast::Node::make<math::Rational>( 2 ),
				ast::Node::make<math::Rational>( 4 )
		} ));
		return EvaluationFailure();
	}

	const ast::Node& condition = operands[0];

	if ( condition.is<ast::Identifier>(ids::True) ) {
		return sessionEnvironment.recursiveEvaluate(operands[1]);
	}
	if ( condition.is<ast::Identifier>(ids::False) ) {
		if ( operands.size() > 2 ) {
			return sessionEnvironment.recursiveEvaluate(operands[2]);
		}
		return ast::Node::make<ast::Identifier>(ids::Null);
	}

	if ( operands.size() == 4 ) {
		return sessionEnvironment.recursiveEvaluate(operands[3]);
	}

	return ast::Node::make<ast::FunctionCall>( ids::If, operands );
}

}}} //namespace tungsten::eval::builtin

