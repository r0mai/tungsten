
#include <boost/test/unit_test.hpp>

#include "ast/AstParser.hpp"

BOOST_AUTO_TEST_SUITE( AstParserTest )

using namespace tungsten;

BOOST_AUTO_TEST_CASE( empty_input_fails ) {
	boost::optional<AstNode> tree = parseInput("");

	BOOST_CHECK( !tree );
}

BOOST_AUTO_TEST_CASE( empty_input_with_spaces_fails ) {
	boost::optional<AstNode> tree = parseInput(" \t");

	BOOST_CHECK( !tree );
}

BOOST_AUTO_TEST_CASE( integer_parsed_correctly ) {
	boost::optional<AstNode> tree = parseInput("42");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), AstNode::makeRational(42) );
}

BOOST_AUTO_TEST_CASE( integer_with_spaces_parsed_correctly ) {
	boost::optional<AstNode> tree = parseInput(" 42\t");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), AstNode::makeRational(42) );
}

BOOST_AUTO_TEST_CASE( negative_integer_parsed_correctly ) {
	boost::optional<AstNode> tree = parseInput("-42");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), AstNode::makeRational(-42) );
}

BOOST_AUTO_TEST_CASE( positive_integer_parsed_correctly ) {
	boost::optional<AstNode> tree = parseInput("+42");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), AstNode::makeRational(42) );
}

BOOST_AUTO_TEST_CASE( real_parsed_correctly ) {
	boost::optional<AstNode> tree = parseInput("1.5");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), AstNode::makeReal(1.5) );
}

BOOST_AUTO_TEST_CASE( negative_real_parsed_correctly ) {
	boost::optional<AstNode> tree = parseInput("-3.5");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), AstNode::makeReal(-3.5) );
}

BOOST_AUTO_TEST_CASE( positive_real_parsed_correctly ) {
	boost::optional<AstNode> tree = parseInput("3.5");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), AstNode::makeReal(3.5) );
}

BOOST_AUTO_TEST_CASE( real_with_no_fraction_part_parsed_correctly ) {
	boost::optional<AstNode> tree = parseInput("3.");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), AstNode::makeReal(-3.) );
}

BOOST_AUTO_TEST_CASE( real_with_no_integer_part_parsed_correctly ) {
	boost::optional<AstNode> tree = parseInput(".5");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), AstNode::makeReal(-.5) );
}

BOOST_AUTO_TEST_CASE( negative_real_with_no_integer_part_parsed_correctly ) {
	boost::optional<AstNode> tree = parseInput("-.5");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), AstNode::makeReal(-.5) );
}

BOOST_AUTO_TEST_CASE( positive_real_with_no_integer_part_parsed_correctly ) {
	boost::optional<AstNode> tree = parseInput("+.5");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), AstNode::makeReal(.5) );
}

BOOST_AUTO_TEST_CASE( Identifier_parsed_correctly ) {
	boost::optional<AstNode> tree = parseInput("Pi");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), AstNode::makeIdentifier("Pi") );
}

BOOST_AUTO_TEST_CASE( Identifier_with_trailing_numbers_parsed_correctly ) {
	boost::optional<AstNode> tree = parseInput("X123");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), AstNode::makeIdentifier("X123") );
}

BOOST_AUTO_TEST_CASE( Identifier_with_numbers_in_middle_parsed_correctly ) {
	boost::optional<AstNode> tree = parseInput("X123Y");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), AstNode::makeIdentifier("X123Y") );
}

BOOST_AUTO_TEST_CASE( Identifier_parsed_correctly_with_spaces ) {
	boost::optional<AstNode> tree = parseInput("\tPi ");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), AstNode::makeIdentifier("Pi") );
}

BOOST_AUTO_TEST_CASE( String_parsed_correctly ) {
	boost::optional<AstNode> tree = parseInput("\"abc\"");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), AstNode::makeString("abc") );
}

BOOST_AUTO_TEST_CASE( String_parsed_correctly_with_spaces_inside ) {
	boost::optional<AstNode> tree = parseInput("\"a b\t c\"");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), AstNode::makeString("a b\tc") );
}

BOOST_AUTO_TEST_CASE( String_parsed_correctly_with_spaces_outside ) {
	boost::optional<AstNode> tree = parseInput("  \"a b\t c\" ");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), AstNode::makeString("a b\tc") );
}

