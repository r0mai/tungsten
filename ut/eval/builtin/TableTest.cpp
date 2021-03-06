
#include <boost/test/unit_test.hpp>

#include "Fixture.hpp"

BOOST_AUTO_TEST_SUITE( TableTest )

using namespace tungsten;

BOOST_FIXTURE_TEST_CASE( test_Table_of_x , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Table[x]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::Identifier>("x") );
}


BOOST_FIXTURE_TEST_CASE( test_build_a_table_out_of_x_for_x_ranging_from_1_to_4 , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Table[x, {x, 1, 4}]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<math::Rational>(1), ast::Node::make<math::Rational>(2), ast::Node::make<math::Rational>(3), ast::Node::make<math::Rational>(4)}) );
}


BOOST_FIXTURE_TEST_CASE( test_build_a_table_out_of_x_for_x_ranging_from_1_to_minus_4 , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Table[x, {x, 1, -4}]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::FunctionCall>("List", {}) );
}


BOOST_FIXTURE_TEST_CASE( test_build_a_table_out_of_x_for_x_ranging_from_1_to_5_in_increments_of_2 , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Table[x, {x, 1, 5, 2}]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<math::Rational>(1), ast::Node::make<math::Rational>(3), ast::Node::make<math::Rational>(5)}) );
}


BOOST_FIXTURE_TEST_CASE( test_build_a_table_out_of_x_for_x_ranging_from_1_to_6_in_increments_of_2 , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Table[x, {x, 1, 6, 2}]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<math::Rational>(1), ast::Node::make<math::Rational>(3), ast::Node::make<math::Rational>(5)}) );
}


BOOST_FIXTURE_TEST_CASE( test_build_a_table_out_of_x_for_x_ranging_from_1_to_6_in_increments_of_minus_2 , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Table[x, {x, 1, 6, -2}]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::FunctionCall>("List", {}) );
}


BOOST_FIXTURE_TEST_CASE( test_build_a_table_out_of_x_for_x_ranging_from_1_to_3 , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Table[x, {x, 3}]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<math::Rational>(1), ast::Node::make<math::Rational>(2), ast::Node::make<math::Rational>(3)}) );
}


BOOST_FIXTURE_TEST_CASE( test_build_a_table_out_of_x_iterated_3_times , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Table[x, {3}]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::Identifier>("x")}) );
}


BOOST_FIXTURE_TEST_CASE( test_build_a_table_out_of_x_for_x_taking_the_values_a__b_and_c , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Table[x, {x, {a, b, c}}]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("a"), ast::Node::make<ast::Identifier>("b"), ast::Node::make<ast::Identifier>("c")}) );
}


BOOST_FIXTURE_TEST_CASE( test_build_a_table_out_of_x_plus_y_for_y_ranging_from_1_to_5__then_for_x_ranging_from_1_to_4 , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Table[x + y, {x, 1, 4}, {y, 1, 5}]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<math::Rational>(2), ast::Node::make<math::Rational>(3), ast::Node::make<math::Rational>(4), ast::Node::make<math::Rational>(5), ast::Node::make<math::Rational>(6)}), ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<math::Rational>(3), ast::Node::make<math::Rational>(4), ast::Node::make<math::Rational>(5), ast::Node::make<math::Rational>(6), ast::Node::make<math::Rational>(7)}), ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<math::Rational>(4), ast::Node::make<math::Rational>(5), ast::Node::make<math::Rational>(6), ast::Node::make<math::Rational>(7), ast::Node::make<math::Rational>(8)}), ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<math::Rational>(5), ast::Node::make<math::Rational>(6), ast::Node::make<math::Rational>(7), ast::Node::make<math::Rational>(8), ast::Node::make<math::Rational>(9)})}) );
}

