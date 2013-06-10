
#include "functions.hpp"
#include "eval/SessionEnvironment.hpp"
#include "eval/patternMatching.hpp"

namespace tungsten { namespace eval { namespace builtin {

OptionalNode MatchQ(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment) {
	if ( operands.size() != 2 ) {
		sessionEnvironment.raiseMessage( Message(ids::MatchQ, ids::argrx, {
				ast::Node::make<ast::Identifier>( ids::MatchQ ),
				ast::Node::make<math::Rational>( operands.size() ),
				ast::Node::make<math::Rational>( 2 )
		} ));
		return EvaluationFailure();
	}


	if ( doesPatternMatch(operands[0], operands[1], sessionEnvironment) ) {
		return ast::Node::make<ast::Identifier>(ids::True);
	} else {
		return ast::Node::make<ast::Identifier>(ids::False);
	}
}

}}} //namespace tungsten::eval::builtin

