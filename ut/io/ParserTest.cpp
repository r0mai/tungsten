
#include <boost/test/unit_test.hpp>

#include "io/Parser.hpp"

BOOST_AUTO_TEST_SUITE( ParserTest )

using namespace tungsten;

BOOST_AUTO_TEST_CASE( empty_input_results_in_Null ) {
	boost::optional<ast::Node> tree = io::parseInput("");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( *tree, ast::Node::make<ast::Identifier>("Null") );
}

BOOST_AUTO_TEST_CASE( empty_input_with_spaces_results_in_Null ) {
	boost::optional<ast::Node> tree = io::parseInput(" \t");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( *tree, ast::Node::make<ast::Identifier>("Null") );
}

BOOST_AUTO_TEST_CASE( empty_input_with_newlines_results_in_Null ) {
	boost::optional<ast::Node> tree = io::parseInput(" \n\n");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( *tree, ast::Node::make<ast::Identifier>("Null") );
}

BOOST_AUTO_TEST_CASE( compoundExpression_test_trailing_semicolon ) {
	boost::optional<ast::Node> tree = io::parseInput("a;");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( *tree, ast::Node::make<ast::FunctionCall>("CompoundExpression",
			{ast::Node::make<ast::Identifier>("a"), ast::Node::make<ast::Identifier>("Null")}) );
}

BOOST_AUTO_TEST_CASE( compoundExpression_test_separating_semicolon ) {
	boost::optional<ast::Node> tree = io::parseInput("a;b");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( *tree, ast::Node::make<ast::FunctionCall>("CompoundExpression",
			{ast::Node::make<ast::Identifier>("a"), ast::Node::make<ast::Identifier>("b")}) );
}

BOOST_AUTO_TEST_CASE( compoundExpression_test_separating_and_semicolon ) {
	boost::optional<ast::Node> tree = io::parseInput("a;b;");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( *tree, ast::Node::make<ast::FunctionCall>("CompoundExpression",
			{ast::Node::make<ast::Identifier>("a"),
					ast::Node::make<ast::Identifier>("b"),
					ast::Node::make<ast::Identifier>("Null")}) );
}

BOOST_AUTO_TEST_CASE( compoundExpression_test_two_separating_semicolon ) {
	boost::optional<ast::Node> tree = io::parseInput("a;b;c");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( *tree, ast::Node::make<ast::FunctionCall>("CompoundExpression",
			{ast::Node::make<ast::Identifier>("a"),
					ast::Node::make<ast::Identifier>("b"),
					ast::Node::make<ast::Identifier>("c")}) );
}

BOOST_AUTO_TEST_CASE( compoundExpression_test_separating_and_trailing_with_parentheses_semicolon ) {
	boost::optional<ast::Node> tree = io::parseInput("(a;);");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( *tree, ast::Node::make<ast::FunctionCall>("CompoundExpression",
			{ast::Node::make<ast::FunctionCall>("CompoundExpression",
			{ast::Node::make<ast::Identifier>("a"),
					ast::Node::make<ast::Identifier>("Null")}), ast::Node::make<ast::Identifier>("Null")})  );
}

BOOST_AUTO_TEST_CASE( integer_parsed_correctly ) {
	boost::optional<ast::Node> tree = io::parseInput("42");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<math::Rational>(42) );
}

BOOST_AUTO_TEST_CASE( huge_integer_parsed_correctly ) {
	boost::optional<ast::Node> tree = io::parseInput("123456789987654321123456789987654321");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<math::Rational>("123456789987654321123456789987654321") );
}

BOOST_AUTO_TEST_CASE( integer_with_spaces_parsed_correctly ) {
	boost::optional<ast::Node> tree = io::parseInput(" 42\t");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<math::Rational>(42) );
}

BOOST_AUTO_TEST_CASE( negative_integer_parsed_correctly ) {
	boost::optional<ast::Node> tree = io::parseInput("-42");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<math::Rational>(-42) );
}

BOOST_AUTO_TEST_CASE( positive_integer_parsed_correctly ) {
	boost::optional<ast::Node> tree = io::parseInput("+42");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<math::Rational>(42) );
}

BOOST_AUTO_TEST_CASE( real_parsed_correctly ) {
	boost::optional<ast::Node> tree = io::parseInput("1.5");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<math::Real>(1.5) );
}

BOOST_AUTO_TEST_CASE( huge_real_parsed_correctly ) {
	boost::optional<ast::Node> tree = io::parseInput("1283618212498721056128561248126489126811.5");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<math::Real>("1283618212498721056128561248126489126811.5") );
}

BOOST_AUTO_TEST_CASE( negative_real_parsed_correctly ) {
	boost::optional<ast::Node> tree = io::parseInput("-3.5");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<math::Real>(-3.5) );
}

BOOST_AUTO_TEST_CASE( positive_real_parsed_correctly ) {
	boost::optional<ast::Node> tree = io::parseInput("3.5");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<math::Real>(3.5) );
}

BOOST_AUTO_TEST_CASE( real_with_no_fraction_part_parsed_correctly ) {
	boost::optional<ast::Node> tree = io::parseInput("3.");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<math::Real>(3.) );
}

BOOST_AUTO_TEST_CASE( real_with_no_integer_part_parsed_correctly ) {
	boost::optional<ast::Node> tree = io::parseInput(".5");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<math::Real>(.5) );
}

