
#include <boost/test/unit_test.hpp>

#include "Fixture.hpp"

BOOST_AUTO_TEST_SUITE( DivideTest )

using namespace tungsten;

BOOST_FIXTURE_TEST_CASE( test_Divide_of_3_and_4 , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("3/4");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<math::Rational>(3,4) );
}


BOOST_FIXTURE_TEST_CASE( test_Divide_of_x_and_y , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("x/y");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("y"), ast::Node::make<math::Rational>(-1)}), ast::Node::make<ast::Identifier>("x")}) );
}


BOOST_FIXTURE_TEST_CASE( test_Divide_of_3_0_and_minus_1_5 , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("3./-1.5");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<math::Real>(-2.) );
}


BOOST_FIXTURE_TEST_CASE( test_Divide_of_3_and_0 , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("3/0");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::FunctionCall>("DirectedInfinity", {}) );
}


BOOST_AUTO_TEST_SUITE_END()
