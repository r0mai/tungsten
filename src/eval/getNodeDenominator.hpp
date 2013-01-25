
#ifndef EVAL_GETNODEDENOMINATOR_HPP_
#define EVAL_GETNODEDENOMINATOR_HPP_

#include "ast/Node.hpp"
#include "SessionEnvironment.hpp"

namespace tungsten { namespace eval {

ast::Node getNodeDenominator(const ast::Node& node, SessionEnvironment& sessionEnvironment);

}} //namespace tungsten::eval

#endif /* EVAL_GETNODEDENOMINATOR_HPP_ */
