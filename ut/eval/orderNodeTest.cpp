
#include <boost/test/unit_test.hpp>

#include "eval/orderNode.hpp"

BOOST_AUTO_TEST_SUITE( GeneratedOrderingTCs )

using namespace tungsten;

//=============================================
//{-2 u, 2 u, u, u^2, 2/u, 2 u^2, v, -2 v, 2 v, 2 u v, 2 u^2 v, 2 u v^2}
//=============================================

BOOST_AUTO_TEST_CASE( test_minus_2_times_u_compared_to_minus_2_times_u ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(-2)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(-2)});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_EQUAL(x,y);
}


BOOST_AUTO_TEST_CASE( test_minus_2_times_u_compared_to_2_times_u ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(-2)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(2)});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_minus_2_times_u_compared_to_u ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(-2)});
	ast::Node y = ast::Node::make<ast::Identifier>("u");
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_minus_2_times_u_compared_to_u_squared ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(-2)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(2)});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_minus_2_times_u_compared_to_2_over_u ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(-2)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(-1)}), ast::Node::make<math::Rational>(2)});
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_minus_2_times_u_compared_to_2_times_u_squared ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(-2)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(2)}), ast::Node::make<math::Rational>(2)});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_minus_2_times_u_compared_to_v ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(-2)});
	ast::Node y = ast::Node::make<ast::Identifier>("v");
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_minus_2_times_u_compared_to_minus_2_times_v ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(-2)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("v"), ast::Node::make<math::Rational>(-2)});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_minus_2_times_u_compared_to_2_times_v ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(-2)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("v"), ast::Node::make<math::Rational>(2)});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_minus_2_times_u_compared_to_2_times_u_times_v ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(-2)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<ast::Identifier>("v"), ast::Node::make<math::Rational>(2)});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_minus_2_times_u_compared_to_2_times_u_squared_times_v ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(-2)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(2)}), ast::Node::make<ast::Identifier>("v"), ast::Node::make<math::Rational>(2)});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_minus_2_times_u_compared_to_2_times_u_times_v_squared ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(-2)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("v"), ast::Node::make<math::Rational>(2)}), ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(2)});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_2_times_u_compared_to_minus_2_times_u ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(2)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(-2)});
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_2_times_u_compared_to_2_times_u ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(2)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(2)});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_EQUAL(x,y);
}


BOOST_AUTO_TEST_CASE( test_2_times_u_compared_to_u ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(2)});
	ast::Node y = ast::Node::make<ast::Identifier>("u");
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_2_times_u_compared_to_u_squared ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(2)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(2)});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_2_times_u_compared_to_2_over_u ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(2)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(-1)}), ast::Node::make<math::Rational>(2)});
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_2_times_u_compared_to_2_times_u_squared ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(2)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(2)}), ast::Node::make<math::Rational>(2)});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_2_times_u_compared_to_v ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(2)});
	ast::Node y = ast::Node::make<ast::Identifier>("v");
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_2_times_u_compared_to_minus_2_times_v ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(2)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("v"), ast::Node::make<math::Rational>(-2)});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_2_times_u_compared_to_2_times_v ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(2)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("v"), ast::Node::make<math::Rational>(2)});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_2_times_u_compared_to_2_times_u_times_v ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(2)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<ast::Identifier>("v"), ast::Node::make<math::Rational>(2)});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_2_times_u_compared_to_2_times_u_squared_times_v ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(2)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(2)}), ast::Node::make<ast::Identifier>("v"), ast::Node::make<math::Rational>(2)});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_2_times_u_compared_to_2_times_u_times_v_squared ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(2)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("v"), ast::Node::make<math::Rational>(2)}), ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(2)});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_u_compared_to_minus_2_times_u ) {
	ast::Node x = ast::Node::make<ast::Identifier>("u");
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(-2)});
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_u_compared_to_2_times_u ) {
	ast::Node x = ast::Node::make<ast::Identifier>("u");
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(2)});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_u_compared_to_u ) {
	ast::Node x = ast::Node::make<ast::Identifier>("u");
	ast::Node y = ast::Node::make<ast::Identifier>("u");
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_EQUAL(x,y);
}


BOOST_AUTO_TEST_CASE( test_u_compared_to_u_squared ) {
	ast::Node x = ast::Node::make<ast::Identifier>("u");
	ast::Node y = ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(2)});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_u_compared_to_2_over_u ) {
	ast::Node x = ast::Node::make<ast::Identifier>("u");
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(-1)}), ast::Node::make<math::Rational>(2)});
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_u_compared_to_2_times_u_squared ) {
	ast::Node x = ast::Node::make<ast::Identifier>("u");
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(2)}), ast::Node::make<math::Rational>(2)});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_u_compared_to_v ) {
	ast::Node x = ast::Node::make<ast::Identifier>("u");
	ast::Node y = ast::Node::make<ast::Identifier>("v");
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_u_compared_to_minus_2_times_v ) {
	ast::Node x = ast::Node::make<ast::Identifier>("u");
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("v"), ast::Node::make<math::Rational>(-2)});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_u_compared_to_2_times_v ) {
	ast::Node x = ast::Node::make<ast::Identifier>("u");
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("v"), ast::Node::make<math::Rational>(2)});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_u_compared_to_2_times_u_times_v ) {
	ast::Node x = ast::Node::make<ast::Identifier>("u");
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<ast::Identifier>("v"), ast::Node::make<math::Rational>(2)});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_u_compared_to_2_times_u_squared_times_v ) {
	ast::Node x = ast::Node::make<ast::Identifier>("u");
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(2)}), ast::Node::make<ast::Identifier>("v"), ast::Node::make<math::Rational>(2)});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_u_compared_to_2_times_u_times_v_squared ) {
	ast::Node x = ast::Node::make<ast::Identifier>("u");
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("v"), ast::Node::make<math::Rational>(2)}), ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(2)});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_u_squared_compared_to_minus_2_times_u ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(2)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(-2)});
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_u_squared_compared_to_2_times_u ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(2)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(2)});
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_u_squared_compared_to_u ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(2)});
	ast::Node y = ast::Node::make<ast::Identifier>("u");
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_u_squared_compared_to_u_squared ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(2)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(2)});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_EQUAL(x,y);
}


BOOST_AUTO_TEST_CASE( test_u_squared_compared_to_2_over_u ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(2)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(-1)}), ast::Node::make<math::Rational>(2)});
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_u_squared_compared_to_2_times_u_squared ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(2)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(2)}), ast::Node::make<math::Rational>(2)});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_u_squared_compared_to_v ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(2)});
	ast::Node y = ast::Node::make<ast::Identifier>("v");
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_u_squared_compared_to_minus_2_times_v ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(2)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("v"), ast::Node::make<math::Rational>(-2)});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_u_squared_compared_to_2_times_v ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(2)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("v"), ast::Node::make<math::Rational>(2)});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_u_squared_compared_to_2_times_u_times_v ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(2)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<ast::Identifier>("v"), ast::Node::make<math::Rational>(2)});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_u_squared_compared_to_2_times_u_squared_times_v ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(2)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(2)}), ast::Node::make<ast::Identifier>("v"), ast::Node::make<math::Rational>(2)});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_u_squared_compared_to_2_times_u_times_v_squared ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(2)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("v"), ast::Node::make<math::Rational>(2)}), ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(2)});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_2_over_u_compared_to_minus_2_times_u ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(-1)}), ast::Node::make<math::Rational>(2)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(-2)});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_2_over_u_compared_to_2_times_u ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(-1)}), ast::Node::make<math::Rational>(2)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(2)});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_2_over_u_compared_to_u ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(-1)}), ast::Node::make<math::Rational>(2)});
	ast::Node y = ast::Node::make<ast::Identifier>("u");
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_2_over_u_compared_to_u_squared ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(-1)}), ast::Node::make<math::Rational>(2)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(2)});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_2_over_u_compared_to_2_over_u ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(-1)}), ast::Node::make<math::Rational>(2)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(-1)}), ast::Node::make<math::Rational>(2)});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_EQUAL(x,y);
}


BOOST_AUTO_TEST_CASE( test_2_over_u_compared_to_2_times_u_squared ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(-1)}), ast::Node::make<math::Rational>(2)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(2)}), ast::Node::make<math::Rational>(2)});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_2_over_u_compared_to_v ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(-1)}), ast::Node::make<math::Rational>(2)});
	ast::Node y = ast::Node::make<ast::Identifier>("v");
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_2_over_u_compared_to_minus_2_times_v ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(-1)}), ast::Node::make<math::Rational>(2)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("v"), ast::Node::make<math::Rational>(-2)});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_2_over_u_compared_to_2_times_v ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(-1)}), ast::Node::make<math::Rational>(2)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("v"), ast::Node::make<math::Rational>(2)});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_2_over_u_compared_to_2_times_u_times_v ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(-1)}), ast::Node::make<math::Rational>(2)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<ast::Identifier>("v"), ast::Node::make<math::Rational>(2)});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_2_over_u_compared_to_2_times_u_squared_times_v ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(-1)}), ast::Node::make<math::Rational>(2)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(2)}), ast::Node::make<ast::Identifier>("v"), ast::Node::make<math::Rational>(2)});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_2_over_u_compared_to_2_times_u_times_v_squared ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(-1)}), ast::Node::make<math::Rational>(2)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("v"), ast::Node::make<math::Rational>(2)}), ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(2)});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_2_times_u_squared_compared_to_minus_2_times_u ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(2)}), ast::Node::make<math::Rational>(2)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(-2)});
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_2_times_u_squared_compared_to_2_times_u ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(2)}), ast::Node::make<math::Rational>(2)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(2)});
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_2_times_u_squared_compared_to_u ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(2)}), ast::Node::make<math::Rational>(2)});
	ast::Node y = ast::Node::make<ast::Identifier>("u");
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_2_times_u_squared_compared_to_u_squared ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(2)}), ast::Node::make<math::Rational>(2)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(2)});
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_2_times_u_squared_compared_to_2_over_u ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(2)}), ast::Node::make<math::Rational>(2)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(-1)}), ast::Node::make<math::Rational>(2)});
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_2_times_u_squared_compared_to_2_times_u_squared ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(2)}), ast::Node::make<math::Rational>(2)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(2)}), ast::Node::make<math::Rational>(2)});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_EQUAL(x,y);
}


BOOST_AUTO_TEST_CASE( test_2_times_u_squared_compared_to_v ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(2)}), ast::Node::make<math::Rational>(2)});
	ast::Node y = ast::Node::make<ast::Identifier>("v");
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_2_times_u_squared_compared_to_minus_2_times_v ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(2)}), ast::Node::make<math::Rational>(2)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("v"), ast::Node::make<math::Rational>(-2)});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_2_times_u_squared_compared_to_2_times_v ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(2)}), ast::Node::make<math::Rational>(2)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("v"), ast::Node::make<math::Rational>(2)});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_2_times_u_squared_compared_to_2_times_u_times_v ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(2)}), ast::Node::make<math::Rational>(2)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<ast::Identifier>("v"), ast::Node::make<math::Rational>(2)});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_2_times_u_squared_compared_to_2_times_u_squared_times_v ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(2)}), ast::Node::make<math::Rational>(2)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(2)}), ast::Node::make<ast::Identifier>("v"), ast::Node::make<math::Rational>(2)});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_2_times_u_squared_compared_to_2_times_u_times_v_squared ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(2)}), ast::Node::make<math::Rational>(2)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("v"), ast::Node::make<math::Rational>(2)}), ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(2)});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_v_compared_to_minus_2_times_u ) {
	ast::Node x = ast::Node::make<ast::Identifier>("v");
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(-2)});
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_v_compared_to_2_times_u ) {
	ast::Node x = ast::Node::make<ast::Identifier>("v");
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(2)});
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_v_compared_to_u ) {
	ast::Node x = ast::Node::make<ast::Identifier>("v");
	ast::Node y = ast::Node::make<ast::Identifier>("u");
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_v_compared_to_u_squared ) {
	ast::Node x = ast::Node::make<ast::Identifier>("v");
	ast::Node y = ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(2)});
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_v_compared_to_2_over_u ) {
	ast::Node x = ast::Node::make<ast::Identifier>("v");
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(-1)}), ast::Node::make<math::Rational>(2)});
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_v_compared_to_2_times_u_squared ) {
	ast::Node x = ast::Node::make<ast::Identifier>("v");
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(2)}), ast::Node::make<math::Rational>(2)});
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_v_compared_to_v ) {
	ast::Node x = ast::Node::make<ast::Identifier>("v");
	ast::Node y = ast::Node::make<ast::Identifier>("v");
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_EQUAL(x,y);
}


