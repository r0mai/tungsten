
#include "functions.hpp"
#include "eval/getNodeNumerator.hpp"
#include "eval/getHead.hpp"

namespace tungsten { namespace eval { namespace builtin {

ast::Node Head(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment) {
	if ( operands.size() != 1 ) {
		sessionEnvironment.raiseMessage( Message(ids::Head, ids::argx, {
				ast::Node::make<ast::Identifier>( ids::Head ),
				ast::Node::make<math::Rational>( operands.size() )
		} ));
		return ast::Node::make<ast::FunctionCall>( ids::Head, operands );
	}
	return getHead( operands[0] );
}

}}} //namespace tungsten::eval::builtin


