
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
	if ( !operands[0].is<ast::FunctionCall>() ) {
		sessionEnvironment.raiseMessage( Message(ids::Append, ids::normal, {
				ast::Node::make<math::Rational>( 2 ),
				ast::Node::make<ast::FunctionCall>( ids::Append, operands )
		} ));
		return EvaluationFailure();
	}

	ast::Operands resultOperands;
	resultOperands.reserve( operands[0].get<ast::FunctionCall>().getOperands().size() + 1 );
	std::copy( operands[0].get<ast::FunctionCall>().getOperands().begin(), operands[0].get<ast::FunctionCall>().getOperands().end(), std::back_inserter(resultOperands) );
	resultOperands.push_back( operands[1] );

	return ast::Node::make<ast::FunctionCall>( operands[0].get<ast::FunctionCall>().getFunction(), std::move(resultOperands) );
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
	if ( !operands[0].is<ast::FunctionCall>() ) {
		sessionEnvironment.raiseMessage( Message(ids::Prepend, ids::normal, {
				ast::Node::make<math::Rational>( 2 ),
				ast::Node::make<ast::FunctionCall>( ids::Prepend, operands )
		} ));
		return EvaluationFailure();
	}

 	ast::Operands resultOperands;
	resultOperands.reserve( operands[0].get<ast::FunctionCall>().getOperands().size() + 1 );
	resultOperands.push_back( operands[1] );
	std::copy( operands[0].get<ast::FunctionCall>().getOperands().begin(), operands[0].get<ast::FunctionCall>().getOperands().end(), std::back_inserter(resultOperands) );

	return ast::Node::make<ast::FunctionCall>( operands[0].get<ast::FunctionCall>().getFunction(), std::move(resultOperands) );
}

}}} //namespace tungsten::eval::builtin