BOOST_AUTO_TEST_CASE( test_v_compared_to_minus_2_times_v ) {
	ast::Node x = ast::Node::make<ast::Identifier>("v");
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("v"), ast::Node::make<math::Rational>(-2)});
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_v_compared_to_2_times_v ) {
	ast::Node x = ast::Node::make<ast::Identifier>("v");
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("v"), ast::Node::make<math::Rational>(2)});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_v_compared_to_2_times_u_times_v ) {
	ast::Node x = ast::Node::make<ast::Identifier>("v");
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<ast::Identifier>("v"), ast::Node::make<math::Rational>(2)});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_v_compared_to_2_times_u_squared_times_v ) {
	ast::Node x = ast::Node::make<ast::Identifier>("v");
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(2)}), ast::Node::make<ast::Identifier>("v"), ast::Node::make<math::Rational>(2)});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_v_compared_to_2_times_u_times_v_squared ) {
	ast::Node x = ast::Node::make<ast::Identifier>("v");
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("v"), ast::Node::make<math::Rational>(2)}), ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(2)});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_minus_2_times_v_compared_to_minus_2_times_u ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("v"), ast::Node::make<math::Rational>(-2)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(-2)});
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_minus_2_times_v_compared_to_2_times_u ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("v"), ast::Node::make<math::Rational>(-2)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(2)});
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_minus_2_times_v_compared_to_u ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("v"), ast::Node::make<math::Rational>(-2)});
	ast::Node y = ast::Node::make<ast::Identifier>("u");
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_minus_2_times_v_compared_to_u_squared ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("v"), ast::Node::make<math::Rational>(-2)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(2)});
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_minus_2_times_v_compared_to_2_over_u ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("v"), ast::Node::make<math::Rational>(-2)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(-1)}), ast::Node::make<math::Rational>(2)});
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_minus_2_times_v_compared_to_2_times_u_squared ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("v"), ast::Node::make<math::Rational>(-2)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(2)}), ast::Node::make<math::Rational>(2)});
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_minus_2_times_v_compared_to_v ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("v"), ast::Node::make<math::Rational>(-2)});
	ast::Node y = ast::Node::make<ast::Identifier>("v");
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_minus_2_times_v_compared_to_minus_2_times_v ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("v"), ast::Node::make<math::Rational>(-2)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("v"), ast::Node::make<math::Rational>(-2)});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_EQUAL(x,y);
}


BOOST_AUTO_TEST_CASE( test_minus_2_times_v_compared_to_2_times_v ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("v"), ast::Node::make<math::Rational>(-2)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("v"), ast::Node::make<math::Rational>(2)});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_minus_2_times_v_compared_to_2_times_u_times_v ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("v"), ast::Node::make<math::Rational>(-2)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<ast::Identifier>("v"), ast::Node::make<math::Rational>(2)});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_minus_2_times_v_compared_to_2_times_u_squared_times_v ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("v"), ast::Node::make<math::Rational>(-2)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(2)}), ast::Node::make<ast::Identifier>("v"), ast::Node::make<math::Rational>(2)});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_minus_2_times_v_compared_to_2_times_u_times_v_squared ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("v"), ast::Node::make<math::Rational>(-2)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("v"), ast::Node::make<math::Rational>(2)}), ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(2)});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_2_times_v_compared_to_minus_2_times_u ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("v"), ast::Node::make<math::Rational>(2)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(-2)});
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_2_times_v_compared_to_2_times_u ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("v"), ast::Node::make<math::Rational>(2)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(2)});
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_2_times_v_compared_to_u ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("v"), ast::Node::make<math::Rational>(2)});
	ast::Node y = ast::Node::make<ast::Identifier>("u");
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_2_times_v_compared_to_u_squared ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("v"), ast::Node::make<math::Rational>(2)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(2)});
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_2_times_v_compared_to_2_over_u ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("v"), ast::Node::make<math::Rational>(2)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(-1)}), ast::Node::make<math::Rational>(2)});
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_2_times_v_compared_to_2_times_u_squared ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("v"), ast::Node::make<math::Rational>(2)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(2)}), ast::Node::make<math::Rational>(2)});
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_2_times_v_compared_to_v ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("v"), ast::Node::make<math::Rational>(2)});
	ast::Node y = ast::Node::make<ast::Identifier>("v");
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_2_times_v_compared_to_minus_2_times_v ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("v"), ast::Node::make<math::Rational>(2)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("v"), ast::Node::make<math::Rational>(-2)});
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_2_times_v_compared_to_2_times_v ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("v"), ast::Node::make<math::Rational>(2)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("v"), ast::Node::make<math::Rational>(2)});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_EQUAL(x,y);
}


BOOST_AUTO_TEST_CASE( test_2_times_v_compared_to_2_times_u_times_v ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("v"), ast::Node::make<math::Rational>(2)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<ast::Identifier>("v"), ast::Node::make<math::Rational>(2)});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_2_times_v_compared_to_2_times_u_squared_times_v ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("v"), ast::Node::make<math::Rational>(2)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(2)}), ast::Node::make<ast::Identifier>("v"), ast::Node::make<math::Rational>(2)});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_2_times_v_compared_to_2_times_u_times_v_squared ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("v"), ast::Node::make<math::Rational>(2)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("v"), ast::Node::make<math::Rational>(2)}), ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(2)});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_2_times_u_times_v_compared_to_minus_2_times_u ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<ast::Identifier>("v"), ast::Node::make<math::Rational>(2)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(-2)});
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_2_times_u_times_v_compared_to_2_times_u ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<ast::Identifier>("v"), ast::Node::make<math::Rational>(2)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(2)});
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_2_times_u_times_v_compared_to_u ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<ast::Identifier>("v"), ast::Node::make<math::Rational>(2)});
	ast::Node y = ast::Node::make<ast::Identifier>("u");
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_2_times_u_times_v_compared_to_u_squared ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<ast::Identifier>("v"), ast::Node::make<math::Rational>(2)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(2)});
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_2_times_u_times_v_compared_to_2_over_u ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<ast::Identifier>("v"), ast::Node::make<math::Rational>(2)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(-1)}), ast::Node::make<math::Rational>(2)});
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_2_times_u_times_v_compared_to_2_times_u_squared ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<ast::Identifier>("v"), ast::Node::make<math::Rational>(2)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(2)}), ast::Node::make<math::Rational>(2)});
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_2_times_u_times_v_compared_to_v ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<ast::Identifier>("v"), ast::Node::make<math::Rational>(2)});
	ast::Node y = ast::Node::make<ast::Identifier>("v");
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_2_times_u_times_v_compared_to_minus_2_times_v ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<ast::Identifier>("v"), ast::Node::make<math::Rational>(2)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("v"), ast::Node::make<math::Rational>(-2)});
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_2_times_u_times_v_compared_to_2_times_v ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<ast::Identifier>("v"), ast::Node::make<math::Rational>(2)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("v"), ast::Node::make<math::Rational>(2)});
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_2_times_u_times_v_compared_to_2_times_u_times_v ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<ast::Identifier>("v"), ast::Node::make<math::Rational>(2)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<ast::Identifier>("v"), ast::Node::make<math::Rational>(2)});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_EQUAL(x,y);
}


BOOST_AUTO_TEST_CASE( test_2_times_u_times_v_compared_to_2_times_u_squared_times_v ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<ast::Identifier>("v"), ast::Node::make<math::Rational>(2)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(2)}), ast::Node::make<ast::Identifier>("v"), ast::Node::make<math::Rational>(2)});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_2_times_u_times_v_compared_to_2_times_u_times_v_squared ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<ast::Identifier>("v"), ast::Node::make<math::Rational>(2)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("v"), ast::Node::make<math::Rational>(2)}), ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(2)});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_2_times_u_squared_times_v_compared_to_minus_2_times_u ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(2)}), ast::Node::make<ast::Identifier>("v"), ast::Node::make<math::Rational>(2)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(-2)});
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_2_times_u_squared_times_v_compared_to_2_times_u ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(2)}), ast::Node::make<ast::Identifier>("v"), ast::Node::make<math::Rational>(2)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(2)});
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_2_times_u_squared_times_v_compared_to_u ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(2)}), ast::Node::make<ast::Identifier>("v"), ast::Node::make<math::Rational>(2)});
	ast::Node y = ast::Node::make<ast::Identifier>("u");
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_2_times_u_squared_times_v_compared_to_u_squared ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(2)}), ast::Node::make<ast::Identifier>("v"), ast::Node::make<math::Rational>(2)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(2)});
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_2_times_u_squared_times_v_compared_to_2_over_u ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(2)}), ast::Node::make<ast::Identifier>("v"), ast::Node::make<math::Rational>(2)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(-1)}), ast::Node::make<math::Rational>(2)});
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_2_times_u_squared_times_v_compared_to_2_times_u_squared ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(2)}), ast::Node::make<ast::Identifier>("v"), ast::Node::make<math::Rational>(2)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(2)}), ast::Node::make<math::Rational>(2)});
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_2_times_u_squared_times_v_compared_to_v ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(2)}), ast::Node::make<ast::Identifier>("v"), ast::Node::make<math::Rational>(2)});
	ast::Node y = ast::Node::make<ast::Identifier>("v");
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_2_times_u_squared_times_v_compared_to_minus_2_times_v ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(2)}), ast::Node::make<ast::Identifier>("v"), ast::Node::make<math::Rational>(2)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("v"), ast::Node::make<math::Rational>(-2)});
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_2_times_u_squared_times_v_compared_to_2_times_v ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(2)}), ast::Node::make<ast::Identifier>("v"), ast::Node::make<math::Rational>(2)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("v"), ast::Node::make<math::Rational>(2)});
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_2_times_u_squared_times_v_compared_to_2_times_u_times_v ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(2)}), ast::Node::make<ast::Identifier>("v"), ast::Node::make<math::Rational>(2)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<ast::Identifier>("v"), ast::Node::make<math::Rational>(2)});
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_2_times_u_squared_times_v_compared_to_2_times_u_squared_times_v ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(2)}), ast::Node::make<ast::Identifier>("v"), ast::Node::make<math::Rational>(2)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(2)}), ast::Node::make<ast::Identifier>("v"), ast::Node::make<math::Rational>(2)});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_EQUAL(x,y);
}


