
#include <boost/test/unit_test.hpp>

#include "Fixture.hpp"

BOOST_AUTO_TEST_SUITE( MapTest )

using namespace tungsten;

BOOST_FIXTURE_TEST_CASE( test_f_slash_at_the_list_a__b__c, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("f /@ {a, b, c}");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::FunctionCall>("f", {ast::Node::make<ast::Identifier>("a")}), ast::Node::make<ast::FunctionCall>("f", {ast::Node::make<ast::Identifier>("b")}), ast::Node::make<ast::FunctionCall>("f", {ast::Node::make<ast::Identifier>("c")})});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_f_slash_at_g_of_a__b_and_c, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("f /@ g[a, b, c]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("g", {ast::Node::make<ast::FunctionCall>("f", {ast::Node::make<ast::Identifier>("a")}), ast::Node::make<ast::FunctionCall>("f", {ast::Node::make<ast::Identifier>("b")}), ast::Node::make<ast::FunctionCall>("f", {ast::Node::make<ast::Identifier>("c")})});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_the_pure_function_hash_plus_1_slash_at_the_list_2__3__4, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("(#1 + 1 & ) /@ {2, 3, 4}");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<math::Rational>(3), ast::Node::make<math::Rational>(4), ast::Node::make<math::Rational>(5)});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_f_slash_at_a, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("f /@ a");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::Identifier>("a");

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_f_slash_at_g_slash_at_the_list_x__y__z, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("f /@ g /@ {x, y, z}");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::FunctionCall>("f", {ast::Node::make<ast::FunctionCall>("g", {ast::Node::make<ast::Identifier>("x")})}), ast::Node::make<ast::FunctionCall>("f", {ast::Node::make<ast::FunctionCall>("g", {ast::Node::make<ast::Identifier>("y")})}), ast::Node::make<ast::FunctionCall>("f", {ast::Node::make<ast::FunctionCall>("g", {ast::Node::make<ast::Identifier>("z")})})});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_AUTO_TEST_SUITE_END()

