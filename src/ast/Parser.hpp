
#ifndef AST_PARSER_HPP_
#define AST_PARSER_HPP_

#include <string>

#include <boost/optional.hpp>

#include "Node.hpp"

namespace tungsten { namespace ast {

boost::optional<Node> parseInput(const std::string& input);

}} //namespace tungsten::ast

#endif /* AST_PARSER_HPP_ */
