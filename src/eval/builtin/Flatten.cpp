
#include "functions.hpp"
#include "eval/SessionEnvironment.hpp"
#include "eval/flattenOperands.hpp"

namespace tungsten { namespace eval { namespace builtin {

OptionalNode Flatten(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment) {
	if ( operands.size() != 1 ) {
		sessionEnvironment.raiseMessage( Message(ids::Flatten, ids::argx, {
				ast::Node::make<ast::Identifier>( ids::Flatten ),
				ast::Node::make<math::Rational>( operands.size() )
		} ));
		return EvaluationFailure();
	}

	if ( !operands[0].is<ast::FunctionCall>() ) {
		sessionEnvironment.raiseMessage( Message(ids::Flatten, ids::normal, {
				ast::Node::make<math::Rational>( 1 ),
				ast::Node::make<ast::FunctionCall>(ids::Flatten, operands)
		} ));
	}

	const ast::Node& operandHead = operands[0].get<ast::FunctionCall>().getFunction();
	const ast::Operands& operandOperands = operands[0].get<ast::FunctionCall>().getOperands();

	return sessionEnvironment.recursiveEvaluate(
		ast::Node::make<ast::FunctionCall>(operandHead, flattenOperands(operandHead, operandOperands))
	);

}

}}} //namespace tungsten::eval::builtin


