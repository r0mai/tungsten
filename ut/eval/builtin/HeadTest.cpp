
#include <boost/test/unit_test.hpp>

#include "Fixture.hpp"

BOOST_AUTO_TEST_SUITE( HeadTest )

using namespace tungsten;

BOOST_FIXTURE_TEST_CASE( test_Head_of_3 , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Head[3]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::Identifier>("Integer") );
}


BOOST_FIXTURE_TEST_CASE( test_Head_of_the_quantity_3_over_4 , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Head[3/4]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::Identifier>("Rational") );
}


BOOST_FIXTURE_TEST_CASE( test_Head_of_3_5 , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Head[3.5]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::Identifier>("Real") );
}


BOOST_FIXTURE_TEST_CASE( test_Head_of_x , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Head[x]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::Identifier>("Symbol") );
}


BOOST_FIXTURE_TEST_CASE( test_Head_of_quote_abc_quote , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Head[\"abc\"]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::Identifier>("String") );
}


BOOST_FIXTURE_TEST_CASE( test_Head_of_f_of_x , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Head[f[x]]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::Identifier>("f") );
}


BOOST_FIXTURE_TEST_CASE( test_Head_of_f_of_x_of_y , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Head[f[x][y]]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::FunctionCall>("f", {ast::Node::make<ast::Identifier>("x")}) );
}

BOOST_AUTO_TEST_SUITE_END()

