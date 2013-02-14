
#include "functions.hpp"

namespace tungsten { namespace eval { namespace builtin {

OptionalNode Replace(const ast::Operands& operands, eval::SessionEnvironment& /*sessionEnvironment*/) {
	return ast::Node::make<ast::FunctionCall>( ids::Replace, operands );
}

}}} //namespace tungsten::eval::builtin