BOOST_AUTO_TEST_CASE( test_2_times_u_squared_times_v_compared_to_2_times_u_times_v_squared ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(2)}), ast::Node::make<ast::Identifier>("v"), ast::Node::make<math::Rational>(2)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("v"), ast::Node::make<math::Rational>(2)}), ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(2)});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_2_times_u_times_v_squared_compared_to_minus_2_times_u ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("v"), ast::Node::make<math::Rational>(2)}), ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(2)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(-2)});
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_2_times_u_times_v_squared_compared_to_2_times_u ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("v"), ast::Node::make<math::Rational>(2)}), ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(2)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(2)});
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_2_times_u_times_v_squared_compared_to_u ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("v"), ast::Node::make<math::Rational>(2)}), ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(2)});
	ast::Node y = ast::Node::make<ast::Identifier>("u");
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_2_times_u_times_v_squared_compared_to_u_squared ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("v"), ast::Node::make<math::Rational>(2)}), ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(2)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(2)});
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_2_times_u_times_v_squared_compared_to_2_over_u ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("v"), ast::Node::make<math::Rational>(2)}), ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(2)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(-1)}), ast::Node::make<math::Rational>(2)});
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_2_times_u_times_v_squared_compared_to_2_times_u_squared ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("v"), ast::Node::make<math::Rational>(2)}), ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(2)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(2)}), ast::Node::make<math::Rational>(2)});
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_2_times_u_times_v_squared_compared_to_v ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("v"), ast::Node::make<math::Rational>(2)}), ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(2)});
	ast::Node y = ast::Node::make<ast::Identifier>("v");
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_2_times_u_times_v_squared_compared_to_minus_2_times_v ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("v"), ast::Node::make<math::Rational>(2)}), ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(2)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("v"), ast::Node::make<math::Rational>(-2)});
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_2_times_u_times_v_squared_compared_to_2_times_v ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("v"), ast::Node::make<math::Rational>(2)}), ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(2)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("v"), ast::Node::make<math::Rational>(2)});
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_2_times_u_times_v_squared_compared_to_2_times_u_times_v ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("v"), ast::Node::make<math::Rational>(2)}), ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(2)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<ast::Identifier>("v"), ast::Node::make<math::Rational>(2)});
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_2_times_u_times_v_squared_compared_to_2_times_u_squared_times_v ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("v"), ast::Node::make<math::Rational>(2)}), ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(2)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(2)}), ast::Node::make<ast::Identifier>("v"), ast::Node::make<math::Rational>(2)});
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_2_times_u_times_v_squared_compared_to_2_times_u_times_v_squared ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("v"), ast::Node::make<math::Rational>(2)}), ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(2)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("v"), ast::Node::make<math::Rational>(2)}), ast::Node::make<ast::Identifier>("u"), ast::Node::make<math::Rational>(2)});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_EQUAL(x,y);
}

//=============================================
//{"", "X", "x", "Y", "y", "Xy", "xY", "xy", "XY"}
//=============================================

BOOST_AUTO_TEST_CASE( test_string__compared_to_ ) {
	ast::Node x = ast::Node::make<ast::String>("");
	ast::Node y = ast::Node::make<ast::String>("");
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_EQUAL(x,y);
}


BOOST_AUTO_TEST_CASE( test_string__compared_to_X ) {
	ast::Node x = ast::Node::make<ast::String>("");
	ast::Node y = ast::Node::make<ast::String>("X");
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_string__compared_to_x ) {
	ast::Node x = ast::Node::make<ast::String>("");
	ast::Node y = ast::Node::make<ast::String>("x");
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_string__compared_to_Y ) {
	ast::Node x = ast::Node::make<ast::String>("");
	ast::Node y = ast::Node::make<ast::String>("Y");
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_string__compared_to_y ) {
	ast::Node x = ast::Node::make<ast::String>("");
	ast::Node y = ast::Node::make<ast::String>("y");
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_string__compared_to_Xy ) {
	ast::Node x = ast::Node::make<ast::String>("");
	ast::Node y = ast::Node::make<ast::String>("Xy");
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_string__compared_to_xY ) {
	ast::Node x = ast::Node::make<ast::String>("");
	ast::Node y = ast::Node::make<ast::String>("xY");
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_string__compared_to_xy ) {
	ast::Node x = ast::Node::make<ast::String>("");
	ast::Node y = ast::Node::make<ast::String>("xy");
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_string__compared_to_XY ) {
	ast::Node x = ast::Node::make<ast::String>("");
	ast::Node y = ast::Node::make<ast::String>("XY");
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_string_X_compared_to_ ) {
	ast::Node x = ast::Node::make<ast::String>("X");
	ast::Node y = ast::Node::make<ast::String>("");
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_string_X_compared_to_X ) {
	ast::Node x = ast::Node::make<ast::String>("X");
	ast::Node y = ast::Node::make<ast::String>("X");
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_EQUAL(x,y);
}


BOOST_AUTO_TEST_CASE( test_string_X_compared_to_x ) {
	ast::Node x = ast::Node::make<ast::String>("X");
	ast::Node y = ast::Node::make<ast::String>("x");
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_string_X_compared_to_Y ) {
	ast::Node x = ast::Node::make<ast::String>("X");
	ast::Node y = ast::Node::make<ast::String>("Y");
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_string_X_compared_to_y ) {
	ast::Node x = ast::Node::make<ast::String>("X");
	ast::Node y = ast::Node::make<ast::String>("y");
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_string_X_compared_to_Xy ) {
	ast::Node x = ast::Node::make<ast::String>("X");
	ast::Node y = ast::Node::make<ast::String>("Xy");
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_string_X_compared_to_xY ) {
	ast::Node x = ast::Node::make<ast::String>("X");
	ast::Node y = ast::Node::make<ast::String>("xY");
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_string_X_compared_to_xy ) {
	ast::Node x = ast::Node::make<ast::String>("X");
	ast::Node y = ast::Node::make<ast::String>("xy");
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_string_X_compared_to_XY ) {
	ast::Node x = ast::Node::make<ast::String>("X");
	ast::Node y = ast::Node::make<ast::String>("XY");
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_string_x_compared_to_ ) {
	ast::Node x = ast::Node::make<ast::String>("x");
	ast::Node y = ast::Node::make<ast::String>("");
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_string_x_compared_to_X ) {
	ast::Node x = ast::Node::make<ast::String>("x");
	ast::Node y = ast::Node::make<ast::String>("X");
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_string_x_compared_to_x ) {
	ast::Node x = ast::Node::make<ast::String>("x");
	ast::Node y = ast::Node::make<ast::String>("x");
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_EQUAL(x,y);
}


BOOST_AUTO_TEST_CASE( test_string_x_compared_to_Y ) {
	ast::Node x = ast::Node::make<ast::String>("x");
	ast::Node y = ast::Node::make<ast::String>("Y");
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_string_x_compared_to_y ) {
	ast::Node x = ast::Node::make<ast::String>("x");
	ast::Node y = ast::Node::make<ast::String>("y");
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_string_x_compared_to_Xy ) {
	ast::Node x = ast::Node::make<ast::String>("x");
	ast::Node y = ast::Node::make<ast::String>("Xy");
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_string_x_compared_to_xY ) {
	ast::Node x = ast::Node::make<ast::String>("x");
	ast::Node y = ast::Node::make<ast::String>("xY");
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_string_x_compared_to_xy ) {
	ast::Node x = ast::Node::make<ast::String>("x");
	ast::Node y = ast::Node::make<ast::String>("xy");
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_string_x_compared_to_XY ) {
	ast::Node x = ast::Node::make<ast::String>("x");
	ast::Node y = ast::Node::make<ast::String>("XY");
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_string_Y_compared_to_ ) {
	ast::Node x = ast::Node::make<ast::String>("Y");
	ast::Node y = ast::Node::make<ast::String>("");
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_string_Y_compared_to_X ) {
	ast::Node x = ast::Node::make<ast::String>("Y");
	ast::Node y = ast::Node::make<ast::String>("X");
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_string_Y_compared_to_x ) {
	ast::Node x = ast::Node::make<ast::String>("Y");
	ast::Node y = ast::Node::make<ast::String>("x");
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_string_Y_compared_to_Y ) {
	ast::Node x = ast::Node::make<ast::String>("Y");
	ast::Node y = ast::Node::make<ast::String>("Y");
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_EQUAL(x,y);
}


BOOST_AUTO_TEST_CASE( test_string_Y_compared_to_y ) {
	ast::Node x = ast::Node::make<ast::String>("Y");
	ast::Node y = ast::Node::make<ast::String>("y");
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_string_Y_compared_to_Xy ) {
	ast::Node x = ast::Node::make<ast::String>("Y");
	ast::Node y = ast::Node::make<ast::String>("Xy");
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_string_Y_compared_to_xY ) {
	ast::Node x = ast::Node::make<ast::String>("Y");
	ast::Node y = ast::Node::make<ast::String>("xY");
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_string_Y_compared_to_xy ) {
	ast::Node x = ast::Node::make<ast::String>("Y");
	ast::Node y = ast::Node::make<ast::String>("xy");
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_string_Y_compared_to_XY ) {
	ast::Node x = ast::Node::make<ast::String>("Y");
	ast::Node y = ast::Node::make<ast::String>("XY");
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_string_y_compared_to_ ) {
	ast::Node x = ast::Node::make<ast::String>("y");
	ast::Node y = ast::Node::make<ast::String>("");
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_string_y_compared_to_X ) {
	ast::Node x = ast::Node::make<ast::String>("y");
	ast::Node y = ast::Node::make<ast::String>("X");
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_string_y_compared_to_x ) {
	ast::Node x = ast::Node::make<ast::String>("y");
	ast::Node y = ast::Node::make<ast::String>("x");
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_string_y_compared_to_Y ) {
	ast::Node x = ast::Node::make<ast::String>("y");
	ast::Node y = ast::Node::make<ast::String>("Y");
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_string_y_compared_to_y ) {
	ast::Node x = ast::Node::make<ast::String>("y");
	ast::Node y = ast::Node::make<ast::String>("y");
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_EQUAL(x,y);
}


BOOST_AUTO_TEST_CASE( test_string_y_compared_to_Xy ) {
	ast::Node x = ast::Node::make<ast::String>("y");
	ast::Node y = ast::Node::make<ast::String>("Xy");
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_string_y_compared_to_xY ) {
	ast::Node x = ast::Node::make<ast::String>("y");
	ast::Node y = ast::Node::make<ast::String>("xY");
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_string_y_compared_to_xy ) {
	ast::Node x = ast::Node::make<ast::String>("y");
	ast::Node y = ast::Node::make<ast::String>("xy");
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_string_y_compared_to_XY ) {
	ast::Node x = ast::Node::make<ast::String>("y");
	ast::Node y = ast::Node::make<ast::String>("XY");
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_string_Xy_compared_to_ ) {
	ast::Node x = ast::Node::make<ast::String>("Xy");
	ast::Node y = ast::Node::make<ast::String>("");
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_string_Xy_compared_to_X ) {
	ast::Node x = ast::Node::make<ast::String>("Xy");
	ast::Node y = ast::Node::make<ast::String>("X");
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_string_Xy_compared_to_x ) {
	ast::Node x = ast::Node::make<ast::String>("Xy");
	ast::Node y = ast::Node::make<ast::String>("x");
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_string_Xy_compared_to_Y ) {
	ast::Node x = ast::Node::make<ast::String>("Xy");
	ast::Node y = ast::Node::make<ast::String>("Y");
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_string_Xy_compared_to_y ) {
	ast::Node x = ast::Node::make<ast::String>("Xy");
	ast::Node y = ast::Node::make<ast::String>("y");
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_string_Xy_compared_to_Xy ) {
	ast::Node x = ast::Node::make<ast::String>("Xy");
	ast::Node y = ast::Node::make<ast::String>("Xy");
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_EQUAL(x,y);
}


BOOST_AUTO_TEST_CASE( test_string_Xy_compared_to_xY ) {
	ast::Node x = ast::Node::make<ast::String>("Xy");
	ast::Node y = ast::Node::make<ast::String>("xY");
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_string_Xy_compared_to_xy ) {
	ast::Node x = ast::Node::make<ast::String>("Xy");
	ast::Node y = ast::Node::make<ast::String>("xy");
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_string_Xy_compared_to_XY ) {
	ast::Node x = ast::Node::make<ast::String>("Xy");
	ast::Node y = ast::Node::make<ast::String>("XY");
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_string_xY_compared_to_ ) {
	ast::Node x = ast::Node::make<ast::String>("xY");
	ast::Node y = ast::Node::make<ast::String>("");
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_string_xY_compared_to_X ) {
	ast::Node x = ast::Node::make<ast::String>("xY");
	ast::Node y = ast::Node::make<ast::String>("X");
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_string_xY_compared_to_x ) {
	ast::Node x = ast::Node::make<ast::String>("xY");
	ast::Node y = ast::Node::make<ast::String>("x");
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_string_xY_compared_to_Y ) {
	ast::Node x = ast::Node::make<ast::String>("xY");
	ast::Node y = ast::Node::make<ast::String>("Y");
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_string_xY_compared_to_y ) {
	ast::Node x = ast::Node::make<ast::String>("xY");
	ast::Node y = ast::Node::make<ast::String>("y");
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_string_xY_compared_to_Xy ) {
	ast::Node x = ast::Node::make<ast::String>("xY");
	ast::Node y = ast::Node::make<ast::String>("Xy");
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_string_xY_compared_to_xY ) {
	ast::Node x = ast::Node::make<ast::String>("xY");
	ast::Node y = ast::Node::make<ast::String>("xY");
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_EQUAL(x,y);
}


