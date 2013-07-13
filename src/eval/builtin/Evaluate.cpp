
#include "functions.hpp"

namespace tungsten { namespace eval { namespace builtin {

OptionalNode Evaluate(const ast::Operands& operands, eval::SessionEnvironment& /*sessionEnvironment*/) {
	if ( operands.size() == 1 ) {
		return operands.front();
	}
	return ast::Node::make<ast::FunctionCall>(ids::Sequence, operands);
}

}}} //namespace tungsten::eval::builtin





