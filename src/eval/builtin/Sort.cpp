
#include "functions.hpp"
#include "eval/SessionEnvironment.hpp"
#include "eval/orderNode.hpp"

namespace tungsten { namespace eval { namespace builtin {

OptionalNode Sort(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment) {
	if ( operands.size() != 1 ) {

		sessionEnvironment.raiseMessage( Message(ids::Sort, ids::argx, {
				ast::Node::make<ast::Identifier>( ids::Sort ),
				ast::Node::make<math::Rational>( operands.size() )
		} ));

		return EvaluationFailure();
	}

	if ( !operands[0].is<ast::FunctionCall>() ) {
		sessionEnvironment.raiseMessage( Message(ids::Sort, ids::Normal, {
				ast::Node::make<math::Rational>( 1 ),
				ast::Node::make<ast::FunctionCall>( ids::Sort, operands )
		} ));

		return EvaluationFailure();
	}

	ast::Operands resultOperands = operands[0].get<ast::FunctionCall>().getOperands();

	std::sort( resultOperands.begin(), resultOperands.end(), NodeComparatorLess{} );

	return ast::Node::make<ast::FunctionCall>( operands[0].get<ast::FunctionCall>().getFunction(), resultOperands );
}

}}} //namespace tungsten::eval::builtin



