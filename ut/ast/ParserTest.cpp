
#include <boost/test/unit_test.hpp>

#include "ast/Parser.hpp"

BOOST_AUTO_TEST_SUITE( AstParserTest )

using namespace tungsten;

BOOST_AUTO_TEST_CASE( empty_input_fails ) {
	boost::optional<ast::Node> tree = ast::parseInput("");

	BOOST_CHECK( !tree );
}

BOOST_AUTO_TEST_CASE( empty_input_with_spaces_fails ) {
	boost::optional<ast::Node> tree = ast::parseInput(" \t");

	BOOST_CHECK( !tree );
}

BOOST_AUTO_TEST_CASE( integer_parsed_correctly ) {
	boost::optional<ast::Node> tree = ast::parseInput("42");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::makeRational(42) );
}

BOOST_AUTO_TEST_CASE( integer_with_spaces_parsed_correctly ) {
	boost::optional<ast::Node> tree = ast::parseInput(" 42\t");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::makeRational(42) );
}

BOOST_AUTO_TEST_CASE( negative_integer_parsed_correctly ) {
	boost::optional<ast::Node> tree = ast::parseInput("-42");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::makeRational(42) );
}

BOOST_AUTO_TEST_CASE( positive_integer_parsed_correctly ) {
	boost::optional<ast::Node> tree = ast::parseInput("+42");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::makeRational(42) );
}

BOOST_AUTO_TEST_CASE( real_parsed_correctly ) {
	boost::optional<ast::Node> tree = ast::parseInput("1.5");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::makeReal(1.5) );
}

BOOST_AUTO_TEST_CASE( negative_real_parsed_correctly ) {
	boost::optional<ast::Node> tree = ast::parseInput("-3.5");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::makeReal(-3.5) );
}

BOOST_AUTO_TEST_CASE( positive_real_parsed_correctly ) {
	boost::optional<ast::Node> tree = ast::parseInput("3.5");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::makeReal(3.5) );
}

BOOST_AUTO_TEST_CASE( real_with_no_fraction_part_parsed_correctly ) {
	boost::optional<ast::Node> tree = ast::parseInput("3.");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::makeReal(-3.) );
}

BOOST_AUTO_TEST_CASE( real_with_no_integer_part_parsed_correctly ) {
	boost::optional<ast::Node> tree = ast::parseInput(".5");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::makeReal(-.5) );
}

BOOST_AUTO_TEST_CASE( negative_real_with_no_integer_part_parsed_correctly ) {
	boost::optional<ast::Node> tree = ast::parseInput("-.5");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::makeReal(-.5) );
}

BOOST_AUTO_TEST_CASE( positive_real_with_no_integer_part_parsed_correctly ) {
	boost::optional<ast::Node> tree = ast::parseInput("+.5");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::makeReal(.5) );
}

BOOST_AUTO_TEST_CASE( Identifier_parsed_correctly ) {
	boost::optional<ast::Node> tree = ast::parseInput("Pi");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::makeIdentifier("Pi") );
}

BOOST_AUTO_TEST_CASE( Identifier_with_trailing_numbers_parsed_correctly ) {
	boost::optional<ast::Node> tree = ast::parseInput("X123");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::makeIdentifier("X123") );
}

BOOST_AUTO_TEST_CASE( Identifier_with_numbers_in_middle_parsed_correctly ) {
	boost::optional<ast::Node> tree = ast::parseInput("X123Y");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::makeIdentifier("X123Y") );
}

BOOST_AUTO_TEST_CASE( Identifier_parsed_correctly_with_spaces ) {
	boost::optional<ast::Node> tree = ast::parseInput("\tPi ");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::makeIdentifier("Pi") );
}

BOOST_AUTO_TEST_CASE( String_parsed_correctly ) {
	boost::optional<ast::Node> tree = ast::parseInput("\"abc\"");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::makeString("abc") );
}

BOOST_AUTO_TEST_CASE( String_parsed_correctly_with_spaces_inside ) {
	boost::optional<ast::Node> tree = ast::parseInput("\"a b\t c\"");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::makeString("a b\tc") );
}

