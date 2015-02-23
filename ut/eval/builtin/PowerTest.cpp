
#include <boost/test/unit_test.hpp>

#include "Fixture.hpp"

BOOST_AUTO_TEST_SUITE( PowerTest )

using namespace tungsten;

BOOST_FIXTURE_TEST_CASE( test_Power_of_no_arguments , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Power[]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<math::Rational>(1) );
}


BOOST_FIXTURE_TEST_CASE( test_Power_of_x , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Power[x]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::Identifier>("x") );
}

BOOST_FIXTURE_TEST_CASE( test_0_to_the_power_of_5 , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("0^5");

	//TODO add check for message
	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<math::Rational>(0) );
}

BOOST_FIXTURE_TEST_CASE( test_0_to_the_power_of_0 , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("0^0");

	//TODO add check for message
	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::Identifier>("Indeterminate") );
}

BOOST_FIXTURE_TEST_CASE( test_0_0_to_the_power_of_0 , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("0.0^0");

	//TODO add check for message
	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::Identifier>("Indeterminate") );
}

BOOST_FIXTURE_TEST_CASE( test_0_to_the_power_of_0_0 , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("0^0.0");

	//TODO add check for message
	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::Identifier>("Indeterminate") );
}

BOOST_FIXTURE_TEST_CASE( test_0_0_to_the_power_of_0_0 , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("0.0^0.0");

	//TODO add check for message
	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::Identifier>("Indeterminate") );
}

BOOST_FIXTURE_TEST_CASE( test_big_exponent_overflow , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("2^9999999999999999999999999");

	//TODO add check for message
	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::FunctionCall>("Overflow") );
}

BOOST_FIXTURE_TEST_CASE( test_x_to_the_power_of_0 , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("x^0");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<math::Rational>(1) );
}

BOOST_FIXTURE_TEST_CASE( test_x_to_the_power_of_1 , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("x^1");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::Identifier>("x") );
}

BOOST_FIXTURE_TEST_CASE( test_x_to_the_power_of_0_0 , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("x^0.0");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<math::Real>(1) );
}

BOOST_FIXTURE_TEST_CASE( test_x_to_the_power_of_y , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("x^y");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::Identifier>("y")}) );
}


BOOST_FIXTURE_TEST_CASE( test_one_over_x , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("x^(-1)");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(-1)}) );
}


BOOST_FIXTURE_TEST_CASE( test_one_over_3 , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("3^(-1)");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<math::Rational>(1,3) );
}


BOOST_FIXTURE_TEST_CASE( test_one_over_3_to_the_4th_power , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("3^(-4)");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<math::Rational>(1,81) );
}


BOOST_FIXTURE_TEST_CASE( test_one_over_3_to_the_4th_power_as_Reals , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("(-3.)^4.");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<math::Real>(81) );
}


BOOST_FIXTURE_TEST_CASE( test_one_over_3_to_the_3th_power_as_Reals , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("(-3.)^3.");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<math::Real>(-27) );
}


BOOST_FIXTURE_TEST_CASE( test_2_to_the_32nd_power , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("2^32");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<math::Rational>("4294967296") );
}


BOOST_FIXTURE_TEST_CASE( test_f_of_x_to_the_power_of_g_of_x , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("f[x]^g[x]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::FunctionCall>("f", {ast::Node::make<ast::Identifier>("x")}), ast::Node::make<ast::FunctionCall>("g", {ast::Node::make<ast::Identifier>("x")})}) );
}


BOOST_FIXTURE_TEST_CASE( test_quote_asd_quote_to_the_power_of_quote_dsa_quote , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("\"asd\"^\"dsa\"");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::String>("asd"), ast::Node::make<ast::String>("dsa")}) );
}


BOOST_FIXTURE_TEST_CASE( test_Power_of_x__y_and_z , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Power[x, y, z]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("y"), ast::Node::make<ast::Identifier>("z")})}) );
}


