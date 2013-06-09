
#include <boost/test/unit_test.hpp>

#include "Fixture.hpp"

BOOST_AUTO_TEST_SUITE( MatchQTest )

using namespace tungsten;


BOOST_FIXTURE_TEST_CASE( test_true_if_x_matches_blank_and_false_otherwise, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("MatchQ[x, _]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::Identifier>("True");

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_true_if_1_matches_blank_and_false_otherwise, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("MatchQ[1, _]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::Identifier>("True");

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_true_if_1_1_matches_blank_and_false_otherwise, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("MatchQ[1.1, _]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::Identifier>("True");

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_true_if_3_over_4_matches_blank_and_false_otherwise, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("MatchQ[3/4, _]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::Identifier>("True");

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_true_if_quote_abc_quote_matches_blank_and_false_otherwise, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("MatchQ[\"abc\", _]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::Identifier>("True");

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_true_if_sine_of_x_matches_blank_and_false_otherwise, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("MatchQ[Sin[x], _]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::Identifier>("True");

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_true_if_x_matches_the_pattern_a_blank_and_false_otherwise, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("MatchQ[x, a_]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::Identifier>("True");

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_true_if_1_matches_the_pattern_a_blank_and_false_otherwise, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("MatchQ[1, a_]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::Identifier>("True");

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_true_if_1_1_matches_the_pattern_a_blank_and_false_otherwise, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("MatchQ[1.1, a_]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::Identifier>("True");

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_true_if_3_over_4_matches_the_pattern_a_blank_and_false_otherwise, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("MatchQ[3/4, a_]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::Identifier>("True");

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_true_if_quote_abc_quote_matches_the_pattern_a_blank_and_false_otherwise, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("MatchQ[\"abc\", a_]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::Identifier>("True");

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_true_if_x_matches_HoldPattern_of_blank_and_false_otherwise, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("MatchQ[x, HoldPattern[_]]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::Identifier>("True");

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_true_if_3_matches_blank_question_mark_the_pure_function_hash_is_greater_than_0_and_false_otherwise, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("MatchQ[3, _?(#1 > 0 & )]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::Identifier>("True");

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_true_if_3_matches_blank_question_mark_the_pure_function_hash_is_less_than_0_and_false_otherwise, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("MatchQ[3, _?(#1 < 0 & )]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::Identifier>("False");

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_true_if_the_list_3__x_matches_the_list_the_pattern_x_blank_Integer__the_pattern_y_blank_Symbol_and_false_otherwise, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("MatchQ[{3, x}, {x_Integer, y_Symbol}]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::Identifier>("True");

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_true_if_x_matches_the_list_blank_and_false_otherwise, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("MatchQ[x, {_}]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::Identifier>("False");

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_true_if_the_list_x_matches_the_list_blank_and_false_otherwise, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("MatchQ[{x}, {_}]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::Identifier>("True");

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_true_if_x_plus_y_matches_HoldPattern_of_the_quantity_blank_plus_blank_and_false_otherwise, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("MatchQ[x + y, HoldPattern[_ + _]]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::Identifier>("True");

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_true_if_x_matches_blank_question_mark_NumericQ_and_false_otherwise, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("MatchQ[x, _?NumericQ]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::Identifier>("False");

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_true_if_Pi_matches_blank_question_mark_NumericQ_and_false_otherwise, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("MatchQ[Pi, _?NumericQ]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::Identifier>("True");

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_true_if_3_matches_blank_question_mark_NumericQ_and_false_otherwise, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("MatchQ[3, _?NumericQ]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::Identifier>("True");

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_true_if_3_13_matches_blank_question_mark_NumericQ_and_false_otherwise, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("MatchQ[3.13, _?NumericQ]");

	BOOST_REQUIRE( result );

	ast::Node expected = ast::Node::make<ast::Identifier>("True");

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_AUTO_TEST_SUITE_END()

