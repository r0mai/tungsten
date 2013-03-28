
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

BOOST_AUTO_TEST_SUITE_END()
