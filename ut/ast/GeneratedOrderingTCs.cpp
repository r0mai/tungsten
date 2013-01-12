
#include <boost/test/unit_test.hpp>

#include "ast/Node.hpp"

BOOST_AUTO_TEST_SUITE( GeneratedOrderingTCs )

using namespace tungsten;

//#1 : {x, "abc", 1.5, Sin[a], 2}
//#2 : {x^2, x^3, x, x^-1, x^x}

//-------------------1-------------------

BOOST_AUTO_TEST_CASE( test_x_compared_to_x ) {
	ast::Node x = ast::Node::make<ast::Identifier>("x");
	ast::Node y = ast::Node::make<ast::Identifier>("x");
	BOOST_CHECK_LE(x,y);
	BOOST_CHECK_LE(y,x);
	BOOST_CHECK_EQUAL(x,y);
}


BOOST_AUTO_TEST_CASE( test_x_compared_to_abc ) {
	ast::Node x = ast::Node::make<ast::Identifier>("x");
	ast::Node y = ast::Node::make<ast::String>("abc");
	BOOST_CHECK_LE(y,x);
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK_LT(y,x);
}


BOOST_AUTO_TEST_CASE( test_x_compared_to_1_5 ) {
	ast::Node x = ast::Node::make<ast::Identifier>("x");
	ast::Node y = ast::Node::make<math::Real>(1.5);
	BOOST_CHECK_LE(y,x);
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK_LT(y,x);
}


BOOST_AUTO_TEST_CASE( test_x_compared_to_sine_of_a ) {
	ast::Node x = ast::Node::make<ast::Identifier>("x");
	ast::Node y = ast::Node::make<ast::FunctionCall>("Sin", {ast::Node::make<ast::Identifier>("a")});
	BOOST_CHECK_LE(x,y);
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK_LT(x,y);
}


BOOST_AUTO_TEST_CASE( test_x_compared_to_2 ) {
	ast::Node x = ast::Node::make<ast::Identifier>("x");
	ast::Node y = ast::Node::make<math::Rational>(2);
	BOOST_CHECK_LE(y,x);
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK_LT(y,x);
}


BOOST_AUTO_TEST_CASE( test_abc_compared_to_x ) {
	ast::Node x = ast::Node::make<ast::String>("abc");
	ast::Node y = ast::Node::make<ast::Identifier>("x");
	BOOST_CHECK_LE(x,y);
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK_LT(x,y);
}


BOOST_AUTO_TEST_CASE( test_abc_compared_to_abc ) {
	ast::Node x = ast::Node::make<ast::String>("abc");
	ast::Node y = ast::Node::make<ast::String>("abc");
	BOOST_CHECK_LE(x,y);
	BOOST_CHECK_LE(y,x);
	BOOST_CHECK_EQUAL(x,y);
}


BOOST_AUTO_TEST_CASE( test_abc_compared_to_1_5 ) {
	ast::Node x = ast::Node::make<ast::String>("abc");
	ast::Node y = ast::Node::make<math::Real>(1.5);
	BOOST_CHECK_LE(y,x);
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK_LT(y,x);
}


BOOST_AUTO_TEST_CASE( test_abc_compared_to_sine_of_a ) {
	ast::Node x = ast::Node::make<ast::String>("abc");
	ast::Node y = ast::Node::make<ast::FunctionCall>("Sin", {ast::Node::make<ast::Identifier>("a")});
	BOOST_CHECK_LE(x,y);
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK_LT(x,y);
}


BOOST_AUTO_TEST_CASE( test_abc_compared_to_2 ) {
	ast::Node x = ast::Node::make<ast::String>("abc");
	ast::Node y = ast::Node::make<math::Rational>(2);
	BOOST_CHECK_LE(y,x);
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK_LT(y,x);
}


BOOST_AUTO_TEST_CASE( test_1_5_compared_to_x ) {
	ast::Node x = ast::Node::make<math::Real>(1.5);
	ast::Node y = ast::Node::make<ast::Identifier>("x");
	BOOST_CHECK_LE(x,y);
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK_LT(x,y);
}


BOOST_AUTO_TEST_CASE( test_1_5_compared_to_abc ) {
	ast::Node x = ast::Node::make<math::Real>(1.5);
	ast::Node y = ast::Node::make<ast::String>("abc");
	BOOST_CHECK_LE(x,y);
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK_LT(x,y);
}


BOOST_AUTO_TEST_CASE( test_1_5_compared_to_1_5 ) {
	ast::Node x = ast::Node::make<math::Real>(1.5);
	ast::Node y = ast::Node::make<math::Real>(1.5);
	BOOST_CHECK_LE(x,y);
	BOOST_CHECK_LE(y,x);
	BOOST_CHECK_EQUAL(x,y);
}


BOOST_AUTO_TEST_CASE( test_1_5_compared_to_sine_of_a ) {
	ast::Node x = ast::Node::make<math::Real>(1.5);
	ast::Node y = ast::Node::make<ast::FunctionCall>("Sin", {ast::Node::make<ast::Identifier>("a")});
	BOOST_CHECK_LE(x,y);
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK_LT(x,y);
}