BOOST_AUTO_TEST_CASE( negative_real_with_no_integer_part_parsed_correctly ) {
	boost::optional<ast::Node> tree = io::parseInput("-.5");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<math::Real>(-.5) );
}

BOOST_AUTO_TEST_CASE( explicit_positive_real_with_no_integer_part_parsed_correctly ) {
	boost::optional<ast::Node> tree = io::parseInput("+.5");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<math::Real>(.5) );
}

BOOST_AUTO_TEST_CASE( Identifier_parsed_correctly ) {
	boost::optional<ast::Node> tree = io::parseInput("Pi");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::Identifier>("Pi") );
}

BOOST_AUTO_TEST_CASE( Identifier_with_trailing_numbers_parsed_correctly ) {
	boost::optional<ast::Node> tree = io::parseInput("X123");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::Identifier>("X123") );
}

BOOST_AUTO_TEST_CASE( Identifier_with_numbers_in_middle_parsed_correctly ) {
	boost::optional<ast::Node> tree = io::parseInput("X123Y");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::Identifier>("X123Y") );
}

BOOST_AUTO_TEST_CASE( Identifier_parsed_correctly_with_spaces ) {
	boost::optional<ast::Node> tree = io::parseInput("\tPi ");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::Identifier>("Pi") );
}

BOOST_AUTO_TEST_CASE( Identifier_parsed_correctly_with_starting_dollar_sign ) {
	boost::optional<ast::Node> tree = io::parseInput("$abc ");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::Identifier>("$abc") );
}

BOOST_AUTO_TEST_CASE( Identifier_parsed_correctly_with_dollarsign ) {
	boost::optional<ast::Node> tree = io::parseInput("a$bc ");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::Identifier>("a$bc") );
}

BOOST_AUTO_TEST_CASE( String_parsed_correctly ) {
	boost::optional<ast::Node> tree = io::parseInput("\"abc\"");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::String>("abc") );
}

BOOST_AUTO_TEST_CASE( String_parsed_correctly_with_spaces_inside ) {
	boost::optional<ast::Node> tree = io::parseInput("\"a b  c\"");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::String>("a b  c") );
}

BOOST_AUTO_TEST_CASE( String_parsed_correctly_with_spaces_outside ) {
	boost::optional<ast::Node> tree = io::parseInput("  \"a b c\" ");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::String>("a b c") );
}

BOOST_AUTO_TEST_CASE( String_parsed_correctly_with_escaped_new_line ) {
	boost::optional<ast::Node> tree = io::parseInput("\"a\\nb\"");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::String>("a\nb") );
}

BOOST_AUTO_TEST_CASE( String_parsed_correctly_with_escaped_carrige_return ) {
	boost::optional<ast::Node> tree = io::parseInput("\"a\\rb\"");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::String>("a\rb") );
}

BOOST_AUTO_TEST_CASE( String_parsed_correctly_with_escaped_bell ) {
	boost::optional<ast::Node> tree = io::parseInput("\"a\\ac\"");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::String>("a\ac") );
}

BOOST_AUTO_TEST_CASE( String_parsed_correctly_with_escaped_backspace ) {
	boost::optional<ast::Node> tree = io::parseInput("\"a\\bc\"");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::String>("a\bc") );
}

BOOST_AUTO_TEST_CASE( String_parsed_correctly_with_escaped_formfeed ) {
	boost::optional<ast::Node> tree = io::parseInput("\"a\\fc\"");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::String>("a\fc") );
}

BOOST_AUTO_TEST_CASE( String_parsed_correctly_with_escaped_horizontal_tab ) {
	boost::optional<ast::Node> tree = io::parseInput("\"a\\tc\"");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::String>("a\tc") );
}

BOOST_AUTO_TEST_CASE( String_parsed_correctly_with_escaped_vertical_tab ) {
	boost::optional<ast::Node> tree = io::parseInput("\"a\\vc\"");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::String>("a\vc") );
}

BOOST_AUTO_TEST_CASE( String_parsed_correctly_with_escaped_quotation_mark ) {
	boost::optional<ast::Node> tree = io::parseInput("\"a\\\"b\"");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::String>("a\"b") );
}

BOOST_AUTO_TEST_CASE( String_parsed_correctly_with_escaped_back_slash ) {
	boost::optional<ast::Node> tree = io::parseInput("\"a\\\\b\"");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::String>("a\\b") );
}

BOOST_AUTO_TEST_CASE( String_parsed_correctly_with_escaped_tabulator ) {
	boost::optional<ast::Node> tree = io::parseInput("\"a\\tb\"");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::String>("a\tb") );
}

BOOST_AUTO_TEST_CASE( String_parsed_correctly_with_multiple_escaped_characters ) {
	boost::optional<ast::Node> tree = io::parseInput("\"\\\"\\n\\\\\"");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::String>("\"\n\\") );
}

BOOST_AUTO_TEST_CASE( function_without_parameters_parsed_correctly ) {
	boost::optional<ast::Node> tree = io::parseInput("foo[]");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::FunctionCall>("foo") );
}

BOOST_AUTO_TEST_CASE( function_without_parameters_with_spaces_parsed_correctly ) {
	boost::optional<ast::Node> tree = io::parseInput("\tfoo\t[ ] ");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::FunctionCall>("foo") );
}

