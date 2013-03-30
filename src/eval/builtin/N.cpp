
#include "functions.hpp"

namespace tungsten { namespace eval { namespace builtin {

OptionalNode N(const ast::Operands& operands, eval::SessionEnvironment& /*sessionEnvironment*/) {
	return ast::Node::make<ast::FunctionCall>( ids::N, operands );
}

}}} //namespace tungsten::eval::builtin





