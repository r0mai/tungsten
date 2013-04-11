
#include <boost/test/unit_test.hpp>

#include "Fixture.hpp"

BOOST_AUTO_TEST_SUITE( AttributesTest )

using namespace tungsten;

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


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_Divide, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[Divide]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("Listable"), ast::Node::make<ast::Identifier>("NumericFunction"), ast::Node::make<ast::Identifier>("Protected")});

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


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_Flatten, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[Flatten]");

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


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_If, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[If]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("HoldRest"), ast::Node::make<ast::Identifier>("Protected")});

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

BOOST_FIXTURE_TEST_CASE( test_Attributes_of_square_root, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[Sqrt]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("Listable"), ast::Node::make<ast::Identifier>("NumericFunction"), ast::Node::make<ast::Identifier>("Protected")});

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


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_secant, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[Sec]");

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


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_Sort, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[Sort]");

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


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_Greater, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[Greater]");

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


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_GreaterEqual, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[GreaterEqual]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("Protected")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_TrueQ, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[TrueQ]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("Protected")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_Not, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[Not]");

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


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_Boole, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[Boole]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("Listable"), ast::Node::make<ast::Identifier>("Protected")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Attributes_of_Plot, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Attributes[Plot]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("HoldAll"), ast::Node::make<ast::Identifier>("Protected")});

	BOOST_CHECK_EQUAL( *result, expected );
}




BOOST_AUTO_TEST_SUITE_END()




