
#include "functions.hpp"
#include "eval/getNodeNumerator.hpp"

namespace tungsten { namespace eval { namespace builtin {

ast::Node Numerator(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment) {
	if ( operands.size() != 1 ) {
		//TODO issue warning
		return ast::Node::make<ast::FunctionCall>( ids::Numerator, operands );
	}

	return getNodeNumerator(operands[0], sessionEnvironment);
}

}}} //namespace tungsten::eval::builtin
