
#include <boost/test/unit_test.hpp>

#include "Fixture.hpp"

BOOST_FIXTURE_TEST_SUITE( TimesTest, BuiltinFunctionFixture )

using namespace tungsten;

BOOST_AUTO_TEST_CASE( empty_Times_is_one ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Times[]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result, ast::Node::make<math::Rational>(1) );
}

BOOST_AUTO_TEST_CASE( single_argument_Times_is_identity ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Times[x]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result, ast::Node::make<ast::Identifier>("x") );
}

BOOST_AUTO_TEST_CASE( single_argument_nested_Times_is_identity ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Times[Times[x]]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result, ast::Node::make<ast::Identifier>("x") );
}

BOOST_AUTO_TEST_CASE( three_Times_six_is_eighteen ) {
	boost::optional<ast::Node> result = parseAndEvaluate("3*6");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result, ast::Node::make<math::Rational>(18) );
}

BOOST_AUTO_TEST_CASE( three_Times_six_is_eighteen_with_juxtaposition ) {
	boost::optional<ast::Node> result = parseAndEvaluate("3 6");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result, ast::Node::make<math::Rational>(18) );
}

BOOST_AUTO_TEST_CASE( single_I_Times_is_Complex ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Times[I]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result, ast::Node::make<math::ComplexRational>(0, 1) );
}

BOOST_AUTO_TEST_CASE( two_Times_I_is_two_I ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Times[2, I]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result, ast::Node::make<math::ComplexRational>(0, 2) );
}

BOOST_AUTO_TEST_CASE( two_Times_I_is_two_I_with_juxtaposition ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Times[2, I]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result, ast::Node::make<math::ComplexRational>(0, 2) );
}

BOOST_AUTO_TEST_CASE( Times_is_Orderless_1 ) {
	boost::optional<ast::Node> result = parseAndEvaluate("x y");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result, ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::Identifier>("y")}) );
}

BOOST_AUTO_TEST_CASE( Times_is_Orderless_2 ) {
	boost::optional<ast::Node> result = parseAndEvaluate("y x");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result, ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::Identifier>("y")}) );
}

BOOST_AUTO_TEST_CASE( two_Times_3x_test ) {
	boost::optional<ast::Node> result = parseAndEvaluate("2*3x");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result, ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<math::Rational>(6), ast::Node::make<ast::Identifier>("x")}) );
}

BOOST_AUTO_TEST_CASE( x_Times_x_test ) {
	boost::optional<ast::Node> result = parseAndEvaluate("x*x");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result, ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)}) );
}

BOOST_AUTO_TEST_CASE( x_Divide_x_test ) {
	boost::optional<ast::Node> result = parseAndEvaluate("x/x");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result, ast::Node::make<math::Rational>(1) );
}

BOOST_AUTO_TEST_CASE( x_reciprocal_Times_x_with_test ) {
	boost::optional<ast::Node> result = parseAndEvaluate("x^-1*x");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result, ast::Node::make<math::Rational>(1) );
}

BOOST_AUTO_TEST_CASE( x_squared_Times_x_test ) {
	boost::optional<ast::Node> result = parseAndEvaluate("x^2*x");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result, ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(3)}) );
}

BOOST_AUTO_TEST_CASE( x_squared_Times_x_with_juxtaposition_test ) {
	boost::optional<ast::Node> result = parseAndEvaluate("x^2 x");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result, ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(3)}) );
}

BOOST_AUTO_TEST_CASE( x_squared_Times_x_Times_y_test ) {
	boost::optional<ast::Node> result = parseAndEvaluate("x^2 x*y");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result, ast::Node::make<ast::FunctionCall>("Times", {
			ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(3)}),
			ast::Node::make<ast::Identifier>("y")}));
}

BOOST_AUTO_TEST_CASE( Rational_Times_Rational_is_Rational ) {
	boost::optional<ast::Node> result = parseAndEvaluate("3*5");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result, ast::Node::make<math::Rational>(15) );
}

BOOST_AUTO_TEST_CASE( Rational_Times_Real_is_Real ) {
	boost::optional<ast::Node> result = parseAndEvaluate("3*5.0");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result, ast::Node::make<math::Real>(15) );
}

BOOST_AUTO_TEST_CASE( Real_Times_Rational_is_Real ) {
	boost::optional<ast::Node> result = parseAndEvaluate("3.0*5");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result, ast::Node::make<math::Real>(15) );
}

BOOST_AUTO_TEST_CASE( Real_Times_Real_is_Real ) {
	boost::optional<ast::Node> result = parseAndEvaluate("3.0*5.0");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result, ast::Node::make<math::Real>(15) );
}

BOOST_AUTO_TEST_CASE( Rational_zero_Times_Identifier_is_Rational_zero ) {
	boost::optional<ast::Node> result = parseAndEvaluate("0*x");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result, ast::Node::make<math::Rational>(0) );
}

BOOST_AUTO_TEST_CASE( Real_zero_Times_Identifier_is_Real_zero ) {
	boost::optional<ast::Node> result = parseAndEvaluate("0.0*x");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result, ast::Node::make<math::Real>(0) );
}

