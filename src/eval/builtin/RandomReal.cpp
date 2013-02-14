
#include "functions.hpp"
#include "eval/SessionEnvironment.hpp"

namespace tungsten { namespace eval { namespace builtin {

OptionalNode RandomReal(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment) {
	if ( !operands.empty() ) {

		sessionEnvironment.raiseMessage( Message(ids::RandomReal, ids::argx, {
				ast::Node::make<ast::Identifier>( ids::RandomReal ),
				ast::Node::make<math::Rational>( operands.size() )
		} ));

		return EvaluationFailure();
	}

	//TODO We should make it work with math::Real as well
	std::uniform_real_distribution<double> distribution(0, 1);

	return ast::Node::make<math::Real>( distribution( sessionEnvironment.getRandomEngine() ) );
}

}}} //namespace tungsten::eval::builtin





