
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


OptionalNode ArcSin(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment) {
	if ( operands.size() != 1 ) {
		sessionEnvironment.raiseMessage( Message(ids::ArcSin, ids::argx, {
				ast::Node::make<ast::Identifier>( ids::ArcSin ),
				ast::Node::make<math::Rational>( operands.size() )
		} ));
		return EvaluationFailure();
	}

	const ast::Node& argument = operands[0];

	if ( argument.is<math::Real>() ) {
		return ast::Node::make<math::Real>(math::Real(asin(argument.get<math::Real>())));
	}
	return ast::Node::make<ast::FunctionCall>(ids::ArcSin, operands);
}

OptionalNode ArcCos(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment) {
	if ( operands.size() != 1 ) {
		sessionEnvironment.raiseMessage( Message(ids::ArcCos, ids::argx, {
				ast::Node::make<ast::Identifier>( ids::ArcCos ),
				ast::Node::make<math::Rational>( operands.size() )
		} ));
		return EvaluationFailure();
	}

	const ast::Node& argument = operands[0];

	if ( argument.is<math::Real>() ) {
		return ast::Node::make<math::Real>(math::Real(acos(argument.get<math::Real>())));
	}
	return ast::Node::make<ast::FunctionCall>(ids::ArcCos, operands);
}

OptionalNode ArcTan(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment) {
	if ( operands.size() != 1 ) {
		sessionEnvironment.raiseMessage( Message(ids::ArcTan, ids::argx, {
				ast::Node::make<ast::Identifier>( ids::ArcTan ),
				ast::Node::make<math::Rational>( operands.size() )
		} ));
		return EvaluationFailure();
	}

	const ast::Node& argument = operands[0];

	if ( argument.is<math::Real>() ) {
		return ast::Node::make<math::Real>(math::Real(atan(argument.get<math::Real>())));
	}
	return ast::Node::make<ast::FunctionCall>(ids::ArcTan, operands);
}
#if 0
OptionalNode ArcCot(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment) {
	if ( operands.size() != 1 ) {
		sessionEnvironment.raiseMessage( Message(ids::ArcCot, ids::argx, {
				ast::Node::make<ast::Identifier>( ids::ArcCot ),
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
#endif
}}} //namespace tungsten::eval::builtin


