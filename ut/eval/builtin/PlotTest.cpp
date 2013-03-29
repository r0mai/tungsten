
#include <boost/test/unit_test.hpp>

#include "Fixture.hpp"

BOOST_AUTO_TEST_SUITE( PlotTest )

using namespace tungsten;

BOOST_FIXTURE_TEST_CASE( test_should_leave_its_local_variable_unassigned, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Plot[x^2,{x,-1,1}];x");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::Identifier>("x") );
}

BOOST_FIXTURE_TEST_CASE( Plot_shouldnt_modify_its_local_variable , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("x=3;Plot[x^2,{x,-1,1}];x");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<math::Rational>(3) );
}

BOOST_AUTO_TEST_SUITE_END()

