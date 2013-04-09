
#include "functions.hpp"
#include "eval/SessionEnvironment.hpp"

namespace tungsten { namespace eval { namespace builtin {

OptionalNode While(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment) {
    if ( operands.empty() || operands.size() > 2 ) {
        
		sessionEnvironment.raiseMessage( Message(ids::While, ids::argt, {
				ast::Node::make<ast::Identifier>( ids::While ),
				ast::Node::make<math::Rational>( operands.size() ),
				ast::Node::make<math::Rational>( 1 ),
				ast::Node::make<math::Rational>( 2 )
		} ));

		return EvaluationFailure();
    }
    const ast::Node& condition = operands[0];
    const bool hasBody = operands.size() == 2;
    while ( sessionEnvironment.recursiveEvaluate(condition).is<ast::Identifier>(ids::True) ) {
        if (hasBody) {
            sessionEnvironment.recursiveEvaluate( operands[1] );
        }
    }
	return ast::Node::make<ast::Identifier>(ids::Null); 
}

}}} //namespace tungsten::eval::builtin