BOOST_AUTO_TEST_CASE( test_string_xY_compared_to_xy ) {
	ast::Node x = ast::Node::make<ast::String>("xY");
	ast::Node y = ast::Node::make<ast::String>("xy");
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_string_xY_compared_to_XY ) {
	ast::Node x = ast::Node::make<ast::String>("xY");
	ast::Node y = ast::Node::make<ast::String>("XY");
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_string_xy_compared_to_ ) {
	ast::Node x = ast::Node::make<ast::String>("xy");
	ast::Node y = ast::Node::make<ast::String>("");
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_string_xy_compared_to_X ) {
	ast::Node x = ast::Node::make<ast::String>("xy");
	ast::Node y = ast::Node::make<ast::String>("X");
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_string_xy_compared_to_x ) {
	ast::Node x = ast::Node::make<ast::String>("xy");
	ast::Node y = ast::Node::make<ast::String>("x");
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_string_xy_compared_to_Y ) {
	ast::Node x = ast::Node::make<ast::String>("xy");
	ast::Node y = ast::Node::make<ast::String>("Y");
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_string_xy_compared_to_y ) {
	ast::Node x = ast::Node::make<ast::String>("xy");
	ast::Node y = ast::Node::make<ast::String>("y");
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_string_xy_compared_to_Xy ) {
	ast::Node x = ast::Node::make<ast::String>("xy");
	ast::Node y = ast::Node::make<ast::String>("Xy");
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_string_xy_compared_to_xY ) {
	ast::Node x = ast::Node::make<ast::String>("xy");
	ast::Node y = ast::Node::make<ast::String>("xY");
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_string_xy_compared_to_xy ) {
	ast::Node x = ast::Node::make<ast::String>("xy");
	ast::Node y = ast::Node::make<ast::String>("xy");
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_EQUAL(x,y);
}


BOOST_AUTO_TEST_CASE( test_string_xy_compared_to_XY ) {
	ast::Node x = ast::Node::make<ast::String>("xy");
	ast::Node y = ast::Node::make<ast::String>("XY");
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_string_XY_compared_to_ ) {
	ast::Node x = ast::Node::make<ast::String>("XY");
	ast::Node y = ast::Node::make<ast::String>("");
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_string_XY_compared_to_X ) {
	ast::Node x = ast::Node::make<ast::String>("XY");
	ast::Node y = ast::Node::make<ast::String>("X");
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_string_XY_compared_to_x ) {
	ast::Node x = ast::Node::make<ast::String>("XY");
	ast::Node y = ast::Node::make<ast::String>("x");
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_string_XY_compared_to_Y ) {
	ast::Node x = ast::Node::make<ast::String>("XY");
	ast::Node y = ast::Node::make<ast::String>("Y");
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_string_XY_compared_to_y ) {
	ast::Node x = ast::Node::make<ast::String>("XY");
	ast::Node y = ast::Node::make<ast::String>("y");
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_string_XY_compared_to_Xy ) {
	ast::Node x = ast::Node::make<ast::String>("XY");
	ast::Node y = ast::Node::make<ast::String>("Xy");
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_string_XY_compared_to_xY ) {
	ast::Node x = ast::Node::make<ast::String>("XY");
	ast::Node y = ast::Node::make<ast::String>("xY");
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_string_XY_compared_to_xy ) {
	ast::Node x = ast::Node::make<ast::String>("XY");
	ast::Node y = ast::Node::make<ast::String>("xy");
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_string_XY_compared_to_XY ) {
	ast::Node x = ast::Node::make<ast::String>("XY");
	ast::Node y = ast::Node::make<ast::String>("XY");
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_EQUAL(x,y);
}

//=============================================
//{X, x, Y, y, Xy, xY, xy, XY}
//=============================================

BOOST_AUTO_TEST_CASE( test_X_compared_to_X ) {
	ast::Node x = ast::Node::make<ast::Identifier>("X");
	ast::Node y = ast::Node::make<ast::Identifier>("X");
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_EQUAL(x,y);
}


BOOST_AUTO_TEST_CASE( test_X_compared_to_x ) {
	ast::Node x = ast::Node::make<ast::Identifier>("X");
	ast::Node y = ast::Node::make<ast::Identifier>("x");
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_X_compared_to_Y ) {
	ast::Node x = ast::Node::make<ast::Identifier>("X");
	ast::Node y = ast::Node::make<ast::Identifier>("Y");
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_X_compared_to_y ) {
	ast::Node x = ast::Node::make<ast::Identifier>("X");
	ast::Node y = ast::Node::make<ast::Identifier>("y");
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_X_compared_to_Xy ) {
	ast::Node x = ast::Node::make<ast::Identifier>("X");
	ast::Node y = ast::Node::make<ast::Identifier>("Xy");
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_X_compared_to_xY ) {
	ast::Node x = ast::Node::make<ast::Identifier>("X");
	ast::Node y = ast::Node::make<ast::Identifier>("xY");
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_X_compared_to_xy ) {
	ast::Node x = ast::Node::make<ast::Identifier>("X");
	ast::Node y = ast::Node::make<ast::Identifier>("xy");
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_X_compared_to_XY ) {
	ast::Node x = ast::Node::make<ast::Identifier>("X");
	ast::Node y = ast::Node::make<ast::Identifier>("XY");
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_x_compared_to_X ) {
	ast::Node x = ast::Node::make<ast::Identifier>("x");
	ast::Node y = ast::Node::make<ast::Identifier>("X");
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_x_compared_to_Y ) {
	ast::Node x = ast::Node::make<ast::Identifier>("x");
	ast::Node y = ast::Node::make<ast::Identifier>("Y");
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_x_compared_to_Xy ) {
	ast::Node x = ast::Node::make<ast::Identifier>("x");
	ast::Node y = ast::Node::make<ast::Identifier>("Xy");
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_x_compared_to_xY ) {
	ast::Node x = ast::Node::make<ast::Identifier>("x");
	ast::Node y = ast::Node::make<ast::Identifier>("xY");
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_x_compared_to_xy ) {
	ast::Node x = ast::Node::make<ast::Identifier>("x");
	ast::Node y = ast::Node::make<ast::Identifier>("xy");
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_x_compared_to_XY ) {
	ast::Node x = ast::Node::make<ast::Identifier>("x");
	ast::Node y = ast::Node::make<ast::Identifier>("XY");
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_Y_compared_to_X ) {
	ast::Node x = ast::Node::make<ast::Identifier>("Y");
	ast::Node y = ast::Node::make<ast::Identifier>("X");
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_Y_compared_to_x ) {
	ast::Node x = ast::Node::make<ast::Identifier>("Y");
	ast::Node y = ast::Node::make<ast::Identifier>("x");
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_Y_compared_to_Y ) {
	ast::Node x = ast::Node::make<ast::Identifier>("Y");
	ast::Node y = ast::Node::make<ast::Identifier>("Y");
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_EQUAL(x,y);
}


BOOST_AUTO_TEST_CASE( test_Y_compared_to_y ) {
	ast::Node x = ast::Node::make<ast::Identifier>("Y");
	ast::Node y = ast::Node::make<ast::Identifier>("y");
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_Y_compared_to_Xy ) {
	ast::Node x = ast::Node::make<ast::Identifier>("Y");
	ast::Node y = ast::Node::make<ast::Identifier>("Xy");
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_Y_compared_to_xY ) {
	ast::Node x = ast::Node::make<ast::Identifier>("Y");
	ast::Node y = ast::Node::make<ast::Identifier>("xY");
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_Y_compared_to_xy ) {
	ast::Node x = ast::Node::make<ast::Identifier>("Y");
	ast::Node y = ast::Node::make<ast::Identifier>("xy");
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_Y_compared_to_XY ) {
	ast::Node x = ast::Node::make<ast::Identifier>("Y");
	ast::Node y = ast::Node::make<ast::Identifier>("XY");
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_y_compared_to_X ) {
	ast::Node x = ast::Node::make<ast::Identifier>("y");
	ast::Node y = ast::Node::make<ast::Identifier>("X");
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}



BOOST_AUTO_TEST_CASE( test_y_compared_to_Y ) {
	ast::Node x = ast::Node::make<ast::Identifier>("y");
	ast::Node y = ast::Node::make<ast::Identifier>("Y");
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_y_compared_to_Xy ) {
	ast::Node x = ast::Node::make<ast::Identifier>("y");
	ast::Node y = ast::Node::make<ast::Identifier>("Xy");
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_y_compared_to_xY ) {
	ast::Node x = ast::Node::make<ast::Identifier>("y");
	ast::Node y = ast::Node::make<ast::Identifier>("xY");
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_y_compared_to_xy ) {
	ast::Node x = ast::Node::make<ast::Identifier>("y");
	ast::Node y = ast::Node::make<ast::Identifier>("xy");
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_y_compared_to_XY ) {
	ast::Node x = ast::Node::make<ast::Identifier>("y");
	ast::Node y = ast::Node::make<ast::Identifier>("XY");
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_Xy_compared_to_X ) {
	ast::Node x = ast::Node::make<ast::Identifier>("Xy");
	ast::Node y = ast::Node::make<ast::Identifier>("X");
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_Xy_compared_to_x ) {
	ast::Node x = ast::Node::make<ast::Identifier>("Xy");
	ast::Node y = ast::Node::make<ast::Identifier>("x");
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_Xy_compared_to_Y ) {
	ast::Node x = ast::Node::make<ast::Identifier>("Xy");
	ast::Node y = ast::Node::make<ast::Identifier>("Y");
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_Xy_compared_to_y ) {
	ast::Node x = ast::Node::make<ast::Identifier>("Xy");
	ast::Node y = ast::Node::make<ast::Identifier>("y");
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_Xy_compared_to_Xy ) {
	ast::Node x = ast::Node::make<ast::Identifier>("Xy");
	ast::Node y = ast::Node::make<ast::Identifier>("Xy");
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_EQUAL(x,y);
}


BOOST_AUTO_TEST_CASE( test_Xy_compared_to_xY ) {
	ast::Node x = ast::Node::make<ast::Identifier>("Xy");
	ast::Node y = ast::Node::make<ast::Identifier>("xY");
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_Xy_compared_to_xy ) {
	ast::Node x = ast::Node::make<ast::Identifier>("Xy");
	ast::Node y = ast::Node::make<ast::Identifier>("xy");
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_Xy_compared_to_XY ) {
	ast::Node x = ast::Node::make<ast::Identifier>("Xy");
	ast::Node y = ast::Node::make<ast::Identifier>("XY");
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_xY_compared_to_X ) {
	ast::Node x = ast::Node::make<ast::Identifier>("xY");
	ast::Node y = ast::Node::make<ast::Identifier>("X");
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_xY_compared_to_x ) {
	ast::Node x = ast::Node::make<ast::Identifier>("xY");
	ast::Node y = ast::Node::make<ast::Identifier>("x");
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_xY_compared_to_Y ) {
	ast::Node x = ast::Node::make<ast::Identifier>("xY");
	ast::Node y = ast::Node::make<ast::Identifier>("Y");
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_xY_compared_to_y ) {
	ast::Node x = ast::Node::make<ast::Identifier>("xY");
	ast::Node y = ast::Node::make<ast::Identifier>("y");
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_xY_compared_to_Xy ) {
	ast::Node x = ast::Node::make<ast::Identifier>("xY");
	ast::Node y = ast::Node::make<ast::Identifier>("Xy");
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_xY_compared_to_xY ) {
	ast::Node x = ast::Node::make<ast::Identifier>("xY");
	ast::Node y = ast::Node::make<ast::Identifier>("xY");
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_EQUAL(x,y);
}


