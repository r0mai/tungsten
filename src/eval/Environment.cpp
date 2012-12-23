
#include "Environment.hpp"

namespace tungsten { namespace eval {

Environment::Environment() {}

Environment::~Environment() {}

ast::Node Environment::evaluate(const ast::Node& node) {
	return node;
}

}} //namespace tungsten::eval


