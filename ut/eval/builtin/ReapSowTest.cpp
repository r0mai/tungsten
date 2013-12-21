

#include <boost/test/unit_test.hpp>

#include "Fixture.hpp"

BOOST_AUTO_TEST_SUITE( ReapSowTest )

using namespace tungsten;


BOOST_FIXTURE_TEST_CASE( test_Reap_of_the_quantity_Sow_of_a_semicolon_b_semicolon_Sow_of_c_semicolon_Sow_of_d_semicolon_e, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Reap[Sow[a]; b; Sow[c]; Sow[d]; e]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("e"), ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("a"), ast::Node::make<ast::Identifier>("c"), ast::Node::make<ast::Identifier>("d")})})}) );
}


BOOST_FIXTURE_TEST_CASE( test_Sow_of_b, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Sow[b]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::Identifier>("b") );
}


BOOST_FIXTURE_TEST_CASE( test_Reap_of_the_quantity_Reap_of_Sow_of_b_semicolon_Sow_of_c, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Reap[Reap[Sow[b]]; Sow[c]]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("c"), ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("c")})})}) );
}


BOOST_FIXTURE_TEST_CASE( test_Reap_of_Reap_of_Sow_of_b, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Reap[Reap[Sow[b]]]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("b"), ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("b")})})}), ast::Node::make<ast::FunctionCall>("List", {})}) );
}



BOOST_AUTO_TEST_SUITE_END()

