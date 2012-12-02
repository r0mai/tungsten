
#ifndef ASTPARSER_HPP_
#define ASTPARSER_HPP_

#include <string>

#include <boost/optional.hpp>

#include "AstNode.hpp"

namespace tungsten {

boost::optional<AstNode> parseInput(const std::string& input);

} //namespace tungsten

#endif /* ASTPARSER_HPP_ */