BOOST_AUTO_TEST_CASE( function_with_single_parameter_parsed_correctly ) {
	boost::optional<ast::Node> tree = io::parseInput("foo[1]");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::FunctionCall>("foo", {ast::Node::make<math::Rational>(1)}) );
}

BOOST_AUTO_TEST_CASE( function_with_single_parameter_with_spaces_parsed_correctly ) {
	boost::optional<ast::Node> tree = io::parseInput("  foo [1 ] ");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::FunctionCall>("foo", {ast::Node::make<math::Rational>(1)}) );
}

BOOST_AUTO_TEST_CASE( function_with_multiple_parameter_parsed_correctly ) {
	boost::optional<ast::Node> tree = io::parseInput("foo[1,2,3]");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::FunctionCall>("foo",
			{ast::Node::make<math::Rational>(1),
			ast::Node::make<math::Rational>(2),
			ast::Node::make<math::Rational>(3)}) );
}

BOOST_AUTO_TEST_CASE( function_with_multiple_parameter_with_spaces_parsed_correctly ) {
	boost::optional<ast::Node> tree = io::parseInput("  foo [1 ,2,3 ] ");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::FunctionCall>("foo",
			{ast::Node::make<math::Rational>(1),
			ast::Node::make<math::Rational>(2),
			ast::Node::make<math::Rational>(3)}) );
}

BOOST_AUTO_TEST_CASE( nested_function_parsed_correctly_1 ) {
	boost::optional<ast::Node> tree = io::parseInput("f[g[]]");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::FunctionCall>("f", {ast::Node::make<ast::FunctionCall>("g")}) );

}

BOOST_AUTO_TEST_CASE( nested_function_parsed_correctly_2 ) {
	boost::optional<ast::Node> tree = io::parseInput("f[g[], h[1]]");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::FunctionCall>("f", {
					ast::Node::make<ast::FunctionCall>("g"),
					ast::Node::make<ast::FunctionCall>("h", {
							ast::Node::make<math::Rational>(1)
					})
	}) );

}

BOOST_AUTO_TEST_CASE( non_identifier_function_parsed_correctly_1 ) {
	boost::optional<ast::Node> tree = io::parseInput(" 2 []\t");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::FunctionCall>(
			ast::Node::make<math::Rational>(2) ) );
}

BOOST_AUTO_TEST_CASE( non_identifier_function_parsed_correctly_2 ) {
	boost::optional<ast::Node> tree = io::parseInput("f[ ]\t[]");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(),
			ast::Node::make<ast::FunctionCall>(
					ast::Node::make<ast::FunctionCall>("f")
			)
	);
}

BOOST_AUTO_TEST_CASE( identifier_function_parsed_correctly_with_parentheses ) {
	boost::optional<ast::Node> tree = io::parseInput("( f) []");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(),
			ast::Node::make<ast::FunctionCall>("f")
	);
}

BOOST_AUTO_TEST_CASE( empty_brackets_not_parsed ) {
	boost::optional<ast::Node> tree = io::parseInput("[]");

	BOOST_CHECK( !tree );
}

BOOST_AUTO_TEST_CASE( unary_minus_parsed_correctly_with_Identifier ) {
	boost::optional<ast::Node> tree = io::parseInput("-a");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<math::Rational>(-1), ast::Node::make<ast::Identifier>("a")}) );
}

BOOST_AUTO_TEST_CASE( unary_plus_parsed_correctly_with_Identifier ) {
	boost::optional<ast::Node> tree = io::parseInput("+a");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::Identifier>("a") );
}

BOOST_AUTO_TEST_CASE( unary_minus_parsed_correctly_with_Identifier_in_parentheses ) {
	boost::optional<ast::Node> tree = io::parseInput("-(a)");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<math::Rational>(-1), ast::Node::make<ast::Identifier>("a")}) );
}

BOOST_AUTO_TEST_CASE( unary_plus_parsed_correctly_with_Identifier_in_parentheses ) {
	boost::optional<ast::Node> tree = io::parseInput("+(a)");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::Identifier>("a") );
}

BOOST_AUTO_TEST_CASE( two_unary_minuses_parsed_correctly_with_Identifier ) {
	boost::optional<ast::Node> tree = io::parseInput("- -a"); //--a is predecrement

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<math::Rational>(-1),
			ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<math::Rational>(-1), ast::Node::make<ast::Identifier>("a")}) } ) );
}

BOOST_AUTO_TEST_CASE( two_unary_pluses_parsed_correctly_with_Identifier ) {
	boost::optional<ast::Node> tree = io::parseInput("+ +a"); //++a is preincrement

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::Identifier>("a") );
}

BOOST_AUTO_TEST_CASE( two_unary_minuses_parsed_correctly_with_Integer ) {
	boost::optional<ast::Node> tree = io::parseInput("- -3");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<math::Rational>(-1), ast::Node::make<math::Rational>(-3)}) );
}

BOOST_AUTO_TEST_CASE( two_unary_minuses_parsed_correctly_with_Real ) {
	boost::optional<ast::Node> tree = io::parseInput("- -3.2");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<math::Rational>(-1), ast::Node::make<math::Real>("-3.2")}) );
}

