

#ifndef EVAL_FLATTENOPERANDS_HPP_
#define EVAL_FLATTENOPERANDS_HPP_

#include "ast/Node.hpp"

namespace tungsten { namespace eval {

ast::Operands flattenOperands(const ast::Identifier& function, const ast::Operands& operands);

}} //namespace tungsten::eval

#endif /* EVAL_FLATTENOPERANDS_HPP_ */
