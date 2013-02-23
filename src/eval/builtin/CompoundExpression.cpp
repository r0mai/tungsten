
#include "functions.hpp"

namespace tungsten { namespace eval { namespace builtin {

OptionalNode CompoundExpression(const ast::Operands& operands, eval::SessionEnvironment& /*sessionEnvironment*/) {
	if ( operands.empty() ) {
		return ast::Node::make<ast::Identifier>(ids::Null);
	}
	return operands.back();
}

}}} //namespace tungsten::eval::builtin