BOOST_AUTO_TEST_CASE( function_without_parameters_parsed_correctly ) {
	boost::optional<AstNode> tree = parseInput("foo[]");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), AstNode::makeFunction("foo") );
}

BOOST_AUTO_TEST_CASE( function_without_parameters_with_spaces_parsed_correctly ) {
	boost::optional<AstNode> tree = parseInput("\tfoo\t[ ] ");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), AstNode::makeFunction("foo") );
}

BOOST_AUTO_TEST_CASE( function_with_single_parameter_parsed_correctly ) {
	boost::optional<AstNode> tree = parseInput("foo[1]");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), AstNode::makeFunction("foo", {AstNode::makeRational(1)}) );
}

BOOST_AUTO_TEST_CASE( function_with_single_parameter_with_spaces_parsed_correctly ) {
	boost::optional<AstNode> tree = parseInput("  foo [1 ] ");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), AstNode::makeFunction("f", {AstNode::makeRational(1)}) );
}

BOOST_AUTO_TEST_CASE( function_with_multiple_parameter_parsed_correctly ) {
	boost::optional<AstNode> tree = parseInput("foo[1,2,3]");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), AstNode::makeFunction("foo",
			{AstNode::makeRational(1),
			AstNode::makeRational(2),
			AstNode::makeRational(3)}) );
}

BOOST_AUTO_TEST_CASE( function_with_multiple_parameter_with_spaces_parsed_correctly ) {
	boost::optional<AstNode> tree = parseInput("  foo [1 ,2,3 ] ");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), AstNode::makeFunction("foo",
			{AstNode::makeRational(1),
			AstNode::makeRational(2),
			AstNode::makeRational(3)}) );
}

BOOST_AUTO_TEST_CASE( nested_function_parsed_correctly_1 ) {
	boost::optional<AstNode> tree = parseInput("f[g[]]");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), AstNode::makeFunction("f", {AstNode::makeFunction("g")}) );

}

BOOST_AUTO_TEST_CASE( nested_function_parsed_correctly_2 ) {
	boost::optional<AstNode> tree = parseInput("f[g[], h[1]]");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), AstNode::makeFunction("f", {
					AstNode::makeFunction("g"),
					AstNode::makeFunction("h", {
							AstNode::makeRational(1)
					})
	}) );

}

BOOST_AUTO_TEST_CASE( addition_parsed_correctly_with_2_arguments ) {
	boost::optional<AstNode> tree = parseInput("a+b");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), AstNode::makeFunction("Plus", {AstNode::makeIdentifier("a"), AstNode::makeIdentifier("b")}) );
}

BOOST_AUTO_TEST_CASE( addition_parsed_correctly_with_2_arguments_with_spaces ) {
	boost::optional<AstNode> tree = parseInput("a +  b ");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), AstNode::makeFunction("Plus", {AstNode::makeIdentifier("a"), AstNode::makeIdentifier("b")}) );
}

BOOST_AUTO_TEST_CASE( addition_parsed_correctly_with_3_arguments ) {
	boost::optional<AstNode> tree = parseInput("a+b+c");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), AstNode::makeFunction("Plus", {AstNode::makeIdentifier("a"), AstNode::makeIdentifier("b"), AstNode::makeIdentifier("b")}) );
}

BOOST_AUTO_TEST_CASE( addition_parsed_correctly_with_3_arguments_with_spaces ) {
	boost::optional<AstNode> tree = parseInput(" \ta \t+ b + c ");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), AstNode::makeFunction("Plus", {AstNode::makeIdentifier("a"), AstNode::makeIdentifier("b"), AstNode::makeIdentifier("b")}) );
}


BOOST_AUTO_TEST_CASE( multiplication_parsed_correctly_with_2_arguments ) {
	boost::optional<AstNode> tree = parseInput("a*b");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), AstNode::makeFunction("Times", {AstNode::makeIdentifier("a"), AstNode::makeIdentifier("b")}) );
}

BOOST_AUTO_TEST_CASE( multiplication_parsed_correctly_with_2_arguments_with_spaces ) {
	boost::optional<AstNode> tree = parseInput("a *  b ");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), AstNode::makeFunction("Times", {AstNode::makeIdentifier("a"), AstNode::makeIdentifier("b")}) );
}

