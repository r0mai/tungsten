
#include <boost/test/unit_test.hpp>

#include "Fixture.hpp"

BOOST_AUTO_TEST_SUITE( PlotTest )

using namespace tungsten;

BOOST_FIXTURE_TEST_CASE( Plot_should_leave_its_local_variable_unassigned, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Plot[x^2,{x,-1,1}];x");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::Identifier>("x") );
}

BOOST_FIXTURE_TEST_CASE( Plot_shouldnt_modify_its_local_variable , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("x=3;Plot[x^2,{x,-1,1}];x");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<math::Rational>(3) );
}

BOOST_FIXTURE_TEST_CASE( Plot_should_return_graphics_001, BuiltinFunctionFixture) {
	boost::optional<ast::Node> result = parseAndEvaluate("Plot[Sin[x], {x, -5, 5}]");
	BOOST_REQUIRE( result );
	BOOST_CHECK( result-> isFunctionCall(eval::ids::Graphics));
}

BOOST_FIXTURE_TEST_CASE( Plot_should_return_graphics_002, BuiltinFunctionFixture) {
	boost::optional<ast::Node> result = parseAndEvaluate("Plot[If[x-Floor[x]>0.5, Sin[x], Infinite], {x, -5, 5}]");
	BOOST_REQUIRE( result );
	BOOST_CHECK( result -> isFunctionCall( eval::ids::Graphics));
}

BOOST_FIXTURE_TEST_CASE( Plot_should_return_graphics_reverse_range, BuiltinFunctionFixture) {
	boost::optional<ast::Node> result = parseAndEvaluate("Plot[If[x-Floor[x]>0.5, Sin[x], Infinite], {x, 5, -5}]");
	BOOST_REQUIRE( result );
	BOOST_CHECK( result -> isFunctionCall( eval::ids::Graphics));
}


BOOST_AUTO_TEST_SUITE_END()

