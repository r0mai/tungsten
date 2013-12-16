
#include "functions.hpp"
#include "math/mathFunctions.hpp"
#include "eval/numericNodeEvaluation.hpp"

namespace tungsten { namespace eval { namespace builtin {

OptionalNode Floor(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment) {
    if ( operands.size() != 1 ) {
		sessionEnvironment.raiseMessage( Message(ids::Floor, ids::argx, {
				ast::Node::make<ast::Identifier>( ids::Floor ),
				ast::Node::make<math::Rational>( operands.size() )
		} ));

		return EvaluationFailure();
    }

    if ( operands[0].isFunctionCall(ids::Floor) && operands[0].get<ast::FunctionCall>().getOperands().size() == 1 ) {
        return operands[0];
    }

    ast::Node numericNode = numericNodeEvaluation(operands[0], sessionEnvironment);
    if ( !numericNode.is<math::Real>() ) {
        return ast::Node::make<ast::FunctionCall>( ids::Floor, operands );
    }
    return ast::Node::make<math::Rational>( math::floor( numericNode.get<math::Real>() ) );
}

OptionalNode Ceiling(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment) {
    if ( operands.size() != 1 ) {
		sessionEnvironment.raiseMessage( Message(ids::Ceiling, ids::argx, {
				ast::Node::make<ast::Identifier>( ids::Ceiling ),
				ast::Node::make<math::Rational>( operands.size() )
		} ));

		return EvaluationFailure();
    }

    if ( operands[0].isFunctionCall(ids::Ceiling) && operands[0].get<ast::FunctionCall>().getOperands().size() == 1 ) {
        return operands[0];
    }

    ast::Node numericNode = numericNodeEvaluation(operands[0], sessionEnvironment);
    if ( !numericNode.is<math::Real>() ) {
        return ast::Node::make<ast::FunctionCall>( ids::Ceiling, operands );
    }
    return ast::Node::make<math::Rational>( math::ceiling( numericNode.get<math::Real>() ) );
}

OptionalNode Round(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment) {
    if ( operands.size() != 1 ) {
		sessionEnvironment.raiseMessage( Message(ids::Round, ids::argx, {
				ast::Node::make<ast::Identifier>( ids::Round ),
				ast::Node::make<math::Rational>( operands.size() )
		} ));

		return EvaluationFailure();
    }

    if ( operands[0].isFunctionCall(ids::Round) && operands[0].get<ast::FunctionCall>().getOperands().size() == 1 ) {
        return operands[0];
    }

    ast::Node numericNode = numericNodeEvaluation(operands[0], sessionEnvironment);
    if ( !numericNode.is<math::Real>() ) {
        return ast::Node::make<ast::FunctionCall>( ids::Round, operands );
    }
    return ast::Node::make<math::Rational>( math::round( numericNode.get<math::Real>() ) );
}

OptionalNode IntegerPart(const ast::Operands& operands, eval::SessionEnvironment& /*sessionEnvironment*/) {
    //TODO
	return ast::Node::make<ast::FunctionCall>( ids::IntegerPart, operands );
}

OptionalNode FractionalPart(const ast::Operands& operands, eval::SessionEnvironment& /*sessionEnvironment*/) {
    //TODO
	return ast::Node::make<ast::FunctionCall>( ids::FractionalPart, operands );
}
}}} //namespace tungsten::eval::builtin


