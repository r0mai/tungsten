

#include <boost/test/unit_test.hpp>

#include "Fixture.hpp"

BOOST_AUTO_TEST_SUITE( FactorialTest )

using namespace tungsten;

//Factorial ----

BOOST_FIXTURE_TEST_CASE( test_x_factorial , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("x!");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::FunctionCall>("Factorial", {ast::Node::make<ast::Identifier>("x")}) );
}


BOOST_FIXTURE_TEST_CASE( test_minus_1_0_factorial , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("(-1)!");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::FunctionCall>("DirectedInfinity", {}) );
}

BOOST_FIXTURE_TEST_CASE( test_minus_1_factorial , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("(-1.0)!");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::FunctionCall>("DirectedInfinity", {}) );
}


BOOST_FIXTURE_TEST_CASE( test_the_quantity_minus_1_over_2_factorial , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("(-2^(-1))!");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("Pi"), ast::Node::make<math::Rational>(1,2)}) );
}


BOOST_FIXTURE_TEST_CASE( test_3_5_factorial , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("3.5!");

	BOOST_REQUIRE( result );

	BOOST_REQUIRE( result->is<math::Real>() );
	//TODO magic number: tolerance
	math::Real resultDelta = 11.6317 - result->get<math::Real>();
	BOOST_CHECK_SMALL( resultDelta, math::Real(0.0001) );
}


BOOST_FIXTURE_TEST_CASE( test_the_quantity_2_over_3_factorial , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("(2/3)!");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::FunctionCall>("Factorial", {ast::Node::make<math::Rational>(2,3)}) );
}


BOOST_FIXTURE_TEST_CASE( test_the_quantity_3_over_2_factorial , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("(3/2)!");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<math::Rational>(3,4), ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("Pi"), ast::Node::make<math::Rational>(1,2)})}) );
}


BOOST_FIXTURE_TEST_CASE( test_2_factorial , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("2!");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<math::Rational>(2) );
}


BOOST_FIXTURE_TEST_CASE( test_1_factorial , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("1!");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<math::Rational>(1) );
}


BOOST_FIXTURE_TEST_CASE( test_0_factorial , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("0!");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<math::Rational>(1) );
}


BOOST_FIXTURE_TEST_CASE( test_6_factorial , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("6!");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<math::Rational>(720) );
}


BOOST_FIXTURE_TEST_CASE( test_the_list_x__y_factorial , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("{x, y}!");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::FunctionCall>("Factorial", {ast::Node::make<ast::Identifier>("x")}), ast::Node::make<ast::FunctionCall>("Factorial", {ast::Node::make<ast::Identifier>("y")})}) );
}


//Factorial2 -------

BOOST_FIXTURE_TEST_CASE( test_x_double_factorial , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("x!!");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::FunctionCall>("Factorial2", {ast::Node::make<ast::Identifier>("x")}) );
}


BOOST_FIXTURE_TEST_CASE( test_minus_1_double_factorial , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("(-1)!!");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<math::Rational>(1) );
}

BOOST_FIXTURE_TEST_CASE( test_minus_3_double_factorial , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("(-3)!!");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<math::Rational>(-1) );
}

BOOST_FIXTURE_TEST_CASE( test_minus_5_double_factorial , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("(-5)!!");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<math::Rational>(1,3) );
}


BOOST_FIXTURE_TEST_CASE( test_the_quantity_minus_1_over_2_double_factorial , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("(-2^(-1))!!");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::FunctionCall>("Factorial2", {ast::Node::make<math::Rational>(-1,2)}) );
}


BOOST_FIXTURE_TEST_CASE( test_3_5_double_factorial , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("3.5!!");

	BOOST_REQUIRE( result );

	BOOST_REQUIRE( result->is<math::Real>() );
	//TODO magic number: tolerance
	math::Real resultDelta = 4.83232 - result->get<math::Real>();
	BOOST_CHECK_SMALL( resultDelta, math::Real(0.0001) );
}


BOOST_FIXTURE_TEST_CASE( test_the_quantity_2_over_3_double_factorial , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("(2/3)!!");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::FunctionCall>("Factorial2", {ast::Node::make<math::Rational>(2,3)}) );
}


BOOST_FIXTURE_TEST_CASE( test_the_quantity_3_over_2_double_factorial , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("(3/2)!!");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::FunctionCall>("Factorial2", {ast::Node::make<math::Rational>(3,2)}) );
}


BOOST_FIXTURE_TEST_CASE( test_2_double_factorial , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("2!!");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<math::Rational>(2) );
}


BOOST_FIXTURE_TEST_CASE( test_1_double_factorial , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("1!!");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<math::Rational>(1) );
}


BOOST_FIXTURE_TEST_CASE( test_0_double_factorial , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("0!!");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<math::Rational>(1) );
}


BOOST_FIXTURE_TEST_CASE( test_6_double_factorial , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("6!!");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<math::Rational>(48) );
}


BOOST_FIXTURE_TEST_CASE( test_the_list_x__y_double_factorial , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("{x, y}!!");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::FunctionCall>("Factorial2", {ast::Node::make<ast::Identifier>("x")}), ast::Node::make<ast::FunctionCall>("Factorial2", {ast::Node::make<ast::Identifier>("y")})}) );
}


BOOST_AUTO_TEST_SUITE_END()

