

#ifndef EVAL_NUMERICNODEEVALUATION_HPP_
#define EVAL_NUMERICNODEEVALUATION_HPP_

#include <boost/optional.hpp>

#include "ast/Node.hpp"
#include "SessionEnvironment.hpp"

namespace tungsten { namespace eval {

//TODO function naming, ehh
ast::Node numericNodeEvaluation(const ast::Node& node, eval::SessionEnvironment& sessionEnvironment);

}} //namespace tungsten::eval

#endif /* EVAL_NUMERICNODEEVALUATION_HPP_ */