BOOST_FIXTURE_TEST_CASE( test_build_a_table_out_of_the_list_a__b_for_b_ranging_from_0_to_1__then_for_a_ranging_from_0_to_2 , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Table[{a, b}, {a, 0, 2}, {b, 0, 1}]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<math::Rational>(0), ast::Node::make<math::Rational>(0)}), ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<math::Rational>(0), ast::Node::make<math::Rational>(1)})}), ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<math::Rational>(1), ast::Node::make<math::Rational>(0)}), ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<math::Rational>(1), ast::Node::make<math::Rational>(1)})}), ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<math::Rational>(2), ast::Node::make<math::Rational>(0)}), ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<math::Rational>(2), ast::Node::make<math::Rational>(1)})})}) );
}

BOOST_FIXTURE_TEST_CASE( test_build_a_table_out_of_x_for_x_ranging_from_2_times_2_to_2_times_2_plus_2 , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Table[x, {x, 2*2, 2*2 + 2}]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<math::Rational>(4), ast::Node::make<math::Rational>(5), ast::Node::make<math::Rational>(6)}) );
}


BOOST_FIXTURE_TEST_CASE( test_build_a_table_out_of_x_for_x_ranging_from_1_to_2_times_2 , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Table[x, {x, 2*2}]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<math::Rational>(1), ast::Node::make<math::Rational>(2), ast::Node::make<math::Rational>(3), ast::Node::make<math::Rational>(4)}) );
}


BOOST_FIXTURE_TEST_CASE( test_build_a_table_out_of_x_for_x_taking_the_values_2_times_2_and_3_times_3 , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Table[x, {x, {2*2, 3*3}}]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<math::Rational>(4), ast::Node::make<math::Rational>(9)}) );
}


BOOST_FIXTURE_TEST_CASE( test_build_a_table_out_of_x_iterated_1_plus_1_times , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Table[x, {1 + 1}]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::Identifier>("x")}) );
}


BOOST_FIXTURE_TEST_CASE( test_Table_of_x_and_the_list_the_list_1_plus_1__1_plus_1 , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Table[x, {{1 + 1, 1 + 1}}]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::Identifier>("x")}) );
}