BOOST_AUTO_TEST_CASE( test_1_5_compared_to_2 ) {
	ast::Node x = ast::Node::make<math::Real>(1.5);
	ast::Node y = ast::Node::make<math::Rational>(2);
	BOOST_CHECK_LE(x,y);
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK_LT(x,y);
}


BOOST_AUTO_TEST_CASE( test_sine_of_a_compared_to_x ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Sin", {ast::Node::make<ast::Identifier>("a")});
	ast::Node y = ast::Node::make<ast::Identifier>("x");
	BOOST_CHECK_LE(y,x);
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK_LT(y,x);
}


BOOST_AUTO_TEST_CASE( test_sine_of_a_compared_to_abc ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Sin", {ast::Node::make<ast::Identifier>("a")});
	ast::Node y = ast::Node::make<ast::String>("abc");
	BOOST_CHECK_LE(y,x);
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK_LT(y,x);
}


BOOST_AUTO_TEST_CASE( test_sine_of_a_compared_to_1_5 ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Sin", {ast::Node::make<ast::Identifier>("a")});
	ast::Node y = ast::Node::make<math::Real>(1.5);
	BOOST_CHECK_LE(y,x);
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK_LT(y,x);
}


BOOST_AUTO_TEST_CASE( test_sine_of_a_compared_to_sine_of_a ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Sin", {ast::Node::make<ast::Identifier>("a")});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Sin", {ast::Node::make<ast::Identifier>("a")});
	BOOST_CHECK_LE(x,y);
	BOOST_CHECK_LE(y,x);
	BOOST_CHECK_EQUAL(x,y);
}


BOOST_AUTO_TEST_CASE( test_sine_of_a_compared_to_2 ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Sin", {ast::Node::make<ast::Identifier>("a")});
	ast::Node y = ast::Node::make<math::Rational>(2);
	BOOST_CHECK_LE(y,x);
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK_LT(y,x);
}


BOOST_AUTO_TEST_CASE( test_2_compared_to_x ) {
	ast::Node x = ast::Node::make<math::Rational>(2);
	ast::Node y = ast::Node::make<ast::Identifier>("x");
	BOOST_CHECK_LE(x,y);
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK_LT(x,y);
}


BOOST_AUTO_TEST_CASE( test_2_compared_to_abc ) {
	ast::Node x = ast::Node::make<math::Rational>(2);
	ast::Node y = ast::Node::make<ast::String>("abc");
	BOOST_CHECK_LE(x,y);
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK_LT(x,y);
}


BOOST_AUTO_TEST_CASE( test_2_compared_to_1_5 ) {
	ast::Node x = ast::Node::make<math::Rational>(2);
	ast::Node y = ast::Node::make<math::Real>(1.5);
	BOOST_CHECK_LE(y,x);
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK_LT(y,x);
}


BOOST_AUTO_TEST_CASE( test_2_compared_to_sine_of_a ) {
	ast::Node x = ast::Node::make<math::Rational>(2);
	ast::Node y = ast::Node::make<ast::FunctionCall>("Sin", {ast::Node::make<ast::Identifier>("a")});
	BOOST_CHECK_LE(x,y);
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK_LT(x,y);
}


BOOST_AUTO_TEST_CASE( test_2_compared_to_2 ) {
	ast::Node x = ast::Node::make<math::Rational>(2);
	ast::Node y = ast::Node::make<math::Rational>(2);
	BOOST_CHECK_LE(x,y);
	BOOST_CHECK_LE(y,x);
	BOOST_CHECK_EQUAL(x,y);
}

//-------------------2-------------------


BOOST_AUTO_TEST_CASE( test_x_squared_compared_to_x_squared ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)});
	BOOST_CHECK_LE(x,y);
	BOOST_CHECK_LE(y,x);
	BOOST_CHECK_EQUAL(x,y);
}


BOOST_AUTO_TEST_CASE( test_x_squared_compared_to_x_cubed ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(3)});
	BOOST_CHECK_LE(x,y);
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK_LT(x,y);
}


BOOST_AUTO_TEST_CASE( test_x_squared_compared_to_x ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)});
	ast::Node y = ast::Node::make<ast::Identifier>("x");
	BOOST_CHECK_LE(y,x);
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK_LT(y,x);
}


BOOST_AUTO_TEST_CASE( test_x_squared_compared_to_one_over_x ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(-1)});
	BOOST_CHECK_LE(y,x);
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK_LT(y,x);
}


BOOST_AUTO_TEST_CASE( test_x_squared_compared_to_x_to_the_power_of_x ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::Identifier>("x")});
	BOOST_CHECK_LE(x,y);
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK_LT(x,y);
}


BOOST_AUTO_TEST_CASE( test_x_cubed_compared_to_x_squared ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(3)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)});
	BOOST_CHECK_LE(y,x);
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK_LT(y,x);
}


