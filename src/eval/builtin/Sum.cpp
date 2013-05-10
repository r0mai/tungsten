
#include "functions.hpp"
#include "eval/SessionEnvironment.hpp"
#include "eval/IterationSpecifier.hpp"
#include "eval/createRange.hpp"

#include <algorithm>
#include <cassert>

#include <boost/scope_exit.hpp>

namespace tungsten { namespace eval { namespace builtin {

OptionalNode Sum(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment) {
	return sessionEnvironment.evaluate(ast::Node::make<ast::FunctionCall>(eval::ids::Apply, {
				ast::Node::make<ast::Identifier>(eval::ids::Plus),
				ast::Node::make<ast::FunctionCall>(eval::ids::Table, operands)
			}));
}
}}} //namespace tungsten::eval::builtin
