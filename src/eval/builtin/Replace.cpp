
#include "functions.hpp"
#include "eval/SessionEnvironment.hpp"

namespace tungsten { namespace eval { namespace builtin {

OptionalNode Replace(const ast::Operands& operands, eval::SessionEnvironment& /*sessionEnvironment*/) {
	return ast::Node::make<ast::FunctionCall>( ids::Replace, operands );
}

OptionalNode ReplaceAll(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment) {
	return ast::Node::make<ast::FunctionCall>( ids::ReplaceAll, operands );
}

}}} //namespace tungsten::eval::builtin


