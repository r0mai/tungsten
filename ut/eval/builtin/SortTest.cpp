
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


BOOST_AUTO_TEST_SUITE_END()