BOOST_AUTO_TEST_CASE( String_parsed_correctly_with_spaces_outside ) {
	boost::optional<ast::Node> tree = ast::parseInput("  \"a b\t c\" ");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::makeString("a b\tc") );
}

BOOST_AUTO_TEST_CASE( String_parsed_correctly_with_escaped_new_line ) {
	boost::optional<ast::Node> tree = ast::parseInput("\"a\\nb\"");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::makeString("a\nb") );
}

BOOST_AUTO_TEST_CASE( String_parsed_correctly_with_escaped_quotation_mark ) {
	boost::optional<ast::Node> tree = ast::parseInput("\"a\\\"b\"");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::makeString("a\"b") );
}

BOOST_AUTO_TEST_CASE( String_parsed_correctly_with_escaped_back_slash ) {
	boost::optional<ast::Node> tree = ast::parseInput("\"a\\\\b\"");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::makeString("a\\b") );
}

BOOST_AUTO_TEST_CASE( String_parsed_correctly_with_escaped_tabulator ) {
	boost::optional<ast::Node> tree = ast::parseInput("\"a\\tb\"");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::makeString("a\tb") );
}

BOOST_AUTO_TEST_CASE( String_parsed_correctly_with_multiple_escaped_characters ) {
	boost::optional<ast::Node> tree = ast::parseInput("\\\"\\t\\\\\\n\\\"");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::makeString("\"\t\\n\"") );
}

BOOST_AUTO_TEST_CASE( function_without_parameters_parsed_correctly ) {
	boost::optional<ast::Node> tree = ast::parseInput("foo[]");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::makeFunctionCall("foo") );
}

BOOST_AUTO_TEST_CASE( function_without_parameters_with_spaces_parsed_correctly ) {
	boost::optional<ast::Node> tree = ast::parseInput("\tfoo\t[ ] ");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::makeFunctionCall("foo") );
}

BOOST_AUTO_TEST_CASE( function_with_single_parameter_parsed_correctly ) {
	boost::optional<ast::Node> tree = ast::parseInput("foo[1]");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::makeFunctionCall("foo", {ast::Node::makeRational(1)}) );
}

BOOST_AUTO_TEST_CASE( function_with_single_parameter_with_spaces_parsed_correctly ) {
	boost::optional<ast::Node> tree = ast::parseInput("  foo [1 ] ");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::makeFunctionCall("f", {ast::Node::makeRational(1)}) );
}

BOOST_AUTO_TEST_CASE( function_with_multiple_parameter_parsed_correctly ) {
	boost::optional<ast::Node> tree = ast::parseInput("foo[1,2,3]");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::makeFunctionCall("foo",
			{ast::Node::makeRational(1),
			ast::Node::makeRational(2),
			ast::Node::makeRational(3)}) );
}

BOOST_AUTO_TEST_CASE( function_with_multiple_parameter_with_spaces_parsed_correctly ) {
	boost::optional<ast::Node> tree = ast::parseInput("  foo [1 ,2,3 ] ");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::makeFunctionCall("foo",
			{ast::Node::makeRational(1),
			ast::Node::makeRational(2),
			ast::Node::makeRational(3)}) );
}

BOOST_AUTO_TEST_CASE( nested_function_parsed_correctly_1 ) {
	boost::optional<ast::Node> tree = ast::parseInput("f[g[]]");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::makeFunctionCall("f", {ast::Node::makeFunctionCall("g")}) );

}

BOOST_AUTO_TEST_CASE( nested_function_parsed_correctly_2 ) {
	boost::optional<ast::Node> tree = ast::parseInput("f[g[], h[1]]");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::makeFunctionCall("f", {
					ast::Node::makeFunctionCall("g"),
					ast::Node::makeFunctionCall("h", {
							ast::Node::makeRational(1)
					})
	}) );

}

BOOST_AUTO_TEST_CASE( non_identifier_function_parsed_correctly_1 ) {
	boost::optional<ast::Node> tree = ast::parseInput(" 2 []\t");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::makeFunctionCall(
			ast::Node::makeRational(2) ) );
}

BOOST_AUTO_TEST_CASE( non_identifier_function_parsed_correctly_2 ) {
	boost::optional<ast::Node> tree = ast::parseInput("f[ ]\t[]");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(),
			ast::Node::makeFunctionCall(
					ast::Node::makeFunctionCall("f")
			)
	);
}

