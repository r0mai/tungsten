
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
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(ArcSin);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(ArcCos);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(ArcTan);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(ArcCot);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(ArcCsc);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(ArcSec);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(Factorial);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(Factorial2);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(Sqrt);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(Rule);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(RuleDelayed);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(Flatten);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(Sort);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(Normal);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(Sequence);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(Evaluate);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(N);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(NumericQ);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(Complex);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(OrderedQ);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(Function);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(Slot);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(SlotSequence);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(Equal);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(Unequal);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(Less);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(LessEqual);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(Greater);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(GreaterEqual);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(If);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(TrueQ);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(And);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(Or);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(Not);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(Boole);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(While);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(Attributes);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(Print);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(Part);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(Span);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(Floor);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(Ceiling);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(Round);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(IntegerPart);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(FractionalPart);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(Hold);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(Append);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(AppendTo);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(Prepend);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(PrependTo);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(Length);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(HoldComplete);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(Range);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(Block);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(Map);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(Sum);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(MatchQ);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(HoldPattern);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(PatternTest);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(ReplaceAll);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(ReplaceRepeated);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(Condition);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(Verbatim);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(Alternatives);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(Optional);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(Except);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(PatternSequence);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(Repeated);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(RepeatedNull);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(BlankSequence);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(BlankNullSequence);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(OptionsPattern);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(Longest);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(Shortest);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(AbsoluteTime);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(Reap);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(Sow);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(Timing);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(ByteCount);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(StringLength);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(StringJoin);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(Characters);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(StringDrop);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(StringTake);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(StringInsert);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(StringReverse);

//Graphics stuff
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(FindDivisions);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(Hyperlink);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(Plot);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(Graphics);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(Export);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(Circle);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(Rectangle);

TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(Red);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(Green);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(Blue);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(Black);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(White);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(Gray);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(Cyan);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(Magenta);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(Yellow);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(Brown);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(Orange);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(Pink);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(Purple);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(LightRed);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(LightGreen);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(LightBlue);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(LightGray);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(LightCyan);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(LightMagenta);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(LightYellow);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(LightBrown);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(LightOrange);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(LightPink);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(LightPurple);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(Transparent);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(Thick);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(Thin);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(Dashed);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(Dotted);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(DotDashed);

TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(Hue);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(None);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(RGBColor);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(GrayLevel);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(Thickness);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(Disk);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(Line);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(Point);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(BezierCurve);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(Arrow);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(Polygon);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(Text);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(Small);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(Large);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(Dashing);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(Tiny);

//Builtin mathematical constants
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(E);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(Pi);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(Degree);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(GoldenRatio);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(EulerGamma);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(Catalan);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(Khinchin);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(I);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(Glaisher);

//Builtin other constants
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(Null);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(Infinity);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(ComplexInfinity);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(Indeterminate);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(True);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(False);

//Attributes //TODO move these to Attribute.hpp
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
TUNGSTEN_DEFINE_CONSTANT_ATTRIBUTE(NHoldAll);
TUNGSTEN_DEFINE_CONSTANT_ATTRIBUTE(NHoldFirst);
TUNGSTEN_DEFINE_CONSTANT_ATTRIBUTE(NHoldRest);
TUNGSTEN_DEFINE_CONSTANT_ATTRIBUTE(HoldAllComplete);
TUNGSTEN_DEFINE_CONSTANT_ATTRIBUTE(Constant);
TUNGSTEN_DEFINE_CONSTANT_ATTRIBUTE(Locked);

//Message symbols
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(General);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(Syntax);

//Message tags
TUNGSTEN_DEFINE_CONSTANT_STRING(argm);
TUNGSTEN_DEFINE_CONSTANT_STRING(argx);
TUNGSTEN_DEFINE_CONSTANT_STRING(argrx);
TUNGSTEN_DEFINE_CONSTANT_STRING(argt);
TUNGSTEN_DEFINE_CONSTANT_STRING(argb);
TUNGSTEN_DEFINE_CONSTANT_STRING(argbu);
TUNGSTEN_DEFINE_CONSTANT_STRING(infy);
TUNGSTEN_DEFINE_CONSTANT_STRING(indet);
TUNGSTEN_DEFINE_CONSTANT_STRING(ovfl);
TUNGSTEN_DEFINE_CONSTANT_STRING(tdlen);
TUNGSTEN_DEFINE_CONSTANT_STRING(itform);
TUNGSTEN_DEFINE_CONSTANT_STRING(iterb);
TUNGSTEN_DEFINE_CONSTANT_STRING(normal);
TUNGSTEN_DEFINE_CONSTANT_STRING(flev);
TUNGSTEN_DEFINE_CONSTANT_STRING(slot);
TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER(fdargs);
TUNGSTEN_DEFINE_CONSTANT_STRING(ssle);
TUNGSTEN_DEFINE_CONSTANT_STRING(pspec);
TUNGSTEN_DEFINE_CONSTANT_STRING(partd);
TUNGSTEN_DEFINE_CONSTANT_STRING(partw);
TUNGSTEN_DEFINE_CONSTANT_STRING(lvlist);
TUNGSTEN_DEFINE_CONSTANT_STRING(lvsym);
TUNGSTEN_DEFINE_CONSTANT_STRING(lvset);
TUNGSTEN_DEFINE_CONSTANT_STRING(patvar);
TUNGSTEN_DEFINE_CONSTANT_STRING(rmix);
TUNGSTEN_DEFINE_CONSTANT_STRING(reps);
TUNGSTEN_DEFINE_CONSTANT_STRING(string);
TUNGSTEN_DEFINE_CONSTANT_STRING(strse);
TUNGSTEN_DEFINE_CONSTANT_STRING(mseqs);
TUNGSTEN_DEFINE_CONSTANT_STRING(drop);
TUNGSTEN_DEFINE_CONSTANT_STRING(take);
TUNGSTEN_DEFINE_CONSTANT_STRING(write);
TUNGSTEN_DEFINE_CONSTANT_STRING(setraw);
TUNGSTEN_DEFINE_CONSTANT_STRING(wrsym);

#undef TUNGSTEN_DEFINE_CONSTANT_ATTRIBUTE
#undef TUNGSTEN_DEFINE_CONSTANT_IDENTIFIER
#undef TUNGSTEN_DEFINE_CONSTANT_STRING

}}} //namespace tungsten::eval::ids

#endif /* EVAL_IDENTIFIERS_HPP_ */
