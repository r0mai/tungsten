
#include "functions.hpp"
#include "eval/SessionEnvironment.hpp"
#include "eval/getHead.hpp"

namespace tungsten { namespace eval { namespace builtin {

OptionalNode Part(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment) {
    if ( operands.size() != 1 && operands.size() != 2 ) {
		sessionEnvironment.raiseMessage( Message(ids::Part, ids::argt, {
				ast::Node::make<ast::Identifier>( ids::Part ),
				ast::Node::make<math::Rational>( operands.size() )
		} ));
		return EvaluationFailure();
    }
    if ( operands.size() == 1 ) {
        return operands[0];
    }

    if ( !operands[1].is<math::Rational>() || !math::isInteger(operands[1].get<math::Rational>()) || 
        !math::fits<std::ptrdiff_t>(math::asInteger(operands[1].get<math::Rational>())) ) 
    {
		sessionEnvironment.raiseMessage( Message(ids::Part, ids::pspec, {
            operands[1]
		} ));
        return EvaluationFailure();
    }
    const ast::Node& expr = operands[0]; 
    std::ptrdiff_t index = math::as<std::ptrdiff_t>(math::asInteger(operands[1].get<math::Rational>()));
    if ( index == 0 ) {
        return getHead( expr );
    } 
    if ( !expr.is<ast::FunctionCall>() ) {
		sessionEnvironment.raiseMessage( Message(ids::Part, ids::partd, {
            ast::Node::make<ast::FunctionCall>( ids::Part, operands )
		} ));
        return EvaluationFailure();
    }
    std::size_t expressionLenght = expr.get<ast::FunctionCall>().getOperands().size();
    std::ptrdiff_t wantedIndex = index-1;
    if ( index < 0 ) {
        //Count from the back
        wantedIndex = expressionLenght + index;
    }
    if ( wantedIndex < 0 || wantedIndex >= static_cast<std::ptrdiff_t>(expressionLenght) ) {
		sessionEnvironment.raiseMessage( Message(ids::Part, ids::partw, {
            operands[1], operands[0]
		} ));
        return EvaluationFailure();
    }
	return expr.get<ast::FunctionCall>().getOperands()[wantedIndex];
}

}}} //namespace tungsten::eval::builtin

