#include <boost/test/unit_test.hpp>

#include "Fixture.hpp"

BOOST_AUTO_TEST_SUITE( AbsTest )

using namespace tungsten;

BOOST_FIXTURE_TEST_CASE( zero_Abs_is_zero, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Abs[0]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result, ast::Node::make<math::Rational>(0) );
}

BOOST_FIXTURE_TEST_CASE( one_Abs_is_one, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Abs[1]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result, ast::Node::make<math::Rational>(1) );
}

BOOST_FIXTURE_TEST_CASE( minusone_Abs_is_minusone, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Abs[-1]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result, ast::Node::make<math::Rational>(-1) );
}

BOOST_AUTO_TEST_SUITE_END()
