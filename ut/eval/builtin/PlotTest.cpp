
#include <boost/test/unit_test.hpp>
#include <boost/mpl/list.hpp>
#include "Fixture.hpp"

BOOST_FIXTURE_TEST_SUITE( PlotTest, BuiltinFunctionFixture )

using namespace tungsten;

BOOST_AUTO_TEST_CASE( Plot_should_leave_its_local_variable_unassigned ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Plot[x^2,{x,-1,1}];x");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::Identifier>("x") );
}

BOOST_AUTO_TEST_CASE( Plot_shouldnt_modify_its_local_variable ) {
	boost::optional<ast::Node> result = parseAndEvaluate("x=3;Plot[x^2,{x,-1,1}];x");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<math::Rational>(3) );
}

BOOST_AUTO_TEST_CASE( Plot_should_return_graphics_001 ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Plot[Sin[x], {x, -5, 5}]");
	BOOST_REQUIRE( result );
	BOOST_CHECK( result-> isFunctionCall(eval::ids::Graphics));
}

BOOST_AUTO_TEST_CASE( Plot_should_return_graphics_even_with_null_points ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Plot[If[x-Floor[x]>0.5, Sin[x], Infinite], {x, -5, 5}]");
	BOOST_REQUIRE( result );
	BOOST_CHECK( result -> isFunctionCall( eval::ids::Graphics ));
}

BOOST_AUTO_TEST_CASE( Plot_should_return_graphics_reverse_range ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Plot[If[x-Floor[x]>0.5, Sin[x], Infinite], {x, 5, -5}]");
	BOOST_REQUIRE( result );
	BOOST_CHECK( result -> isFunctionCall( eval::ids::Graphics));
}

using namespace boost::mpl;
using linear_test_values = list<
		pair<int_<1>, pair<int_<0>, int_<1>>>,
		pair<int_<-1>, pair<int_<0>, int_<1>>>
		>;

BOOST_AUTO_TEST_CASE_TEMPLATE( Plot_should_have_line_for_linear_function, range, linear_test_values ) {
	const auto coeffecient = range::first::value;
	const auto rangeBegin = range::second::first::value;
	const auto rangeEnd = range::second::second::value;

	std::stringstream ss;
	ss << "Plot[" << coeffecient << "*x, {x, " << rangeBegin << ", " << rangeEnd << "}]";

	boost::optional<ast::Node> result = parseAndEvaluate(ss.str());
	BOOST_REQUIRE( result );
	BOOST_REQUIRE( result->isFunctionCall( eval::ids::Graphics ));

	const auto operands = result->get<ast::FunctionCall>().getOperands();

	BOOST_REQUIRE_EQUAL( operands.size(), 1);
	BOOST_REQUIRE( operands.front().isFunctionCall( eval::ids::List ));

	const auto listOperands = operands.front().get<ast::FunctionCall>().getOperands();

	BOOST_REQUIRE_GE( listOperands.size(), 3 );
	const auto functionLine = listOperands[0];
	const auto xLine = listOperands[1];
	const auto yLine = listOperands[2];

	BOOST_REQUIRE( functionLine.isFunctionCall( eval::ids::Line ));
	const auto lineOperands = functionLine.get<ast::FunctionCall>().getOperands();

	BOOST_REQUIRE_GE( lineOperands.size(), 2 );
	BOOST_REQUIRE( lineOperands.front().isFunctionCall(eval::ids::List));
	const auto start = lineOperands.front().get<ast::FunctionCall>().getOperands().front();
	const auto finish = lineOperands.front().get<ast::FunctionCall>().getOperands().back();

	BOOST_REQUIRE(start.isFunctionCall( eval::ids::List ));
	BOOST_REQUIRE(finish.isFunctionCall( eval::ids::List ));

	BOOST_REQUIRE_EQUAL(start.get<ast::FunctionCall>().getOperands().size(), 2);
	BOOST_REQUIRE_EQUAL(finish.get<ast::FunctionCall>().getOperands().size(), 2);

	const math::Real startX = start.get<ast::FunctionCall>().getOperands().front().getNumeric();
	const math::Real startY = start.get<ast::FunctionCall>().getOperands().back().getNumeric();
	const math::Real endX = finish.get<ast::FunctionCall>().getOperands().front().getNumeric();
	const math::Real endY = finish.get<ast::FunctionCall>().getOperands().back().getNumeric();

	BOOST_CHECK_CLOSE(rangeBegin, startX.convert_to<double>(), 0.15);
	BOOST_CHECK_CLOSE(rangeBegin*coeffecient, startY.convert_to<double>(), 0.15);
	BOOST_CHECK_CLOSE(rangeEnd, endX.convert_to<double>(), 0.15);
	BOOST_CHECK_CLOSE(rangeEnd*coeffecient, endY.convert_to<double>(), 0.15);
	// 0.15 above is 0.15%
}

BOOST_AUTO_TEST_SUITE_END()