BOOST_AUTO_TEST_CASE( test_xY_compared_to_xy ) {
	ast::Node x = ast::Node::make<ast::Identifier>("xY");
	ast::Node y = ast::Node::make<ast::Identifier>("xy");
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_xY_compared_to_XY ) {
	ast::Node x = ast::Node::make<ast::Identifier>("xY");
	ast::Node y = ast::Node::make<ast::Identifier>("XY");
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_xy_compared_to_X ) {
	ast::Node x = ast::Node::make<ast::Identifier>("xy");
	ast::Node y = ast::Node::make<ast::Identifier>("X");
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_xy_compared_to_x ) {
	ast::Node x = ast::Node::make<ast::Identifier>("xy");
	ast::Node y = ast::Node::make<ast::Identifier>("x");
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_xy_compared_to_Y ) {
	ast::Node x = ast::Node::make<ast::Identifier>("xy");
	ast::Node y = ast::Node::make<ast::Identifier>("Y");
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_xy_compared_to_y ) {
	ast::Node x = ast::Node::make<ast::Identifier>("xy");
	ast::Node y = ast::Node::make<ast::Identifier>("y");
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_xy_compared_to_Xy ) {
	ast::Node x = ast::Node::make<ast::Identifier>("xy");
	ast::Node y = ast::Node::make<ast::Identifier>("Xy");
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_xy_compared_to_xY ) {
	ast::Node x = ast::Node::make<ast::Identifier>("xy");
	ast::Node y = ast::Node::make<ast::Identifier>("xY");
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_xy_compared_to_xy ) {
	ast::Node x = ast::Node::make<ast::Identifier>("xy");
	ast::Node y = ast::Node::make<ast::Identifier>("xy");
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_EQUAL(x,y);
}


BOOST_AUTO_TEST_CASE( test_xy_compared_to_XY ) {
	ast::Node x = ast::Node::make<ast::Identifier>("xy");
	ast::Node y = ast::Node::make<ast::Identifier>("XY");
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_XY_compared_to_X ) {
	ast::Node x = ast::Node::make<ast::Identifier>("XY");
	ast::Node y = ast::Node::make<ast::Identifier>("X");
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_XY_compared_to_x ) {
	ast::Node x = ast::Node::make<ast::Identifier>("XY");
	ast::Node y = ast::Node::make<ast::Identifier>("x");
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_XY_compared_to_Y ) {
	ast::Node x = ast::Node::make<ast::Identifier>("XY");
	ast::Node y = ast::Node::make<ast::Identifier>("Y");
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_XY_compared_to_y ) {
	ast::Node x = ast::Node::make<ast::Identifier>("XY");
	ast::Node y = ast::Node::make<ast::Identifier>("y");
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_XY_compared_to_Xy ) {
	ast::Node x = ast::Node::make<ast::Identifier>("XY");
	ast::Node y = ast::Node::make<ast::Identifier>("Xy");
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_XY_compared_to_xY ) {
	ast::Node x = ast::Node::make<ast::Identifier>("XY");
	ast::Node y = ast::Node::make<ast::Identifier>("xY");
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_XY_compared_to_xy ) {
	ast::Node x = ast::Node::make<ast::Identifier>("XY");
	ast::Node y = ast::Node::make<ast::Identifier>("xy");
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_XY_compared_to_XY ) {
	ast::Node x = ast::Node::make<ast::Identifier>("XY");
	ast::Node y = ast::Node::make<ast::Identifier>("XY");
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_EQUAL(x,y);
}

//=============================================
//{x, x^-1, x^2, 1, 2, 2 x, Sin[x], f[x, y], 1.0, 1.5, x y, y, x^2 y, x/y, 2 x^2, 3 x^2 y}
//=============================================

BOOST_AUTO_TEST_CASE( test_x_compared_to_x ) {
	ast::Node x = ast::Node::make<ast::Identifier>("x");
	ast::Node y = ast::Node::make<ast::Identifier>("x");
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_EQUAL(x,y);
}


BOOST_AUTO_TEST_CASE( test_x_compared_to_one_over_x ) {
	ast::Node x = ast::Node::make<ast::Identifier>("x");
	ast::Node y = ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(-1)});
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_x_compared_to_x_squared ) {
	ast::Node x = ast::Node::make<ast::Identifier>("x");
	ast::Node y = ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_x_compared_to_1 ) {
	ast::Node x = ast::Node::make<ast::Identifier>("x");
	ast::Node y = ast::Node::make<math::Rational>(1);
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_x_compared_to_2 ) {
	ast::Node x = ast::Node::make<ast::Identifier>("x");
	ast::Node y = ast::Node::make<math::Rational>(2);
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_x_compared_to_2_times_x ) {
	ast::Node x = ast::Node::make<ast::Identifier>("x");
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_x_compared_to_sine_of_x ) {
	ast::Node x = ast::Node::make<ast::Identifier>("x");
	ast::Node y = ast::Node::make<ast::FunctionCall>("Sin", {ast::Node::make<ast::Identifier>("x")});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_x_compared_to_f_of_x_and_y ) {
	ast::Node x = ast::Node::make<ast::Identifier>("x");
	ast::Node y = ast::Node::make<ast::FunctionCall>("f", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::Identifier>("y")});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_x_compared_to_1_0 ) {
	ast::Node x = ast::Node::make<ast::Identifier>("x");
	ast::Node y = ast::Node::make<math::Real>(1.);
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_x_compared_to_1_5 ) {
	ast::Node x = ast::Node::make<ast::Identifier>("x");
	ast::Node y = ast::Node::make<math::Real>(1.5);
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_x_compared_to_x_times_y ) {
	ast::Node x = ast::Node::make<ast::Identifier>("x");
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::Identifier>("y")});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_x_compared_to_y ) {
	ast::Node x = ast::Node::make<ast::Identifier>("x");
	ast::Node y = ast::Node::make<ast::Identifier>("y");
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_x_compared_to_x_squared_times_y ) {
	ast::Node x = ast::Node::make<ast::Identifier>("x");
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)}), ast::Node::make<ast::Identifier>("y")});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_x_compared_to_x_over_y ) {
	ast::Node x = ast::Node::make<ast::Identifier>("x");
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("y"), ast::Node::make<math::Rational>(-1)}), ast::Node::make<ast::Identifier>("x")});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_x_compared_to_2_times_x_squared ) {
	ast::Node x = ast::Node::make<ast::Identifier>("x");
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)}), ast::Node::make<math::Rational>(2)});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_x_compared_to_3_times_x_squared_times_y ) {
	ast::Node x = ast::Node::make<ast::Identifier>("x");
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)}), ast::Node::make<ast::Identifier>("y"), ast::Node::make<math::Rational>(3)});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_one_over_x_compared_to_x ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(-1)});
	ast::Node y = ast::Node::make<ast::Identifier>("x");
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_one_over_x_compared_to_one_over_x ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(-1)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(-1)});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_EQUAL(x,y);
}


BOOST_AUTO_TEST_CASE( test_one_over_x_compared_to_x_squared ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(-1)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_one_over_x_compared_to_1 ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(-1)});
	ast::Node y = ast::Node::make<math::Rational>(1);
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_one_over_x_compared_to_2 ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(-1)});
	ast::Node y = ast::Node::make<math::Rational>(2);
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_one_over_x_compared_to_2_times_x ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(-1)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_one_over_x_compared_to_sine_of_x ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(-1)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Sin", {ast::Node::make<ast::Identifier>("x")});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_one_over_x_compared_to_f_of_x_and_y ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(-1)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("f", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::Identifier>("y")});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_one_over_x_compared_to_1_0 ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(-1)});
	ast::Node y = ast::Node::make<math::Real>(1.);
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_one_over_x_compared_to_1_5 ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(-1)});
	ast::Node y = ast::Node::make<math::Real>(1.5);
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_one_over_x_compared_to_x_times_y ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(-1)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::Identifier>("y")});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_one_over_x_compared_to_y ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(-1)});
	ast::Node y = ast::Node::make<ast::Identifier>("y");
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_one_over_x_compared_to_x_squared_times_y ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(-1)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)}), ast::Node::make<ast::Identifier>("y")});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_one_over_x_compared_to_x_over_y ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(-1)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("y"), ast::Node::make<math::Rational>(-1)}), ast::Node::make<ast::Identifier>("x")});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_one_over_x_compared_to_2_times_x_squared ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(-1)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)}), ast::Node::make<math::Rational>(2)});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_one_over_x_compared_to_3_times_x_squared_times_y ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(-1)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)}), ast::Node::make<ast::Identifier>("y"), ast::Node::make<math::Rational>(3)});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_x_squared_compared_to_x ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)});
	ast::Node y = ast::Node::make<ast::Identifier>("x");
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_x_squared_compared_to_one_over_x ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(-1)});
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_x_squared_compared_to_x_squared ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_EQUAL(x,y);
}


BOOST_AUTO_TEST_CASE( test_x_squared_compared_to_1 ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)});
	ast::Node y = ast::Node::make<math::Rational>(1);
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_x_squared_compared_to_2 ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)});
	ast::Node y = ast::Node::make<math::Rational>(2);
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_x_squared_compared_to_2_times_x ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)});
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_x_squared_compared_to_sine_of_x ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Sin", {ast::Node::make<ast::Identifier>("x")});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_x_squared_compared_to_f_of_x_and_y ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("f", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::Identifier>("y")});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_x_squared_compared_to_1_0 ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)});
	ast::Node y = ast::Node::make<math::Real>(1.);
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_x_squared_compared_to_1_5 ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)});
	ast::Node y = ast::Node::make<math::Real>(1.5);
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_x_squared_compared_to_x_times_y ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::Identifier>("y")});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_x_squared_compared_to_y ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)});
	ast::Node y = ast::Node::make<ast::Identifier>("y");
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_x_squared_compared_to_x_squared_times_y ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)}), ast::Node::make<ast::Identifier>("y")});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_x_squared_compared_to_x_over_y ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("y"), ast::Node::make<math::Rational>(-1)}), ast::Node::make<ast::Identifier>("x")});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_x_squared_compared_to_2_times_x_squared ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)}), ast::Node::make<math::Rational>(2)});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_x_squared_compared_to_3_times_x_squared_times_y ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)}), ast::Node::make<ast::Identifier>("y"), ast::Node::make<math::Rational>(3)});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_1_compared_to_x ) {
	ast::Node x = ast::Node::make<math::Rational>(1);
	ast::Node y = ast::Node::make<ast::Identifier>("x");
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_1_compared_to_one_over_x ) {
	ast::Node x = ast::Node::make<math::Rational>(1);
	ast::Node y = ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(-1)});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_1_compared_to_x_squared ) {
	ast::Node x = ast::Node::make<math::Rational>(1);
	ast::Node y = ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_1_compared_to_1 ) {
	ast::Node x = ast::Node::make<math::Rational>(1);
	ast::Node y = ast::Node::make<math::Rational>(1);
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_EQUAL(x,y);
}


