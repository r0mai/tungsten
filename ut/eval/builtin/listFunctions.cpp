
#include <boost/test/unit_test.hpp>

#include "Fixture.hpp"

BOOST_FIXTURE_TEST_SUITE( ListFunctionsTest, BuiltinFunctionFixture )

using namespace tungsten;

BOOST_AUTO_TEST_CASE( isLessThan10ShouldBeTrueForAllOfEmptyList ) {
	boost::optional<ast::Node> result = parseAndEvaluate(
			"AllTrue[{}, #<10&]");

	BOOST_REQUIRE(result);

	ast::Node expected = ast::Node::make<ast::Identifier>("True");

	BOOST_CHECK_EQUAL( *result, expected );
}

BOOST_AUTO_TEST_CASE( nonPredicateShouldBeTrueForAllOfEmptyList ) {
	boost::optional<ast::Node> result = parseAndEvaluate(
			"AllTrue[{}, a]");

	BOOST_REQUIRE(result);

	ast::Node expected = ast::Node::make<ast::Identifier>("True");

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_AUTO_TEST_SUITE_END()
