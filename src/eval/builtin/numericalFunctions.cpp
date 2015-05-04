
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

struct ReVisitor: boost::static_visitor<ast::Node> {

	template<typename T>
	ast::Node operator()(const T& t) const {
		return ast::Node::make<typename math::detail::RemoveComplex<T>::type>(
				math::detail::getRealPart(t));
	}

};

OptionalNode Re(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment) {
	if ( operands.size() != 1) {
		sessionEnvironment.raiseMessage( Message(ids::Re, ids::argx, {
				ast::Node::make<ast::Identifier>( ids::Re ),
				ast::Node::make<math::Rational>( operands.size() )
		}));
		return EvaluationFailure();
	}
	if ( operands[0].is<math::Rational, math::ComplexRational,
			math::Real, math::ComplexReal>() ) {
		return ast::applyVisitor(operands.front(), ReVisitor{});
	} else {
		return EvaluationFailure();
	}
}

struct ImVisitor: boost::static_visitor<ast::Node> {

	template<typename T>
	ast::Node operator()(const T& t) const {
		return ast::Node::make<typename math::detail::RemoveComplex<T>::type>(
				math::detail::getImaginaryPart(t));
	}

};

OptionalNode Im(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment) {
	if ( operands.size() != 1) {
		sessionEnvironment.raiseMessage( Message(ids::Re, ids::argx, {
				ast::Node::make<ast::Identifier>( ids::Re ),
				ast::Node::make<math::Rational>( operands.size() )
		}));
		return EvaluationFailure();
	}
	if ( operands[0].is<math::Rational, math::ComplexRational,
			math::Real, math::ComplexReal>() ) {
		const auto numerical = operands.front().get<math::Rational, math::Real,
						math::ComplexRational, math::ComplexReal>();
		return boost::apply_visitor(ImVisitor{}, numerical);
	} else if ( operands[0].is<ast::Identifier>(eval::ids::I) ) {
		return ast::Node::make<math::Rational>(1);
	} else{
		return EvaluationFailure();
	}
}

OptionalNode Complex(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment) {
	if ( operands.size() != 2 ) {
		return EvaluationFailure();
	}
	bool areAllReal = std::all_of(operands.begin(), operands.end(), [](const ast::Node& node) { return node.isNumeric(); });
	if(areAllReal) {
		return ast::Node::make<ast::FunctionCall>(ids::Plus, {
				operands.front(),
				ast::Node::make<ast::FunctionCall>(ids::Times, {
						operands.back(),
						ast::Node::make<ast::Identifier>(ids::I)
				})});
	}
	return EvaluationFailure();
}

}}} //namespace tungsten::eval::builtin


