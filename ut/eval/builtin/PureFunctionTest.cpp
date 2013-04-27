
//Name should be FunctionTest.cpp, but that sounds strange ;)

#include <boost/test/unit_test.hpp>

#include "Fixture.hpp"

BOOST_AUTO_TEST_SUITE( PureFunctionTest )

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


BOOST_FIXTURE_TEST_CASE( test_the_pure_function_the_pure_function_hash_to_the_power_of_hash_of_x_of_x, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("((#1^#1 & ) & )[x][x]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::Identifier>("x")});

	BOOST_CHECK_EQUAL( *result, expected );
}

BOOST_FIXTURE_TEST_CASE( test_the_pure_function_f_of_x__hash_hash__y_and_hash_hash_of_a__b__c_and_d, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("(f[x, ##1, y, ##1] & )[a, b, c, d]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("f", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::Identifier>("a"), ast::Node::make<ast::Identifier>("b"), ast::Node::make<ast::Identifier>("c"), ast::Node::make<ast::Identifier>("d"), ast::Node::make<ast::Identifier>("y"), ast::Node::make<ast::Identifier>("a"), ast::Node::make<ast::Identifier>("b"), ast::Node::make<ast::Identifier>("c"), ast::Node::make<ast::Identifier>("d")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_the_pure_function_Table_of_a_of_i_and_j_and_hash_hash_at_at_the_list_the_list_i__3__the_list_j__2, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("(Table[a[i, j], ##1] & ) @@ {{i, 3}, {j, 2}}");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::FunctionCall>("a", {ast::Node::make<math::Rational>(1), ast::Node::make<math::Rational>(1)}), ast::Node::make<ast::FunctionCall>("a", {ast::Node::make<math::Rational>(1), ast::Node::make<math::Rational>(2)})}), ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::FunctionCall>("a", {ast::Node::make<math::Rational>(2), ast::Node::make<math::Rational>(1)}), ast::Node::make<ast::FunctionCall>("a", {ast::Node::make<math::Rational>(2), ast::Node::make<math::Rational>(2)})}), ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::FunctionCall>("a", {ast::Node::make<math::Rational>(3), ast::Node::make<math::Rational>(1)}), ast::Node::make<ast::FunctionCall>("a", {ast::Node::make<math::Rational>(3), ast::Node::make<math::Rational>(2)})})});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_the_pure_function_the_list_hash_hash_of_x__y_and_z, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("({##1} & )[x, y, z]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::Identifier>("y"), ast::Node::make<ast::Identifier>("z")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_the_pure_function_the_list_hash_hash_2_of_x__y_and_z, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("({##2} & )[x, y, z]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("y"), ast::Node::make<ast::Identifier>("z")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_the_pure_function_the_list_hash_hash_3_of_x__y_and_z, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("({##3} & )[x, y, z]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("z")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_the_pure_function_the_list_hash_hash_4_of_x__y_and_z, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("({##4} & )[x, y, z]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_the_pure_function_the_hash_hash_of_x__y_and_z, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("(##1 & )[x, y, z]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("Sequence", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::Identifier>("y"), ast::Node::make<ast::Identifier>("z")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_the_pure_function_the_hash_hash_2_of_x__y_and_z, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("(##2 & )[x, y, z]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("Sequence", {ast::Node::make<ast::Identifier>("y"), ast::Node::make<ast::Identifier>("z")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_the_pure_function_the_hash_hash_3_of_x__y_and_z, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("(##3 & )[x, y, z]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("Sequence", {ast::Node::make<ast::Identifier>("z")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_the_pure_function_the_hash_hash_4_of_x__y_and_z, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("(##4 & )[x, y, z]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("Sequence", {});

	BOOST_CHECK_EQUAL( *result, expected );
}
BOOST_AUTO_TEST_SUITE_END()