BOOST_AUTO_TEST_CASE( test_x_cubed_compared_to_x_cubed ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(3)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(3)});
	BOOST_CHECK_LE(x,y);
	BOOST_CHECK_LE(y,x);
	BOOST_CHECK_EQUAL(x,y);
}


BOOST_AUTO_TEST_CASE( test_x_cubed_compared_to_x ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(3)});
	ast::Node y = ast::Node::make<ast::Identifier>("x");
	BOOST_CHECK_LE(y,x);
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK_LT(y,x);
}


BOOST_AUTO_TEST_CASE( test_x_cubed_compared_to_one_over_x ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(3)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(-1)});
	BOOST_CHECK_LE(y,x);
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK_LT(y,x);
}


BOOST_AUTO_TEST_CASE( test_x_cubed_compared_to_x_to_the_power_of_x ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(3)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::Identifier>("x")});
	BOOST_CHECK_LE(x,y);
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK_LT(x,y);
}


BOOST_AUTO_TEST_CASE( test_x_compared_to_x_squared ) {
	ast::Node x = ast::Node::make<ast::Identifier>("x");
	ast::Node y = ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)});
	BOOST_CHECK_LE(x,y);
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK_LT(x,y);
}


BOOST_AUTO_TEST_CASE( test_x_compared_to_x_cubed ) {
	ast::Node x = ast::Node::make<ast::Identifier>("x");
	ast::Node y = ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(3)});
	BOOST_CHECK_LE(x,y);
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK_LT(x,y);
}

/*
BOOST_AUTO_TEST_CASE( test_x_compared_to_x ) {
	ast::Node x = ast::Node::make<ast::Identifier>("x");
	ast::Node y = ast::Node::make<ast::Identifier>("x");
	BOOST_CHECK_LE(x,y);
	BOOST_CHECK_LE(y,x);
	BOOST_CHECK_EQUAL(x,y);
}
*/

BOOST_AUTO_TEST_CASE( test_x_compared_to_one_over_x ) {
	ast::Node x = ast::Node::make<ast::Identifier>("x");
	ast::Node y = ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(-1)});
	BOOST_CHECK_LE(y,x);
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK_LT(y,x);
}


BOOST_AUTO_TEST_CASE( test_x_compared_to_x_to_the_power_of_x ) {
	ast::Node x = ast::Node::make<ast::Identifier>("x");
	ast::Node y = ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::Identifier>("x")});
	BOOST_CHECK_LE(x,y);
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK_LT(x,y);
}


BOOST_AUTO_TEST_CASE( test_one_over_x_compared_to_x_squared ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(-1)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)});
	BOOST_CHECK_LE(x,y);
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK_LT(x,y);
}


BOOST_AUTO_TEST_CASE( test_one_over_x_compared_to_x_cubed ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(-1)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(3)});
	BOOST_CHECK_LE(x,y);
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK_LT(x,y);
}


BOOST_AUTO_TEST_CASE( test_one_over_x_compared_to_x ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(-1)});
	ast::Node y = ast::Node::make<ast::Identifier>("x");
	BOOST_CHECK_LE(x,y);
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK_LT(x,y);
}


BOOST_AUTO_TEST_CASE( test_one_over_x_compared_to_one_over_x ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(-1)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(-1)});
	BOOST_CHECK_LE(x,y);
	BOOST_CHECK_LE(y,x);
	BOOST_CHECK_EQUAL(x,y);
}


BOOST_AUTO_TEST_CASE( test_one_over_x_compared_to_x_to_the_power_of_x ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(-1)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::Identifier>("x")});
	BOOST_CHECK_LE(x,y);
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK_LT(x,y);
}


BOOST_AUTO_TEST_CASE( test_x_to_the_power_of_x_compared_to_x_squared ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::Identifier>("x")});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)});
	BOOST_CHECK_LE(y,x);
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK_LT(y,x);
}


BOOST_AUTO_TEST_CASE( test_x_to_the_power_of_x_compared_to_x_cubed ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::Identifier>("x")});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(3)});
	BOOST_CHECK_LE(y,x);
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK_LT(y,x);
}


BOOST_AUTO_TEST_CASE( test_x_to_the_power_of_x_compared_to_x ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::Identifier>("x")});
	ast::Node y = ast::Node::make<ast::Identifier>("x");
	BOOST_CHECK_LE(y,x);
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK_LT(y,x);
}


BOOST_AUTO_TEST_CASE( test_x_to_the_power_of_x_compared_to_one_over_x ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::Identifier>("x")});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(-1)});
	BOOST_CHECK_LE(y,x);
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK_LT(y,x);
}


BOOST_AUTO_TEST_CASE( test_x_to_the_power_of_x_compared_to_x_to_the_power_of_x ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::Identifier>("x")});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::Identifier>("x")});
	BOOST_CHECK_LE(x,y);
	BOOST_CHECK_LE(y,x);
	BOOST_CHECK_EQUAL(x,y);
}

BOOST_AUTO_TEST_SUITE_END()
