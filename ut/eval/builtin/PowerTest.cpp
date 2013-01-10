
#include <boost/test/unit_test.hpp>

#include "Fixture.hpp"

BOOST_AUTO_TEST_SUITE( PowerTest )

using namespace tungsten;

BOOST_FIXTURE_TEST_CASE( test_Power_of_no_arguments , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Power[]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::makeRational(1) );
}


BOOST_FIXTURE_TEST_CASE( test_Power_of_x , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Power[x]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::makeIdentifier("x") );
}


BOOST_FIXTURE_TEST_CASE( test_x_to_the_power_of_y , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("x^y");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::makeFunctionCall("Power", {ast::Node::makeIdentifier("x"), ast::Node::makeIdentifier("y")}) );
}


BOOST_FIXTURE_TEST_CASE( test_one_over_x , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("x^(-1)");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::makeFunctionCall("Power", {ast::Node::makeIdentifier("x"), ast::Node::makeRational(-1)}) );
}


BOOST_FIXTURE_TEST_CASE( test_one_over_3 , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("3^(-1)");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::makeRational(1,3) );
}


BOOST_FIXTURE_TEST_CASE( test_one_over_3_to_the_4th_power , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("3^(-4)");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::makeRational(1,81) );
}


BOOST_FIXTURE_TEST_CASE( test_2_to_the_32nd_power , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("2^32");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::makeRational("4294967296") );
}


BOOST_FIXTURE_TEST_CASE( test_f_of_x_to_the_power_of_g_of_x , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("f[x]^g[x]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::makeFunctionCall("Power", {ast::Node::makeFunctionCall("f", {ast::Node::makeIdentifier("x")}), ast::Node::makeFunctionCall("g", {ast::Node::makeIdentifier("x")})}) );
}


BOOST_FIXTURE_TEST_CASE( test_quote_asd_quote_to_the_power_of_quote_dsa_quote , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("\"asd\"^\"dsa\"");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::makeFunctionCall("Power", {ast::Node::makeString("asd"), ast::Node::makeString("dsa")}) );
}


BOOST_FIXTURE_TEST_CASE( test_Power_of_x__y_and_z , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Power[x, y, z]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::makeFunctionCall("Power", {ast::Node::makeIdentifier("x"), ast::Node::makeFunctionCall("Power", {ast::Node::makeIdentifier("y"), ast::Node::makeIdentifier("z")})}) );
}


BOOST_FIXTURE_TEST_CASE( test_x_to_the_power_of_y_to_the_power_of_z , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("x^y^z");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::makeFunctionCall("Power", {ast::Node::makeIdentifier("x"), ast::Node::makeFunctionCall("Power", {ast::Node::makeIdentifier("y"), ast::Node::makeIdentifier("z")})}) );
}


BOOST_FIXTURE_TEST_CASE( test_the_quantity_x_to_the_power_of_y_to_the_power_of_z , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("(x^y)^z");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::makeFunctionCall("Power", {ast::Node::makeFunctionCall("Power", {ast::Node::makeIdentifier("x"), ast::Node::makeIdentifier("y")}), ast::Node::makeIdentifier("z")}) );
}


BOOST_FIXTURE_TEST_CASE( test_3_to_the_power_of_1_0 , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("3^1.");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::makeReal(3.) );
}


BOOST_FIXTURE_TEST_CASE( test_2_0_to_the_5th_power , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("2.^5");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::makeReal(32.) );
}


BOOST_FIXTURE_TEST_CASE( test_2_0_to_the_power_of_5_0 , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("2.^5.");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::makeReal(32.) );
}


BOOST_FIXTURE_TEST_CASE( test_the_quantity_a_to_the_power_of_b_to_the_5th_power , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("(a^b)^5");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::makeFunctionCall("Power", {ast::Node::makeIdentifier("a"), ast::Node::makeFunctionCall("Times", {ast::Node::makeIdentifier("b"), ast::Node::makeRational(5)})}) );
}


BOOST_FIXTURE_TEST_CASE( test_the_quantity_a_to_the_power_of_b_to_the_power_of_5_0 , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("(a^b)^5.");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::makeFunctionCall("Power", {ast::Node::makeFunctionCall("Power", {ast::Node::makeIdentifier("a"), ast::Node::makeIdentifier("b")}), ast::Node::makeReal(5.)}) );
}

BOOST_AUTO_TEST_SUITE_END()