BOOST_AUTO_TEST_CASE( unary_minus_has_lower_precedence_than_Plus ) {
	boost::optional<ast::Node> tree = io::parseInput("-a+b");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(),
			ast::Node::make<ast::FunctionCall>("Plus", {
					ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<math::Rational>(-1), ast::Node::make<ast::Identifier>("a")}),
					ast::Node::make<ast::Identifier>("b")
			}) );
}

BOOST_AUTO_TEST_CASE( unary_minus_has_lower_precedence_than_Times ) {
	boost::optional<ast::Node> tree = io::parseInput("-a*b");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(),
			ast::Node::make<ast::FunctionCall>("Times", {
					ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<math::Rational>(-1), ast::Node::make<ast::Identifier>("a")}),
					ast::Node::make<ast::Identifier>("b")
			}) );
}

BOOST_AUTO_TEST_CASE( unary_minus_has_higher_precedence_than_Power ) {
	boost::optional<ast::Node> tree = io::parseInput("-a^b");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(),
			ast::Node::make<ast::FunctionCall>("Times", {
					ast::Node::make<math::Rational>(-1),
					ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("a"), ast::Node::make<ast::Identifier>("b")})
			}) );
}

BOOST_AUTO_TEST_CASE( addition_parsed_correctly_with_2_arguments ) {
	boost::optional<ast::Node> tree = io::parseInput("a+b");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::FunctionCall>("Plus", {ast::Node::make<ast::Identifier>("a"), ast::Node::make<ast::Identifier>("b")}) );
}

BOOST_AUTO_TEST_CASE( addition_parsed_correctly_with_2_arguments_with_spaces ) {
	boost::optional<ast::Node> tree = io::parseInput("a +  b ");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::FunctionCall>("Plus", {ast::Node::make<ast::Identifier>("a"), ast::Node::make<ast::Identifier>("b")}) );
}

BOOST_AUTO_TEST_CASE( addition_parsed_correctly_with_3_arguments ) {
	boost::optional<ast::Node> tree = io::parseInput("a+b+c");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::FunctionCall>("Plus", {ast::Node::make<ast::Identifier>("a"), ast::Node::make<ast::Identifier>("b"), ast::Node::make<ast::Identifier>("c")}) );
}

BOOST_AUTO_TEST_CASE( addition_parsed_correctly_with_3_arguments_with_spaces ) {
	boost::optional<ast::Node> tree = io::parseInput(" \ta \t+ b + c ");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::FunctionCall>("Plus", {ast::Node::make<ast::Identifier>("a"), ast::Node::make<ast::Identifier>("b"), ast::Node::make<ast::Identifier>("c")}) );
}

BOOST_AUTO_TEST_CASE( binary_Minus_Parentheses_parsed_correctly ) {
	boost::optional<ast::Node> tree = io::parseInput("a-(b)");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::FunctionCall>("Plus", {
			ast::Node::make<ast::Identifier>("a"),
			ast::Node::make<ast::FunctionCall>("Times", {
					ast::Node::make<math::Rational>(-1),
					ast::Node::make<ast::Identifier>("b")
			})
	}) );
}

BOOST_AUTO_TEST_CASE( Divide_Parentheses_parsed_correctly ) {
	boost::optional<ast::Node> tree = io::parseInput("a/(b)");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::FunctionCall>("Times", {
			ast::Node::make<ast::Identifier>("a"),
			ast::Node::make<ast::FunctionCall>("Power", {
					ast::Node::make<ast::Identifier>("b"),
					ast::Node::make<math::Rational>(-1)
			})
	}) );
}

BOOST_AUTO_TEST_CASE( multiplication_parsed_correctly_with_2_arguments ) {
	boost::optional<ast::Node> tree = io::parseInput("a*b");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("a"), ast::Node::make<ast::Identifier>("b")}) );
}

BOOST_AUTO_TEST_CASE( multiplication_parsed_correctly_with_2_arguments_with_spaces ) {
	boost::optional<ast::Node> tree = io::parseInput("a *  b ");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("a"), ast::Node::make<ast::Identifier>("b")}) );
}

BOOST_AUTO_TEST_CASE( multiplication_parsed_correctly_with_3_arguments ) {
	boost::optional<ast::Node> tree = io::parseInput("a*b*c");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("a"), ast::Node::make<ast::Identifier>("b"), ast::Node::make<ast::Identifier>("c")}) );
}

BOOST_AUTO_TEST_CASE( multiplication_parsed_correctly_with_3_arguments_with_spaces ) {
	boost::optional<ast::Node> tree = io::parseInput(" \ta \t* b * c ");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("a"), ast::Node::make<ast::Identifier>("b"), ast::Node::make<ast::Identifier>("c")}) );
}

BOOST_AUTO_TEST_CASE( juxtaposition_works_for_two_identifiers ) {
	boost::optional<ast::Node> tree = io::parseInput("a b");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("a"), ast::Node::make<ast::Identifier>("b")}) );
}

BOOST_AUTO_TEST_CASE( juxtaposition_works_for_two_integers ) {
	boost::optional<ast::Node> tree = io::parseInput("10 2");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<math::Rational>(10), ast::Node::make<math::Rational>(2)}) );
}