BOOST_AUTO_TEST_CASE( test_1_compared_to_2 ) {
	ast::Node x = ast::Node::make<math::Rational>(1);
	ast::Node y = ast::Node::make<math::Rational>(2);
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_1_compared_to_2_times_x ) {
	ast::Node x = ast::Node::make<math::Rational>(1);
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_1_compared_to_sine_of_x ) {
	ast::Node x = ast::Node::make<math::Rational>(1);
	ast::Node y = ast::Node::make<ast::FunctionCall>("Sin", {ast::Node::make<ast::Identifier>("x")});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_1_compared_to_f_of_x_and_y ) {
	ast::Node x = ast::Node::make<math::Rational>(1);
	ast::Node y = ast::Node::make<ast::FunctionCall>("f", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::Identifier>("y")});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_1_compared_to_1_0 ) {
	ast::Node x = ast::Node::make<math::Rational>(1);
	ast::Node y = ast::Node::make<math::Real>(1.);
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_1_compared_to_1_5 ) {
	ast::Node x = ast::Node::make<math::Rational>(1);
	ast::Node y = ast::Node::make<math::Real>(1.5);
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_1_compared_to_x_times_y ) {
	ast::Node x = ast::Node::make<math::Rational>(1);
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::Identifier>("y")});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_1_compared_to_y ) {
	ast::Node x = ast::Node::make<math::Rational>(1);
	ast::Node y = ast::Node::make<ast::Identifier>("y");
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_1_compared_to_x_squared_times_y ) {
	ast::Node x = ast::Node::make<math::Rational>(1);
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)}), ast::Node::make<ast::Identifier>("y")});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_1_compared_to_x_over_y ) {
	ast::Node x = ast::Node::make<math::Rational>(1);
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("y"), ast::Node::make<math::Rational>(-1)}), ast::Node::make<ast::Identifier>("x")});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_1_compared_to_2_times_x_squared ) {
	ast::Node x = ast::Node::make<math::Rational>(1);
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)}), ast::Node::make<math::Rational>(2)});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_1_compared_to_3_times_x_squared_times_y ) {
	ast::Node x = ast::Node::make<math::Rational>(1);
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)}), ast::Node::make<ast::Identifier>("y"), ast::Node::make<math::Rational>(3)});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_2_compared_to_x ) {
	ast::Node x = ast::Node::make<math::Rational>(2);
	ast::Node y = ast::Node::make<ast::Identifier>("x");
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_2_compared_to_one_over_x ) {
	ast::Node x = ast::Node::make<math::Rational>(2);
	ast::Node y = ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(-1)});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_2_compared_to_x_squared ) {
	ast::Node x = ast::Node::make<math::Rational>(2);
	ast::Node y = ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_2_compared_to_1 ) {
	ast::Node x = ast::Node::make<math::Rational>(2);
	ast::Node y = ast::Node::make<math::Rational>(1);
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_2_compared_to_2 ) {
	ast::Node x = ast::Node::make<math::Rational>(2);
	ast::Node y = ast::Node::make<math::Rational>(2);
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_EQUAL(x,y);
}


BOOST_AUTO_TEST_CASE( test_2_compared_to_2_times_x ) {
	ast::Node x = ast::Node::make<math::Rational>(2);
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_2_compared_to_sine_of_x ) {
	ast::Node x = ast::Node::make<math::Rational>(2);
	ast::Node y = ast::Node::make<ast::FunctionCall>("Sin", {ast::Node::make<ast::Identifier>("x")});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_2_compared_to_f_of_x_and_y ) {
	ast::Node x = ast::Node::make<math::Rational>(2);
	ast::Node y = ast::Node::make<ast::FunctionCall>("f", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::Identifier>("y")});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_2_compared_to_1_0 ) {
	ast::Node x = ast::Node::make<math::Rational>(2);
	ast::Node y = ast::Node::make<math::Real>(1.);
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_2_compared_to_1_5 ) {
	ast::Node x = ast::Node::make<math::Rational>(2);
	ast::Node y = ast::Node::make<math::Real>(1.5);
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_2_compared_to_x_times_y ) {
	ast::Node x = ast::Node::make<math::Rational>(2);
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::Identifier>("y")});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_2_compared_to_y ) {
	ast::Node x = ast::Node::make<math::Rational>(2);
	ast::Node y = ast::Node::make<ast::Identifier>("y");
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_2_compared_to_x_squared_times_y ) {
	ast::Node x = ast::Node::make<math::Rational>(2);
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)}), ast::Node::make<ast::Identifier>("y")});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_2_compared_to_x_over_y ) {
	ast::Node x = ast::Node::make<math::Rational>(2);
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("y"), ast::Node::make<math::Rational>(-1)}), ast::Node::make<ast::Identifier>("x")});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_2_compared_to_2_times_x_squared ) {
	ast::Node x = ast::Node::make<math::Rational>(2);
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)}), ast::Node::make<math::Rational>(2)});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_2_compared_to_3_times_x_squared_times_y ) {
	ast::Node x = ast::Node::make<math::Rational>(2);
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)}), ast::Node::make<ast::Identifier>("y"), ast::Node::make<math::Rational>(3)});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_2_times_x_compared_to_x ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)});
	ast::Node y = ast::Node::make<ast::Identifier>("x");
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_2_times_x_compared_to_one_over_x ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(-1)});
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_2_times_x_compared_to_x_squared ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_2_times_x_compared_to_1 ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)});
	ast::Node y = ast::Node::make<math::Rational>(1);
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_2_times_x_compared_to_2 ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)});
	ast::Node y = ast::Node::make<math::Rational>(2);
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_2_times_x_compared_to_2_times_x ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_EQUAL(x,y);
}


BOOST_AUTO_TEST_CASE( test_2_times_x_compared_to_sine_of_x ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Sin", {ast::Node::make<ast::Identifier>("x")});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_2_times_x_compared_to_f_of_x_and_y ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("f", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::Identifier>("y")});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_2_times_x_compared_to_1_0 ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)});
	ast::Node y = ast::Node::make<math::Real>(1.);
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_2_times_x_compared_to_1_5 ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)});
	ast::Node y = ast::Node::make<math::Real>(1.5);
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_2_times_x_compared_to_x_times_y ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::Identifier>("y")});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_2_times_x_compared_to_y ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)});
	ast::Node y = ast::Node::make<ast::Identifier>("y");
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_2_times_x_compared_to_x_squared_times_y ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)}), ast::Node::make<ast::Identifier>("y")});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_2_times_x_compared_to_x_over_y ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("y"), ast::Node::make<math::Rational>(-1)}), ast::Node::make<ast::Identifier>("x")});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_2_times_x_compared_to_2_times_x_squared ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)}), ast::Node::make<math::Rational>(2)});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_2_times_x_compared_to_3_times_x_squared_times_y ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)}), ast::Node::make<ast::Identifier>("y"), ast::Node::make<math::Rational>(3)});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_sine_of_x_compared_to_x ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Sin", {ast::Node::make<ast::Identifier>("x")});
	ast::Node y = ast::Node::make<ast::Identifier>("x");
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_sine_of_x_compared_to_one_over_x ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Sin", {ast::Node::make<ast::Identifier>("x")});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(-1)});
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_sine_of_x_compared_to_x_squared ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Sin", {ast::Node::make<ast::Identifier>("x")});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)});
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_sine_of_x_compared_to_1 ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Sin", {ast::Node::make<ast::Identifier>("x")});
	ast::Node y = ast::Node::make<math::Rational>(1);
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_sine_of_x_compared_to_2 ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Sin", {ast::Node::make<ast::Identifier>("x")});
	ast::Node y = ast::Node::make<math::Rational>(2);
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_sine_of_x_compared_to_2_times_x ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Sin", {ast::Node::make<ast::Identifier>("x")});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)});
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_sine_of_x_compared_to_sine_of_x ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Sin", {ast::Node::make<ast::Identifier>("x")});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Sin", {ast::Node::make<ast::Identifier>("x")});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_EQUAL(x,y);
}


BOOST_AUTO_TEST_CASE( test_sine_of_x_compared_to_f_of_x_and_y ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Sin", {ast::Node::make<ast::Identifier>("x")});
	ast::Node y = ast::Node::make<ast::FunctionCall>("f", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::Identifier>("y")});
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_sine_of_x_compared_to_1_0 ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Sin", {ast::Node::make<ast::Identifier>("x")});
	ast::Node y = ast::Node::make<math::Real>(1.);
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_sine_of_x_compared_to_1_5 ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Sin", {ast::Node::make<ast::Identifier>("x")});
	ast::Node y = ast::Node::make<math::Real>(1.5);
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_sine_of_x_compared_to_x_times_y ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Sin", {ast::Node::make<ast::Identifier>("x")});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::Identifier>("y")});
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_sine_of_x_compared_to_y ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Sin", {ast::Node::make<ast::Identifier>("x")});
	ast::Node y = ast::Node::make<ast::Identifier>("y");
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_sine_of_x_compared_to_x_squared_times_y ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Sin", {ast::Node::make<ast::Identifier>("x")});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)}), ast::Node::make<ast::Identifier>("y")});
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_sine_of_x_compared_to_x_over_y ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Sin", {ast::Node::make<ast::Identifier>("x")});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("y"), ast::Node::make<math::Rational>(-1)}), ast::Node::make<ast::Identifier>("x")});
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_sine_of_x_compared_to_2_times_x_squared ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Sin", {ast::Node::make<ast::Identifier>("x")});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)}), ast::Node::make<math::Rational>(2)});
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_sine_of_x_compared_to_3_times_x_squared_times_y ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Sin", {ast::Node::make<ast::Identifier>("x")});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)}), ast::Node::make<ast::Identifier>("y"), ast::Node::make<math::Rational>(3)});
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_f_of_x_and_y_compared_to_x ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("f", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::Identifier>("y")});
	ast::Node y = ast::Node::make<ast::Identifier>("x");
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_f_of_x_and_y_compared_to_one_over_x ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("f", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::Identifier>("y")});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(-1)});
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_f_of_x_and_y_compared_to_x_squared ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("f", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::Identifier>("y")});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)});
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_f_of_x_and_y_compared_to_1 ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("f", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::Identifier>("y")});
	ast::Node y = ast::Node::make<math::Rational>(1);
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_f_of_x_and_y_compared_to_2 ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("f", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::Identifier>("y")});
	ast::Node y = ast::Node::make<math::Rational>(2);
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_f_of_x_and_y_compared_to_2_times_x ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("f", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::Identifier>("y")});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)});
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_f_of_x_and_y_compared_to_sine_of_x ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("f", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::Identifier>("y")});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Sin", {ast::Node::make<ast::Identifier>("x")});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_f_of_x_and_y_compared_to_f_of_x_and_y ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("f", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::Identifier>("y")});
	ast::Node y = ast::Node::make<ast::FunctionCall>("f", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::Identifier>("y")});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_EQUAL(x,y);
}


BOOST_AUTO_TEST_CASE( test_f_of_x_and_y_compared_to_1_0 ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("f", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::Identifier>("y")});
	ast::Node y = ast::Node::make<math::Real>(1.);
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_f_of_x_and_y_compared_to_1_5 ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("f", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::Identifier>("y")});
	ast::Node y = ast::Node::make<math::Real>(1.5);
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_f_of_x_and_y_compared_to_x_times_y ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("f", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::Identifier>("y")});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::Identifier>("y")});
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_f_of_x_and_y_compared_to_y ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("f", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::Identifier>("y")});
	ast::Node y = ast::Node::make<ast::Identifier>("y");
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_f_of_x_and_y_compared_to_x_squared_times_y ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("f", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::Identifier>("y")});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)}), ast::Node::make<ast::Identifier>("y")});
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_f_of_x_and_y_compared_to_x_over_y ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("f", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::Identifier>("y")});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("y"), ast::Node::make<math::Rational>(-1)}), ast::Node::make<ast::Identifier>("x")});
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_f_of_x_and_y_compared_to_2_times_x_squared ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("f", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::Identifier>("y")});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)}), ast::Node::make<math::Rational>(2)});
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_f_of_x_and_y_compared_to_3_times_x_squared_times_y ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("f", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::Identifier>("y")});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)}), ast::Node::make<ast::Identifier>("y"), ast::Node::make<math::Rational>(3)});
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_1_0_compared_to_x ) {
	ast::Node x = ast::Node::make<math::Real>(1.);
	ast::Node y = ast::Node::make<ast::Identifier>("x");
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_1_0_compared_to_one_over_x ) {
	ast::Node x = ast::Node::make<math::Real>(1.);
	ast::Node y = ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(-1)});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_1_0_compared_to_x_squared ) {
	ast::Node x = ast::Node::make<math::Real>(1.);
	ast::Node y = ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_1_0_compared_to_1 ) {
	ast::Node x = ast::Node::make<math::Real>(1.);
	ast::Node y = ast::Node::make<math::Rational>(1);
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_1_0_compared_to_2 ) {
	ast::Node x = ast::Node::make<math::Real>(1.);
	ast::Node y = ast::Node::make<math::Rational>(2);
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_1_0_compared_to_2_times_x ) {
	ast::Node x = ast::Node::make<math::Real>(1.);
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_1_0_compared_to_sine_of_x ) {
	ast::Node x = ast::Node::make<math::Real>(1.);
	ast::Node y = ast::Node::make<ast::FunctionCall>("Sin", {ast::Node::make<ast::Identifier>("x")});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_1_0_compared_to_f_of_x_and_y ) {
	ast::Node x = ast::Node::make<math::Real>(1.);
	ast::Node y = ast::Node::make<ast::FunctionCall>("f", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::Identifier>("y")});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_1_0_compared_to_1_0 ) {
	ast::Node x = ast::Node::make<math::Real>(1.);
	ast::Node y = ast::Node::make<math::Real>(1.);
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_EQUAL(x,y);
}


