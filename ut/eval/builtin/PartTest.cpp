
#include <boost/test/unit_test.hpp>

#include "Fixture.hpp"

BOOST_AUTO_TEST_SUITE( PartTest )

using namespace tungsten;

BOOST_FIXTURE_TEST_CASE( test_the_length_of_x, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Length[x]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<math::Rational>(0);

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_the_length_of_quote_a_quote, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Length[\"a\"]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<math::Rational>(0);

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_the_length_of_1, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Length[1]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<math::Rational>(0);

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_the_length_of_1_over_2, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Length[1/2]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<math::Rational>(0);

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_the_length_of_1_0, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Length[1.]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<math::Rational>(0);

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_the_length_of_an_empty_list, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Length[{}]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<math::Rational>(0);

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_the_length_of_the_list_x, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Length[{x}]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<math::Rational>(1);

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_the_length_of_the_list_x__y, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Length[{x, y}]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<math::Rational>(2);

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_the_length_of_the_list_x__the_list_y__z, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Length[{x, {y, z}}]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<math::Rational>(2);

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_AUTO_TEST_SUITE_END()

