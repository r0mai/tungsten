
#include "functions.hpp"
#include "eval/SessionEnvironment.hpp"

namespace tungsten { namespace eval { namespace builtin {

OptionalNode Append(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment) {
	if ( operands.size() != 2 ) {
		sessionEnvironment.raiseMessage( Message(ids::Append, ids::argrx, {
				ast::Node::make<ast::Identifier>( ids::Append ),
				ast::Node::make<math::Rational>( operands.size() ),
				ast::Node::make<math::Rational>( 2 )
		} ));
		return EvaluationFailure();
	}

	const ast::Node& listToAppend = operands.front();
	const ast::Node& item = operands.back();

	if ( !listToAppend.is<ast::FunctionCall>() ) {
		sessionEnvironment.raiseMessage( Message(ids::Append, ids::normal, {
				ast::Node::make<math::Rational>( 2 ),
				ast::Node::make<ast::FunctionCall>( ids::Append, operands )
		} ));
		return EvaluationFailure();
	}
	ast::Node result = listToAppend;
	result.get<ast::FunctionCall>().getOperands().push_back( item );
	
	return result;
}

OptionalNode Prepend(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment) {
	if ( operands.size() != 2 ) {
		sessionEnvironment.raiseMessage( Message(ids::Prepend, ids::argrx, {
				ast::Node::make<ast::Identifier>( ids::Prepend ),
				ast::Node::make<math::Rational>( operands.size() ),
				ast::Node::make<math::Rational>( 2 )
		} ));
		return EvaluationFailure();
	}

	const ast::Node& listToPrepend = operands.front();
	const ast::Node& item = operands.back();

	if ( !listToPrepend.is<ast::FunctionCall>() ) {
		sessionEnvironment.raiseMessage( Message(ids::Prepend, ids::normal, {
				ast::Node::make<math::Rational>( 2 ),
				ast::Node::make<ast::FunctionCall>( ids::Prepend, operands )
		} ));
		return EvaluationFailure();
	}
	ast::Node result = listToPrepend;
	result.get<ast::FunctionCall>().getOperands().push_front( item );
	
	return result;
}

}}} //namespace tungsten::eval::builtin

