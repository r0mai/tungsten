
#include <boost/test/unit_test.hpp>

#include "Fixture.hpp"

BOOST_AUTO_TEST_SUITE( AttributesTest )

using namespace tungsten;

BOOST_FIXTURE_TEST_CASE( test_x_colon_equals_3_semicolon_x, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("x := 3; x");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<math::Rational>(3);

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_x_equals_3_semicolon_x, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("x = 3; x");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<math::Rational>(3);

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_f1_of_the_pattern_a_blank_colon_equals_a_squared_semicolon_the_list_f1_of_2__f1_of_a__f1_of_no_arguments, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("f1[a_] := a^2; {f1[2], f1[a], f1[]}");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<math::Rational>(4), ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("a"), ast::Node::make<math::Rational>(2)}), ast::Node::make<ast::FunctionCall>("f1", {})});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_f2_of_the_pattern_a_blank_Integer_colon_equals_a_squared_semicolon_the_list_f2_of_2__f2_of_a__f2_of_no_arguments, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("f2[a_Integer] := a^2; {f2[2], f2[a], f2[]}");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<math::Rational>(4), ast::Node::make<ast::FunctionCall>("f2", {ast::Node::make<ast::Identifier>("a")}), ast::Node::make<ast::FunctionCall>("f2", {})});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_f3_of_the_pattern_a_blank_equals_a_squared_semicolon_the_list_f3_of_2__f3_of_a__f3_of_no_arguments, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("f3[a_] = a^2; {f3[2], f3[a], f3[]}");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<math::Rational>(4), ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("a"), ast::Node::make<math::Rational>(2)}), ast::Node::make<ast::FunctionCall>("f3", {})});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_f1_of_the_quantity_the_pattern_x_blank_with_condition_x_is_greater_than_0_colon_equals_x_squared_semicolon_the_list_f1_of_3__f1_of_minus_3__f1_of_x, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("f1[x_ /; x > 0] := x^2; {f1[3], f1[-3], f1[x]}");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<math::Rational>(9), ast::Node::make<ast::FunctionCall>("f1", {ast::Node::make<math::Rational>(-3)}), ast::Node::make<ast::FunctionCall>("f1", {ast::Node::make<ast::Identifier>("x")})});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_AUTO_TEST_SUITE_END()

