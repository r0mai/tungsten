
#ifndef IO_NODETOTEXFORM_HPP_
#define IO_NODETOTEXFORM_HPP_

#include <string>

#include "ast/Node.hpp"
#include "eval/SessionEnvironment.hpp"

namespace tungsten { namespace io {

typedef std::string TeXFormString;

TeXFormString NodeToTeXForm(const ast::Node& node);

TeXFormString NodeToTeXFormRecursive(const ast::Node& node, int precedence);

}} //namespace tungsten::io

#endif /* IO_NODETOTEXFORM_HPP_ */
