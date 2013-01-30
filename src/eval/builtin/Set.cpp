
#include "functions.hpp"
#include "eval/getNodeNumerator.hpp"

namespace tungsten { namespace eval { namespace builtin {

ast::Node Set(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment) {
	if ( operands.size() != 2 ) {
		//TODO issue error
		return ast::Node::make<ast::FunctionCall>( ids::Set, operands );
	}

	sessionEnvironment.addPattern(operands[0], operands[1]);
	return operands[1];
}

}}} //namespace tungsten::eval::builtin

