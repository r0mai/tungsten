
#include <boost/test/unit_test.hpp>

#include "Fixture.hpp"

BOOST_AUTO_TEST_SUITE( ReplaceTest )

using namespace tungsten;

BOOST_FIXTURE_TEST_CASE( test_the_list_x__x_squared__y__z_slash_dot_x_goes_to_a, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("{x, x^2, y, z} /. x -> a");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("a"), ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("a"), ast::Node::make<math::Rational>(2)}), ast::Node::make<ast::Identifier>("y"), ast::Node::make<ast::Identifier>("z")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_the_list_x__x_squared__y__z_slash_dot_x_goes_to_the_list_a__b, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("{x, x^2, y, z} /. x -> {a, b}");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("a"), ast::Node::make<ast::Identifier>("b")}), ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("a"), ast::Node::make<math::Rational>(2)}), ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("b"), ast::Node::make<math::Rational>(2)})}), ast::Node::make<ast::Identifier>("y"), ast::Node::make<ast::Identifier>("z")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_sine_of_x_slash_dot_sine_goes_to_cosine, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Sin[x] /. Sin -> Cos");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("Cos", {ast::Node::make<ast::Identifier>("x")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_1_plus_x_squared_plus_x_to_the_4th_power_slash_dot_x_to_the_power_of_the_pattern_p_blank_goes_to_f_of_p, BuiltinFunctionFixture ) {
		boost::optional<ast::Node> result = parseAndEvaluate("1 + x^2 + x^4 /. x^(p_) -> f[p]");

			BOOST_REQUIRE( result );

				ast::Node expected = ast::Node::make<ast::FunctionCall>("Plus", {ast::Node::make<math::Rational>(1), ast::Node::make<ast::FunctionCall>("f", {ast::Node::make<math::Rational>(2)}), ast::Node::make<ast::FunctionCall>("f", {ast::Node::make<math::Rational>(4)})});

					BOOST_CHECK_EQUAL( *result, expected );
}

BOOST_FIXTURE_TEST_CASE( test_x_slash_dot_x_goes_to_1__x_goes_to_3_and_x_goes_to_7, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("x /. {x -> 1, x -> 3, x -> 7}");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<math::Rational>(1);

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_x_slash_dot_the_list_x_goes_to_1__the_list_x_goes_to_3_and_the_list_x_goes_to_7, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("x /. {{x -> 1}, {x -> 3}, {x -> 7}}");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<math::Rational>(1), ast::Node::make<math::Rational>(3), ast::Node::make<math::Rational>(7)});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Hold_of_the_quantity_x_plus_x_slash_dot_x_goes_to_7, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Hold[x + x] /. x -> 7");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("Hold", {ast::Node::make<ast::FunctionCall>("Plus", {ast::Node::make<math::Rational>(7), ast::Node::make<math::Rational>(7)})});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Hold_of_the_quantity_x_plus_x_slash_dot_x_colon_goes_to_2_squared, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Hold[x + x] /. x :> 2^2");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("Hold", {ast::Node::make<ast::FunctionCall>("Plus", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<math::Rational>(2), ast::Node::make<math::Rational>(2)}), ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<math::Rational>(2), ast::Node::make<math::Rational>(2)})})});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Hold_of_the_quantity_x_plus_x_slash_dot_x_goes_to_2_squared, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Hold[x + x] /. x -> 2^2");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("Hold", {ast::Node::make<ast::FunctionCall>("Plus", {ast::Node::make<math::Rational>(4), ast::Node::make<math::Rational>(4)})});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_the_list_a__b__c_slash_dot_a_goes_to_b_slash_dot_b_goes_to_d, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("{a, b, c} /. a -> b /. b -> d");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("d"), ast::Node::make<ast::Identifier>("d"), ast::Node::make<ast::Identifier>("c")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_the_list_a__b__c_slash_dot_a_goes_to_b_and_b_goes_to_d, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("{a, b, c} /. {a -> b, b -> d}");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("b"), ast::Node::make<ast::Identifier>("d"), ast::Node::make<ast::Identifier>("c")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_the_list_g_of_1__Hold_of_g_of_1_slash_dot_g_of_the_pattern_n_blank_colon_goes_to_n_plus_1, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("{g[1], Hold[g[1]]} /. g[n_] :> n + 1");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<math::Rational>(2), ast::Node::make<ast::FunctionCall>("Hold", {ast::Node::make<ast::FunctionCall>("Plus", {ast::Node::make<math::Rational>(1), ast::Node::make<math::Rational>(1)})})});

	BOOST_CHECK_EQUAL( *result, expected );
}




BOOST_AUTO_TEST_SUITE_END()