BOOST_AUTO_TEST_CASE( Real_zero_Times_Rational_Times_Identifier_is_Real_zero ) {
	boost::optional<ast::Node> result = parseAndEvaluate("0.0*3*x");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result, ast::Node::make<math::Real>(0) );
}

BOOST_AUTO_TEST_CASE( Rational_zero_Times_Real_Times_Identifier_is_Real_zero ) {
	boost::optional<ast::Node> result = parseAndEvaluate("0*3.0*x");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result, ast::Node::make<math::Real>(0) );
}

BOOST_AUTO_TEST_CASE( Real_exponent_doesnt_alter_other_Rational_exponents ) {
	boost::optional<ast::Node> result = parseAndEvaluate("x^2 * x^2.5 * y^2 * y^2");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result, ast::Node::make<ast::FunctionCall>("Times", {
		ast::Node::make<ast::FunctionCall>( "Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Real>(4.5)} ),
		ast::Node::make<ast::FunctionCall>( "Power", {ast::Node::make<ast::Identifier>("y"), ast::Node::make<math::Rational>(4)} )
	}) );
}

BOOST_AUTO_TEST_CASE( Negative_Infinity_Times_Positive_Infinity_should_be_Negative_Infinity ) {
	boost::optional<ast::Node> result = parseAndEvaluate("DirectedInfinity[-1] * DirectedInfinity[1]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result, ast::Node::make<ast::FunctionCall>("DirectedInfinity", {
		ast::Node::make<math::Real>(-1)
	}) );
}

BOOST_AUTO_TEST_CASE( Positive_Infinity_Times_Negative_Infinity_should_be_Negative_Infinity ) {
	boost::optional<ast::Node> result = parseAndEvaluate("DirectedInfinity[1] * DirectedInfinity[-1]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result, ast::Node::make<ast::FunctionCall>("DirectedInfinity", {
		ast::Node::make<math::Real>(-1)
	}) );
}

BOOST_AUTO_TEST_CASE( Positive_Infinity_Times_Positive_Infinity_should_be_Positive_Infinity ) {
	boost::optional<ast::Node> result = parseAndEvaluate("DirectedInfinity[1] * DirectedInfinity[1]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result, ast::Node::make<ast::FunctionCall>("DirectedInfinity", {
		ast::Node::make<math::Real>(1)
	}) );
}

BOOST_AUTO_TEST_CASE( Negative_Infinity_Times_Negative_Infinity_should_be_Positive_Infinity ) {
	boost::optional<ast::Node> result = parseAndEvaluate("DirectedInfinity[-1] * DirectedInfinity[-1]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result, ast::Node::make<ast::FunctionCall>("DirectedInfinity", {
		ast::Node::make<math::Real>(1)
	}) );
}

BOOST_AUTO_TEST_CASE( Negative_Infinity_Times_Undirected_Infinity_should_be_Undirected_Infinity ) {
	boost::optional<ast::Node> result = parseAndEvaluate("DirectedInfinity[-1] * DirectedInfinity[]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result, ast::Node::make<ast::FunctionCall>("DirectedInfinity", { }) );
}

BOOST_AUTO_TEST_CASE( Positive_Infinity_Times_Undirected_Infinity_should_be_Undirected_Infinity ) {
	boost::optional<ast::Node> result = parseAndEvaluate("DirectedInfinity[1] * DirectedInfinity[]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result, ast::Node::make<ast::FunctionCall>("DirectedInfinity", { }) );
}

BOOST_AUTO_TEST_CASE( Undirected_Infinity_Times_Negative_Infinity_should_be_Undirected_Infinity ) {
	boost::optional<ast::Node> result = parseAndEvaluate("DirectedInfinity[] * DirectedInfinity[-1]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result, ast::Node::make<ast::FunctionCall>("DirectedInfinity", { }) );
}

BOOST_AUTO_TEST_CASE( Undirected_Infinity_Times_Positive_Infinity_should_be_Undirected_Infinity ) {
	boost::optional<ast::Node> result = parseAndEvaluate("DirectedInfinity[] * DirectedInfinity[1]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result, ast::Node::make<ast::FunctionCall>("DirectedInfinity", { }) );
}

BOOST_AUTO_TEST_CASE( Undirected_Infinity_Times_Undirected_Infinity_should_be_Undirected_Infinity ) {
	boost::optional<ast::Node> result = parseAndEvaluate("DirectedInfinity[] * DirectedInfinity[]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result, ast::Node::make<ast::FunctionCall>("DirectedInfinity", { }) );
}

//Test for Issue 1
BOOST_AUTO_TEST_CASE( Times_Sqrt_2_test ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Times[Sqrt[2]]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result, ast::Node::make<ast::FunctionCall>( "Power", {ast::Node::make<math::Rational>(2), ast::Node::make<math::Rational>(1,2)} ) );
}

BOOST_AUTO_TEST_SUITE_END()

