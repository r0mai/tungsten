
//Name should be FunctionTest.cpp, but that sounds strange ;)

#include <boost/test/unit_test.hpp>

#include "Fixture.hpp"

BOOST_AUTO_TEST_SUITE( MinusTest )

using namespace tungsten;


BOOST_FIXTURE_TEST_CASE( test_the_pure_function_hash_of_x, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("(#1 & )[x]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::Identifier>("x");

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_f_equals_the_pure_function_3_plus_hash_semicolon_the_list_f_of_1__f_of_minus_1, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("f = 3 + #1 & ; {f[1], f[-1]}");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<math::Rational>(4), ast::Node::make<math::Rational>(2)});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_the_pure_function_hash_squared_plus_hash_2_to_the_4th_power_of_x_and_y, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("(#1^2 + #2^4 & )[x, y]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("Plus", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)}), ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("y"), ast::Node::make<math::Rational>(4)})});

	BOOST_CHECK_EQUAL( *result, expected );
}

BOOST_FIXTURE_TEST_CASE( test_f_equals_the_pure_function_if_hash_equals_equals_1_then_1_else_hash_times_hash_0_of_the_quantity_hash_minus_1_semicolon_f_of_10, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("f = If[#1 <= 1, 1, #1*#0[#1 - 1]] & ; f[10]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<math::Rational>(3628800);

	BOOST_CHECK_EQUAL( *result, expected );
}

BOOST_AUTO_TEST_SUITE_END()


