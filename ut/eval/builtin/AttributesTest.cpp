
#include <boost/test/unit_test.hpp>

#include "Fixture.hpp"

BOOST_AUTO_TEST_SUITE( AttributesTest )

using namespace tungsten;
BOOST_FIXTURE_TEST_CASE( test_Attributes_of_List, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[List]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("Locked"), ast::Node::make<ast::Identifier>("Protected")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_Plus, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[Plus]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("Flat"), ast::Node::make<ast::Identifier>("Listable"), ast::Node::make<ast::Identifier>("NumericFunction"), ast::Node::make<ast::Identifier>("OneIdentity"), ast::Node::make<ast::Identifier>("Orderless"), ast::Node::make<ast::Identifier>("Protected")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_Times, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[Times]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("Flat"), ast::Node::make<ast::Identifier>("Listable"), ast::Node::make<ast::Identifier>("NumericFunction"), ast::Node::make<ast::Identifier>("OneIdentity"), ast::Node::make<ast::Identifier>("Orderless"), ast::Node::make<ast::Identifier>("Protected")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_Power, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[Power]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("Listable"), ast::Node::make<ast::Identifier>("NumericFunction"), ast::Node::make<ast::Identifier>("OneIdentity"), ast::Node::make<ast::Identifier>("Protected")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_Abs, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[Abs]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("Listable"), ast::Node::make<ast::Identifier>("NumericFunction"), ast::Node::make<ast::Identifier>("Protected")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_Divide, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[Divide]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("Listable"), ast::Node::make<ast::Identifier>("NumericFunction"), ast::Node::make<ast::Identifier>("Protected")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_Numerator, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[Numerator]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("Listable"), ast::Node::make<ast::Identifier>("Protected")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_Denominator, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[Denominator]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("Listable"), ast::Node::make<ast::Identifier>("Protected")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_Replace, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[Replace]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("Protected")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_Set, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[Set]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("HoldFirst"), ast::Node::make<ast::Identifier>("Protected"), ast::Node::make<ast::Identifier>("SequenceHold")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_SetDelayed, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[SetDelayed]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("HoldAll"), ast::Node::make<ast::Identifier>("Protected"), ast::Node::make<ast::Identifier>("SequenceHold")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_RandomReal, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[RandomReal]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("Protected")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_DirectedInfinity, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[DirectedInfinity]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("Listable"), ast::Node::make<ast::Identifier>("Protected"), ast::Node::make<ast::Identifier>("ReadProtected")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_Overflow, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[Overflow]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("Protected")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_Thread, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[Thread]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("Protected")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_Pattern, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[Pattern]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("HoldFirst"), ast::Node::make<ast::Identifier>("Protected")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_Blank, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[Blank]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("Protected")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_Integer, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[Integer]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("Protected")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_Rational, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[Rational]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("Protected")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_Real, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[Real]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("Protected")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_String, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[String]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("Protected")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_Symbol, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[Symbol]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("Locked"), ast::Node::make<ast::Identifier>("Protected")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_Head, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[Head]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("Protected")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_Table, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[Table]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("HoldAll"), ast::Node::make<ast::Identifier>("Protected")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_CompoundExpression, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[CompoundExpression]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("HoldAll"), ast::Node::make<ast::Identifier>("Protected"), ast::Node::make<ast::Identifier>("ReadProtected")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_Minus, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[Minus]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("Listable"), ast::Node::make<ast::Identifier>("NumericFunction"), ast::Node::make<ast::Identifier>("Protected")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_Subtract, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[Subtract]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("Listable"), ast::Node::make<ast::Identifier>("NumericFunction"), ast::Node::make<ast::Identifier>("Protected")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_Apply, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[Apply]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("Protected")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_sine, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[Sin]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("Listable"), ast::Node::make<ast::Identifier>("NumericFunction"), ast::Node::make<ast::Identifier>("Protected")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_cosine, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[Cos]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("Listable"), ast::Node::make<ast::Identifier>("NumericFunction"), ast::Node::make<ast::Identifier>("Protected")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_tangent, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[Tan]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("Listable"), ast::Node::make<ast::Identifier>("NumericFunction"), ast::Node::make<ast::Identifier>("Protected")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_cotangent, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[Cot]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("Listable"), ast::Node::make<ast::Identifier>("NumericFunction"), ast::Node::make<ast::Identifier>("Protected")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_cosecant, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[Csc]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("Listable"), ast::Node::make<ast::Identifier>("NumericFunction"), ast::Node::make<ast::Identifier>("Protected")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_secant, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[Sec]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("Listable"), ast::Node::make<ast::Identifier>("NumericFunction"), ast::Node::make<ast::Identifier>("Protected")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_arc_sine, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[ArcSin]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("Listable"), ast::Node::make<ast::Identifier>("NumericFunction"), ast::Node::make<ast::Identifier>("Protected"), ast::Node::make<ast::Identifier>("ReadProtected")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_arc_cosine, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[ArcCos]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("Listable"), ast::Node::make<ast::Identifier>("NumericFunction"), ast::Node::make<ast::Identifier>("Protected"), ast::Node::make<ast::Identifier>("ReadProtected")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_arc_tangent, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[ArcTan]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("Listable"), ast::Node::make<ast::Identifier>("NumericFunction"), ast::Node::make<ast::Identifier>("Protected"), ast::Node::make<ast::Identifier>("ReadProtected")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_arc_cotangent, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[ArcCot]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("Listable"), ast::Node::make<ast::Identifier>("NumericFunction"), ast::Node::make<ast::Identifier>("Protected"), ast::Node::make<ast::Identifier>("ReadProtected")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_arc_cosecant, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[ArcCsc]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("Listable"), ast::Node::make<ast::Identifier>("NumericFunction"), ast::Node::make<ast::Identifier>("Protected"), ast::Node::make<ast::Identifier>("ReadProtected")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_arc_secant, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[ArcSec]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("Listable"), ast::Node::make<ast::Identifier>("NumericFunction"), ast::Node::make<ast::Identifier>("Protected"), ast::Node::make<ast::Identifier>("ReadProtected")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_Factorial, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[Factorial]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("Listable"), ast::Node::make<ast::Identifier>("NumericFunction"), ast::Node::make<ast::Identifier>("Protected")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_Factorial2, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[Factorial2]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("Listable"), ast::Node::make<ast::Identifier>("NumericFunction"), ast::Node::make<ast::Identifier>("Protected")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_square_root, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[Sqrt]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("Listable"), ast::Node::make<ast::Identifier>("NumericFunction"), ast::Node::make<ast::Identifier>("Protected")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_Rule, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[Rule]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("Protected"), ast::Node::make<ast::Identifier>("SequenceHold")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_RuleDelayed, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[RuleDelayed]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("HoldRest"), ast::Node::make<ast::Identifier>("Protected"), ast::Node::make<ast::Identifier>("SequenceHold")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_Flatten, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[Flatten]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("Protected")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_Sort, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[Sort]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("Protected")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_Normal, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[Normal]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("Protected")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_Sequence, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[Sequence]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("Protected")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_Evaluate, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[Evaluate]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("Protected")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_N, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[N]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("Protected")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_NumericQ, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[NumericQ]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("Protected")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_Complex, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[Complex]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("Protected")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_OrderedQ, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[OrderedQ]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("Protected")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_Function, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[Function]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("HoldAll"), ast::Node::make<ast::Identifier>("Protected")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_Slot, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[Slot]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("NHoldAll"), ast::Node::make<ast::Identifier>("Protected")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_SlotSequence, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[SlotSequence]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("NHoldAll"), ast::Node::make<ast::Identifier>("Protected")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_Equal, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[Equal]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("Protected")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_Unequal, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[Unequal]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("Protected")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_Less, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[Less]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("Protected")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_LessEqual, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[LessEqual]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("Protected")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_Greater, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[Greater]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("Protected")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_GreaterEqual, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[GreaterEqual]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("Protected")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_If, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[If]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("HoldRest"), ast::Node::make<ast::Identifier>("Protected")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_TrueQ, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[TrueQ]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("Protected")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_And, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[And]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("Flat"), ast::Node::make<ast::Identifier>("HoldAll"), ast::Node::make<ast::Identifier>("OneIdentity"), ast::Node::make<ast::Identifier>("Protected")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_Or, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[Or]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("Flat"), ast::Node::make<ast::Identifier>("HoldAll"), ast::Node::make<ast::Identifier>("OneIdentity"), ast::Node::make<ast::Identifier>("Protected")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_Not, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[Not]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("Protected")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_Boole, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[Boole]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("Listable"), ast::Node::make<ast::Identifier>("Protected")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_While, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[While]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("HoldAll"), ast::Node::make<ast::Identifier>("Protected")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_Attributes, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[Attributes]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("HoldAll"), ast::Node::make<ast::Identifier>("Listable"), ast::Node::make<ast::Identifier>("Protected")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_Print, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[Print]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("Protected")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_Part, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[Part]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("NHoldRest"), ast::Node::make<ast::Identifier>("Protected"), ast::Node::make<ast::Identifier>("ReadProtected")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_Span, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[Span]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("Protected")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_Floor, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[Floor]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("Listable"), ast::Node::make<ast::Identifier>("NumericFunction"), ast::Node::make<ast::Identifier>("Protected")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_Ceiling, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[Ceiling]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("Listable"), ast::Node::make<ast::Identifier>("NumericFunction"), ast::Node::make<ast::Identifier>("Protected")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_Round, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[Round]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("Listable"), ast::Node::make<ast::Identifier>("NumericFunction"), ast::Node::make<ast::Identifier>("Protected")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_IntegerPart, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[IntegerPart]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("Listable"), ast::Node::make<ast::Identifier>("NumericFunction"), ast::Node::make<ast::Identifier>("Protected")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_FractionalPart, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[FractionalPart]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("Listable"), ast::Node::make<ast::Identifier>("NumericFunction"), ast::Node::make<ast::Identifier>("Protected")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_Hold, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[Hold]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("HoldAll"), ast::Node::make<ast::Identifier>("Protected")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_Append, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[Append]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("Protected")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_AppendTo, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[AppendTo]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("HoldFirst"), ast::Node::make<ast::Identifier>("Protected")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_Prepend, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[Prepend]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("Protected")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_PrependTo, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[PrependTo]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("HoldFirst"), ast::Node::make<ast::Identifier>("Protected")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_Length, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[Length]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("Protected")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_HoldComplete, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[HoldComplete]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("HoldAllComplete"), ast::Node::make<ast::Identifier>("Protected")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_Plot, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[Plot]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("HoldAll"), ast::Node::make<ast::Identifier>("Protected")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_Graphics, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[Graphics]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("Protected"), ast::Node::make<ast::Identifier>("ReadProtected")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_Export, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[Export]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("Protected"), ast::Node::make<ast::Identifier>("ReadProtected")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_Circle, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[Circle]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("Protected"), ast::Node::make<ast::Identifier>("ReadProtected")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_Rectangle, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[Rectangle]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("Protected"), ast::Node::make<ast::Identifier>("ReadProtected")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_Red, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[Red]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("Protected")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_Hue, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[Hue]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("Protected"), ast::Node::make<ast::Identifier>("ReadProtected")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_Blue, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[Blue]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("Protected")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_Green, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[Green]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("Protected")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_Black, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[Black]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("Protected")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_White, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[White]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("Protected")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_None, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[None]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("Protected")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_RGBColor, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[RGBColor]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("Protected"), ast::Node::make<ast::Identifier>("ReadProtected")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_Gray, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[Gray]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("Protected")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_Cyan, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[Cyan]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("Protected")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_Magenta, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[Magenta]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("Protected")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_Yellow, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[Yellow]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("Protected")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_Brown, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[Brown]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("Protected")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_Orange, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[Orange]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("Protected")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_Pink, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[Pink]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("Protected")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_Purple, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[Purple]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("Protected")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_Thick, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[Thick]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("Protected"), ast::Node::make<ast::Identifier>("ReadProtected")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_Thin, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[Thin]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("Protected"), ast::Node::make<ast::Identifier>("ReadProtected")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_Thickness, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[Thickness]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("Protected"), ast::Node::make<ast::Identifier>("ReadProtected")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_Disk, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[Disk]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("Protected"), ast::Node::make<ast::Identifier>("ReadProtected")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_Line, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[Line]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("Protected"), ast::Node::make<ast::Identifier>("ReadProtected")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_Point, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[Point]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("Protected"), ast::Node::make<ast::Identifier>("ReadProtected")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_BezierCurve, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[BezierCurve]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("Protected"), ast::Node::make<ast::Identifier>("ReadProtected")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_Arrow, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[Arrow]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("Protected"), ast::Node::make<ast::Identifier>("ReadProtected")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_Polygon, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[Polygon]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("Protected"), ast::Node::make<ast::Identifier>("ReadProtected")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_E, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[E]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("Constant"), ast::Node::make<ast::Identifier>("Protected"), ast::Node::make<ast::Identifier>("ReadProtected")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_Pi, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[Pi]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("Constant"), ast::Node::make<ast::Identifier>("Protected"), ast::Node::make<ast::Identifier>("ReadProtected")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_Degree, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[Degree]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("Constant"), ast::Node::make<ast::Identifier>("Protected"), ast::Node::make<ast::Identifier>("ReadProtected")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_GoldenRatio, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[GoldenRatio]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("Constant"), ast::Node::make<ast::Identifier>("Protected")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_EulerGamma, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[EulerGamma]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("Constant"), ast::Node::make<ast::Identifier>("Protected")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_Catalan, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[Catalan]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("Constant"), ast::Node::make<ast::Identifier>("Protected")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_Khinchin, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[Khinchin]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("Constant"), ast::Node::make<ast::Identifier>("Protected")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_I, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[I]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("Locked"), ast::Node::make<ast::Identifier>("Protected"), ast::Node::make<ast::Identifier>("ReadProtected")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_Glaisher, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[Glaisher]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("Constant"), ast::Node::make<ast::Identifier>("Protected")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_Null, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[Null]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("Protected")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_infinity, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[Infinity]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("Protected"), ast::Node::make<ast::Identifier>("ReadProtected")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_Indeterminate, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[Indeterminate]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("Protected")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_True, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[True]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("Locked"), ast::Node::make<ast::Identifier>("Protected")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_False, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[False]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("Locked"), ast::Node::make<ast::Identifier>("Protected")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_Flat, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[Flat]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("Protected")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_Listable, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[Listable]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("Protected")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_NumericFunction, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[NumericFunction]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("Protected")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_OneIdentity, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[OneIdentity]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("Protected")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_Orderless, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[Orderless]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("Protected")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_Protected, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[Protected]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("Protected")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_ReadProtected, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[ReadProtected]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("Protected")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_SequenceHold, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[SequenceHold]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("Protected")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_HoldFirst, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[HoldFirst]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("Protected")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_HoldRest, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[HoldRest]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("Protected")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_HoldAll, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[HoldAll]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("Protected")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_NHoldAll, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[NHoldAll]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("Protected")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_NHoldFirst, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[NHoldFirst]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("Protected")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_NHoldRest, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[NHoldRest]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("Protected")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_HoldAllComplete, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[HoldAllComplete]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("Protected")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_General, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[General]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("Protected")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_Syntax, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[Syntax]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("Protected")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_Range, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[Range]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("Listable"), ast::Node::make<ast::Identifier>("Protected")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_Block, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[Block]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("HoldAll"), ast::Node::make<ast::Identifier>("Protected")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_Map, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[Map]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("Protected")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_MatchQ, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[MatchQ]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("Protected")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_PatternTest, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[PatternTest]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("HoldRest"), ast::Node::make<ast::Identifier>("Protected")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_HoldPattern, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[HoldPattern]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("HoldAll"), ast::Node::make<ast::Identifier>("Protected")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_ReplaceAll, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[ReplaceAll]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("Protected")});

	BOOST_CHECK_EQUAL( *result, expected );
}

BOOST_AUTO_TEST_SUITE_END()