BOOST_FIXTURE_TEST_CASE( test_x_to_the_power_of_y_to_the_power_of_z , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("x^y^z");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("y"), ast::Node::make<ast::Identifier>("z")})}) );
}


BOOST_FIXTURE_TEST_CASE( test_the_quantity_x_to_the_power_of_y_to_the_power_of_z , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("(x^y)^z");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::Identifier>("y")}), ast::Node::make<ast::Identifier>("z")}) );
}

BOOST_FIXTURE_TEST_CASE( test_the_quantity_x_to_the_power_of_y_to_the_power_of_5 , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("(x^y)^5");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<math::Rational>("5"), ast::Node::make<ast::Identifier>("y")})}) );
}

BOOST_FIXTURE_TEST_CASE( test_the_quantity_a_times_b_times_c_cubed , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("(a*b*c)^3");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::FunctionCall>("Times",
			{
					ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("a"), ast::Node::make<math::Rational>(3)}),
					ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("b"), ast::Node::make<math::Rational>(3)}),
					ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("c"), ast::Node::make<math::Rational>(3)})
			}) );
}

BOOST_FIXTURE_TEST_CASE( test_the_quantity_2_times_c_cubed , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("(2*c)^3");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::FunctionCall>("Times",
			{
					ast::Node::make<math::Rational>(8),
					ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("c"), ast::Node::make<math::Rational>(3)})
			}) );
}

BOOST_FIXTURE_TEST_CASE( test_3_to_the_power_of_1_0 , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("3^1.");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<math::Real>(3.) );
}


BOOST_FIXTURE_TEST_CASE( test_2_0_to_the_5th_power , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("2.^5");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<math::Real>(32.) );
}


BOOST_FIXTURE_TEST_CASE( test_2_0_to_the_power_of_5_0 , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("2.^5.");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<math::Real>(32.) );
}


BOOST_FIXTURE_TEST_CASE( test_the_quantity_a_to_the_power_of_b_to_the_5th_power , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("(a^b)^5");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("a"), ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<math::Rational>(5), ast::Node::make<ast::Identifier>("b")})}) );
}


BOOST_FIXTURE_TEST_CASE( test_the_quantity_a_to_the_power_of_b_to_the_power_of_5_0 , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("(a^b)^5.");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("a"), ast::Node::make<ast::Identifier>("b")}), ast::Node::make<math::Real>(5.)}) );
}

BOOST_FIXTURE_TEST_CASE( test_the_square_of_undirected_infinity, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("DirectedInfinity[]^2");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result, ast::Node::make<ast::FunctionCall>("DirectedInfinity", { }) );
}

BOOST_FIXTURE_TEST_CASE( test_the_cube_of_undirected_infinity, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("DirectedInfinity[]^3");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result, ast::Node::make<ast::FunctionCall>("DirectedInfinity", { }) );
}

BOOST_FIXTURE_TEST_CASE( test_the_square_of_positive_infinity, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("DirectedInfinity[1]^2");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result, ast::Node::make<ast::FunctionCall>("DirectedInfinity", {
				ast::Node::make<math::Real>(1)
	}) );
}

BOOST_FIXTURE_TEST_CASE( test_the_cube_of_positive_infinity, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("DirectedInfinity[1]^3");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result, ast::Node::make<ast::FunctionCall>("DirectedInfinity", {
				ast::Node::make<math::Real>(1)
	}) );
}

BOOST_FIXTURE_TEST_CASE( test_the_square_of_negative_infinity, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("DirectedInfinity[-1]^2");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result, ast::Node::make<ast::FunctionCall>("DirectedInfinity", {
				ast::Node::make<math::Real>(1)
	}) );
}

BOOST_FIXTURE_TEST_CASE( test_the_cube_of_negative_infinity, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("DirectedInfinity[-1]^3");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result, ast::Node::make<ast::FunctionCall>("DirectedInfinity", {
				ast::Node::make<math::Real>(-1)
	}) );
}

