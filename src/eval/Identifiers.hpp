
#ifndef EVAL_IDENTIFIERS_HPP_
#define EVAL_IDENTIFIERS_HPP_

#include "ast/Identifier.hpp"
#include "ast/String.hpp"
#include "Attribute.hpp"

//This namespace contains all the used builtin Identifier names as costant Identifers.
//TODO think about if this is the best place for this
namespace tungsten { namespace eval { namespace ids {

#define TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(x) const ast::Identifier x = #x
#define TUNGSTEN_DEFINE_CONSTANT_ATTRIBUTE(x) const Attribute x = #x
#define TUNGSTEN_DEFINE_CONSTANT_STRING(x) const ast::String x = #x

//Builtin Functions
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(List);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(Plus);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(Times);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(Power);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(Abs);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(Divide);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(Numerator);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(Denominator);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(Replace);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(Set);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(SetDelayed);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(RandomReal);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(DirectedInfinity);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(Overflow);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(Thread);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(Pattern);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(Blank);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(Integer);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(Rational);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(Real);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(String);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(Symbol);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(Head);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(Table);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(CompoundExpression);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(Minus);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(Subtract);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(Apply);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(Sin);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(Cos);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(Tan);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(Cot);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(Csc);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(Sec);

//Graphics stuff
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(Graphics);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(Circle);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(Rectangle);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(Ellipse);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(Red);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(Hue);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(Blue);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(Green);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(RGBColor);

//Builtin constants
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(Null);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(Infinity);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(Indeterminate);

//Attributes //TODO move these to Attrubte.hpp
TUNGSTEN_DEFINE_CONSTANT_ATTRIBUTE(Flat);
TUNGSTEN_DEFINE_CONSTANT_ATTRIBUTE(Listable);
TUNGSTEN_DEFINE_CONSTANT_ATTRIBUTE(NumericFunction);
TUNGSTEN_DEFINE_CONSTANT_ATTRIBUTE(OneIdentity);
TUNGSTEN_DEFINE_CONSTANT_ATTRIBUTE(Orderless);
TUNGSTEN_DEFINE_CONSTANT_ATTRIBUTE(Protected);
TUNGSTEN_DEFINE_CONSTANT_ATTRIBUTE(ReadProtected);
TUNGSTEN_DEFINE_CONSTANT_ATTRIBUTE(SequenceHold);
TUNGSTEN_DEFINE_CONSTANT_ATTRIBUTE(HoldFirst);
TUNGSTEN_DEFINE_CONSTANT_ATTRIBUTE(HoldRest);
TUNGSTEN_DEFINE_CONSTANT_ATTRIBUTE(HoldAll);

//Message symbols
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(General);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(Syntax);

//Message tags
TUNGSTEN_DEFINE_CONSTANT_STRING(argm);
TUNGSTEN_DEFINE_CONSTANT_STRING(argx);
TUNGSTEN_DEFINE_CONSTANT_STRING(argrx);
TUNGSTEN_DEFINE_CONSTANT_STRING(argt);
TUNGSTEN_DEFINE_CONSTANT_STRING(infy);
TUNGSTEN_DEFINE_CONSTANT_STRING(indet);
TUNGSTEN_DEFINE_CONSTANT_STRING(ovfl);
TUNGSTEN_DEFINE_CONSTANT_STRING(tdlen);
TUNGSTEN_DEFINE_CONSTANT_STRING(itform);
TUNGSTEN_DEFINE_CONSTANT_STRING(iterb);

#undef TUNGSTEN_DEFINE_CONSTANT_ATTRIBUTE
#undef TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER
#undef TUNGSTEN_DEFINE_CONSTANT_STRING

}}} //namespace tungsten::eval::ids

#endif /* EVAL_IDENTIFIERS_HPP_ */
