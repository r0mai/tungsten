
#include "functions.hpp"
#include "eval/SessionEnvironment.hpp"

namespace tungsten { namespace eval { namespace builtin {

OptionalNode TrueQ(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment) {
	if ( operands.size() != 1 ) {
		sessionEnvironment.raiseMessage( Message(ids::TrueQ, ids::argx, {
				ast::Node::make<ast::Identifier>( ids::TrueQ ),
				ast::Node::make<math::Rational>( operands.size() )
		} ));
		return EvaluationFailure();
	}

	if ( operands[0].is<ast::Identifier>(ids::True) ) {
		return ast::Node::make<ast::Identifier>(ids::True);
	}
	return ast::Node::make<ast::Identifier>(ids::False);
}

OptionalNode Not(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment) {
	if ( operands.size() != 1 ) {
		sessionEnvironment.raiseMessage( Message(ids::TrueQ, ids::argx, {
				ast::Node::make<ast::Identifier>( ids::TrueQ ),
				ast::Node::make<math::Rational>( operands.size() )
		} ));
		return EvaluationFailure();
	}

	const ast::Node& operand = operands[0];

	if ( operand.is<ast::Identifier>(ids::True) ) {
		return ast::Node::make<ast::Identifier>(ids::False);
	} else if ( operand.is<ast::Identifier>(ids::False) ) {
		return ast::Node::make<ast::Identifier>(ids::True);
	} else if ( operand.isFunctionCall(ids::Not) && operand.get<ast::FunctionCall>().getOperands().size() == 1 ) {
		return operand.get<ast::FunctionCall>().getOperands()[0];
	} else if ( operand.isFunctionCall(ids::Less) && operand.get<ast::FunctionCall>().getOperands().size() == 2 ) {
		return ast::Node::make<ast::FunctionCall>( ids::GreaterEqual, operand.get<ast::FunctionCall>().getOperands() );
	} else if ( operand.isFunctionCall(ids::Greater) && operand.get<ast::FunctionCall>().getOperands().size() == 2 ) {
		return ast::Node::make<ast::FunctionCall>( ids::LessEqual, operand.get<ast::FunctionCall>().getOperands() );
	} else if ( operand.isFunctionCall(ids::GreaterEqual) && operand.get<ast::FunctionCall>().getOperands().size() == 2 ) {
		return ast::Node::make<ast::FunctionCall>( ids::Less, operand.get<ast::FunctionCall>().getOperands() );
	} else if ( operand.isFunctionCall(ids::LessEqual) && operand.get<ast::FunctionCall>().getOperands().size() == 2 ) {
		return ast::Node::make<ast::FunctionCall>( ids::Greater, operand.get<ast::FunctionCall>().getOperands() );
	} else if ( operand.isFunctionCall(ids::Equal) && operand.get<ast::FunctionCall>().getOperands().size() == 2 ) {
		return ast::Node::make<ast::FunctionCall>( ids::Unequal, operand.get<ast::FunctionCall>().getOperands() );
	} else if ( operand.isFunctionCall(ids::Unequal) && operand.get<ast::FunctionCall>().getOperands().size() == 2 ) {
		return ast::Node::make<ast::FunctionCall>( ids::Equal, operand.get<ast::FunctionCall>().getOperands() );
	}

	return ast::Node::make<ast::FunctionCall>( ids::Not, operands );
}

OptionalNode And(const ast::Operands& /*operands*/, eval::SessionEnvironment& /*sessionEnvironment*/) {
	return EvaluationFailure();
}

OptionalNode Or(const ast::Operands& /*operands*/, eval::SessionEnvironment& /*sessionEnvironment*/) {
	return EvaluationFailure();
}

OptionalNode Boole(const ast::Operands& /*operands*/, eval::SessionEnvironment& /*sessionEnvironment*/) {
	return EvaluationFailure();
}

}}} //namespace tungsten::eval::builtin


