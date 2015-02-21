#include "functions.hpp"
#include "eval/SessionEnvironment.hpp"

namespace tungsten { namespace eval { namespace builtin {

OptionalNode FindDivisions(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment) {
	if ( operands.size() != 2 ) {
		sessionEnvironment.raiseMessage( Message(ids::FindDivisions, ids::argrx, {
				ast::Node::make<ast::Identifier>( ids::FindDivisions ),
				ast::Node::make<math::Rational>( operands.size() ),
				ast::Node::make<math::Rational>( 2 )
		} ));
		return EvaluationFailure();
	}

	const auto range = operands[0];
	const auto n = operands[1];

	if ( !range.is<ast::FunctionCall>() ) {
		sessionEnvironment.raiseMessage( Message(ids::FindDivisions, ids::fdargs, {
				range,
				ast::Node::make<ast::FunctionCall>( ids::FindDivisions, operands )
		} ));
		return EvaluationFailure();
	}

	if ( !n.isNumeric() ) {
		sessionEnvironment.raiseMessage( Message(ids::FindDivisions, ids::fdargs, {
				n,
				ast::Node::make<ast::FunctionCall>( ids::FindDivisions, operands )
		} ));
		return EvaluationFailure();
	}

	return ast::Node::make_list();
}

}}} // namespace tungsten::eval::builtin