//These tests functionality in Times as well
BOOST_FIXTURE_TEST_CASE( test_0_over_0 , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("0/0");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::Identifier>("Indeterminate") );
}

BOOST_FIXTURE_TEST_CASE( test_5_over_0 , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("5/0");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::FunctionCall>("DirectedInfinity", {}) );
}

BOOST_FIXTURE_TEST_CASE( test_a_over_0 , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("a/0");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::FunctionCall>("DirectedInfinity", {}) );
}

BOOST_FIXTURE_TEST_CASE( test_a_over_0_0 , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("a/0.0");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::FunctionCall>("DirectedInfinity", {}) );
}

BOOST_FIXTURE_TEST_CASE( test_0_0_over_0_0 , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("0.0/0.0");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::Identifier>("Indeterminate") );
}

BOOST_FIXTURE_TEST_CASE( test_0_over_0_0 , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("0/0.0");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::Identifier>("Indeterminate") );
}

BOOST_FIXTURE_TEST_CASE( test_0_0_over_0 , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("0.0/0");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::Identifier>("Indeterminate") );
}

//SQRT:

BOOST_FIXTURE_TEST_CASE( test_square_root_of_x , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Sqrt[x]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(1,2)}) );
}


BOOST_FIXTURE_TEST_CASE( test_square_root_of_the_list_x__y , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Sqrt[{x, y}]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(1,2)}), ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("y"), ast::Node::make<math::Rational>(1,2)})}) );
}


BOOST_FIXTURE_TEST_CASE( test_square_root_of_the_quantity_x_squared , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Sqrt[x^2]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)}), ast::Node::make<math::Rational>(1,2)}) );
}


BOOST_FIXTURE_TEST_CASE( test_square_root_of_4 , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Sqrt[4]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<math::Rational>(2) );
}


BOOST_FIXTURE_TEST_CASE( test_square_root_of_3 , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Sqrt[3]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<math::Rational>(3), ast::Node::make<math::Rational>(1,2)}) );
}


BOOST_FIXTURE_TEST_CASE( test_square_root_of_4_0 , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Sqrt[4.]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<math::Real>(2.) );
}


BOOST_FIXTURE_TEST_CASE( test_square_root_of_square_root_of_x , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Sqrt[Sqrt[x]]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(1,4)}) );
}


BOOST_FIXTURE_TEST_CASE( test_square_root_of_16 , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Sqrt[Sqrt[16]]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<math::Rational>(2) );
}


BOOST_FIXTURE_TEST_CASE( test_square_root_of_the_list_4__9__16, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Sqrt[{4, 9, 16}]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<math::Rational>(2), ast::Node::make<math::Rational>(3), ast::Node::make<math::Rational>(4)});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_8_to_the_power_of_the_quantity_1_over_3, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("8^(1/3)");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<math::Rational>(2);

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_8_to_the_power_of_the_quantity_2_over_3, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("8^(2/3)");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<math::Rational>(4);

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_the_quantity_1_over_8_to_the_power_of_the_quantity_2_over_3, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("(1/8)^(2/3)");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<math::Rational>(1,4);

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_the_quantity_4_over_9_to_the_power_of_the_quantity_1_over_2, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("(4/9)^(1/2)");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<math::Rational>(2,3);

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_the_quantity_4_over_7_to_the_power_of_the_quantity_1_over_2, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("(4/7)^(1/2)");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<math::Rational>(2), ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<math::Rational>(7), ast::Node::make<math::Rational>(-1,2)})});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_the_quantity_7_over_4_to_the_power_of_the_quantity_1_over_2, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("(7/4)^(1/2)");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<math::Rational>(1,2), ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<math::Rational>(7), ast::Node::make<math::Rational>(1,2)}) });

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_AUTO_TEST_SUITE_END()
