
#include <boost/test/unit_test.hpp>

#include "Fixture.hpp"

BOOST_AUTO_TEST_SUITE( WhileTest )

using namespace tungsten;

BOOST_FIXTURE_TEST_CASE( test_n_equals_1_semicolon_while_n_is_less_than_4_remains_true__do_n_equals_n_plus_1_semicolon_n, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("n = 1; While[n < 4, n = n + 1]; n");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<math::Rational>(4);

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_n_equals_1_semicolon_while_n_equals_n_plus_1_semicolon_n_is_less_than_4_remains_true__do_nothing_semicolon_n, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("n = 1; While[n = n + 1; n < 4]; n");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<math::Rational>(4);

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_while_False_remains_true__do_k_equals_3_semicolon_k, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("While[False, k = 3]; k");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::Identifier>("k");

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_while_False_remains_true__do_nothing, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("While[False]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::Identifier>("Null");

	BOOST_CHECK_EQUAL( *result, expected );
}




BOOST_AUTO_TEST_SUITE_END()

