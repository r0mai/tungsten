
#include <boost/test/unit_test.hpp>

#include <io/graphics/Primitives.hpp>
#include "../../eval/builtin/Fixture.hpp"

BOOST_FIXTURE_TEST_SUITE( PrimitivesTest, BuiltinFunctionFixture )

using namespace tungsten;

BOOST_AUTO_TEST_CASE( Line_of_two_points_should_have_two_points_in_svg ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Line[{{0,0},{1,1}}]");

	BOOST_REQUIRE( result );
	BOOST_REQUIRE( result->isFunctionCall(eval::ids::Line) );

	const auto lineOperands = result->get<ast::FunctionCall>().getOperands();
	BOOST_REQUIRE( !lineOperands.empty() );
	BOOST_CHECK_EQUAL( lineOperands.size(), 1);

	const auto pointList = lineOperands.front();

	BOOST_REQUIRE( pointList.isFunctionCall(eval::ids::List) );

	const auto points = pointList.get<ast::FunctionCall>().getOperands();

	BOOST_REQUIRE_EQUAL(points.size(), 2);

	const auto start = points[0];
	const auto finish = points[1];

	BOOST_REQUIRE( start.isFunctionCall(eval::ids::List) );
	BOOST_REQUIRE( start.isFunctionCall(eval::ids::List) );

	const auto startPoint = points[0].get<ast::FunctionCall>().getOperands();
	const auto endPoint = points[1].get<ast::FunctionCall>().getOperands();

	BOOST_REQUIRE_EQUAL(startPoint.size(), 2);
	BOOST_REQUIRE_EQUAL(endPoint.size(), 2);

	BOOST_CHECK_EQUAL( startPoint[0].getNumeric(), 0 );
	BOOST_CHECK_EQUAL( startPoint[1].getNumeric(), 0 );
	BOOST_CHECK_EQUAL( endPoint[0].getNumeric(), 1 );
	BOOST_CHECK_EQUAL( endPoint[1].getNumeric(), 1 );
}

BOOST_AUTO_TEST_SUITE_END()
