
#ifndef EVAL_GETNODEDENOMINATOR_HPP_
#define EVAL_GETNODEDENOMINATOR_HPP_

#include "ast/Node.hpp"
#include "SessionEnvironment.hpp"

namespace tungsten { namespace eval {

ast::Node getNodeDenominator(const ast::Node& node);

//There's a difference between existing && ==1 and non-existing denominator. getNodeDenominator returns 1 on both cases
//This returns an empty optional if there are really nothing in the denominator
boost::optional<ast::Node> getPrintableNodeDenominator(const ast::Node& node);

}} //namespace tungsten::eval

#endif /* EVAL_GETNODEDENOMINATOR_HPP_ */
