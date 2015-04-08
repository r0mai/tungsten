
#include <boost/test/unit_test.hpp>

#include "Fixture.hpp"

BOOST_FIXTURE_TEST_SUITE( numericalFunctionsTest2, BuiltinFunctionFixture )

using namespace tungsten;

BOOST_AUTO_TEST_CASE( test_Floor_of_x ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Floor[x]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("Floor", {ast::Node::make<ast::Identifier>("x")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_AUTO_TEST_CASE( test_Floor_of_1_5 ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Floor[1.5]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<math::Rational>(1);

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_AUTO_TEST_CASE( test_Floor_of_15 ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Floor[15]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<math::Rational>(15);

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_AUTO_TEST_CASE( test_Floor_of_minus_2 ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Floor[-2]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<math::Rational>(-2);

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_AUTO_TEST_CASE( test_Floor_of_0 ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Floor[0]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<math::Rational>(0);

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_AUTO_TEST_CASE( test_Floor_of_the_quantity_1_over_2 ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Floor[1/2]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<math::Rational>(0);

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_AUTO_TEST_CASE( test_Floor_of_the_quantity_minus_1_over_2 ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Floor[-2^(-1)]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<math::Rational>(-1);

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_AUTO_TEST_CASE( test_Floor_of_the_list_x__1_5__minus_1_5__1__minus_1__1_over_2__3_over_4__minus_3_over_4 ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Floor[{x, 1.5, -1.5, 1, -1, 1/2, 3/4, -3/4}]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::FunctionCall>("Floor", {ast::Node::make<ast::Identifier>("x")}), ast::Node::make<math::Rational>(1), ast::Node::make<math::Rational>(-2), ast::Node::make<math::Rational>(1), ast::Node::make<math::Rational>(-1), ast::Node::make<math::Rational>(0), ast::Node::make<math::Rational>(0), ast::Node::make<math::Rational>(-1)});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_AUTO_TEST_CASE( test_Floor_of_Pi ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Floor[Pi]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<math::Rational>(3);

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_AUTO_TEST_CASE( test_Floor_of_the_quantity_Pi_plus_E ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Floor[Pi + E]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<math::Rational>(5);

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_AUTO_TEST_CASE( test_Floor_of_E ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Floor[E]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<math::Rational>(2);

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_AUTO_TEST_CASE( test_Ceiling_of_x ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Ceiling[x]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("Ceiling", {ast::Node::make<ast::Identifier>("x")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_AUTO_TEST_CASE( test_Ceiling_of_1_5 ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Ceiling[1.5]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<math::Rational>(2);

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_AUTO_TEST_CASE( test_Ceiling_of_15 ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Ceiling[15]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<math::Rational>(15);

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_AUTO_TEST_CASE( test_Ceiling_of_minus_2 ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Ceiling[-2]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<math::Rational>(-2);

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_AUTO_TEST_CASE( test_Ceiling_of_0 ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Ceiling[0]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<math::Rational>(0);

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_AUTO_TEST_CASE( test_Ceiling_of_the_quantity_1_over_2 ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Ceiling[1/2]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<math::Rational>(1);

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_AUTO_TEST_CASE( test_Ceiling_of_the_quantity_minus_1_over_2 ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Ceiling[-2^(-1)]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<math::Rational>(0);

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_AUTO_TEST_CASE( test_Ceiling_of_Pi ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Ceiling[Pi]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<math::Rational>(4);

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_AUTO_TEST_CASE( test_Ceiling_of_the_quantity_Pi_plus_E ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Ceiling[Pi + E]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<math::Rational>(6);

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_AUTO_TEST_CASE( test_Ceiling_of_E ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Ceiling[E]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<math::Rational>(3);

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_AUTO_TEST_CASE( test_the_integer_closest_to_x ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Round[x]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("Round", {ast::Node::make<ast::Identifier>("x")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_AUTO_TEST_CASE( test_the_integer_closest_to_1_5 ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Round[1.5]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<math::Rational>(2);

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_AUTO_TEST_CASE( test_the_integer_closest_to_2_5 ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Round[2.5]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<math::Rational>(2);

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_AUTO_TEST_CASE( test_the_integer_closest_to_3_5 ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Round[3.5]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<math::Rational>(4);

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_AUTO_TEST_CASE( test_the_integer_closest_to_minus_1_5 ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Round[-1.5]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<math::Rational>(-2);

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_AUTO_TEST_CASE( test_the_integer_closest_to_minus_2_5 ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Round[-2.5]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<math::Rational>(-2);

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_AUTO_TEST_CASE( test_the_integer_closest_to_minus_3_5 ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Round[-3.5]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<math::Rational>(-4);

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_AUTO_TEST_CASE( test_the_integer_closest_to_15 ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Round[15]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<math::Rational>(15);

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_AUTO_TEST_CASE( test_the_integer_closest_to_minus_2 ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Round[-2]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<math::Rational>(-2);

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_AUTO_TEST_CASE( test_the_integer_closest_to_0 ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Round[0]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<math::Rational>(0);

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_AUTO_TEST_CASE( test_the_integer_closest_to_the_quantity_1_over_2 ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Round[1/2]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<math::Rational>(0);

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_AUTO_TEST_CASE( test_the_integer_closest_to_the_quantity_minus_1_over_2 ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Round[-2^(-1)]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<math::Rational>(0);

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_AUTO_TEST_CASE( test_the_integer_closest_to_Pi ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Round[Pi]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<math::Rational>(3);

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_AUTO_TEST_CASE( test_the_integer_closest_to_the_quantity_Pi_plus_E ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Round[Pi + E]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<math::Rational>(6);

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_AUTO_TEST_CASE( test_the_integer_closest_to_E ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Round[E]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<math::Rational>(3);

	BOOST_CHECK_EQUAL( *result, expected );
}

BOOST_AUTO_TEST_CASE( test_Floor_of_Floor_of_x ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Floor[Floor[x]]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("Floor", {ast::Node::make<ast::Identifier>("x")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_AUTO_TEST_CASE( test_Ceiling_of_Ceiling_of_x ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Ceiling[Ceiling[x]]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("Ceiling", {ast::Node::make<ast::Identifier>("x")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_AUTO_TEST_CASE( test_the_integer_closest_to_the_integer_closest_to_x ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Round[Round[x]]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("Round", {ast::Node::make<ast::Identifier>("x")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_AUTO_TEST_CASE( test_Re_of_positive_rational ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Re[2]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<math::Rational>(2);

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_AUTO_TEST_CASE( test_Re_of_negative_rational ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Re[-2]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<math::Rational>(-2);

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_AUTO_TEST_CASE( test_Re_of_rational_zero ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Re[0]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<math::Rational>(0);

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_AUTO_TEST_CASE( test_Re_of_positive_real ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Re[2.0]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<math::Real>(2);

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_AUTO_TEST_CASE( test_Re_of_negative_real ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Re[-2.0]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<math::Real>(-2);

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_AUTO_TEST_CASE( test_Re_of_real_zero ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Re[0.0]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<math::Real>(0);

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_AUTO_TEST_CASE( test_Re_of_rational_plus_I ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Re[2+I]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<math::Rational>(2);

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_AUTO_TEST_CASE( test_Re_of_rational_plus_float_I ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Re[2+3.2I]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<math::Real>(2);

	BOOST_CHECK_EQUAL( *result, expected );
}

BOOST_AUTO_TEST_CASE( test_Re_of_real_plus_I ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Re[2.0+I]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<math::Real>(2);

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_AUTO_TEST_SUITE_END()
