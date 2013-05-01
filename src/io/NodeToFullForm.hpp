
#ifndef IO_NODETOFULLFORMOUTPUT_HPP_
#define IO_NODETOFULLFORMOUTPUT_HPP_

#include "ast/Node.hpp"

#include <string>

namespace tungsten { namespace io {

typedef std::string FullFormString;

FullFormString NodeToFullForm(const ast::Node& node);

}} //namespace tungsten::io

#endif /* IO_NODETOFULLFORMOUTPUT_HPP_ */
