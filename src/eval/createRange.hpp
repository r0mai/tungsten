
#ifndef EVAL_CREATERANGE_HPP_
#define EVAL_CREATERANGE_HPP_

#include "ast/Node.hpp"
#include "SessionEnvironment.hpp"

namespace tungsten { namespace eval {

boost::optional<ast::Operands> createRange(const ast::Node& min, const ast::Node& max, const ast::Node& step, SessionEnvironment& sessionEnvironment);

}} //namespace tungsten::eval

#endif //EVAL_CREATERANGE_HPP_

