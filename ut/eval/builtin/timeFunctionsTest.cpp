#include <boost/test/unit_test.hpp>

#include "../../eval/UnitTestSessionEnvironment.hpp"
#include "../../eval/builtin/Fixture.hpp"

BOOST_FIXTURE_TEST_SUITE( TimeFunctionsTest, BuiltinFunctionFixture )

using namespace tungsten;

BOOST_AUTO_TEST_CASE( AbsoluteTimeShouldReturnInt ) {
	boost::optional<ast::Node> result = parseAndEvaluate("AbsoluteTime[]");
	BOOST_REQUIRE(result);
	BOOST_CHECK(result->isNumeric());
}

BOOST_AUTO_TEST_SUITE_END()
