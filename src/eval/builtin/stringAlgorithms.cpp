
#include "functions.hpp"

#include "eval/SessionEnvironment.hpp"

namespace tungsten { namespace eval { namespace builtin {

OptionalNode StringLength(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment) {
	if ( operands.size() != 1 ) {
		sessionEnvironment.raiseMessage( Message(ids::StringLength, ids::argx, {
				ast::Node::make<ast::Identifier>( ids::StringLength ),
				ast::Node::make<math::Rational>( operands.size() )
		} ));
		return EvaluationFailure();
	}
	const ast::Node& operand = operands.front();

	if ( !operand.is<ast::String>() ) {
		sessionEnvironment.raiseMessage( Message(ids::StringLength, ids::string, {
				ast::Node::make<math::Rational>( 1 ),
				ast::Node::make<ast::FunctionCall>( ids::StringLength, operands )
		} ));
		return EvaluationFailure();
	}

	const ast::String& string = operand.get<ast::String>();
	return ast::Node::make<math::Rational>(string.length());
}

OptionalNode Characters(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment) {
	if ( operands.size() != 1 ) {
		sessionEnvironment.raiseMessage( Message(ids::Characters, ids::argx, {
				ast::Node::make<ast::Identifier>( ids::Characters ),
				ast::Node::make<math::Rational>( operands.size() )
		} ));
		return EvaluationFailure();
	}
	const ast::Node& operand = operands.front();

	if ( !operand.is<ast::String>() ) {
		return ast::Node::make<ast::FunctionCall>(ids::Characters, operands);
	}

	const ast::String& string = operand.get<ast::String>();
	ast::Operands resultOperands;
	resultOperands.reserve(string.size());

	for ( char ch : string ) {
		resultOperands.push_back( ast::Node::make<ast::String>(1, ch) );
	}

	return ast::Node::make<ast::FunctionCall>(ids::List, std::move(resultOperands));
}

OptionalNode StringJoin(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment) {
	return EvaluationFailure();
}

OptionalNode StringInsert(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment) {
	return EvaluationFailure();
}

OptionalNode StringDrop(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment) {
	return EvaluationFailure();
}

OptionalNode StringTake(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment) {
	return EvaluationFailure();
}

OptionalNode StringReverse(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment) {
	if ( operands.size() != 1 ) {
		sessionEnvironment.raiseMessage( Message(ids::StringReverse, ids::argx, {
				ast::Node::make<ast::Identifier>( ids::StringReverse ),
				ast::Node::make<math::Rational>( operands.size() )
		} ));
		return EvaluationFailure();
	}
	const ast::Node& operand = operands.front();

	if ( !operand.is<ast::String>() ) {
		sessionEnvironment.raiseMessage( Message(ids::StringReverse, ids::string, {
				ast::Node::make<math::Rational>( 1 ),
				ast::Node::make<ast::FunctionCall>( ids::StringReverse, operands )
		} ));
		return EvaluationFailure();
	}

	ast::String string = operand.get<ast::String>();
	std::reverse(string.begin(), string.end());
	return ast::Node::make<ast::String>(string);
}

}}} //namespace tungsten::eval::builtin