BOOST_AUTO_TEST_CASE( identifier_function_parsed_correctly_with_parentheses ) {
	boost::optional<ast::Node> tree = ast::parseInput("( f) []");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(),
			ast::Node::makeFunctionCall(
					ast::Node::makeFunctionCall("f")
			)
	);
}

BOOST_AUTO_TEST_CASE( empty_brackets_not_parsed ) {
	boost::optional<ast::Node> tree = ast::parseInput("[]");

	BOOST_CHECK( !tree );
}

BOOST_AUTO_TEST_CASE( addition_parsed_correctly_with_2_arguments ) {
	boost::optional<ast::Node> tree = ast::parseInput("a+b");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::makeFunctionCall("Plus", {ast::Node::makeIdentifier("a"), ast::Node::makeIdentifier("b")}) );
}

BOOST_AUTO_TEST_CASE( addition_parsed_correctly_with_2_arguments_with_spaces ) {
	boost::optional<ast::Node> tree = ast::parseInput("a +  b ");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::makeFunctionCall("Plus", {ast::Node::makeIdentifier("a"), ast::Node::makeIdentifier("b")}) );
}

BOOST_AUTO_TEST_CASE( addition_parsed_correctly_with_3_arguments ) {
	boost::optional<ast::Node> tree = ast::parseInput("a+b+c");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::makeFunctionCall("Plus", {ast::Node::makeIdentifier("a"), ast::Node::makeIdentifier("b"), ast::Node::makeIdentifier("c")}) );
}

BOOST_AUTO_TEST_CASE( addition_parsed_correctly_with_3_arguments_with_spaces ) {
	boost::optional<ast::Node> tree = ast::parseInput(" \ta \t+ b + c ");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::makeFunctionCall("Plus", {ast::Node::makeIdentifier("a"), ast::Node::makeIdentifier("b"), ast::Node::makeIdentifier("c")}) );
}


BOOST_AUTO_TEST_CASE( multiplication_parsed_correctly_with_2_arguments ) {
	boost::optional<ast::Node> tree = ast::parseInput("a*b");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::makeFunctionCall("Times", {ast::Node::makeIdentifier("a"), ast::Node::makeIdentifier("b")}) );
}

BOOST_AUTO_TEST_CASE( multiplication_parsed_correctly_with_2_arguments_with_spaces ) {
	boost::optional<ast::Node> tree = ast::parseInput("a *  b ");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::makeFunctionCall("Times", {ast::Node::makeIdentifier("a"), ast::Node::makeIdentifier("b")}) );
}

BOOST_AUTO_TEST_CASE( multiplication_parsed_correctly_with_3_arguments ) {
	boost::optional<ast::Node> tree = ast::parseInput("a*b*c");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::makeFunctionCall("Times", {ast::Node::makeIdentifier("a"), ast::Node::makeIdentifier("b"), ast::Node::makeIdentifier("c")}) );
}

BOOST_AUTO_TEST_CASE( multiplication_parsed_correctly_with_3_arguments_with_spaces ) {
	boost::optional<ast::Node> tree = ast::parseInput(" \ta \t* b * c ");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::makeFunctionCall("Times", {ast::Node::makeIdentifier("a"), ast::Node::makeIdentifier("b"), ast::Node::makeIdentifier("c")}) );
}

BOOST_AUTO_TEST_CASE( juxtaposition_works_for_two_identifiers ) {
	boost::optional<ast::Node> tree = ast::parseInput("a b");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::makeFunctionCall("Times", {ast::Node::makeIdentifier("a"), ast::Node::makeIdentifier("b")}) );
}

BOOST_AUTO_TEST_CASE( juxtaposition_works_for_two_integers ) {
	boost::optional<ast::Node> tree = ast::parseInput("10 2");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::makeFunctionCall("Times", {ast::Node::makeRational(10), ast::Node::makeRational(2)}) );
}

BOOST_AUTO_TEST_CASE( juxtaposition_works_for_two_reals_1 ) {
	boost::optional<ast::Node> tree = ast::parseInput("10.0 2.5");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::makeFunctionCall("Times", {ast::Node::makeReal(10.0), ast::Node::makeReal(2.5)}) );
}

