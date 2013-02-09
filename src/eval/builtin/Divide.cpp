
#include "functions.hpp"
#include "eval/getNodeNumerator.hpp"

namespace tungsten { namespace eval { namespace builtin {

ast::Node Divide(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment) {
	if ( operands.size() != 2 ) {
		sessionEnvironment.raiseMessage( Message(ids::Divide, ids::argrx, {
				ast::Node::make<ast::Identifier>( ids::Divide ),
				ast::Node::make<math::Rational>( operands.size() ),
				ast::Node::make<math::Rational>( 2 )
		} ));
		return ast::Node::make<ast::FunctionCall>( ids::Divide, operands );
	}

	const ast::Node& numerator = operands[0];
	const ast::Node& denominator = operands[1];

	return sessionEnvironment.evaluate(
			ast::Node::make<ast::FunctionCall>( ids::Times, {
				numerator,
				ast::Node::make<ast::FunctionCall>( ids::Power, {
					denominator,
					ast::Node::make<math::Rational>( -1 )
				})
			})
	);
}

}}} //namespace tungsten::eval::builtin


