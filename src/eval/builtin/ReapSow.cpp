
#include "eval/SessionEnvironment.hpp"

namespace tungsten { namespace eval { namespace builtin {

OptionalNode Reap(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment) {
	if ( operands.size() != 1 ) {
		sessionEnvironment.raiseMessage( Message(ids::Reap, ids::argx, {
				ast::Node::make<ast::Identifier>( ids::Reap ),
				ast::Node::make<math::Rational>( operands.size() )
		} ));
		return EvaluationFailure();
	}

	sessionEnvironment.pushReapStack();

	ast::Node resultExpression = sessionEnvironment.recursiveEvaluate(operands[0]);

	ast::Operands sowed = sessionEnvironment.popReapStack();

	return ast::Node::make<ast::FunctionCall>("List", {
				resultExpression,
				ast::Node::make<ast::FunctionCall>("List", {
					ast::Node::make<ast::FunctionCall>("List", sowed)
				})
			});

}

OptionalNode Sow(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment) {
	if ( operands.size() != 1 ) {
		sessionEnvironment.raiseMessage( Message(ids::Sow, ids::argx, {
				ast::Node::make<ast::Identifier>( ids::Sow ),
				ast::Node::make<math::Rational>( operands.size() )
		} ));
		return EvaluationFailure();
	}
	if ( !sessionEnvironment.isReapStackEmpty() ) {
		sessionEnvironment.sowToReapStack(operands[0]);
	}

	return operands[0];
}

}}} //namespace tungsten::eval::builtin


