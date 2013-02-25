
#include "functions.hpp"
#include "eval/SessionEnvironment.hpp"

namespace tungsten { namespace eval { namespace builtin {

OptionalNode Sin(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment) {
	if ( operands.size() != 1 ) {
		sessionEnvironment.raiseMessage( Message(ids::Sin, ids::argx, {
				ast::Node::make<ast::Identifier>( ids::Sin ),
				ast::Node::make<math::Rational>( operands.size() )
		} ));
		return EvaluationFailure();
	}

	const ast::Node& argument = operands[0];

	if ( argument.is<math::Real>() ) {
		return ast::Node::make<math::Real>(math::Real(sin(argument.get<math::Real>())));
	}
	return ast::Node::make<ast::FunctionCall>(ids::Sin, operands);
}

OptionalNode Cos(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment) {
	if ( operands.size() != 1 ) {
		sessionEnvironment.raiseMessage( Message(ids::Cos, ids::argx, {
				ast::Node::make<ast::Identifier>( ids::Cos ),
				ast::Node::make<math::Rational>( operands.size() )
		} ));
		return EvaluationFailure();
	}

	const ast::Node& argument = operands[0];

	if ( argument.is<math::Real>() ) {
		return ast::Node::make<math::Real>(math::Real(cos(argument.get<math::Real>())));
	}
	return ast::Node::make<ast::FunctionCall>(ids::Cos, operands);
}

OptionalNode Tan(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment) {
	if ( operands.size() != 1 ) {
		sessionEnvironment.raiseMessage( Message(ids::Tan, ids::argx, {
				ast::Node::make<ast::Identifier>( ids::Tan ),
				ast::Node::make<math::Rational>( operands.size() )
		} ));
		return EvaluationFailure();
	}

	const ast::Node& argument = operands[0];

	if ( argument.is<math::Real>() ) {
		return ast::Node::make<math::Real>(math::Real(tan(argument.get<math::Real>())));
	}
	return ast::Node::make<ast::FunctionCall>(ids::Tan, operands);
}

OptionalNode Cot(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment) {
	if ( operands.size() != 1 ) {
		sessionEnvironment.raiseMessage( Message(ids::Cot, ids::argx, {
				ast::Node::make<ast::Identifier>( ids::Cot ),
				ast::Node::make<math::Rational>( operands.size() )
		} ));
		return EvaluationFailure();
	}

	const ast::Node& argument = operands[0];

	if ( argument.is<math::Real>() ) {
		return ast::Node::make<math::Real>(math::Real( 1/tan(argument.get<math::Real>()) ));
	}
	return ast::Node::make<ast::FunctionCall>(ids::Cot, operands);
}

OptionalNode Csc(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment) {
	if ( operands.size() != 1 ) {
		sessionEnvironment.raiseMessage( Message(ids::Csc, ids::argx, {
				ast::Node::make<ast::Identifier>( ids::Csc ),
				ast::Node::make<math::Rational>( operands.size() )
		} ));
		return EvaluationFailure();
	}

	const ast::Node& argument = operands[0];

	if ( argument.is<math::Real>() ) {
		return ast::Node::make<math::Real>(math::Real( 1/sin(argument.get<math::Real>()) ));
	}
	return ast::Node::make<ast::FunctionCall>(ids::Csc, operands);
}

OptionalNode Sec(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment) {
	if ( operands.size() != 1 ) {
		sessionEnvironment.raiseMessage( Message(ids::Sec, ids::argx, {
				ast::Node::make<ast::Identifier>( ids::Sec ),
				ast::Node::make<math::Rational>( operands.size() )
		} ));
		return EvaluationFailure();
	}

	const ast::Node& argument = operands[0];

	if ( argument.is<math::Real>() ) {
		return ast::Node::make<math::Real>(math::Real( 1/cos(argument.get<math::Real>()) ));
	}
	return ast::Node::make<ast::FunctionCall>(ids::Sec, operands);
}

}}} //namespace tungsten::eval::builtin