BOOST_AUTO_TEST_CASE( juxtaposition_works_for_two_reals_1 ) {
	boost::optional<ast::Node> tree = io::parseInput("10.0 2.5");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<math::Real>(10.0), ast::Node::make<math::Real>(2.5)}) );
}

BOOST_AUTO_TEST_CASE( juxtaposition_works_for_two_reals_2 ) {
	boost::optional<ast::Node> tree = io::parseInput("10. .5");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<math::Real>(10.0), ast::Node::make<math::Real>(0.5)}) );
}

BOOST_AUTO_TEST_CASE( juxtaposition_works_for_two_reals_3 ) {
	boost::optional<ast::Node> tree = io::parseInput(".5 2.");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<math::Real>(.5), ast::Node::make<math::Real>(2.)}) );
}

BOOST_AUTO_TEST_CASE( juxtaposition_works_between_integer_and_identifier ) {
	boost::optional<ast::Node> tree = io::parseInput("3Pi");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<math::Rational>(3), ast::Node::make<ast::Identifier>("Pi")}) );
}

BOOST_AUTO_TEST_CASE( juxtaposition_works_between_real_and_identifier_1 ) {
	boost::optional<ast::Node> tree = io::parseInput("3.5Pi");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<math::Real>(3.5), ast::Node::make<ast::Identifier>("Pi")}) );
}

BOOST_AUTO_TEST_CASE( juxtaposition_works_between_real_and_identifier_2 ) {
	boost::optional<ast::Node> tree = io::parseInput("3.Pi");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<math::Real>(3.), ast::Node::make<ast::Identifier>("Pi")}) );
}

BOOST_AUTO_TEST_CASE( juxtaposition_works_with_integer_and_paranthesis ) {
	boost::optional<ast::Node> tree = io::parseInput("3(4)");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<math::Rational>(3), ast::Node::make<math::Rational>(4)}) );
}

BOOST_AUTO_TEST_CASE( juxtaposition_works_between_two_paranthesis ) {
	boost::optional<ast::Node> tree = io::parseInput("(x)(y)");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::Identifier>("y")}) );
}

BOOST_AUTO_TEST_CASE( exponentation_parsed_correctly_with_2_arguments ) {
	boost::optional<ast::Node> tree = io::parseInput("a^b");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("a"), ast::Node::make<ast::Identifier>("b")}) );
}

BOOST_AUTO_TEST_CASE( right_to_left_associativity_works_with_exponentation ) {
	boost::optional<ast::Node> tree = io::parseInput("a^b^c");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("a"), ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("b"), ast::Node::make<ast::Identifier>("c")})}) );
}

BOOST_AUTO_TEST_CASE( parentheses_around_the_whole_expression_makes_no_difference ) {
	boost::optional<ast::Node> tree = io::parseInput("(a)");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::Identifier>("a") );
}

BOOST_AUTO_TEST_CASE( plus_has_higher_precedence_than_multiplication_1 ) {
	boost::optional<ast::Node> tree = io::parseInput("a + b * c");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::FunctionCall>("Plus", {ast::Node::make<ast::Identifier>("a"), ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("b"), ast::Node::make<ast::Identifier>("c")})}) );
}

BOOST_AUTO_TEST_CASE( plus_has_higher_precedence_than_multiplication_2 ) {
	boost::optional<ast::Node> tree = io::parseInput("a * b + c");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::FunctionCall>("Plus", {ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("a"), ast::Node::make<ast::Identifier>("b")}), ast::Node::make<ast::Identifier>("c")}) );
}

BOOST_AUTO_TEST_CASE( parenthesis_modifies_precedence_with_Plus_and_Times ) {
	boost::optional<ast::Node> tree = io::parseInput("(a + b) * c");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Plus", {ast::Node::make<ast::Identifier>("a"), ast::Node::make<ast::Identifier>("b")}), ast::Node::make<ast::Identifier>("c")}) );
}

BOOST_AUTO_TEST_CASE( empty_List_parsed_correctly ) {
	boost::optional<ast::Node> tree = io::parseInput("{}");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::FunctionCall>("List") );
}

BOOST_AUTO_TEST_CASE( one_argument_List_parsed_correctly ) {
	boost::optional<ast::Node> tree = io::parseInput("{x}");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("x")}) );
}

BOOST_AUTO_TEST_CASE( two_argument_List_parsed_correctly ) {
	boost::optional<ast::Node> tree = io::parseInput("{x, y}");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::Identifier>("y")}) );
}

BOOST_AUTO_TEST_CASE( Lists_can_take_part_in_expressions ) {
	boost::optional<ast::Node> tree = io::parseInput("{x} + {}");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::FunctionCall>("Plus",
			{ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("x")}),
			ast::Node::make<ast::FunctionCall>("List")}) );
}

BOOST_AUTO_TEST_CASE( Set_operator_basic_test ) {
	boost::optional<ast::Node> tree = io::parseInput("x=3");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::FunctionCall>("Set",
			{ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(3)}) );
}

BOOST_AUTO_TEST_CASE( nested_Set_operator_test ) {
	boost::optional<ast::Node> tree = io::parseInput("x=y=3");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::FunctionCall>("Set", {
			ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::FunctionCall>("Set", {
							ast::Node::make<ast::Identifier>("y"),
					ast::Node::make<math::Rational>(3)})}) );
}

