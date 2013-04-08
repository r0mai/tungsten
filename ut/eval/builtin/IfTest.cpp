
#include <boost/test/unit_test.hpp>

#include "Fixture.hpp"

BOOST_AUTO_TEST_SUITE( IfTest )

using namespace tungsten;

BOOST_FIXTURE_TEST_CASE( test_if_a_then_1_else_2_or__if_the_condition_is_neither_true_nor_false__3, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("If[a, 1, 2, 3]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<math::Rational>(3);

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_if_x_then_1, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("If[x, 1]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("If", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(1)});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_if_True_then_1, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("If[True, 1]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<math::Rational>(1);

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_if_False_then_1, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("If[False, 1]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::Identifier>("Null");

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_if_x_then_1_else_2, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("If[x, 1, 2]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("If", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(1), ast::Node::make<math::Rational>(2)});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_if_True_then_1_else_2, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("If[True, 1, 2]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<math::Rational>(1);

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_if_False_then_1_else_2, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("If[False, 1, 2]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<math::Rational>(2);

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_if_x_then_1_else_2_or__if_the_condition_is_neither_true_nor_false__3, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("If[x, 1, 2, 3]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<math::Rational>(3);

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_if_True_then_1_else_2_or__if_the_condition_is_neither_true_nor_false__3, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("If[True, 1, 2, 3]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<math::Rational>(1);

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_if_False_then_1_else_2_or__if_the_condition_is_neither_true_nor_false__3, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("If[False, 1, 2, 3]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<math::Rational>(2);

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_if_a_is_less_than_b_then_1_else_0, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("If[a < b, 1, 0]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("If", {ast::Node::make<ast::FunctionCall>("Less", {ast::Node::make<ast::Identifier>("a"), ast::Node::make<ast::Identifier>("b")}), ast::Node::make<math::Rational>(1), ast::Node::make<math::Rational>(0)});

	BOOST_CHECK_EQUAL( *result, expected );
}

BOOST_FIXTURE_TEST_CASE( test_x_equals_minus_2_semicolon_if_x_is_less_than_0_then_y_equals_minus_x_else_y_equals_x_semicolon_y, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("x = -2; If[x < 0, y = -x, y = x]; y");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<math::Rational>(2);

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_AUTO_TEST_SUITE_END()
