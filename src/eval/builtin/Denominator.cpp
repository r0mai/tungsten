
#include "functions.hpp"
#include "eval/getNodeDenominator.hpp"

namespace tungsten { namespace eval { namespace builtin {

ast::Node Denominator(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment) {
	if ( operands.size() != 1 ) {
		//TODO issue warning
		return ast::Node::make<ast::FunctionCall>( ids::Denominator, operands );
	}

	return getNodeDenominator(operands[0], sessionEnvironment);
}

}}} //namespace tungsten::eval::builtin