BOOST_AUTO_TEST_CASE( Set_operator_has_lower_precedence_than_Plus ) {
	boost::optional<ast::Node> tree = io::parseInput("x=a+b");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::FunctionCall>("Set",
			{ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::FunctionCall>("Plus",
					{ast::Node::make<ast::Identifier>("a"), ast::Node::make<ast::Identifier>("b")})}) );
}

BOOST_AUTO_TEST_CASE( Set_operator_has_lower_precedence_than_Times ) {
	boost::optional<ast::Node> tree = io::parseInput("x=a*b");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::FunctionCall>("Set",
			{ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::FunctionCall>("Times",
					{ast::Node::make<ast::Identifier>("a"), ast::Node::make<ast::Identifier>("b")})}) );
}

BOOST_AUTO_TEST_CASE( Set_operator_has_lower_precedence_than_Power ) {
	boost::optional<ast::Node> tree = io::parseInput("x=a^b");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::FunctionCall>("Set",
			{ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::FunctionCall>("Power",
					{ast::Node::make<ast::Identifier>("a"), ast::Node::make<ast::Identifier>("b")})}) );
}

BOOST_AUTO_TEST_CASE( SetDelayed_operator_basic_test ) {
	boost::optional<ast::Node> tree = io::parseInput("x:=3");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::FunctionCall>("SetDelayed",
			{ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(3)}) );
}

BOOST_AUTO_TEST_CASE( nested_SetDelayed_operator_test ) {
	boost::optional<ast::Node> tree = io::parseInput("x:=y:=3");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::FunctionCall>("SetDelayed", {
			ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::FunctionCall>("SetDelayed", {
							ast::Node::make<ast::Identifier>("y"),
					ast::Node::make<math::Rational>(3)})}) );
}

BOOST_AUTO_TEST_CASE( SetDelayed_operator_has_lower_precedence_than_Plus ) {
	boost::optional<ast::Node> tree = io::parseInput("x:=a+b");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::FunctionCall>("SetDelayed",
			{ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::FunctionCall>("Plus",
					{ast::Node::make<ast::Identifier>("a"), ast::Node::make<ast::Identifier>("b")})}) );
}

BOOST_AUTO_TEST_CASE( SetDelayed_operator_has_lower_precedence_than_Times ) {
	boost::optional<ast::Node> tree = io::parseInput("x:=a*b");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::FunctionCall>("SetDelayed",
			{ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::FunctionCall>("Times",
					{ast::Node::make<ast::Identifier>("a"), ast::Node::make<ast::Identifier>("b")})}) );
}

BOOST_AUTO_TEST_CASE( SetDelayed_operator_has_lower_precedence_than_Power ) {
	boost::optional<ast::Node> tree = io::parseInput("x:=a^b");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::FunctionCall>("SetDelayed",
			{ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::FunctionCall>("Power",
					{ast::Node::make<ast::Identifier>("a"), ast::Node::make<ast::Identifier>("b")})}) );
}


BOOST_AUTO_TEST_CASE( Infinity_parsed_as_Identifier ) {
	boost::optional<ast::Node> tree = io::parseInput("Infinity");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::Identifier>("Infinity") );
}

BOOST_AUTO_TEST_CASE( Inf_parsed_as_Identifier ) {
	boost::optional<ast::Node> tree = io::parseInput("Inf");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::Identifier>("Inf") );
}

BOOST_AUTO_TEST_CASE( nan_parsed_as_Identifier ) {
	boost::optional<ast::Node> tree = io::parseInput("nan");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::Identifier>("nan") );
}

BOOST_AUTO_TEST_CASE( parsing_blank ) {
	boost::optional<ast::Node>tree = io::parseInput("_");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::FunctionCall>("Blank"));
}


BOOST_AUTO_TEST_CASE( parsing_the_pattern_x_blank ) {
	boost::optional<ast::Node>tree = io::parseInput("x_");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::FunctionCall>("Pattern",
			{ast::Node::make<ast::Identifier>("x"),
			ast::Node::make<ast::FunctionCall>("Blank", {})}));
}


BOOST_AUTO_TEST_CASE( parsing_blank_times_x ) {
	boost::optional<ast::Node>tree = io::parseInput("x _");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::FunctionCall>("Blank", {})}));
}


BOOST_AUTO_TEST_CASE( parsing_the_pattern_x_blank_with_colon ) {
	boost::optional<ast::Node>tree = io::parseInput("x:_");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::FunctionCall>("Pattern",
			{ast::Node::make<ast::Identifier>("x"),
			ast::Node::make<ast::FunctionCall>("Blank", {})}));
}

BOOST_AUTO_TEST_CASE( parsing_the_pattern_x_blank_in_function_f ) {
	boost::optional<ast::Node>tree = io::parseInput("f[x_]");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::FunctionCall>("f", \
			{ast::Node::make<ast::FunctionCall>("Pattern", \
			{ast::Node::make<ast::Identifier>("x"), \
			ast::Node::make<ast::FunctionCall>("Blank", {})})}));
}

BOOST_AUTO_TEST_CASE( parsing_the_pattern_x_blank_with_colon_in_function_f ) {
	boost::optional<ast::Node>tree = io::parseInput("f[x:_]");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::FunctionCall>("f", \
			{ast::Node::make<ast::FunctionCall>("Pattern", \
			{ast::Node::make<ast::Identifier>("x"), \
			ast::Node::make<ast::FunctionCall>("Blank", {})})}));
}

