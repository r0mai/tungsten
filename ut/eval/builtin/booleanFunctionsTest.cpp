
#include <boost/test/unit_test.hpp>

#include "Fixture.hpp"

BOOST_AUTO_TEST_SUITE( BooleanFunctionsTest )

using namespace tungsten;

BOOST_FIXTURE_TEST_CASE( test_TrueQ_of_True, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("TrueQ[True]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::Identifier>("True");

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_TrueQ_of_False, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("TrueQ[False]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::Identifier>("False");

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_TrueQ_of_x, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("TrueQ[x]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::Identifier>("False");

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_TrueQ_of_the_list_True, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("TrueQ[{True}]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::Identifier>("False");

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_not_True, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate(" !True");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::Identifier>("False");

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_not_False, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate(" !False");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::Identifier>("True");

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_not_x, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate(" !x");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("Not", {ast::Node::make<ast::Identifier>("x")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_not_not_x, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate(" !( !x)");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::Identifier>("x");

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_not_not_not_x, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate(" !( !( !x))");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("Not", {ast::Node::make<ast::Identifier>("x")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_not_a_is_greater_than_b, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate(" !a > b");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("LessEqual", {ast::Node::make<ast::Identifier>("a"), ast::Node::make<ast::Identifier>("b")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_not_a_is_less_than_b, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate(" !a < b");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("GreaterEqual", {ast::Node::make<ast::Identifier>("a"), ast::Node::make<ast::Identifier>("b")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_not_a_is_greater_than_or_equal_to_b, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate(" !a >= b");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("Less", {ast::Node::make<ast::Identifier>("a"), ast::Node::make<ast::Identifier>("b")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_not_a_is_less_than_or_equal_to_b, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate(" !a <= b");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("Greater", {ast::Node::make<ast::Identifier>("a"), ast::Node::make<ast::Identifier>("b")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_not_a_equals_equals_b, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate(" !a == b");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("Unequal", {ast::Node::make<ast::Identifier>("a"), ast::Node::make<ast::Identifier>("b")});

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_not_a_is_not_equal_to_b, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate(" !a != b");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::FunctionCall>("Equal", {ast::Node::make<ast::Identifier>("a"), ast::Node::make<ast::Identifier>("b")});

	BOOST_CHECK_EQUAL( *result, expected );
}



BOOST_AUTO_TEST_SUITE_END()

