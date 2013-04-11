
#ifndef IO_PARSER_HPP_
#define IO_PARSER_HPP_

#include <string>

#include <boost/optional.hpp>

#include "ast/Node.hpp"

namespace tungsten { namespace io {

boost::optional<ast::Node> parseInput(const std::string& input);

}} //namespace tungsten::io

#endif /* IO_PARSER_HPP_ */