BOOST_AUTO_TEST_CASE( parsing_f_applied_to_list_of_x ) {
	boost::optional<ast::Node>tree = io::parseInput("f @@ {x}");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::FunctionCall>("Apply", {
		ast::Node::make<ast::Identifier>("f"),
		ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("x")})
	}));
}

BOOST_AUTO_TEST_CASE( parsing_Apply_with_Plus ) {
	boost::optional<ast::Node>tree = io::parseInput("x+y @@ a+b");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::FunctionCall>("Plus", {
			ast::Node::make<ast::Identifier>("x"),
			ast::Node::make<ast::FunctionCall>("Apply", {
				ast::Node::make<ast::Identifier>("y"),
				ast::Node::make<ast::Identifier>("a")
			}),
			ast::Node::make<ast::Identifier>("b")
	}));
}

BOOST_AUTO_TEST_CASE( parsing_Apply_with_Times ) {
	boost::optional<ast::Node>tree = io::parseInput("x*y @@ a*b");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::FunctionCall>("Times", {
			ast::Node::make<ast::Identifier>("x"),
			ast::Node::make<ast::FunctionCall>("Apply", {
				ast::Node::make<ast::Identifier>("y"),
				ast::Node::make<ast::Identifier>("a")
			}),
			ast::Node::make<ast::Identifier>("b")
	}));
}
BOOST_AUTO_TEST_CASE( parsing_x_factorial ) {
	boost::optional<ast::Node>tree = io::parseInput("x!");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::FunctionCall>("Factorial", {ast::Node::make<ast::Identifier>("x")}));
}


BOOST_AUTO_TEST_CASE( parsing_1_factorial ) {
	boost::optional<ast::Node>tree = io::parseInput("1!");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::FunctionCall>("Factorial", {ast::Node::make<math::Rational>(1)}));
}


BOOST_AUTO_TEST_CASE( parsing_quote_abc_quote_factorial ) {
	boost::optional<ast::Node>tree = io::parseInput("\"abc\"!");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::FunctionCall>("Factorial", {ast::Node::make<ast::String>("abc")}));
}


BOOST_AUTO_TEST_CASE( parsing_x_times_y_factorial ) {
	boost::optional<ast::Node>tree = io::parseInput("x y!");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::FunctionCall>("Factorial", {ast::Node::make<ast::Identifier>("y")})}));
}


BOOST_AUTO_TEST_CASE( parsing_x_plus_y_factorial ) {
	boost::optional<ast::Node>tree = io::parseInput("x + y!");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::FunctionCall>("Plus", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::FunctionCall>("Factorial", {ast::Node::make<ast::Identifier>("y")})}));
}


BOOST_AUTO_TEST_CASE( parsing_x_to_the_power_of_y_factorial ) {
	boost::optional<ast::Node>tree = io::parseInput("x ^ y!");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::FunctionCall>("Factorial", {ast::Node::make<ast::Identifier>("y")})}));
}


BOOST_AUTO_TEST_CASE( parsing_x_double_factorial ) {
	boost::optional<ast::Node>tree = io::parseInput("x!!");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::FunctionCall>("Factorial2", {ast::Node::make<ast::Identifier>("x")}));
}


BOOST_AUTO_TEST_CASE( parsing_x_times_y_double_factorial ) {
	boost::optional<ast::Node>tree = io::parseInput("x y!!");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::FunctionCall>("Factorial2", {ast::Node::make<ast::Identifier>("y")})}));
}


BOOST_AUTO_TEST_CASE( parsing_x_plus_y_double_factorial ) {
	boost::optional<ast::Node>tree = io::parseInput("x + y!!");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::FunctionCall>("Plus", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::FunctionCall>("Factorial2", {ast::Node::make<ast::Identifier>("y")})}));
}


BOOST_AUTO_TEST_CASE( parsing_x_to_the_power_of_y_double_factorial ) {
	boost::optional<ast::Node>tree = io::parseInput("x ^ y!!");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::FunctionCall>("Factorial2", {ast::Node::make<ast::Identifier>("y")})}));
}


BOOST_AUTO_TEST_CASE( parsing_x_double_factorial_factorial ) {
	boost::optional<ast::Node>tree = io::parseInput("x!!!");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::FunctionCall>("Factorial", {ast::Node::make<ast::FunctionCall>("Factorial2", {ast::Node::make<ast::Identifier>("x")})}));
}


BOOST_AUTO_TEST_CASE( parsing_x_factorial_double_factorial ) {
	boost::optional<ast::Node>tree = io::parseInput("(x!)!!");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::FunctionCall>("Factorial2", {ast::Node::make<ast::FunctionCall>("Factorial", {ast::Node::make<ast::Identifier>("x")})}));
}

BOOST_AUTO_TEST_CASE( parsing_y_of_x_postfix_no_paren ) {
	boost::optional<ast::Node>tree = io::parseInput("x//y");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::FunctionCall>("y", {ast::Node::make<ast::Identifier>("x")}));
}


BOOST_AUTO_TEST_CASE( parsing_z_of_y_of_x_postfix ) {
	boost::optional<ast::Node>tree = io::parseInput("x//y//z");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::FunctionCall>("z", {ast::Node::make<ast::FunctionCall>("y", {ast::Node::make<ast::Identifier>("x")})}));
}


