
#include <boost/test/unit_test.hpp>

#include <io/graphics/Primitives.hpp>
#include "../../eval/UnitTestSessionEnvironment.hpp"
#include "../../eval/builtin/Fixture.hpp"

BOOST_FIXTURE_TEST_SUITE( PrimitivesTest, BuiltinFunctionFixture )

using namespace tungsten;

BOOST_AUTO_TEST_CASE( Circle_with_no_params_should_be_centered_on_origin_with_radius_of_one ) {
	UnitTestEnvironment environment;

	auto circle = io::graphics::Circle{}.fromOperands({
	}, environment);

	BOOST_CHECK_EQUAL(circle.center().first, 0);
	BOOST_CHECK_EQUAL(circle.center().second, 0);
	BOOST_CHECK_EQUAL(circle.radius(), 1);

}

BOOST_AUTO_TEST_CASE( Line_of_two_points_should_have_two_points ) {
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


BOOST_AUTO_TEST_CASE( BoundingBox_of_two_point_line_should_same_as_points ) {

	UnitTestEnvironment environment;
	auto line = io::graphics::Line{}.fromOperands({
			ast::Node::make<ast::FunctionCall>(eval::ids::List, {
					ast::Node::make<ast::FunctionCall>(eval::ids::List, {
							ast::Node::make<math::Real>(0),
							ast::Node::make<math::Real>(0)
					}),
					ast::Node::make<ast::FunctionCall>(eval::ids::List, {
							ast::Node::make<math::Real>(1),
							ast::Node::make<math::Real>(1)
					})
			})
	}, environment);

	const auto boundingBox = line.getBoundingBox();
	BOOST_CHECK_EQUAL(boundingBox.minX, 0);
	BOOST_CHECK_EQUAL(boundingBox.minY, 0);
	BOOST_CHECK_EQUAL(boundingBox.maxX, 1);
	BOOST_CHECK_EQUAL(boundingBox.maxY, 1);

}

BOOST_AUTO_TEST_CASE( Svg_string_of_two_point_line_test ) {


	UnitTestEnvironment environment;
	auto line = io::graphics::Line{}.fromOperands({
			ast::Node::make<ast::FunctionCall>(eval::ids::List, {
					ast::Node::make<ast::FunctionCall>(eval::ids::List, {
							ast::Node::make<math::Real>(0),
							ast::Node::make<math::Real>(0)
					}),
					ast::Node::make<ast::FunctionCall>(eval::ids::List, {
							ast::Node::make<math::Real>(1),
							ast::Node::make<math::Real>(1)
					})
			})
	}, environment);

	const auto svgString = line.toSVGString();

	const auto expected = R"phi(<path stroke-width="1" stroke-opacity="1" fill-opacity="1" fill="none" stroke="rgb(0, 0, 0)" vector-effect="non-scaling-stroke" d="M0 0 L1 -1"/>)phi";

	BOOST_CHECK_EQUAL(svgString, expected);

}

BOOST_AUTO_TEST_CASE( Svg_string_of_three_point_line_test ) {

	UnitTestEnvironment environment;
	auto line = io::graphics::Line{}.fromOperands({
			ast::Node::make<ast::FunctionCall>(eval::ids::List, {
					ast::Node::make<ast::FunctionCall>(eval::ids::List, {
							ast::Node::make<math::Real>(0),
							ast::Node::make<math::Real>(0)
					}),
					ast::Node::make<ast::FunctionCall>(eval::ids::List, {
							ast::Node::make<math::Real>(1),
							ast::Node::make<math::Real>(1)
					}),
					ast::Node::make<ast::FunctionCall>(eval::ids::List, {
							ast::Node::make<math::Real>(2),
							ast::Node::make<math::Real>(0)
					})
			})
	}, environment);

	const auto svgString = line.toSVGString();

	const auto expected = R"phi(<path stroke-width="1" stroke-opacity="1" fill-opacity="1" fill="none" stroke="rgb(0, 0, 0)" vector-effect="non-scaling-stroke" d="M0 0 L1 -1 L2 0"/>)phi";

	BOOST_CHECK_EQUAL(svgString, expected);

}

BOOST_AUTO_TEST_SUITE_END()