BOOST_FIXTURE_TEST_CASE( test_build_a_table_out_of_x_for_x_ranging_from_1_over_2_to_3_4, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Table[x, {x, 1/2, 3.4}]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<math::Rational>(1,2), ast::Node::make<math::Rational>(3,2), ast::Node::make<math::Rational>(5,2)});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_build_a_table_out_of_x_for_x_ranging_from_1_over_2_to_Pi, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Table[x, {x, 1/2, Pi}]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<math::Rational>(1,2), ast::Node::make<math::Rational>(3,2), ast::Node::make<math::Rational>(5,2)});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_build_a_table_out_of_x_for_x_ranging_from_1_over_2_to_5_6_in_increments_of_2, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Table[x, {x, 1/2, 5.6, 2}]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<math::Rational>(1,2), ast::Node::make<math::Rational>(5,2), ast::Node::make<math::Rational>(9,2)});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_build_a_table_out_of_x_iterated_Pi_times, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Table[x, {Pi}]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::Identifier>("x")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_x_equals_3_semicolon_build_a_table_out_of_x_iterated_x_times, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("x = 3; Table[x, {x}]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<math::Rational>(3), ast::Node::make<math::Rational>(3), ast::Node::make<math::Rational>(3)});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_build_a_table_out_of_x_for_x_ranging_from_a_to_b_in_increments_of_the_quantity_b_minus_a_over_2, BuiltinFunctionFixture ) {
		boost::optional<ast::Node> result = parseAndEvaluate("Table[x, {x, a, b, (b - a)/2}]");

			BOOST_REQUIRE( result );

				ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("a"), ast::Node::make<ast::FunctionCall>("Plus", {ast::Node::make<ast::Identifier>("a"), ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<math::Rational>(1,2), ast::Node::make<ast::FunctionCall>("Plus", {ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<math::Rational>(-1), ast::Node::make<ast::Identifier>("a")}), ast::Node::make<ast::Identifier>("b")})}) }), ast::Node::make<ast::Identifier>("b")});

					BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_build_a_table_out_of_i_for_i_ranging_from_n_to_3_times_n_in_increments_of_n, BuiltinFunctionFixture ) {
		boost::optional<ast::Node> result = parseAndEvaluate("Table[i, {i, n, 3*n, n}]");

			BOOST_REQUIRE( result );

				ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("n"), ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<math::Rational>(2), ast::Node::make<ast::Identifier>("n")}), ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<math::Rational>(3), ast::Node::make<ast::Identifier>("n")})});

					BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_build_a_table_out_of_i_for_i_ranging_from_1_to_Pi, BuiltinFunctionFixture ) {
		boost::optional<ast::Node> result = parseAndEvaluate("Table[i, {i, 1, Pi}]");

			BOOST_REQUIRE( result );

				ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<math::Rational>(1), ast::Node::make<math::Rational>(2), ast::Node::make<math::Rational>(3)});

					BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_build_a_table_out_of_i_for_i_ranging_from_1_to_8_in_increments_of_Pi, BuiltinFunctionFixture ) {
		boost::optional<ast::Node> result = parseAndEvaluate("Table[i, {i, 1, 8, Pi}]");

			BOOST_REQUIRE( result );

				ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<math::Rational>(1), ast::Node::make<ast::FunctionCall>("Plus", {ast::Node::make<math::Rational>(1), ast::Node::make<ast::Identifier>("Pi")}), ast::Node::make<ast::FunctionCall>("Plus", {ast::Node::make<math::Rational>(1), ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<math::Rational>(2), ast::Node::make<ast::Identifier>("Pi")})})});

					BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_build_a_list_of_values_from_1_to_10_with_step_2, BuiltinFunctionFixture ) {
		boost::optional<ast::Node> result = parseAndEvaluate("Range[1, 10, 2]");

			BOOST_REQUIRE( result );

				ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<math::Rational>(1), ast::Node::make<math::Rational>(3), ast::Node::make<math::Rational>(5), ast::Node::make<math::Rational>(7), ast::Node::make<math::Rational>(9)});

					BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_build_a_list_of_values_from_1_to_4, BuiltinFunctionFixture ) {
		boost::optional<ast::Node> result = parseAndEvaluate("Range[4]");

			BOOST_REQUIRE( result );

				ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<math::Rational>(1), ast::Node::make<math::Rational>(2), ast::Node::make<math::Rational>(3), ast::Node::make<math::Rational>(4)});

					BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_build_a_list_of_values_from_0_to_10_with_step_Pi, BuiltinFunctionFixture ) {
		boost::optional<ast::Node> result = parseAndEvaluate("Range[0, 10, Pi]");

			BOOST_REQUIRE( result );

				ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<math::Rational>(0), ast::Node::make<ast::Identifier>("Pi"), ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<math::Rational>(2), ast::Node::make<ast::Identifier>("Pi")}), ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<math::Rational>(3), ast::Node::make<ast::Identifier>("Pi")})});

					BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_build_a_list_of_values_from_0_to_3, BuiltinFunctionFixture ) {
		boost::optional<ast::Node> result = parseAndEvaluate("Range[0, 3]");

			BOOST_REQUIRE( result );

				ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<math::Rational>(0), ast::Node::make<math::Rational>(1), ast::Node::make<math::Rational>(2), ast::Node::make<math::Rational>(3)});

					BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_build_a_list_of_values_from_1_to_the_list_3__2, BuiltinFunctionFixture ) {
		boost::optional<ast::Node> result = parseAndEvaluate("Range[{3, 2}]");

			BOOST_REQUIRE( result );

				ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<math::Rational>(1), ast::Node::make<math::Rational>(2), ast::Node::make<math::Rational>(3)}), ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<math::Rational>(1), ast::Node::make<math::Rational>(2)})});

					BOOST_CHECK_EQUAL( *result, expected );
}



BOOST_AUTO_TEST_SUITE_END()
