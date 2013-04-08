
#include <boost/test/unit_test.hpp>

#include "Fixture.hpp"

BOOST_AUTO_TEST_SUITE( NumericQTest )

using namespace tungsten;

BOOST_FIXTURE_TEST_CASE( test_NumericQ_of_3, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("NumericQ[3]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::Identifier>("True") );
}


BOOST_FIXTURE_TEST_CASE( test_NumericQ_of_Pi, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("NumericQ[Pi]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::Identifier>("True") );
}


BOOST_FIXTURE_TEST_CASE( test_NumericQ_of_E, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("NumericQ[E]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::Identifier>("True") );
}


BOOST_FIXTURE_TEST_CASE( test_NumericQ_of_Degree, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("NumericQ[Degree]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::Identifier>("True") );
}


BOOST_FIXTURE_TEST_CASE( test_NumericQ_of_GoldenRatio, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("NumericQ[GoldenRatio]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::Identifier>("True") );
}


BOOST_FIXTURE_TEST_CASE( test_NumericQ_of_EulerGamma, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("NumericQ[EulerGamma]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::Identifier>("True") );
}


BOOST_FIXTURE_TEST_CASE( test_NumericQ_of_Catalan, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("NumericQ[Catalan]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::Identifier>("True") );
}


BOOST_FIXTURE_TEST_CASE( test_NumericQ_of_I, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("NumericQ[I]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::Identifier>("True") );
}


BOOST_FIXTURE_TEST_CASE( test_NumericQ_of_Khinchin, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("NumericQ[Khinchin]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::Identifier>("True") );
}


BOOST_FIXTURE_TEST_CASE( test_NumericQ_of_Glaisher, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("NumericQ[Glaisher]");

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

BOOST_FIXTURE_TEST_CASE( test_NumericQ_of_x , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("NumericQ[x]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::Identifier>("False") );
}


BOOST_FIXTURE_TEST_CASE( test_NumericQ_of_square_root_of_x , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("NumericQ[Sqrt[x]]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::Identifier>("False") );
}


BOOST_FIXTURE_TEST_CASE( test_NumericQ_of_quote_a_quote , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("NumericQ[\"a\"]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::Identifier>("False") );
}


BOOST_FIXTURE_TEST_CASE( test_NumericQ_of_the_quantity_quote_a_quote_plus_quote_b_quote , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("NumericQ[\"a\" + \"b\"]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::Identifier>("False") );
}


BOOST_FIXTURE_TEST_CASE( test_NumericQ_of_the_quantity_sine_of_x_plus_sine_of_3 , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("NumericQ[Sin[x] + Sin[3]]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::Identifier>("False") );
}


BOOST_FIXTURE_TEST_CASE( test_NumericQ_of_cosine_of_3 , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("NumericQ[Cos[3]]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::Identifier>("True") );
}


BOOST_AUTO_TEST_SUITE_END()
