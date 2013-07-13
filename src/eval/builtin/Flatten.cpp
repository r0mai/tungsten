
#include "functions.hpp"
#include "eval/SessionEnvironment.hpp"
#include "eval/flattenOperands.hpp"

#include <limits>

namespace tungsten { namespace eval { namespace builtin {

OptionalNode Flatten(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment) {
	if ( operands.empty() || operands.size() > 2 ) {
		sessionEnvironment.raiseMessage( Message(ids::Flatten, ids::argx, {
				ast::Node::make<ast::Identifier>( ids::Flatten ),
				ast::Node::make<math::Rational>( operands.size() )
		} ));
		return EvaluationFailure();
	}

	const ast::Node& argument = operands.front();
	if ( !argument.is<ast::FunctionCall>() ) {
		sessionEnvironment.raiseMessage( Message(ids::Flatten, ids::normal, {
				ast::Node::make<math::Rational>( 1 ),
				ast::Node::make<ast::FunctionCall>(ids::Flatten, operands)
		} ));
		return EvaluationFailure();
	}

	unsigned long level = std::numeric_limits<unsigned long>::max();

	if ( operands.size() > 1 ) {
		const ast::Node& levelspecNode = operands.back();
		if ( !levelspecNode.is<math::Rational>() || !math::isInteger(levelspecNode.get<math::Rational>()) || levelspecNode.get<math::Rational>() < 0 ) {
			sessionEnvironment.raiseMessage( Message(ids::Flatten, ids::flev, {
					levelspecNode,
					ast::Node::make<math::Rational>( 1 ),
					ast::Node::make<ast::FunctionCall>(ids::Flatten, operands)
			} ));
			return EvaluationFailure();
		}
		math::Integer levelNode = math::asInteger( levelspecNode.get<math::Rational>() );
		//If it doesn't fit, max() will be big enough..
		if ( math::fits<unsigned long>(levelNode) ) {
			level = math::as<unsigned long>(levelNode);
		}
	}

	const ast::Node& operandHead = argument.get<ast::FunctionCall>().getFunction();
	const ast::Operands& operandOperands = argument.get<ast::FunctionCall>().getOperands();

	return sessionEnvironment.recursiveEvaluate(
		ast::Node::make<ast::FunctionCall>(operandHead, flattenOperands(operandHead, operandOperands, level))
	);

}

}}} //namespace tungsten::eval::builtin


