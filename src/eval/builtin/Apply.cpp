
#include "functions.hpp"
#include "eval/getNodeNumerator.hpp"

namespace tungsten { namespace eval { namespace builtin {

OptionalNode Apply(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment) {
	if ( operands.size() != 2 /*|| operands.size() != 3*/ ) {
		sessionEnvironment.raiseMessage( Message(ids::Apply, ids::argt, {
				ast::Node::make<ast::Identifier>( ids::Apply ),
				ast::Node::make<math::Rational>( operands.size() ),
				ast::Node::make<math::Rational>( 2 ),
				ast::Node::make<math::Rational>( 3 )
		} ));
		return EvaluationFailure();
	}

	const ast::Node& newHead = operands.front();
	ast::Node expression = operands[1]; //[1] because levelspec will come later
	//TODO levelspec

	if ( expression.is<ast::FunctionCall>() ) {
		expression.get<ast::FunctionCall>().getFunction() = newHead;
		expression = sessionEnvironment.recursiveEvaluate(expression);
	}

	return expression;
}

}}} //namespace tungsten::eval::builtin


