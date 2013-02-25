

#include <boost/test/unit_test.hpp>

#include "Fixture.hpp"

BOOST_AUTO_TEST_SUITE( CompoundExpressionTest )

using namespace tungsten;

BOOST_FIXTURE_TEST_CASE( test_a_semicolon_b , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("a; b");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::Identifier>("b") );
}


BOOST_FIXTURE_TEST_CASE( test_a_semicolon , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("a; ");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::Identifier>("Null") );
}


BOOST_FIXTURE_TEST_CASE( test_a_semicolon_b_semicolon , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("a; b;");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::Identifier>("Null") );
}


BOOST_FIXTURE_TEST_CASE( test_a_equals_3_semicolon_a_squared , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("a = 3; a^2");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<math::Rational>(9) );
}




BOOST_AUTO_TEST_SUITE_END()

