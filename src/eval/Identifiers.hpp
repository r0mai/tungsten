
#ifndef EVAL_IDENTIFIERS_HPP_
#define EVAL_IDENTIFIERS_HPP_

#include "ast/Identifier.hpp"
#include "Attribute.hpp"

//This namespace contains all the used builtin Identifier names as costant Identifers.
//TODO think about if this is the best place for this
namespace tungsten { namespace eval { namespace ids {

#define TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(x) const ast::Identifier x = #x
#define TUNGSTEN_DEFINE_CONSTANT_ATTRIBUTE(x) const Attribute x = #x

//Builtin Functions
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(List);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(Plus);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(Times);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(Power);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(DirectedInfinity);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(Overflow);

//Builtin constants
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(Indeterminate);


//Attributes //TODO move these to Attrubte.hpp
TUNGSTEN_DEFINE_CONSTANT_ATTRIBUTE(Flat);
TUNGSTEN_DEFINE_CONSTANT_ATTRIBUTE(Listable);
TUNGSTEN_DEFINE_CONSTANT_ATTRIBUTE(NumericFunction);
TUNGSTEN_DEFINE_CONSTANT_ATTRIBUTE(OneIdentity);
TUNGSTEN_DEFINE_CONSTANT_ATTRIBUTE(Orderless);
TUNGSTEN_DEFINE_CONSTANT_ATTRIBUTE(Protected);

#undef TUNGSTEN_DEFINE_CONSTANT_ATTRIBUTE
#undef TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER

}}} //namespace tungsten::eval::ids

#endif /* EVAL_IDENTIFIERS_HPP_ */
