
#include "functions.hpp"
#include "eval/SessionEnvironment.hpp"

namespace tungsten { namespace eval { namespace builtin {

OptionalNode Map(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment) {
	if ( operands.size() != 2 /*|| operands.size() != 3*/ ) {
		sessionEnvironment.raiseMessage( Message(ids::Map, ids::argt, {
				ast::Node::make<ast::Identifier>( ids::Map ),
				ast::Node::make<math::Rational>( operands.size() ),
				ast::Node::make<math::Rational>( 2 ),
				ast::Node::make<math::Rational>( 3 )
		} ));
		return EvaluationFailure();
	}

	const ast::Node& function = operands[0];
	ast::Node expression = operands[1];

	if ( expression.is<ast::FunctionCall>() ) {
		for ( ast::Node& node : expression.get<ast::FunctionCall>().getOperands() ) {
			node = ast::Node::make<ast::FunctionCall>( function, {node} );
		}
	}


	return sessionEnvironment.recursiveEvaluate(expression);
}

}}} //namespace tungsten::eval::builtin

