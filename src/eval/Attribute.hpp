
#ifndef EVAL_ATTRIBUTE_HPP_
#define EVAL_ATTRIBUTE_HPP_

#include <map>
#include <vector>

#include "ast/Identifier.hpp"

namespace tungsten { namespace eval {

typedef ast::Identifier Attribute;
typedef std::vector<Attribute> AttributeVector;
typedef std::map<ast::Identifier, AttributeVector> AttributeMap;

AttributeMap createDefaultAttributeMap();

}} //namespace tungsten::eval

#endif /* EVAL_ATTRIBUTE_HPP_ */
