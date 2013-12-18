

#include <boost/test/unit_test.hpp>

#include "Fixture.hpp"

BOOST_AUTO_TEST_SUITE( SumTest )

using namespace tungsten;

BOOST_FIXTURE_TEST_CASE( test_the_sum_of_i_over_i_from_1_to_100, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Sum[i, {i, 1, 100}]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<math::Rational>(5050) );
}

BOOST_FIXTURE_TEST_CASE( test_the_sum_of_i_times_j_over_j_from_5_to_10__then_over_i_from_1_to_5, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Sum[i*j, {i, 1, 5}, {j, 5, 10}]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<math::Rational>(675) );
}


BOOST_AUTO_TEST_SUITE_END()

