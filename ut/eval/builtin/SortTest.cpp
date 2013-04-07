
#include <boost/test/unit_test.hpp>

#include "Fixture.hpp"

BOOST_AUTO_TEST_SUITE( SortTest )

using namespace tungsten;

BOOST_FIXTURE_TEST_CASE( test_sort_the_elements_of_an_empty_list_into_canonical_order , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Sort[{}]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::FunctionCall>("List", {}) );
}


BOOST_FIXTURE_TEST_CASE( test_sort_the_elements_of_f_of_no_arguments_into_canonical_order , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Sort[f[]]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::FunctionCall>("f", {}) );
}


BOOST_FIXTURE_TEST_CASE( test_sort_the_elements_of_the_list_x__sine_of_x__f_of_x_and_y__1_0__1_5_into_canonical_order , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Sort[{x, Sin[x], f[x, y], 1., 1.5}]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<math::Real>(1.), ast::Node::make<math::Real>(1.5), ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::FunctionCall>("f", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::Identifier>("y")}), ast::Node::make<ast::FunctionCall>("Sin", {ast::Node::make<ast::Identifier>("x")})}) );
}


BOOST_FIXTURE_TEST_CASE( test_sort_the_elements_of_f_of_x__sine_of_x__f_of_x_and_y__1_0_and_1_5_into_canonical_order , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Sort[f[x, Sin[x], f[x, y], 1., 1.5]]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::FunctionCall>("f", {ast::Node::make<math::Real>(1.), ast::Node::make<math::Real>(1.5), ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::FunctionCall>("f", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::Identifier>("y")}), ast::Node::make<ast::FunctionCall>("Sin", {ast::Node::make<ast::Identifier>("x")})}) );
}


BOOST_FIXTURE_TEST_CASE( test_sort_the_elements_of_the_list_4__1__3__2__2_using_the_ordering_Greater , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Sort[{4, 1, 3, 2, 2}, Greater]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<math::Rational>(4), ast::Node::make<math::Rational>(3), ast::Node::make<math::Rational>(2), ast::Node::make<math::Rational>(2), ast::Node::make<math::Rational>(1)}) );
}


BOOST_FIXTURE_TEST_CASE( test_sort_the_elements_of_the_list_4__1__3__2__2_using_the_ordering_the_pure_function_hash_is_greater_than_hash_2 , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Sort[{4, 1, 3, 2, 2}, #1 > #2 & ]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<math::Rational>(4), ast::Node::make<math::Rational>(3), ast::Node::make<math::Rational>(2), ast::Node::make<math::Rational>(2), ast::Node::make<math::Rational>(1)}) );
}

BOOST_FIXTURE_TEST_CASE( test_sort_the_elements_of_the_list_Pi__E__2__3__1__square_root_of_2_using_the_ordering_Less , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Sort[{Pi, E, 2, 3, 1, Sqrt[2]}, Less]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<math::Rational>(1), ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<math::Rational>(2), ast::Node::make<math::Rational>(1,2)}), ast::Node::make<math::Rational>(2), ast::Node::make<ast::Identifier>("E"), ast::Node::make<math::Rational>(3), ast::Node::make<ast::Identifier>("Pi")}) );
}


BOOST_FIXTURE_TEST_CASE( test_OrderedQ_of_the_list_x__y, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("OrderedQ[{x, y}]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::Identifier>("True") );
}


BOOST_FIXTURE_TEST_CASE( test_OrderedQ_of_the_list_x__x, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("OrderedQ[{x, x}]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::Identifier>("True") );
}


BOOST_FIXTURE_TEST_CASE( test_OrderedQ_of_the_list_1_2__10_over_3__3, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("OrderedQ[{1.2, 10/3, 3}]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::Identifier>("False") );
}


BOOST_FIXTURE_TEST_CASE( test_OrderedQ_of_the_list_1_2__3__10_over_3, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("OrderedQ[{1.2, 3, 10/3}]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::Identifier>("True") );
}


BOOST_FIXTURE_TEST_CASE( test_OrderedQ_of_the_list_quote_bca_quote__quote_BCA_quote, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("OrderedQ[{\"bca\", \"BCA\"}]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::Identifier>("True") );
}


BOOST_FIXTURE_TEST_CASE( test_OrderedQ_of_the_list_quote_BCA_quote__quote_bca_quote, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("OrderedQ[{\"BCA\", \"bca\"}]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::Identifier>("False") );
}


BOOST_FIXTURE_TEST_CASE( test_OrderedQ_of_the_list_sine_of_x, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("OrderedQ[{Sin[x]}]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::Identifier>("True") );
}


BOOST_FIXTURE_TEST_CASE( test_OrderedQ_of_an_empty_list, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("OrderedQ[{}]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::Identifier>("True") );
}


BOOST_FIXTURE_TEST_CASE( test_OrderedQ_of_f_of_3__4_and_5, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("OrderedQ[f[3, 4, 5]]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::Identifier>("True") );
}


BOOST_FIXTURE_TEST_CASE( test_OrderedQ_of_the_list_sine_of_3__cosine_of_3, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("OrderedQ[{Sin[3], Cos[3]}]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::Identifier>("False") );
}


BOOST_FIXTURE_TEST_CASE( test_OrderedQ_of_the_list_4__3__2__1_and_Greater , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("OrderedQ[{4, 3, 2, 1}, Greater]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::Identifier>("True") );
}


BOOST_FIXTURE_TEST_CASE( test_sort_the_elements_of_the_list_x__y__x_squared__y_squared__x_plus_y_using_the_ordering_the_pure_function_OrderedQ_of_the_list_hash__hash_2, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Sort[{x, y, x^2, y^2, x + y}, OrderedQ[{#1, #2}] & ]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)}), ast::Node::make<ast::Identifier>("y"), ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("y"), ast::Node::make<math::Rational>(2)}), ast::Node::make<ast::FunctionCall>("Plus", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::Identifier>("y")})});

	BOOST_CHECK_EQUAL( *result, expected );
}

BOOST_AUTO_TEST_SUITE_END()
