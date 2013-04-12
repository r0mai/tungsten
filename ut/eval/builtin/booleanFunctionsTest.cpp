
#include <boost/test/unit_test.hpp>

#include "Fixture.hpp"

BOOST_AUTO_TEST_SUITE( BooleanFunctionsTest )

using namespace tungsten;

BOOST_FIXTURE_TEST_CASE( test_TrueQ_of_True, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("TrueQ[True]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::Identifier>("True");

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_TrueQ_of_False, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("TrueQ[False]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::Identifier>("False");

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_TrueQ_of_x, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("TrueQ[x]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::Identifier>("False");

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_TrueQ_of_the_list_True, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("TrueQ[{True}]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::Identifier>("False");

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_not_True, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate(" !True");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::Identifier>("False");

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_not_False, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate(" !False");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::Identifier>("True");

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_not_x, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate(" !x");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("Not", {ast::Node::make<ast::Identifier>("x")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_not_not_x, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate(" !( !x)");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::Identifier>("x");

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_not_not_not_x, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate(" !( !( !x))");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("Not", {ast::Node::make<ast::Identifier>("x")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_not_a_is_greater_than_b, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate(" !a > b");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("LessEqual", {ast::Node::make<ast::Identifier>("a"), ast::Node::make<ast::Identifier>("b")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_not_a_is_less_than_b, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate(" !a < b");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("GreaterEqual", {ast::Node::make<ast::Identifier>("a"), ast::Node::make<ast::Identifier>("b")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_not_a_is_greater_than_or_equal_to_b, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate(" !a >= b");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("Less", {ast::Node::make<ast::Identifier>("a"), ast::Node::make<ast::Identifier>("b")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_not_a_is_less_than_or_equal_to_b, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate(" !a <= b");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("Greater", {ast::Node::make<ast::Identifier>("a"), ast::Node::make<ast::Identifier>("b")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_not_a_equals_equals_b, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate(" !a == b");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("Unequal", {ast::Node::make<ast::Identifier>("a"), ast::Node::make<ast::Identifier>("b")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_not_a_is_not_equal_to_b, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate(" !a != b");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("Equal", {ast::Node::make<ast::Identifier>("a"), ast::Node::make<ast::Identifier>("b")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_1_if_False_is_true_and_0_otherwise, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Boole[False]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<math::Rational>(0);

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_1_if_True_is_true_and_0_otherwise, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Boole[True]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<math::Rational>(1);

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_1_if_x_is_true_and_0_otherwise, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Boole[x]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("Boole", {ast::Node::make<ast::Identifier>("x")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_1_if_the_list_True__False__x_is_true_and_0_otherwise, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Boole[{True, False, x}]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<math::Rational>(1), ast::Node::make<math::Rational>(0), ast::Node::make<ast::FunctionCall>("Boole", {ast::Node::make<ast::Identifier>("x")})});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_2_is_greater_than_1_and_Pi_is_greater_than_3, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("2 > 1 && Pi > 3");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::Identifier>("True");

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_x_and_the_quantity_y_and_z, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("x && (y && z)");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("And", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::Identifier>("y"), ast::Node::make<ast::Identifier>("z")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_the_quantity_x_and_y_or_z, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("(x && y) || z");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("Or", {ast::Node::make<ast::FunctionCall>("And", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::Identifier>("y")}), ast::Node::make<ast::Identifier>("z")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_x_or_the_quantity_y_and_z, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("x || (y && z)");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("Or", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::FunctionCall>("And", {ast::Node::make<ast::Identifier>("y"), ast::Node::make<ast::Identifier>("z")})});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_True_and_False, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("True && False");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::Identifier>("False");

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_True_and_x, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("True && x");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::Identifier>("x");

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_And_of_no_arguments, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("And[]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::Identifier>("True");

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Or_of_no_arguments, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Or[]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::Identifier>("False");

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_And_of_x, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("And[x]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::Identifier>("x");

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Or_of_x, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Or[x]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::Identifier>("x");

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_False_or_True, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("False || True");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::Identifier>("True");

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_True_or_False, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("True || False");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::Identifier>("True");

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_False_and_x, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("False && x");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::Identifier>("False");

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_True_and_True_and_x_and_y_and_False, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("True && True && x && y && False");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::Identifier>("False");

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_False_or_the_quantity_False_and_x_and_y_and_True, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("False || (False && x && y && True)");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::Identifier>("False");

	BOOST_CHECK_EQUAL( *result, expected );
}

BOOST_FIXTURE_TEST_CASE( test_x_and_True_and_y, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("x && True && y");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("And", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::Identifier>("y")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_x_or_False_or_y, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("x || False || y");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("Or", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::Identifier>("y")});

	BOOST_CHECK_EQUAL( *result, expected );
}





BOOST_AUTO_TEST_SUITE_END()