BOOST_AUTO_TEST_CASE( juxtaposition_works_for_two_reals_2 ) {
	boost::optional<ast::Node> tree = ast::parseInput("10. .5");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::makeFunctionCall("Times", {ast::Node::makeReal(10.0), ast::Node::makeReal(0.5)}) );
}

BOOST_AUTO_TEST_CASE( juxtaposition_works_for_two_reals_3 ) {
	boost::optional<ast::Node> tree = ast::parseInput(".5 2.");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::makeFunctionCall("Times", {ast::Node::makeReal(.5), ast::Node::makeReal(2.)}) );
}

BOOST_AUTO_TEST_CASE( juxtaposition_works_between_integer_and_identifier ) {
	boost::optional<ast::Node> tree = ast::parseInput("3Pi");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::makeFunctionCall("Times", {ast::Node::makeRational(3), ast::Node::makeIdentifier("Pi")}) );
}

BOOST_AUTO_TEST_CASE( juxtaposition_works_between_real_and_identifier_1 ) {
	boost::optional<ast::Node> tree = ast::parseInput("3.5Pi");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::makeFunctionCall("Times", {ast::Node::makeReal(3.5), ast::Node::makeIdentifier("Pi")}) );
}

BOOST_AUTO_TEST_CASE( juxtaposition_works_between_real_and_identifier_2 ) {
	boost::optional<ast::Node> tree = ast::parseInput("3.Pi");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::makeFunctionCall("Times", {ast::Node::makeReal(3.), ast::Node::makeIdentifier("Pi")}) );
}

BOOST_AUTO_TEST_CASE( juxtaposition_works_with_integer_and_paranthesis ) {
	boost::optional<ast::Node> tree = ast::parseInput("3(4)");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::makeFunctionCall("Times", {ast::Node::makeRational(3), ast::Node::makeRational(4)}) );
}

BOOST_AUTO_TEST_CASE( juxtaposition_works_between_two_paranthesis ) {
	boost::optional<ast::Node> tree = ast::parseInput("(x)(y)");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::makeFunctionCall("Times", {ast::Node::makeIdentifier("x"), ast::Node::makeIdentifier("y")}) );
}

BOOST_AUTO_TEST_CASE( exponentation_parsed_correctly_with_2_arguments ) {
	boost::optional<ast::Node> tree = ast::parseInput("a^b");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::makeFunctionCall("Power", {ast::Node::makeIdentifier("a"), ast::Node::makeIdentifier("b")}) );
}

BOOST_AUTO_TEST_CASE( right_to_left_associativity_works_with_exponentation ) {
	boost::optional<ast::Node> tree = ast::parseInput("a^b^c");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::makeFunctionCall("Power", {ast::Node::makeIdentifier("a"), ast::Node::makeFunctionCall("Power", {ast::Node::makeIdentifier("b"), ast::Node::makeIdentifier("c")})}) );
}

BOOST_AUTO_TEST_CASE( plus_has_higher_precedence_than_multiplication_1 ) {
	boost::optional<ast::Node> tree = ast::parseInput("a + b * c");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::makeFunctionCall("Plus", {ast::Node::makeIdentifier("a"), ast::Node::makeFunctionCall("Times", {ast::Node::makeIdentifier("b"), ast::Node::makeIdentifier("c")})}) );
}

BOOST_AUTO_TEST_CASE( plus_has_higher_precedence_than_multiplication_2 ) {
	boost::optional<ast::Node> tree = ast::parseInput("a * b + c");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::makeFunctionCall("Plus", {ast::Node::makeFunctionCall("Times", {ast::Node::makeIdentifier("a"), ast::Node::makeIdentifier("b")}), ast::Node::makeIdentifier("c")}) );
}

BOOST_AUTO_TEST_CASE( parenthesis_modifies_precedence ) {
	boost::optional<ast::Node> tree = ast::parseInput("(a + b) * c");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::makeFunctionCall("Times", {ast::Node::makeFunctionCall("Plus", {ast::Node::makeIdentifier("a"), ast::Node::makeIdentifier("b")}), ast::Node::makeIdentifier("c")}) );
}

BOOST_AUTO_TEST_SUITE_END()
