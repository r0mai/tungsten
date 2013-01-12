
#include <boost/test/unit_test.hpp>

#include "Fixture.hpp"

BOOST_AUTO_TEST_SUITE( TimesTest )

using namespace tungsten;

BOOST_FIXTURE_TEST_CASE( empty_Times_is_one, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Times[]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result, ast::Node::make<math::Rational>(1) );
}

BOOST_FIXTURE_TEST_CASE( single_argument_Times_is_identity, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Times[x]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result, ast::Node::make<ast::Identifier>("x") );
}

BOOST_FIXTURE_TEST_CASE( single_argument_nested_Times_is_identity, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Times[Times[x]]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result, ast::Node::make<ast::Identifier>("x") );
}

BOOST_FIXTURE_TEST_CASE( three_Times_six_is_eighteen, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("3*6");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result, ast::Node::make<math::Rational>(18) );
}

BOOST_FIXTURE_TEST_CASE( three_Times_six_is_eighteen_with_juxtaposition, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("3 6");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result, ast::Node::make<math::Rational>(18) );
}

BOOST_FIXTURE_TEST_CASE( Times_is_Orderless_1, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("x y");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result, ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::Identifier>("y")}) );
}

BOOST_FIXTURE_TEST_CASE( Times_is_Orderless_2, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("y x");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result, ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::Identifier>("y")}) );
}

BOOST_FIXTURE_TEST_CASE( two_Times_3x_test, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("2*3x");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result, ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<math::Rational>(6), ast::Node::make<ast::Identifier>("x")}) );
}

BOOST_FIXTURE_TEST_CASE( x_Times_x_test, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("x*x");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result, ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)}) );
}

BOOST_FIXTURE_TEST_CASE( x_Divide_x_test, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("x/x");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result, ast::Node::make<math::Rational>(1) );
}

BOOST_FIXTURE_TEST_CASE( x_reciprocal_Times_x_with_test, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("x^-1*x");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result, ast::Node::make<math::Rational>(1) );
}

BOOST_FIXTURE_TEST_CASE( x_squared_Times_x_test, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("x^2*x");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result, ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(3)}) );
}

BOOST_FIXTURE_TEST_CASE( x_squared_Times_x_with_juxtaposition_test, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("x^2 x");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result, ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(3)}) );
}

BOOST_FIXTURE_TEST_CASE( x_squared_Times_x_Times_y_test, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("x^2 x*y");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result, ast::Node::make<ast::FunctionCall>("Times", {
			ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(3)}),
			ast::Node::make<ast::Identifier>("y")}));
}

BOOST_FIXTURE_TEST_CASE( Rational_Times_Rational_is_Rational, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("3*5");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result, ast::Node::make<math::Rational>(15) );
}

BOOST_FIXTURE_TEST_CASE( Rational_Times_Real_is_Real, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("3*5.0");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result, ast::Node::make<math::Real>(15) );
}

BOOST_FIXTURE_TEST_CASE( Real_Times_Rational_is_Real, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("3.0*5");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result, ast::Node::make<math::Real>(15) );
}

BOOST_FIXTURE_TEST_CASE( Real_Times_Real_is_Real, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("3.0*5.0");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result, ast::Node::make<math::Real>(15) );
}

BOOST_FIXTURE_TEST_CASE( Rational_zero_Times_Identifier_is_Rational_zero, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("0*x");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result, ast::Node::make<math::Rational>(0) );
}

BOOST_FIXTURE_TEST_CASE( Real_zero_Times_Identifier_is_Real_zero, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("0.0*x");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result, ast::Node::make<math::Real>(0) );
}

BOOST_FIXTURE_TEST_CASE( Real_zero_Times_Rational_Times_Identifier_is_Real_zero, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("0.0*3*x");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result, ast::Node::make<math::Real>(0) );
}

BOOST_FIXTURE_TEST_CASE( Rational_zero_Times_Real_Times_Identifier_is_Real_zero, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("0*3.0*x");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result, ast::Node::make<math::Real>(0) );
}

BOOST_FIXTURE_TEST_CASE( Real_exponent_doesnt_alter_other_Rational_exponents, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("x^2 * x^2.5 * y^2 * y^2");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result, ast::Node::make<ast::FunctionCall>("Times", {
		ast::Node::make<ast::FunctionCall>( "Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Real>(4.5)} ),
		ast::Node::make<ast::FunctionCall>( "Power", {ast::Node::make<ast::Identifier>("y"), ast::Node::make<math::Rational>(4)} )
	}) );
}



BOOST_AUTO_TEST_SUITE_END()