BOOST_AUTO_TEST_CASE( parsing_y_of_x_postfix_x_in_paren ) {
	boost::optional<ast::Node>tree = io::parseInput("(x)//y");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::FunctionCall>("y", {ast::Node::make<ast::Identifier>("x")}));
}


BOOST_AUTO_TEST_CASE( parsing_y_of_x_postfix_y_in_paren ) {
	boost::optional<ast::Node>tree = io::parseInput("x//(y)");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::FunctionCall>("y", {ast::Node::make<ast::Identifier>("x")}));
}


BOOST_AUTO_TEST_CASE( parsing_c_of_the_quantity_a_plus_b_postfix ) {
	boost::optional<ast::Node>tree = io::parseInput("a+b//c");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::FunctionCall>("c", {ast::Node::make<ast::FunctionCall>("Plus", {ast::Node::make<ast::Identifier>("a"), ast::Node::make<ast::Identifier>("b")})}));
}


BOOST_AUTO_TEST_CASE( parsing_c_plus_d_of_a_postfix ) {
	boost::optional<ast::Node>tree = io::parseInput("a//c+d");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::FunctionCall>(ast::Node::make<ast::FunctionCall>("Plus", {ast::Node::make<ast::Identifier>("c"), ast::Node::make<ast::Identifier>("d")}), {ast::Node::make<ast::Identifier>("a")}));
}


BOOST_AUTO_TEST_CASE( parsing_c_of_the_quantity_a_times_b_postfix ) {
	boost::optional<ast::Node>tree = io::parseInput("a b//c");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::FunctionCall>("c", {ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("a"), ast::Node::make<ast::Identifier>("b")})}));
}


BOOST_AUTO_TEST_CASE( parsing_c_of_the_quantity_a_to_the_power_of_b_postfix ) {
	boost::optional<ast::Node>tree = io::parseInput("a^b//c");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::FunctionCall>("c", {ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("a"), ast::Node::make<ast::Identifier>("b")})}));
}


BOOST_AUTO_TEST_CASE( parsing_c_to_the_power_of_d_of_a_postfix ) {
	boost::optional<ast::Node>tree = io::parseInput("a//c^d");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::FunctionCall>(ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("c"), ast::Node::make<ast::Identifier>("d")}), {ast::Node::make<ast::Identifier>("a")}));
}


BOOST_AUTO_TEST_CASE( parsing_c_of_a_of_b_postfix ) {
	boost::optional<ast::Node>tree = io::parseInput("a@b//c");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::FunctionCall>("c", {ast::Node::make<ast::FunctionCall>("a", {ast::Node::make<ast::Identifier>("b")})}));
}


BOOST_AUTO_TEST_CASE( parsing_c_of_d_of_a_postfix ) {
	boost::optional<ast::Node>tree = io::parseInput("a//c@d");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::FunctionCall>(ast::Node::make<ast::FunctionCall>("c", {ast::Node::make<ast::Identifier>("d")}), {ast::Node::make<ast::Identifier>("a")}));
}


BOOST_AUTO_TEST_CASE( parsing_hash ) {
	boost::optional<ast::Node>tree = io::parseInput("#");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::FunctionCall>("Slot", {ast::Node::make<math::Rational>(1)}));
}

BOOST_AUTO_TEST_CASE( parsing_hash_1 ) {
	boost::optional<ast::Node>tree = io::parseInput("#1");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::FunctionCall>("Slot", {ast::Node::make<math::Rational>(1)}));
}

BOOST_AUTO_TEST_CASE( parsing_hash_2 ) {
	boost::optional<ast::Node>tree = io::parseInput("#2");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::FunctionCall>("Slot", {ast::Node::make<math::Rational>(2)}));
}


BOOST_AUTO_TEST_CASE( parsing_the_pure_function_hash_1 ) {
	boost::optional<ast::Node>tree = io::parseInput("#1 & ");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::FunctionCall>("Function", {ast::Node::make<ast::FunctionCall>("Slot", {ast::Node::make<math::Rational>(1)})}));
}

BOOST_AUTO_TEST_CASE( parsing_the_pure_function_hash ) {
	boost::optional<ast::Node>tree = io::parseInput("#& ");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::FunctionCall>("Function", {ast::Node::make<ast::FunctionCall>("Slot", {ast::Node::make<math::Rational>(1)})}));
}

BOOST_AUTO_TEST_CASE( parsing_the_pure_function_hash_plus_hash_2 ) {
	boost::optional<ast::Node>tree = io::parseInput("#1 + #2 & ");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::FunctionCall>("Function", {ast::Node::make<ast::FunctionCall>("Plus", {ast::Node::make<ast::FunctionCall>("Slot", {ast::Node::make<math::Rational>(1)}), ast::Node::make<ast::FunctionCall>("Slot", {ast::Node::make<math::Rational>(2)})})}));
}

BOOST_AUTO_TEST_CASE( parsing_Slot_times_1 ) {
	boost::optional<ast::Node>tree = io::parseInput("# 1");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Slot", {ast::Node::make<math::Rational>(1)}), ast::Node::make<math::Rational>(1)}));
}

BOOST_AUTO_TEST_SUITE_END()