BOOST_AUTO_TEST_CASE( multiplication_parsed_correctly_with_3_arguments ) {
	boost::optional<AstNode> tree = parseInput("a*b*c");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), AstNode::makeFunction("Times", {AstNode::makeIdentifier("a"), AstNode::makeIdentifier("b"), AstNode::makeIdentifier("b")}) );
}

BOOST_AUTO_TEST_CASE( multiplication_parsed_correctly_with_3_arguments_with_spaces ) {
	boost::optional<AstNode> tree = parseInput(" \ta \t* b * c ");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), AstNode::makeFunction("Times", {AstNode::makeIdentifier("a"), AstNode::makeIdentifier("b"), AstNode::makeIdentifier("b")}) );
}

BOOST_AUTO_TEST_CASE( juxtaposition_works_for_two_identifiers ) {
	boost::optional<AstNode> tree = parseInput("a b");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), AstNode::makeFunction("Times", {AstNode::makeIdentifier("a"), AstNode::makeIdentifier("b")}) );
}

BOOST_AUTO_TEST_CASE( juxtaposition_works_for_two_integers ) {
	boost::optional<AstNode> tree = parseInput("10 2");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), AstNode::makeFunction("Times", {AstNode::makeRational(10), AstNode::makeRational(2)}) );
}

BOOST_AUTO_TEST_CASE( juxtaposition_works_for_two_reals_1 ) {
	boost::optional<AstNode> tree = parseInput("10.0 2.5");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), AstNode::makeFunction("Times", {AstNode::makeReal(10.0), AstNode::makeReal(2.5)}) );
}

BOOST_AUTO_TEST_CASE( juxtaposition_works_for_two_reals_2 ) {
	boost::optional<AstNode> tree = parseInput("10. .5");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), AstNode::makeFunction("Times", {AstNode::makeReal(10.0), AstNode::makeReal(0.5)}) );
}

BOOST_AUTO_TEST_CASE( juxtaposition_works_for_two_reals_3 ) {
	boost::optional<AstNode> tree = parseInput(".5 2.");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), AstNode::makeFunction("Times", {AstNode::makeReal(.5), AstNode::makeReal(2.)}) );
}

BOOST_AUTO_TEST_CASE( juxtaposition_works_between_integer_and_identifier ) {
	boost::optional<AstNode> tree = parseInput("3Pi");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), AstNode::makeFunction("Times", {AstNode::makeRational(3), AstNode::makeIdentifier("Pi")}) );
}

BOOST_AUTO_TEST_CASE( juxtaposition_works_between_real_and_identifier_1 ) {
	boost::optional<AstNode> tree = parseInput("3.5Pi");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), AstNode::makeFunction("Times", {AstNode::makeReal(3.5), AstNode::makeIdentifier("Pi")}) );
}

BOOST_AUTO_TEST_CASE( juxtaposition_works_between_real_and_identifier_2 ) {
	boost::optional<AstNode> tree = parseInput("3.Pi");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), AstNode::makeFunction("Times", {AstNode::makeReal(3.), AstNode::makeIdentifier("Pi")}) );
}

BOOST_AUTO_TEST_CASE( juxtaposition_works_with_integer_and_paranthesis ) {
	boost::optional<AstNode> tree = parseInput("3(4)");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), AstNode::makeFunction("Times", {AstNode::makeRational(3), AstNode::makeRational(4)}) );
}

BOOST_AUTO_TEST_CASE( juxtaposition_works_between_two_paranthesis ) {
	boost::optional<AstNode> tree = parseInput("(x)(y)");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), AstNode::makeFunction("Times", {AstNode::makeIdentifier("x"), AstNode::makeIdentifier("y")}) );
}

BOOST_AUTO_TEST_CASE( exponentation_parsed_correctly_with_2_arguments ) {
	boost::optional<AstNode> tree = parseInput("a^b");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), AstNode::makeFunction("Power", {AstNode::makeIdentifier("a"), AstNode::makeIdentifier("b")}) );
}

BOOST_AUTO_TEST_CASE( right_to_left_associativity_works_with_exponentation ) {
	boost::optional<AstNode> tree = parseInput("a^b^c");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), AstNode::makeFunction("Power", {AstNode::makeIdentifier("a"), AstNode::makeFunction("Power", {AstNode::makeIdentifier("b"), AstNode::makeIdentifier("c")})}) );
}

BOOST_AUTO_TEST_SUITE_END()
