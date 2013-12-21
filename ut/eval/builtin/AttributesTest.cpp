
#include <boost/test/unit_test.hpp>

#include "Fixture.hpp"

BOOST_AUTO_TEST_SUITE( AttributesTest )

using namespace tungsten;

#define TUNGSTEN_ATTRIBUTES_TEST_CASE(symbol, ...) \
	BOOST_FIXTURE_TEST_CASE( test_Attributes_of_ ## symbol, BuiltinFunctionFixture ) { \
		boost::optional<ast::Node> result = parseAndEvaluate("Attributes[" #symbol "]"); \
		BOOST_REQUIRE( result ); \
		std::vector<ast::Identifier> attributes = __VA_ARGS__; \
		ast::Operands attributeOperands; \
		std::transform(attributes.begin(), attributes.end(), std::back_inserter(attributeOperands), \
		   	[](const std::string& str) { return ast::Node::make<ast::Identifier>(str); }); \
		ast::Node expected = ast::Node::make<ast::FunctionCall>("List", attributeOperands); \
		BOOST_CHECK_EQUAL( *result, expected ); \
	}

TUNGSTEN_ATTRIBUTES_TEST_CASE(List, {"Locked", "Protected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(Plus, {"Flat", "Listable", "NumericFunction", "OneIdentity", "Orderless", "Protected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(Times, {"Flat", "Listable", "NumericFunction", "OneIdentity", "Orderless", "Protected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(Power, {"Listable", "NumericFunction", "OneIdentity", "Protected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(Abs, {"Listable", "NumericFunction", "Protected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(Divide, {"Listable", "NumericFunction", "Protected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(Numerator, {"Listable", "Protected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(Denominator, {"Listable", "Protected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(Replace, {"Protected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(Set, {"HoldFirst", "Protected", "SequenceHold"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(SetDelayed, {"HoldAll", "Protected", "SequenceHold"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(RandomReal, {"Protected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(DirectedInfinity, {"Listable", "Protected", "ReadProtected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(Overflow, {"Protected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(Thread, {"Protected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(Pattern, {"HoldFirst", "Protected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(Blank, {"Protected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(Integer, {"Protected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(Rational, {"Protected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(Real, {"Protected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(String, {"Protected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(Symbol, {"Locked", "Protected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(Head, {"Protected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(Table, {"HoldAll", "Protected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(CompoundExpression, {"HoldAll", "Protected", "ReadProtected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(Minus, {"Listable", "NumericFunction", "Protected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(Subtract, {"Listable", "NumericFunction", "Protected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(Apply, {"Protected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(Sin, {"Listable", "NumericFunction", "Protected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(Cos, {"Listable", "NumericFunction", "Protected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(Tan, {"Listable", "NumericFunction", "Protected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(Cot, {"Listable", "NumericFunction", "Protected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(Csc, {"Listable", "NumericFunction", "Protected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(Sec, {"Listable", "NumericFunction", "Protected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(ArcSin, {"Listable", "NumericFunction", "Protected", "ReadProtected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(ArcCos, {"Listable", "NumericFunction", "Protected", "ReadProtected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(ArcTan, {"Listable", "NumericFunction", "Protected", "ReadProtected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(ArcCot, {"Listable", "NumericFunction", "Protected", "ReadProtected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(ArcCsc, {"Listable", "NumericFunction", "Protected", "ReadProtected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(ArcSec, {"Listable", "NumericFunction", "Protected", "ReadProtected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(Factorial, {"Listable", "NumericFunction", "Protected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(Factorial2, {"Listable", "NumericFunction", "Protected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(Sqrt, {"Listable", "NumericFunction", "Protected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(Rule, {"Protected", "SequenceHold"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(RuleDelayed, {"HoldRest", "Protected", "SequenceHold"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(Flatten, {"Protected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(Sort, {"Protected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(Normal, {"Protected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(Sequence, {"Protected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(Evaluate, {"Protected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(N, {"Protected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(NumericQ, {"Protected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(Complex, {"Protected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(OrderedQ, {"Protected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(Function, {"HoldAll", "Protected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(Slot, {"NHoldAll", "Protected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(SlotSequence, {"NHoldAll", "Protected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(Equal, {"Protected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(Unequal, {"Protected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(Less, {"Protected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(LessEqual, {"Protected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(Greater, {"Protected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(GreaterEqual, {"Protected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(If, {"HoldRest", "Protected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(TrueQ, {"Protected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(And, {"Flat", "HoldAll", "OneIdentity", "Protected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(Or, {"Flat", "HoldAll", "OneIdentity", "Protected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(Not, {"Protected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(Boole, {"Listable", "Protected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(While, {"HoldAll", "Protected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(Attributes, {"HoldAll", "Listable", "Protected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(Print, {"Protected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(Part, {"NHoldRest", "Protected", "ReadProtected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(Span, {"Protected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(Floor, {"Listable", "NumericFunction", "Protected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(Ceiling, {"Listable", "NumericFunction", "Protected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(Round, {"Listable", "NumericFunction", "Protected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(IntegerPart, {"Listable", "NumericFunction", "Protected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(FractionalPart, {"Listable", "NumericFunction", "Protected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(Hold, {"HoldAll", "Protected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(Append, {"Protected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(AppendTo, {"HoldFirst", "Protected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(Prepend, {"Protected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(PrependTo, {"HoldFirst", "Protected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(Length, {"Protected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(HoldComplete, {"HoldAllComplete", "Protected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(Range, {"Listable", "Protected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(Block, {"HoldAll", "Protected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(Map, {"Protected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(Sum, {"HoldAll", "Protected", "ReadProtected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(MatchQ, {"Protected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(HoldPattern, {"HoldAll", "Protected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(PatternTest, {"HoldRest", "Protected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(ReplaceAll, {"Protected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(ReplaceRepeated, {"Protected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(Condition, {"HoldAll", "Protected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(Verbatim, {"Protected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(Alternatives, {"Protected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(Optional, {"Protected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(Except, {"Protected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(PatternSequence, {"Protected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(Repeated, {"Protected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(RepeatedNull, {"Protected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(BlankSequence, {"Protected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(BlankNullSequence, {"Protected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(OptionsPattern, {"Protected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(Longest, {"Protected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(Shortest, {"Protected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(AbsoluteTime, {"Protected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(Reap, {"HoldFirst", "Protected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(Sow, {"Protected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(Hyperlink, {"Protected", "ReadProtected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(Plot, {"HoldAll", "Protected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(Graphics, {"Protected", "ReadProtected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(Export, {"Protected", "ReadProtected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(Circle, {"Protected", "ReadProtected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(Rectangle, {"Protected", "ReadProtected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(Red, {"Protected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(Green, {"Protected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(Blue, {"Protected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(Black, {"Protected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(White, {"Protected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(Gray, {"Protected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(Cyan, {"Protected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(Magenta, {"Protected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(Yellow, {"Protected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(Brown, {"Protected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(Orange, {"Protected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(Pink, {"Protected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(Purple, {"Protected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(LightRed, {"Protected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(LightGreen, {"Protected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(LightBlue, {"Protected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(LightGray, {"Protected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(LightCyan, {"Protected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(LightMagenta, {"Protected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(LightYellow, {"Protected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(LightBrown, {"Protected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(LightOrange, {"Protected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(LightPink, {"Protected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(LightPurple, {"Protected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(Transparent, {"Protected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(Thick, {"Protected", "ReadProtected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(Thin, {"Protected", "ReadProtected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(Dashed, {"Protected", "ReadProtected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(Dotted, {"Protected", "ReadProtected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(DotDashed, {"Protected", "ReadProtected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(Hue, {"Protected", "ReadProtected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(None, {"Protected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(RGBColor, {"Protected", "ReadProtected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(GrayLevel, {"Protected", "ReadProtected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(Thickness, {"Protected", "ReadProtected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(Disk, {"Protected", "ReadProtected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(Line, {"Protected", "ReadProtected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(Point, {"Protected", "ReadProtected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(BezierCurve, {"Protected", "ReadProtected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(Arrow, {"Protected", "ReadProtected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(Polygon, {"Protected", "ReadProtected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(Text, {"Protected", "ReadProtected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(Small, {"Protected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(Large, {"Protected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(Dashing, {"Protected", "ReadProtected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(Tiny, {"Protected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(E, {"Constant", "Protected", "ReadProtected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(Pi, {"Constant", "Protected", "ReadProtected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(Degree, {"Constant", "Protected", "ReadProtected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(GoldenRatio, {"Constant", "Protected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(EulerGamma, {"Constant", "Protected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(Catalan, {"Constant", "Protected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(Khinchin, {"Constant", "Protected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(I, {"Locked", "Protected", "ReadProtected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(Glaisher, {"Constant", "Protected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(Null, {"Protected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(Infinity, {"Protected", "ReadProtected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(ComplexInfinity, {"Protected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(Indeterminate, {"Protected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(True, {"Locked", "Protected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(False, {"Locked", "Protected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(Flat, {"Protected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(Listable, {"Protected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(NumericFunction, {"Protected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(OneIdentity, {"Protected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(Orderless, {"Protected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(Protected, {"Protected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(ReadProtected, {"Protected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(SequenceHold, {"Protected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(HoldFirst, {"Protected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(HoldRest, {"Protected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(HoldAll, {"Protected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(NHoldAll, {"Protected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(NHoldFirst, {"Protected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(NHoldRest, {"Protected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(HoldAllComplete, {"Protected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(Constant, {"Protected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(Locked, {"Protected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(General, {"Protected"})
TUNGSTEN_ATTRIBUTES_TEST_CASE(Syntax, {"Protected"})

BOOST_AUTO_TEST_SUITE_END()

