
#include "functions.hpp"
#include "eval/SessionEnvironment.hpp"

namespace tungsten { namespace eval { namespace builtin {

ast::Node SetDelayed(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment) {
	if ( operands.size() != 2 ) {
		//TODO issue error
		return ast::Node::make<ast::FunctionCall>( ids::SetDelayed, operands );
	}

	sessionEnvironment.addPattern(operands[0], operands[1]);
	return ast::Node::make<ast::Identifier>(ids::Null);
}

}}} //namespace tungsten::eval::builtin
