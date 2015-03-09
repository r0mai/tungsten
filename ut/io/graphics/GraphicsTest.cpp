
#include <boost/test/unit_test.hpp>

#include "../../eval/builtin/Fixture.hpp"

BOOST_FIXTURE_TEST_SUITE( GraphicsTest, BuiltinFunctionFixture )

using namespace tungsten;

BOOST_AUTO_TEST_CASE( GraphicsShouldSurviveAbuse001 ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Graphics[Rule[1,2,3]]");

	BOOST_REQUIRE( result );
}



BOOST_AUTO_TEST_SUITE_END()