BOOST_AUTO_TEST_CASE( test_1_0_compared_to_1_5 ) {
	ast::Node x = ast::Node::make<math::Real>(1.);
	ast::Node y = ast::Node::make<math::Real>(1.5);
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_1_0_compared_to_x_times_y ) {
	ast::Node x = ast::Node::make<math::Real>(1.);
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::Identifier>("y")});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_1_0_compared_to_y ) {
	ast::Node x = ast::Node::make<math::Real>(1.);
	ast::Node y = ast::Node::make<ast::Identifier>("y");
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_1_0_compared_to_x_squared_times_y ) {
	ast::Node x = ast::Node::make<math::Real>(1.);
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)}), ast::Node::make<ast::Identifier>("y")});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_1_0_compared_to_x_over_y ) {
	ast::Node x = ast::Node::make<math::Real>(1.);
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("y"), ast::Node::make<math::Rational>(-1)}), ast::Node::make<ast::Identifier>("x")});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_1_0_compared_to_2_times_x_squared ) {
	ast::Node x = ast::Node::make<math::Real>(1.);
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)}), ast::Node::make<math::Rational>(2)});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_1_0_compared_to_3_times_x_squared_times_y ) {
	ast::Node x = ast::Node::make<math::Real>(1.);
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)}), ast::Node::make<ast::Identifier>("y"), ast::Node::make<math::Rational>(3)});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_1_5_compared_to_x ) {
	ast::Node x = ast::Node::make<math::Real>(1.5);
	ast::Node y = ast::Node::make<ast::Identifier>("x");
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_1_5_compared_to_one_over_x ) {
	ast::Node x = ast::Node::make<math::Real>(1.5);
	ast::Node y = ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(-1)});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_1_5_compared_to_x_squared ) {
	ast::Node x = ast::Node::make<math::Real>(1.5);
	ast::Node y = ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_1_5_compared_to_1 ) {
	ast::Node x = ast::Node::make<math::Real>(1.5);
	ast::Node y = ast::Node::make<math::Rational>(1);
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_1_5_compared_to_2 ) {
	ast::Node x = ast::Node::make<math::Real>(1.5);
	ast::Node y = ast::Node::make<math::Rational>(2);
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_1_5_compared_to_2_times_x ) {
	ast::Node x = ast::Node::make<math::Real>(1.5);
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_1_5_compared_to_sine_of_x ) {
	ast::Node x = ast::Node::make<math::Real>(1.5);
	ast::Node y = ast::Node::make<ast::FunctionCall>("Sin", {ast::Node::make<ast::Identifier>("x")});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_1_5_compared_to_f_of_x_and_y ) {
	ast::Node x = ast::Node::make<math::Real>(1.5);
	ast::Node y = ast::Node::make<ast::FunctionCall>("f", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::Identifier>("y")});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_1_5_compared_to_1_0 ) {
	ast::Node x = ast::Node::make<math::Real>(1.5);
	ast::Node y = ast::Node::make<math::Real>(1.);
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_1_5_compared_to_1_5 ) {
	ast::Node x = ast::Node::make<math::Real>(1.5);
	ast::Node y = ast::Node::make<math::Real>(1.5);
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_EQUAL(x,y);
}


BOOST_AUTO_TEST_CASE( test_1_5_compared_to_x_times_y ) {
	ast::Node x = ast::Node::make<math::Real>(1.5);
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::Identifier>("y")});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_1_5_compared_to_y ) {
	ast::Node x = ast::Node::make<math::Real>(1.5);
	ast::Node y = ast::Node::make<ast::Identifier>("y");
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_1_5_compared_to_x_squared_times_y ) {
	ast::Node x = ast::Node::make<math::Real>(1.5);
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)}), ast::Node::make<ast::Identifier>("y")});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_1_5_compared_to_x_over_y ) {
	ast::Node x = ast::Node::make<math::Real>(1.5);
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("y"), ast::Node::make<math::Rational>(-1)}), ast::Node::make<ast::Identifier>("x")});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_1_5_compared_to_2_times_x_squared ) {
	ast::Node x = ast::Node::make<math::Real>(1.5);
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)}), ast::Node::make<math::Rational>(2)});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_1_5_compared_to_3_times_x_squared_times_y ) {
	ast::Node x = ast::Node::make<math::Real>(1.5);
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)}), ast::Node::make<ast::Identifier>("y"), ast::Node::make<math::Rational>(3)});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_x_times_y_compared_to_x ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::Identifier>("y")});
	ast::Node y = ast::Node::make<ast::Identifier>("x");
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_x_times_y_compared_to_one_over_x ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::Identifier>("y")});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(-1)});
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_x_times_y_compared_to_x_squared ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::Identifier>("y")});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)});
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_x_times_y_compared_to_1 ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::Identifier>("y")});
	ast::Node y = ast::Node::make<math::Rational>(1);
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_x_times_y_compared_to_2 ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::Identifier>("y")});
	ast::Node y = ast::Node::make<math::Rational>(2);
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_x_times_y_compared_to_2_times_x ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::Identifier>("y")});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)});
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_x_times_y_compared_to_sine_of_x ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::Identifier>("y")});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Sin", {ast::Node::make<ast::Identifier>("x")});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_x_times_y_compared_to_f_of_x_and_y ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::Identifier>("y")});
	ast::Node y = ast::Node::make<ast::FunctionCall>("f", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::Identifier>("y")});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_x_times_y_compared_to_1_0 ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::Identifier>("y")});
	ast::Node y = ast::Node::make<math::Real>(1.);
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_x_times_y_compared_to_1_5 ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::Identifier>("y")});
	ast::Node y = ast::Node::make<math::Real>(1.5);
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_x_times_y_compared_to_x_times_y ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::Identifier>("y")});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::Identifier>("y")});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_EQUAL(x,y);
}


BOOST_AUTO_TEST_CASE( test_x_times_y_compared_to_y ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::Identifier>("y")});
	ast::Node y = ast::Node::make<ast::Identifier>("y");
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_x_times_y_compared_to_x_squared_times_y ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::Identifier>("y")});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)}), ast::Node::make<ast::Identifier>("y")});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_x_times_y_compared_to_x_over_y ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::Identifier>("y")});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("y"), ast::Node::make<math::Rational>(-1)}), ast::Node::make<ast::Identifier>("x")});
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_x_times_y_compared_to_2_times_x_squared ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::Identifier>("y")});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)}), ast::Node::make<math::Rational>(2)});
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_x_times_y_compared_to_3_times_x_squared_times_y ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::Identifier>("y")});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)}), ast::Node::make<ast::Identifier>("y"), ast::Node::make<math::Rational>(3)});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_y_compared_to_x ) {
	ast::Node x = ast::Node::make<ast::Identifier>("y");
	ast::Node y = ast::Node::make<ast::Identifier>("x");
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_y_compared_to_one_over_x ) {
	ast::Node x = ast::Node::make<ast::Identifier>("y");
	ast::Node y = ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(-1)});
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_y_compared_to_x_squared ) {
	ast::Node x = ast::Node::make<ast::Identifier>("y");
	ast::Node y = ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)});
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_y_compared_to_1 ) {
	ast::Node x = ast::Node::make<ast::Identifier>("y");
	ast::Node y = ast::Node::make<math::Rational>(1);
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_y_compared_to_2 ) {
	ast::Node x = ast::Node::make<ast::Identifier>("y");
	ast::Node y = ast::Node::make<math::Rational>(2);
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_y_compared_to_2_times_x ) {
	ast::Node x = ast::Node::make<ast::Identifier>("y");
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)});
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_y_compared_to_sine_of_x ) {
	ast::Node x = ast::Node::make<ast::Identifier>("y");
	ast::Node y = ast::Node::make<ast::FunctionCall>("Sin", {ast::Node::make<ast::Identifier>("x")});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_y_compared_to_f_of_x_and_y ) {
	ast::Node x = ast::Node::make<ast::Identifier>("y");
	ast::Node y = ast::Node::make<ast::FunctionCall>("f", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::Identifier>("y")});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_y_compared_to_1_0 ) {
	ast::Node x = ast::Node::make<ast::Identifier>("y");
	ast::Node y = ast::Node::make<math::Real>(1.);
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_y_compared_to_1_5 ) {
	ast::Node x = ast::Node::make<ast::Identifier>("y");
	ast::Node y = ast::Node::make<math::Real>(1.5);
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_y_compared_to_x_times_y ) {
	ast::Node x = ast::Node::make<ast::Identifier>("y");
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::Identifier>("y")});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_y_compared_to_y ) {
	ast::Node x = ast::Node::make<ast::Identifier>("y");
	ast::Node y = ast::Node::make<ast::Identifier>("y");
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_EQUAL(x,y);
}


BOOST_AUTO_TEST_CASE( test_y_compared_to_x_squared_times_y ) {
	ast::Node x = ast::Node::make<ast::Identifier>("y");
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)}), ast::Node::make<ast::Identifier>("y")});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_y_compared_to_x_over_y ) {
	ast::Node x = ast::Node::make<ast::Identifier>("y");
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("y"), ast::Node::make<math::Rational>(-1)}), ast::Node::make<ast::Identifier>("x")});
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_y_compared_to_2_times_x_squared ) {
	ast::Node x = ast::Node::make<ast::Identifier>("y");
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)}), ast::Node::make<math::Rational>(2)});
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_y_compared_to_3_times_x_squared_times_y ) {
	ast::Node x = ast::Node::make<ast::Identifier>("y");
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)}), ast::Node::make<ast::Identifier>("y"), ast::Node::make<math::Rational>(3)});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_x_squared_times_y_compared_to_x ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)}), ast::Node::make<ast::Identifier>("y")});
	ast::Node y = ast::Node::make<ast::Identifier>("x");
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_x_squared_times_y_compared_to_one_over_x ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)}), ast::Node::make<ast::Identifier>("y")});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(-1)});
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_x_squared_times_y_compared_to_x_squared ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)}), ast::Node::make<ast::Identifier>("y")});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)});
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_x_squared_times_y_compared_to_1 ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)}), ast::Node::make<ast::Identifier>("y")});
	ast::Node y = ast::Node::make<math::Rational>(1);
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_x_squared_times_y_compared_to_2 ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)}), ast::Node::make<ast::Identifier>("y")});
	ast::Node y = ast::Node::make<math::Rational>(2);
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_x_squared_times_y_compared_to_2_times_x ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)}), ast::Node::make<ast::Identifier>("y")});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)});
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_x_squared_times_y_compared_to_sine_of_x ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)}), ast::Node::make<ast::Identifier>("y")});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Sin", {ast::Node::make<ast::Identifier>("x")});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_x_squared_times_y_compared_to_f_of_x_and_y ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)}), ast::Node::make<ast::Identifier>("y")});
	ast::Node y = ast::Node::make<ast::FunctionCall>("f", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::Identifier>("y")});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_x_squared_times_y_compared_to_1_0 ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)}), ast::Node::make<ast::Identifier>("y")});
	ast::Node y = ast::Node::make<math::Real>(1.);
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_x_squared_times_y_compared_to_1_5 ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)}), ast::Node::make<ast::Identifier>("y")});
	ast::Node y = ast::Node::make<math::Real>(1.5);
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_x_squared_times_y_compared_to_x_times_y ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)}), ast::Node::make<ast::Identifier>("y")});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::Identifier>("y")});
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_x_squared_times_y_compared_to_y ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)}), ast::Node::make<ast::Identifier>("y")});
	ast::Node y = ast::Node::make<ast::Identifier>("y");
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_x_squared_times_y_compared_to_x_squared_times_y ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)}), ast::Node::make<ast::Identifier>("y")});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)}), ast::Node::make<ast::Identifier>("y")});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_EQUAL(x,y);
}


