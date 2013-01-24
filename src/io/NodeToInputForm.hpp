
#ifndef IO_NODETOINPUTFORMOUTPUT_HPP_
#define IO_NODETOINPUTFORMOUTPUT_HPP_

#include "ast/Node.hpp"

#include <string>

namespace tungsten { namespace io {

typedef std::string InputFormString;

InputFormString NodeToInputForm(const ast::Node& node);

InputFormString NodeToInputFormRecursive(const ast::Node& node, int precedence);

}} //namespace tungsten::io

#endif /* IO_NODETOINPUTFORMOUTPUT_HPP_ */
