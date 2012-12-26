
#include <boost/test/unit_test.hpp>

#include "Fixture.hpp"

BOOST_AUTO_TEST_SUITE( PlusTest )

using namespace tungsten;

BOOST_FIXTURE_TEST_CASE( one_plus_two_is_three, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("1+2");

	BOOST_REQUIRE( result );

	BOOST_REQUIRE( result->isRational() );
	BOOST_CHECK_EQUAL( result->getRational(), 3 );
}

BOOST_AUTO_TEST_SUITE_END()
