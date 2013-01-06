
#include <boost/test/unit_test.hpp>

#include "Fixture.hpp"

BOOST_AUTO_TEST_SUITE( TimesTest )

using namespace tungsten;

BOOST_FIXTURE_TEST_CASE( empty_Times_is_one, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Times[]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result, ast::Node::makeRational(1) );
}

BOOST_FIXTURE_TEST_CASE( single_argument_Times_is_identity, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Times[x]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result, ast::Node::makeIdentifier("x") );
}

BOOST_FIXTURE_TEST_CASE( single_argument_nested_Times_is_identity, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Times[Times[x]]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result, ast::Node::makeIdentifier("x") );
}

BOOST_FIXTURE_TEST_CASE( three_Times_six_is_eighteen, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("3*6");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result, ast::Node::makeRational(18) );
}

BOOST_FIXTURE_TEST_CASE( three_Times_six_is_eighteen_with_juxtaposition, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("3 6");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result, ast::Node::makeRational(18) );
}

BOOST_FIXTURE_TEST_CASE( Times_is_Orderless_1, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("x y");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result, ast::Node::makeFunctionCall("Times", {ast::Node::makeIdentifier("x"), ast::Node::makeIdentifier("y")}) );
}

BOOST_FIXTURE_TEST_CASE( Times_is_Orderless_2, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("y x");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result, ast::Node::makeFunctionCall("Times", {ast::Node::makeIdentifier("x"), ast::Node::makeIdentifier("y")}) );
}

BOOST_FIXTURE_TEST_CASE( two_Times_3x_test, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("2*3x");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result, ast::Node::makeFunctionCall("Times", {ast::Node::makeRational(6), ast::Node::makeIdentifier("x")}) );
}

BOOST_FIXTURE_TEST_CASE( x_Times_x_test, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("x*x");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result, ast::Node::makeFunctionCall("Power", {ast::Node::makeIdentifier("x"), ast::Node::makeRational(2)}) );
}

BOOST_FIXTURE_TEST_CASE( x_Divide_x_test, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("x/x");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result, ast::Node::makeRational(1) );
}

BOOST_FIXTURE_TEST_CASE( x_reciprocal_Times_x_with_test, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("x^-1*x");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result, ast::Node::makeRational(1) );
}

BOOST_FIXTURE_TEST_CASE( x_squared_Times_x_test, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("x^2*x");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result, ast::Node::makeFunctionCall("Power", {ast::Node::makeIdentifier("x"), ast::Node::makeRational(3)}) );
}

BOOST_FIXTURE_TEST_CASE( x_squared_Times_x_with_juxtaposition_test, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("x^2 x");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result, ast::Node::makeFunctionCall("Power", {ast::Node::makeIdentifier("x"), ast::Node::makeRational(3)}) );
}

BOOST_FIXTURE_TEST_CASE( x_squared_Times_x_Times_y_test, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("x^2 x*y");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result, ast::Node::makeFunctionCall("Times", {
			ast::Node::makeFunctionCall("Power", {ast::Node::makeIdentifier("x"), ast::Node::makeRational(3)}),
			ast::Node::makeIdentifier("y")}));
}


BOOST_AUTO_TEST_SUITE_END()

