
#include <boost/test/unit_test.hpp>

#include "Fixture.hpp"

BOOST_AUTO_TEST_SUITE( AbsTest )

using namespace tungsten;

BOOST_FIXTURE_TEST_CASE( test_NumericQ_of_3 , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("NumericQ[3]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::Identifier>("True") );
}


BOOST_FIXTURE_TEST_CASE( test_NumericQ_of_3_2 , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("NumericQ[3.2]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::Identifier>("True") );
}


BOOST_FIXTURE_TEST_CASE( test_NumericQ_of_the_quantity_3_over_4 , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("NumericQ[3/4]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::Identifier>("True") );
}


BOOST_FIXTURE_TEST_CASE( test_x , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("x");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::Identifier>("x") );
}


BOOST_FIXTURE_TEST_CASE( test_square_root_of_x , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Sqrt[x]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(1,2)}) );
}


BOOST_FIXTURE_TEST_CASE( test_a , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("\"a\"");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::String>("a") );
}


BOOST_FIXTURE_TEST_CASE( test_quote_a_quote_plus_quote_b_quote , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("\"a\" + \"b\"");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::FunctionCall>("Plus", {ast::Node::make<ast::String>("a"), ast::Node::make<ast::String>("b")}) );
}


BOOST_FIXTURE_TEST_CASE( test_sine_of_x_plus_sine_of_3 , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Sin[x] + Sin[3]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::FunctionCall>("Plus", {ast::Node::make<ast::FunctionCall>("Sin", {ast::Node::make<ast::Identifier>("x")}), ast::Node::make<ast::FunctionCall>("Sin", {ast::Node::make<math::Rational>(3)})}) );
}


BOOST_FIXTURE_TEST_CASE( test_cosine_of_3 , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Cos[3]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::FunctionCall>("Cos", {ast::Node::make<math::Rational>(3)}) );
}


BOOST_AUTO_TEST_SUITE_END()
