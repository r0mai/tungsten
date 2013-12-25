
#include <boost/test/unit_test.hpp>

#include "Fixture.hpp"

BOOST_AUTO_TEST_SUITE( stringAlgorithmTest )

using namespace tungsten;

BOOST_FIXTURE_TEST_CASE( test_StringLength_of_quote_quote, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("StringLength[\"\"]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<math::Rational>(0) );
}


BOOST_FIXTURE_TEST_CASE( test_StringLength_of_quote_a_quote, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("StringLength[\"a\"]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<math::Rational>(1) );
}


BOOST_FIXTURE_TEST_CASE( test_StringLength_of_quote_space_quote, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("StringLength[\" \"]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<math::Rational>(1) );
}


BOOST_FIXTURE_TEST_CASE( test_StringLength_of_quote_tab_quote, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("StringLength[\"\\t\"]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<math::Rational>(1) );
}


BOOST_FIXTURE_TEST_CASE( test_StringLength_of_quote_abc_quote, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("StringLength[\"abc\"]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<math::Rational>(3) );
}


BOOST_FIXTURE_TEST_CASE( test_Characters_of_empty_string, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Characters[\"\"]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::FunctionCall>("List", {}) );
}


BOOST_FIXTURE_TEST_CASE( test_Characters_of_a_string, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Characters[\"a\"]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::String>("a")}) );
}


BOOST_FIXTURE_TEST_CASE( test_Characters_of_ab_string, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Characters[\"ab\"]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::String>("a"), ast::Node::make<ast::String>("b")}) );
}


BOOST_FIXTURE_TEST_CASE( test_Characters_of_Rational, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Characters[2]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::FunctionCall>("Characters", {ast::Node::make<math::Rational>(2)}) );
}


BOOST_FIXTURE_TEST_CASE( test_Characters_of_Real, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Characters[2.0]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::FunctionCall>("Characters", {ast::Node::make<math::Real>(2)}) );
}


BOOST_FIXTURE_TEST_CASE( test_Characters_of_Identifier, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Characters[x]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::FunctionCall>("Characters", {ast::Node::make<ast::Identifier>("x")}) );
}

BOOST_FIXTURE_TEST_CASE( test_StringReverse_of_an_empty_string, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("StringReverse[\"\"]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::String>("") );
}

BOOST_FIXTURE_TEST_CASE( test_StringReverse_of_a_string, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("StringReverse[\"a\"]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::String>("a") );
}


BOOST_FIXTURE_TEST_CASE( test_StringReverse_of_ab_string, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("StringReverse[\"ab\"]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::String>("ba") );
}

BOOST_FIXTURE_TEST_CASE( test_StringReverse_of_abc_string, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("StringReverse[\"abc\"]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::String>("cba") );
}

BOOST_FIXTURE_TEST_CASE( test_StringJoin_of_no_arguments, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("StringJoin[]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::String>("") );
}

BOOST_FIXTURE_TEST_CASE( test_StringJoin_of_a_single_argument, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("StringJoin[\"a\"]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::String>("a") );
}


BOOST_FIXTURE_TEST_CASE( test_StringJoin_of_a_multiple_arguments_1, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("\"a\" <> \"b\"");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::String>("ab") );
}


BOOST_FIXTURE_TEST_CASE( test_StringJoin_of_a_multiple_arguments_2, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("\"a\" <> \"b\" <> \"cd\"");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::String>("abcd") );
}

BOOST_AUTO_TEST_SUITE_END()

