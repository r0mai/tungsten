
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


BOOST_AUTO_TEST_SUITE_END()