BOOST_AUTO_TEST_CASE( test_x_squared_times_y_compared_to_x_over_y ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)}), ast::Node::make<ast::Identifier>("y")});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("y"), ast::Node::make<math::Rational>(-1)}), ast::Node::make<ast::Identifier>("x")});
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_x_squared_times_y_compared_to_2_times_x_squared ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)}), ast::Node::make<ast::Identifier>("y")});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)}), ast::Node::make<math::Rational>(2)});
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_x_squared_times_y_compared_to_3_times_x_squared_times_y ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)}), ast::Node::make<ast::Identifier>("y")});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)}), ast::Node::make<ast::Identifier>("y"), ast::Node::make<math::Rational>(3)});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_x_over_y_compared_to_x ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("y"), ast::Node::make<math::Rational>(-1)}), ast::Node::make<ast::Identifier>("x")});
	ast::Node y = ast::Node::make<ast::Identifier>("x");
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_x_over_y_compared_to_one_over_x ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("y"), ast::Node::make<math::Rational>(-1)}), ast::Node::make<ast::Identifier>("x")});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(-1)});
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_x_over_y_compared_to_x_squared ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("y"), ast::Node::make<math::Rational>(-1)}), ast::Node::make<ast::Identifier>("x")});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)});
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_x_over_y_compared_to_1 ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("y"), ast::Node::make<math::Rational>(-1)}), ast::Node::make<ast::Identifier>("x")});
	ast::Node y = ast::Node::make<math::Rational>(1);
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_x_over_y_compared_to_2 ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("y"), ast::Node::make<math::Rational>(-1)}), ast::Node::make<ast::Identifier>("x")});
	ast::Node y = ast::Node::make<math::Rational>(2);
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_x_over_y_compared_to_2_times_x ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("y"), ast::Node::make<math::Rational>(-1)}), ast::Node::make<ast::Identifier>("x")});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)});
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_x_over_y_compared_to_sine_of_x ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("y"), ast::Node::make<math::Rational>(-1)}), ast::Node::make<ast::Identifier>("x")});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Sin", {ast::Node::make<ast::Identifier>("x")});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_x_over_y_compared_to_f_of_x_and_y ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("y"), ast::Node::make<math::Rational>(-1)}), ast::Node::make<ast::Identifier>("x")});
	ast::Node y = ast::Node::make<ast::FunctionCall>("f", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::Identifier>("y")});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_x_over_y_compared_to_1_0 ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("y"), ast::Node::make<math::Rational>(-1)}), ast::Node::make<ast::Identifier>("x")});
	ast::Node y = ast::Node::make<math::Real>(1.);
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_x_over_y_compared_to_1_5 ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("y"), ast::Node::make<math::Rational>(-1)}), ast::Node::make<ast::Identifier>("x")});
	ast::Node y = ast::Node::make<math::Real>(1.5);
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_x_over_y_compared_to_x_times_y ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("y"), ast::Node::make<math::Rational>(-1)}), ast::Node::make<ast::Identifier>("x")});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::Identifier>("y")});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_x_over_y_compared_to_y ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("y"), ast::Node::make<math::Rational>(-1)}), ast::Node::make<ast::Identifier>("x")});
	ast::Node y = ast::Node::make<ast::Identifier>("y");
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_x_over_y_compared_to_x_squared_times_y ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("y"), ast::Node::make<math::Rational>(-1)}), ast::Node::make<ast::Identifier>("x")});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)}), ast::Node::make<ast::Identifier>("y")});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_x_over_y_compared_to_x_over_y ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("y"), ast::Node::make<math::Rational>(-1)}), ast::Node::make<ast::Identifier>("x")});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("y"), ast::Node::make<math::Rational>(-1)}), ast::Node::make<ast::Identifier>("x")});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_EQUAL(x,y);
}


BOOST_AUTO_TEST_CASE( test_x_over_y_compared_to_2_times_x_squared ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("y"), ast::Node::make<math::Rational>(-1)}), ast::Node::make<ast::Identifier>("x")});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)}), ast::Node::make<math::Rational>(2)});
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_x_over_y_compared_to_3_times_x_squared_times_y ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("y"), ast::Node::make<math::Rational>(-1)}), ast::Node::make<ast::Identifier>("x")});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)}), ast::Node::make<ast::Identifier>("y"), ast::Node::make<math::Rational>(3)});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_2_times_x_squared_compared_to_x ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)}), ast::Node::make<math::Rational>(2)});
	ast::Node y = ast::Node::make<ast::Identifier>("x");
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_2_times_x_squared_compared_to_one_over_x ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)}), ast::Node::make<math::Rational>(2)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(-1)});
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_2_times_x_squared_compared_to_x_squared ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)}), ast::Node::make<math::Rational>(2)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)});
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_2_times_x_squared_compared_to_1 ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)}), ast::Node::make<math::Rational>(2)});
	ast::Node y = ast::Node::make<math::Rational>(1);
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_2_times_x_squared_compared_to_2 ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)}), ast::Node::make<math::Rational>(2)});
	ast::Node y = ast::Node::make<math::Rational>(2);
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_2_times_x_squared_compared_to_2_times_x ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)}), ast::Node::make<math::Rational>(2)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)});
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_2_times_x_squared_compared_to_sine_of_x ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)}), ast::Node::make<math::Rational>(2)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Sin", {ast::Node::make<ast::Identifier>("x")});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_2_times_x_squared_compared_to_f_of_x_and_y ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)}), ast::Node::make<math::Rational>(2)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("f", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::Identifier>("y")});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_2_times_x_squared_compared_to_1_0 ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)}), ast::Node::make<math::Rational>(2)});
	ast::Node y = ast::Node::make<math::Real>(1.);
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_2_times_x_squared_compared_to_1_5 ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)}), ast::Node::make<math::Rational>(2)});
	ast::Node y = ast::Node::make<math::Real>(1.5);
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_2_times_x_squared_compared_to_x_times_y ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)}), ast::Node::make<math::Rational>(2)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::Identifier>("y")});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_2_times_x_squared_compared_to_y ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)}), ast::Node::make<math::Rational>(2)});
	ast::Node y = ast::Node::make<ast::Identifier>("y");
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_2_times_x_squared_compared_to_x_squared_times_y ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)}), ast::Node::make<math::Rational>(2)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)}), ast::Node::make<ast::Identifier>("y")});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_2_times_x_squared_compared_to_x_over_y ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)}), ast::Node::make<math::Rational>(2)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("y"), ast::Node::make<math::Rational>(-1)}), ast::Node::make<ast::Identifier>("x")});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_2_times_x_squared_compared_to_2_times_x_squared ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)}), ast::Node::make<math::Rational>(2)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)}), ast::Node::make<math::Rational>(2)});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_EQUAL(x,y);
}


BOOST_AUTO_TEST_CASE( test_2_times_x_squared_compared_to_3_times_x_squared_times_y ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)}), ast::Node::make<math::Rational>(2)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)}), ast::Node::make<ast::Identifier>("y"), ast::Node::make<math::Rational>(3)});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_3_times_x_squared_times_y_compared_to_x ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)}), ast::Node::make<ast::Identifier>("y"), ast::Node::make<math::Rational>(3)});
	ast::Node y = ast::Node::make<ast::Identifier>("x");
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_3_times_x_squared_times_y_compared_to_one_over_x ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)}), ast::Node::make<ast::Identifier>("y"), ast::Node::make<math::Rational>(3)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(-1)});
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_3_times_x_squared_times_y_compared_to_x_squared ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)}), ast::Node::make<ast::Identifier>("y"), ast::Node::make<math::Rational>(3)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)});
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_3_times_x_squared_times_y_compared_to_1 ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)}), ast::Node::make<ast::Identifier>("y"), ast::Node::make<math::Rational>(3)});
	ast::Node y = ast::Node::make<math::Rational>(1);
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_3_times_x_squared_times_y_compared_to_2 ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)}), ast::Node::make<ast::Identifier>("y"), ast::Node::make<math::Rational>(3)});
	ast::Node y = ast::Node::make<math::Rational>(2);
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_3_times_x_squared_times_y_compared_to_2_times_x ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)}), ast::Node::make<ast::Identifier>("y"), ast::Node::make<math::Rational>(3)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)});
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_3_times_x_squared_times_y_compared_to_sine_of_x ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)}), ast::Node::make<ast::Identifier>("y"), ast::Node::make<math::Rational>(3)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Sin", {ast::Node::make<ast::Identifier>("x")});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_3_times_x_squared_times_y_compared_to_f_of_x_and_y ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)}), ast::Node::make<ast::Identifier>("y"), ast::Node::make<math::Rational>(3)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("f", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::Identifier>("y")});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(x,y));
}


BOOST_AUTO_TEST_CASE( test_3_times_x_squared_times_y_compared_to_1_0 ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)}), ast::Node::make<ast::Identifier>("y"), ast::Node::make<math::Rational>(3)});
	ast::Node y = ast::Node::make<math::Real>(1.);
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_3_times_x_squared_times_y_compared_to_1_5 ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)}), ast::Node::make<ast::Identifier>("y"), ast::Node::make<math::Rational>(3)});
	ast::Node y = ast::Node::make<math::Real>(1.5);
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_3_times_x_squared_times_y_compared_to_x_times_y ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)}), ast::Node::make<ast::Identifier>("y"), ast::Node::make<math::Rational>(3)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::Identifier>("y")});
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_3_times_x_squared_times_y_compared_to_y ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)}), ast::Node::make<ast::Identifier>("y"), ast::Node::make<math::Rational>(3)});
	ast::Node y = ast::Node::make<ast::Identifier>("y");
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_3_times_x_squared_times_y_compared_to_x_squared_times_y ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)}), ast::Node::make<ast::Identifier>("y"), ast::Node::make<math::Rational>(3)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)}), ast::Node::make<ast::Identifier>("y")});
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_3_times_x_squared_times_y_compared_to_x_over_y ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)}), ast::Node::make<ast::Identifier>("y"), ast::Node::make<math::Rational>(3)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("y"), ast::Node::make<math::Rational>(-1)}), ast::Node::make<ast::Identifier>("x")});
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_3_times_x_squared_times_y_compared_to_2_times_x_squared ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)}), ast::Node::make<ast::Identifier>("y"), ast::Node::make<math::Rational>(3)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)}), ast::Node::make<math::Rational>(2)});
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_NE(x,y);
	BOOST_CHECK(eval::nodeLess(y,x));
}


BOOST_AUTO_TEST_CASE( test_3_times_x_squared_times_y_compared_to_3_times_x_squared_times_y ) {
	ast::Node x = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)}), ast::Node::make<ast::Identifier>("y"), ast::Node::make<math::Rational>(3)});
	ast::Node y = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)}), ast::Node::make<ast::Identifier>("y"), ast::Node::make<math::Rational>(3)});
	BOOST_CHECK(!eval::nodeLess(y,x));
	BOOST_CHECK(!eval::nodeLess(x,y));
	BOOST_CHECK_EQUAL(x,y);
}

BOOST_AUTO_TEST_SUITE_END()
