
#include <boost/test/unit_test.hpp>

#include "Fixture.hpp"

BOOST_AUTO_TEST_SUITE( PlusTest )

using namespace tungsten;

BOOST_FIXTURE_TEST_CASE( empty_Plus_is_zero, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Plus[]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result, ast::Node::make<math::Rational>(0) );
}

BOOST_FIXTURE_TEST_CASE( single_argument_Plus_is_identity, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Plus[x]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result, ast::Node::make<ast::Identifier>("x") );
}

BOOST_FIXTURE_TEST_CASE( single_argument_nested_Plus_is_identity, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Plus[Plus[x]]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result, ast::Node::make<ast::Identifier>("x") );
}

BOOST_FIXTURE_TEST_CASE( one_plus_two_is_three, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("1+2");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result, ast::Node::make<math::Rational>(3) );
}

BOOST_FIXTURE_TEST_CASE( one_plus_two_plus_x_test, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("1+2+x");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result, ast::Node::make<ast::FunctionCall>("Plus", {ast::Node::make<math::Rational>(3), ast::Node::make<ast::Identifier>("x")}) );
}

BOOST_FIXTURE_TEST_CASE( x_plus_x_test, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("x+x");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result, ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<math::Rational>(2), ast::Node::make<ast::Identifier>("x")}) );
}

BOOST_FIXTURE_TEST_CASE( x_plus_x_plus_1_test, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("x+x+1");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result, ast::Node::make<ast::FunctionCall>("Plus", {ast::Node::make<math::Rational>(1),
			ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<math::Rational>(2), ast::Node::make<ast::Identifier>("x")})}) );
}

BOOST_FIXTURE_TEST_CASE( x_plus_y_test, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("x+y");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result, ast::Node::make<ast::FunctionCall>("Plus", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::Identifier>("y")}) );
}

BOOST_FIXTURE_TEST_CASE( x_plus_2x_test, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("x+2x");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result, ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<math::Rational>(3), ast::Node::make<ast::Identifier>("x")}) );
}

BOOST_FIXTURE_TEST_CASE( x_plus_2x_plus_2y_plus_y_test, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("x+2x+2y+y");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result, ast::Node::make<ast::FunctionCall>("Plus", {
			ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<math::Rational>(3), ast::Node::make<ast::Identifier>("x")}),
			ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<math::Rational>(3), ast::Node::make<ast::Identifier>("y")})}) );
}

BOOST_FIXTURE_TEST_CASE( x_minus_x_test, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("x-x");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result, ast::Node::make<math::Rational>(0) );
}

BOOST_FIXTURE_TEST_CASE( x_minus_x_minus_3_test, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("x-x-3");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result, ast::Node::make<math::Rational>(-3) );
}

BOOST_FIXTURE_TEST_CASE( y_plus_x_minus_x_plus_3_test, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("y+x-x+3");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result, ast::Node::make<ast::FunctionCall>("Plus", {ast::Node::make<math::Rational>(3), ast::Node::make<ast::Identifier>("y")}) );
}

BOOST_FIXTURE_TEST_CASE( y_plus_2x_minus_2x_plus_3_test, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("y+2x-2x+3");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result, ast::Node::make<ast::FunctionCall>("Plus", {ast::Node::make<math::Rational>(3), ast::Node::make<ast::Identifier>("y")}) );
}

BOOST_FIXTURE_TEST_CASE( Real_plus_Rational_is_real, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("3.5+1");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result, ast::Node::make<math::Real>(4.5) );
}

BOOST_FIXTURE_TEST_CASE( Rational_plus_Real_is_real, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("1+3.5");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result, ast::Node::make<math::Real>(4.5) );
}

BOOST_FIXTURE_TEST_CASE( only_Real_identifier_coefficients_is_Real, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("1.5x+1.0x");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result, ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<math::Real>(2.5), ast::Node::make<ast::Identifier>("x")}) );
}

BOOST_FIXTURE_TEST_CASE( mixed_Numeric_identifier_coefficients_is_Real, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("1.5x+2x");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result, ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<math::Real>(3.5), ast::Node::make<ast::Identifier>("x")}) );
}

BOOST_FIXTURE_TEST_CASE( real_coefficient_doesnt_alter_other_coefficients, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("1.5x+x*2+3y");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result, ast::Node::make<ast::FunctionCall>("Plus", {
			ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<math::Real>(3.5), ast::Node::make<ast::Identifier>("x")}),
			ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<math::Rational>(3), ast::Node::make<ast::Identifier>("y")})}) );
}

BOOST_FIXTURE_TEST_CASE( real_coefficient_doesnt_alter_constant, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("1.5x+2x+3");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result, ast::Node::make<ast::FunctionCall>("Plus", {
			ast::Node::make<math::Rational>(3),
			ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<math::Real>(3.5), ast::Node::make<ast::Identifier>("x")})}) );
}

BOOST_FIXTURE_TEST_CASE( complex_expression_as_variable, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("2x^2+3x^2");

	BOOST_REQUIRE( result );

	ast::Node xSquared = ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)});

	BOOST_CHECK_EQUAL( *result, ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<math::Rational>(5), xSquared}) );
}

BOOST_AUTO_TEST_SUITE_END()
