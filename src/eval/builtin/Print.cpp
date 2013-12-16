
#include "functions.hpp"
#include "eval/SessionEnvironment.hpp"

namespace tungsten { namespace eval { namespace builtin {

OptionalNode Print(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment) {
	sessionEnvironment.printToStdout( operands );
	return ast::Node::make<ast::Identifier>( ids::Null );
}

}}} //namespace tungsten::eval::builtin


