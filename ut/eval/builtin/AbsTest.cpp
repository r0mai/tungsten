#include <boost/test/unit_test.hpp>

#include "Fixture.hpp"

BOOST_AUTO_TEST_SUITE( AbsTest )

using namespace tungsten;

BOOST_FIXTURE_TEST_CASE( zero_Abs_is_zero, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Abs[0]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result, ast::Node::make<math::Rational>(0) );
}

BOOST_FIXTURE_TEST_CASE( one_Abs_is_one, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Abs[1]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result, ast::Node::make<math::Rational>(1) );
}

BOOST_FIXTURE_TEST_CASE( minusone_Abs_is_minusone, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Abs[-1]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result, ast::Node::make<math::Rational>(-1) );
}

BOOST_FIXTURE_TEST_CASE( test_the_absolute_value_of_x , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Abs[x]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::FunctionCall>("Abs", {ast::Node::make<ast::Identifier>("x")}) );
}


BOOST_FIXTURE_TEST_CASE( test_the_absolute_value_of_the_absolute_value_of_x , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Abs[Abs[x]]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::FunctionCall>("Abs", {ast::Node::make<ast::Identifier>("x")}) );
}


BOOST_FIXTURE_TEST_CASE( test_the_absolute_value_of_minus_1 , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Abs[-1]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<math::Rational>(1) );
}


BOOST_FIXTURE_TEST_CASE( test_the_absolute_value_of_1 , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Abs[1]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<math::Rational>(1) );
}


BOOST_FIXTURE_TEST_CASE( test_the_absolute_value_of_minus_1_0 , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Abs[-1.]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<math::Real>(1.) );
}


BOOST_FIXTURE_TEST_CASE( test_the_absolute_value_of_1_0 , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Abs[1.]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<math::Real>(1.) );
}


BOOST_FIXTURE_TEST_CASE( test_the_absolute_value_of_the_list_x__y__minus_1 , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Abs[{x, y, -1}]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::FunctionCall>("Abs", {ast::Node::make<ast::Identifier>("x")}), ast::Node::make<ast::FunctionCall>("Abs", {ast::Node::make<ast::Identifier>("y")}), ast::Node::make<math::Rational>(1)}) );
}

BOOST_FIXTURE_TEST_CASE( test_the_absolute_value_of_minus_infinity , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Abs[-Infinity]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::FunctionCall>("DirectedInfinity", {ast::Node::make<math::Rational>(1)}) );
}


BOOST_FIXTURE_TEST_CASE( test_the_absolute_value_of_infinity , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Abs[Infinity]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::FunctionCall>("DirectedInfinity", {ast::Node::make<math::Rational>(1)}) );
}


BOOST_FIXTURE_TEST_CASE( test_the_absolute_value_of_complex_infinity , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Abs[ComplexInfinity]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::FunctionCall>("DirectedInfinity", {ast::Node::make<math::Rational>(1)}) );
}

BOOST_FIXTURE_TEST_CASE( test_the_absolute_value_of_directed_infinity_minus_1 , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Abs[DirectedInfinity[-1]]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::FunctionCall>("DirectedInfinity", {ast::Node::make<math::Rational>(1)}) );
}


BOOST_FIXTURE_TEST_CASE( test_the_absolute_value_of_directed_infinity_1 , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Abs[DirectedInfinity[1]]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::FunctionCall>("DirectedInfinity", {ast::Node::make<math::Rational>(1)}) );
}


BOOST_FIXTURE_TEST_CASE( test_the_absolute_value_of_directed_infinity , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Abs[DirectedInfinity[]]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::FunctionCall>("DirectedInfinity", {ast::Node::make<math::Rational>(1)}) );
}


BOOST_AUTO_TEST_SUITE_END()
