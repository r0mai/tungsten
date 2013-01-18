
#include <boost/test/unit_test.hpp>

#include "ast/Parser.hpp"

BOOST_AUTO_TEST_SUITE( AstParserTest )

using namespace tungsten;

BOOST_AUTO_TEST_CASE( empty_input_results_in_Null ) {
	boost::optional<ast::Node> tree = ast::parseInput("");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( *tree, ast::Node::make<ast::Identifier>("Null") );
}

BOOST_AUTO_TEST_CASE( empty_input_with_spaces_results_in_Null ) {
	boost::optional<ast::Node> tree = ast::parseInput(" \t");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( *tree, ast::Node::make<ast::Identifier>("Null") );
}

BOOST_AUTO_TEST_CASE( empty_input_with_newlines_results_in_Null ) {
	boost::optional<ast::Node> tree = ast::parseInput(" \n\n");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( *tree, ast::Node::make<ast::Identifier>("Null") );
}

BOOST_AUTO_TEST_CASE( integer_parsed_correctly ) {
	boost::optional<ast::Node> tree = ast::parseInput("42");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<math::Rational>(42) );
}

BOOST_AUTO_TEST_CASE( huge_integer_parsed_correctly ) {
	boost::optional<ast::Node> tree = ast::parseInput("123456789987654321123456789987654321");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<math::Rational>("123456789987654321123456789987654321") );
}

BOOST_AUTO_TEST_CASE( integer_with_spaces_parsed_correctly ) {
	boost::optional<ast::Node> tree = ast::parseInput(" 42\t");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<math::Rational>(42) );
}

BOOST_AUTO_TEST_CASE( negative_integer_parsed_correctly ) {
	boost::optional<ast::Node> tree = ast::parseInput("-42");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<math::Rational>(-42) );
}

BOOST_AUTO_TEST_CASE( positive_integer_parsed_correctly ) {
	boost::optional<ast::Node> tree = ast::parseInput("+42");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<math::Rational>(42) );
}

BOOST_AUTO_TEST_CASE( real_parsed_correctly ) {
	boost::optional<ast::Node> tree = ast::parseInput("1.5");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<math::Real>(1.5) );
}

BOOST_AUTO_TEST_CASE( huge_real_parsed_correctly ) {
	boost::optional<ast::Node> tree = ast::parseInput("1283618212498721056128561248126489126811.5");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<math::Real>("1283618212498721056128561248126489126811.5") );
}

BOOST_AUTO_TEST_CASE( negative_real_parsed_correctly ) {
	boost::optional<ast::Node> tree = ast::parseInput("-3.5");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<math::Real>(-3.5) );
}

BOOST_AUTO_TEST_CASE( positive_real_parsed_correctly ) {
	boost::optional<ast::Node> tree = ast::parseInput("3.5");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<math::Real>(3.5) );
}

BOOST_AUTO_TEST_CASE( real_with_no_fraction_part_parsed_correctly ) {
	boost::optional<ast::Node> tree = ast::parseInput("3.");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<math::Real>(3.) );
}

BOOST_AUTO_TEST_CASE( real_with_no_integer_part_parsed_correctly ) {
	boost::optional<ast::Node> tree = ast::parseInput(".5");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<math::Real>(.5) );
}

BOOST_AUTO_TEST_CASE( negative_real_with_no_integer_part_parsed_correctly ) {
	boost::optional<ast::Node> tree = ast::parseInput("-.5");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<math::Real>(-.5) );
}

BOOST_AUTO_TEST_CASE( explicit_positive_real_with_no_integer_part_parsed_correctly ) {
	boost::optional<ast::Node> tree = ast::parseInput("+.5");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<math::Real>(.5) );
}

BOOST_AUTO_TEST_CASE( Identifier_parsed_correctly ) {
	boost::optional<ast::Node> tree = ast::parseInput("Pi");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::Identifier>("Pi") );
}

BOOST_AUTO_TEST_CASE( Identifier_with_trailing_numbers_parsed_correctly ) {
	boost::optional<ast::Node> tree = ast::parseInput("X123");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::Identifier>("X123") );
}

BOOST_AUTO_TEST_CASE( Identifier_with_numbers_in_middle_parsed_correctly ) {
	boost::optional<ast::Node> tree = ast::parseInput("X123Y");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::Identifier>("X123Y") );
}

BOOST_AUTO_TEST_CASE( Identifier_parsed_correctly_with_spaces ) {
	boost::optional<ast::Node> tree = ast::parseInput("\tPi ");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::Identifier>("Pi") );
}

BOOST_AUTO_TEST_CASE( Identifier_parsed_correctly_with_starting_dollar_sign ) {
	boost::optional<ast::Node> tree = ast::parseInput("$abc ");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::Identifier>("$abc") );
}

BOOST_AUTO_TEST_CASE( Identifier_parsed_correctly_with_dollarsign ) {
	boost::optional<ast::Node> tree = ast::parseInput("a$bc ");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::Identifier>("a$bc") );
}

BOOST_AUTO_TEST_CASE( String_parsed_correctly ) {
	boost::optional<ast::Node> tree = ast::parseInput("\"abc\"");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::String>("abc") );
}

BOOST_AUTO_TEST_CASE( String_parsed_correctly_with_spaces_inside ) {
	boost::optional<ast::Node> tree = ast::parseInput("\"a b  c\"");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::String>("a b  c") );
}

BOOST_AUTO_TEST_CASE( String_parsed_correctly_with_spaces_outside ) {
	boost::optional<ast::Node> tree = ast::parseInput("  \"a b c\" ");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::String>("a b c") );
}

BOOST_AUTO_TEST_CASE( String_parsed_correctly_with_escaped_new_line ) {
	boost::optional<ast::Node> tree = ast::parseInput("\"a\\nb\"");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::String>("a\nb") );
}

BOOST_AUTO_TEST_CASE( String_parsed_correctly_with_escaped_carrige_return ) {
	boost::optional<ast::Node> tree = ast::parseInput("\"a\\rb\"");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::String>("a\rb") );
}

BOOST_AUTO_TEST_CASE( String_parsed_correctly_with_escaped_bell ) {
	boost::optional<ast::Node> tree = ast::parseInput("\"a\\ac\"");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::String>("a\ac") );
}

BOOST_AUTO_TEST_CASE( String_parsed_correctly_with_escaped_backspace ) {
	boost::optional<ast::Node> tree = ast::parseInput("\"a\\bc\"");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::String>("a\bc") );
}

BOOST_AUTO_TEST_CASE( String_parsed_correctly_with_escaped_formfeed ) {
	boost::optional<ast::Node> tree = ast::parseInput("\"a\\fc\"");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::String>("a\fc") );
}

BOOST_AUTO_TEST_CASE( String_parsed_correctly_with_escaped_horizontal_tab ) {
	boost::optional<ast::Node> tree = ast::parseInput("\"a\\tc\"");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::String>("a\tc") );
}

BOOST_AUTO_TEST_CASE( String_parsed_correctly_with_escaped_vertical_tab ) {
	boost::optional<ast::Node> tree = ast::parseInput("\"a\\vc\"");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::String>("a\vc") );
}

BOOST_AUTO_TEST_CASE( String_parsed_correctly_with_escaped_quotation_mark ) {
	boost::optional<ast::Node> tree = ast::parseInput("\"a\\\"b\"");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::String>("a\"b") );
}

BOOST_AUTO_TEST_CASE( String_parsed_correctly_with_escaped_back_slash ) {
	boost::optional<ast::Node> tree = ast::parseInput("\"a\\\\b\"");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::String>("a\\b") );
}

BOOST_AUTO_TEST_CASE( String_parsed_correctly_with_escaped_tabulator ) {
	boost::optional<ast::Node> tree = ast::parseInput("\"a\\tb\"");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::String>("a\tb") );
}

BOOST_AUTO_TEST_CASE( String_parsed_correctly_with_multiple_escaped_characters ) {
	boost::optional<ast::Node> tree = ast::parseInput("\"\\\"\\n\\\\\"");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::String>("\"\n\\") );
}

BOOST_AUTO_TEST_CASE( function_without_parameters_parsed_correctly ) {
	boost::optional<ast::Node> tree = ast::parseInput("foo[]");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::FunctionCall>("foo") );
}

BOOST_AUTO_TEST_CASE( function_without_parameters_with_spaces_parsed_correctly ) {
	boost::optional<ast::Node> tree = ast::parseInput("\tfoo\t[ ] ");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::FunctionCall>("foo") );
}

BOOST_AUTO_TEST_CASE( function_with_single_parameter_parsed_correctly ) {
	boost::optional<ast::Node> tree = ast::parseInput("foo[1]");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::FunctionCall>("foo", {ast::Node::make<math::Rational>(1)}) );
}

BOOST_AUTO_TEST_CASE( function_with_single_parameter_with_spaces_parsed_correctly ) {
	boost::optional<ast::Node> tree = ast::parseInput("  foo [1 ] ");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::FunctionCall>("foo", {ast::Node::make<math::Rational>(1)}) );
}

BOOST_AUTO_TEST_CASE( function_with_multiple_parameter_parsed_correctly ) {
	boost::optional<ast::Node> tree = ast::parseInput("foo[1,2,3]");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::FunctionCall>("foo",
			{ast::Node::make<math::Rational>(1),
			ast::Node::make<math::Rational>(2),
			ast::Node::make<math::Rational>(3)}) );
}

BOOST_AUTO_TEST_CASE( function_with_multiple_parameter_with_spaces_parsed_correctly ) {
	boost::optional<ast::Node> tree = ast::parseInput("  foo [1 ,2,3 ] ");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::FunctionCall>("foo",
			{ast::Node::make<math::Rational>(1),
			ast::Node::make<math::Rational>(2),
			ast::Node::make<math::Rational>(3)}) );
}

BOOST_AUTO_TEST_CASE( nested_function_parsed_correctly_1 ) {
	boost::optional<ast::Node> tree = ast::parseInput("f[g[]]");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::FunctionCall>("f", {ast::Node::make<ast::FunctionCall>("g")}) );

}

BOOST_AUTO_TEST_CASE( nested_function_parsed_correctly_2 ) {
	boost::optional<ast::Node> tree = ast::parseInput("f[g[], h[1]]");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::FunctionCall>("f", {
					ast::Node::make<ast::FunctionCall>("g"),
					ast::Node::make<ast::FunctionCall>("h", {
							ast::Node::make<math::Rational>(1)
					})
	}) );

}

BOOST_AUTO_TEST_CASE( non_identifier_function_parsed_correctly_1 ) {
	boost::optional<ast::Node> tree = ast::parseInput(" 2 []\t");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::FunctionCall>(
			ast::Node::make<math::Rational>(2) ) );
}

BOOST_AUTO_TEST_CASE( non_identifier_function_parsed_correctly_2 ) {
	boost::optional<ast::Node> tree = ast::parseInput("f[ ]\t[]");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(),
			ast::Node::make<ast::FunctionCall>(
					ast::Node::make<ast::FunctionCall>("f")
			)
	);
}

BOOST_AUTO_TEST_CASE( identifier_function_parsed_correctly_with_parentheses ) {
	boost::optional<ast::Node> tree = ast::parseInput("( f) []");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(),
			ast::Node::make<ast::FunctionCall>(
					ast::Node::make<ast::FunctionCall>("f")
			)
	);
}

BOOST_AUTO_TEST_CASE( empty_brackets_not_parsed ) {
	boost::optional<ast::Node> tree = ast::parseInput("[]");

	BOOST_CHECK( !tree );
}

BOOST_AUTO_TEST_CASE( unary_minus_parsed_correctly_with_Identifier ) {
	boost::optional<ast::Node> tree = ast::parseInput("-a");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<math::Rational>(-1), ast::Node::make<ast::Identifier>("a")}) );
}

BOOST_AUTO_TEST_CASE( unary_plus_parsed_correctly_with_Identifier ) {
	boost::optional<ast::Node> tree = ast::parseInput("+a");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::Identifier>("a") );
}

BOOST_AUTO_TEST_CASE( unary_minus_parsed_correctly_with_Identifier_in_parentheses ) {
	boost::optional<ast::Node> tree = ast::parseInput("-(a)");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<math::Rational>(-1), ast::Node::make<ast::Identifier>("a")}) );
}

BOOST_AUTO_TEST_CASE( unary_plus_parsed_correctly_with_Identifier_in_parentheses ) {
	boost::optional<ast::Node> tree = ast::parseInput("+(a)");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::Identifier>("a") );
}

BOOST_AUTO_TEST_CASE( two_unary_minuses_parsed_correctly_with_Identifier ) {
	boost::optional<ast::Node> tree = ast::parseInput("- -a"); //--a is predecrement

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<math::Rational>(-1),
			ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<math::Rational>(-1), ast::Node::make<ast::Identifier>("a")}) } ) );
}

BOOST_AUTO_TEST_CASE( two_unary_pluses_parsed_correctly_with_Identifier ) {
	boost::optional<ast::Node> tree = ast::parseInput("+ +a"); //++a is preincrement

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::Identifier>("a") );
}

BOOST_AUTO_TEST_CASE( two_unary_minuses_parsed_correctly_with_Integer ) {
	boost::optional<ast::Node> tree = ast::parseInput("- -3");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<math::Rational>(-1), ast::Node::make<math::Rational>(-3)}) );
}

BOOST_AUTO_TEST_CASE( two_unary_minuses_parsed_correctly_with_Real ) {
	boost::optional<ast::Node> tree = ast::parseInput("- -3.2");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<math::Rational>(-1), ast::Node::make<math::Real>(-3.2)}) );
}

BOOST_AUTO_TEST_CASE( unary_minus_has_lower_precedence_than_Plus ) {
	boost::optional<ast::Node> tree = ast::parseInput("-a+b");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(),
			ast::Node::make<ast::FunctionCall>("Plus", {
					ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<math::Rational>(-1), ast::Node::make<ast::Identifier>("a")}),
					ast::Node::make<ast::Identifier>("b")
			}) );
}

BOOST_AUTO_TEST_CASE( unary_minus_has_lower_precedence_than_Times ) {
	boost::optional<ast::Node> tree = ast::parseInput("-a*b");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(),
			ast::Node::make<ast::FunctionCall>("Times", {
					ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<math::Rational>(-1), ast::Node::make<ast::Identifier>("a")}),
					ast::Node::make<ast::Identifier>("b")
			}) );
}

BOOST_AUTO_TEST_CASE( unary_minus_has_higher_precedence_than_Power ) {
	boost::optional<ast::Node> tree = ast::parseInput("-a^b");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(),
			ast::Node::make<ast::FunctionCall>("Times", {
					ast::Node::make<math::Rational>(-1),
					ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("a"), ast::Node::make<ast::Identifier>("b")})
			}) );
}

BOOST_AUTO_TEST_CASE( addition_parsed_correctly_with_2_arguments ) {
	boost::optional<ast::Node> tree = ast::parseInput("a+b");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::FunctionCall>("Plus", {ast::Node::make<ast::Identifier>("a"), ast::Node::make<ast::Identifier>("b")}) );
}

BOOST_AUTO_TEST_CASE( addition_parsed_correctly_with_2_arguments_with_spaces ) {
	boost::optional<ast::Node> tree = ast::parseInput("a +  b ");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::FunctionCall>("Plus", {ast::Node::make<ast::Identifier>("a"), ast::Node::make<ast::Identifier>("b")}) );
}

BOOST_AUTO_TEST_CASE( addition_parsed_correctly_with_3_arguments ) {
	boost::optional<ast::Node> tree = ast::parseInput("a+b+c");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::FunctionCall>("Plus", {ast::Node::make<ast::Identifier>("a"), ast::Node::make<ast::Identifier>("b"), ast::Node::make<ast::Identifier>("c")}) );
}

BOOST_AUTO_TEST_CASE( addition_parsed_correctly_with_3_arguments_with_spaces ) {
	boost::optional<ast::Node> tree = ast::parseInput(" \ta \t+ b + c ");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::FunctionCall>("Plus", {ast::Node::make<ast::Identifier>("a"), ast::Node::make<ast::Identifier>("b"), ast::Node::make<ast::Identifier>("c")}) );
}

BOOST_AUTO_TEST_CASE( binary_Minus_Parentheses_parsed_correctly ) {
	boost::optional<ast::Node> tree = ast::parseInput("a-(b)");

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
	boost::optional<ast::Node> tree = ast::parseInput("a/(b)");

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
	boost::optional<ast::Node> tree = ast::parseInput("a*b");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("a"), ast::Node::make<ast::Identifier>("b")}) );
}

BOOST_AUTO_TEST_CASE( multiplication_parsed_correctly_with_2_arguments_with_spaces ) {
	boost::optional<ast::Node> tree = ast::parseInput("a *  b ");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("a"), ast::Node::make<ast::Identifier>("b")}) );
}

BOOST_AUTO_TEST_CASE( multiplication_parsed_correctly_with_3_arguments ) {
	boost::optional<ast::Node> tree = ast::parseInput("a*b*c");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("a"), ast::Node::make<ast::Identifier>("b"), ast::Node::make<ast::Identifier>("c")}) );
}

BOOST_AUTO_TEST_CASE( multiplication_parsed_correctly_with_3_arguments_with_spaces ) {
	boost::optional<ast::Node> tree = ast::parseInput(" \ta \t* b * c ");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("a"), ast::Node::make<ast::Identifier>("b"), ast::Node::make<ast::Identifier>("c")}) );
}

BOOST_AUTO_TEST_CASE( juxtaposition_works_for_two_identifiers ) {
	boost::optional<ast::Node> tree = ast::parseInput("a b");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("a"), ast::Node::make<ast::Identifier>("b")}) );
}

BOOST_AUTO_TEST_CASE( juxtaposition_works_for_two_integers ) {
	boost::optional<ast::Node> tree = ast::parseInput("10 2");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<math::Rational>(10), ast::Node::make<math::Rational>(2)}) );
}

BOOST_AUTO_TEST_CASE( juxtaposition_works_for_two_reals_1 ) {
	boost::optional<ast::Node> tree = ast::parseInput("10.0 2.5");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<math::Real>(10.0), ast::Node::make<math::Real>(2.5)}) );
}

BOOST_AUTO_TEST_CASE( juxtaposition_works_for_two_reals_2 ) {
	boost::optional<ast::Node> tree = ast::parseInput("10. .5");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<math::Real>(10.0), ast::Node::make<math::Real>(0.5)}) );
}

BOOST_AUTO_TEST_CASE( juxtaposition_works_for_two_reals_3 ) {
	boost::optional<ast::Node> tree = ast::parseInput(".5 2.");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<math::Real>(.5), ast::Node::make<math::Real>(2.)}) );
}

BOOST_AUTO_TEST_CASE( juxtaposition_works_between_integer_and_identifier ) {
	boost::optional<ast::Node> tree = ast::parseInput("3Pi");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<math::Rational>(3), ast::Node::make<ast::Identifier>("Pi")}) );
}

BOOST_AUTO_TEST_CASE( juxtaposition_works_between_real_and_identifier_1 ) {
	boost::optional<ast::Node> tree = ast::parseInput("3.5Pi");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<math::Real>(3.5), ast::Node::make<ast::Identifier>("Pi")}) );
}

BOOST_AUTO_TEST_CASE( juxtaposition_works_between_real_and_identifier_2 ) {
	boost::optional<ast::Node> tree = ast::parseInput("3.Pi");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<math::Real>(3.), ast::Node::make<ast::Identifier>("Pi")}) );
}

BOOST_AUTO_TEST_CASE( juxtaposition_works_with_integer_and_paranthesis ) {
	boost::optional<ast::Node> tree = ast::parseInput("3(4)");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<math::Rational>(3), ast::Node::make<math::Rational>(4)}) );
}

BOOST_AUTO_TEST_CASE( juxtaposition_works_between_two_paranthesis ) {
	boost::optional<ast::Node> tree = ast::parseInput("(x)(y)");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::Identifier>("y")}) );
}

BOOST_AUTO_TEST_CASE( exponentation_parsed_correctly_with_2_arguments ) {
	boost::optional<ast::Node> tree = ast::parseInput("a^b");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("a"), ast::Node::make<ast::Identifier>("b")}) );
}

BOOST_AUTO_TEST_CASE( right_to_left_associativity_works_with_exponentation ) {
	boost::optional<ast::Node> tree = ast::parseInput("a^b^c");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("a"), ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("b"), ast::Node::make<ast::Identifier>("c")})}) );
}

BOOST_AUTO_TEST_CASE( parentheses_around_the_whole_expression_makes_no_difference ) {
	boost::optional<ast::Node> tree = ast::parseInput("(a)");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::Identifier>("a") );
}

BOOST_AUTO_TEST_CASE( plus_has_higher_precedence_than_multiplication_1 ) {
	boost::optional<ast::Node> tree = ast::parseInput("a + b * c");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::FunctionCall>("Plus", {ast::Node::make<ast::Identifier>("a"), ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("b"), ast::Node::make<ast::Identifier>("c")})}) );
}

BOOST_AUTO_TEST_CASE( plus_has_higher_precedence_than_multiplication_2 ) {
	boost::optional<ast::Node> tree = ast::parseInput("a * b + c");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::FunctionCall>("Plus", {ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::Identifier>("a"), ast::Node::make<ast::Identifier>("b")}), ast::Node::make<ast::Identifier>("c")}) );
}

BOOST_AUTO_TEST_CASE( parenthesis_modifies_precedence_with_Plus_and_Times ) {
	boost::optional<ast::Node> tree = ast::parseInput("(a + b) * c");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<ast::FunctionCall>("Plus", {ast::Node::make<ast::Identifier>("a"), ast::Node::make<ast::Identifier>("b")}), ast::Node::make<ast::Identifier>("c")}) );
}

BOOST_AUTO_TEST_CASE( empty_List_parsed_correctly ) {
	boost::optional<ast::Node> tree = ast::parseInput("{}");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::FunctionCall>("List") );
}

BOOST_AUTO_TEST_CASE( one_argument_List_parsed_correctly ) {
	boost::optional<ast::Node> tree = ast::parseInput("{x}");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("x")}) );
}

BOOST_AUTO_TEST_CASE( two_argument_List_parsed_correctly ) {
	boost::optional<ast::Node> tree = ast::parseInput("{x, y}");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::Identifier>("y")}) );
}

BOOST_AUTO_TEST_CASE( Lists_can_take_part_in_expressions ) {
	boost::optional<ast::Node> tree = ast::parseInput("{x} + {}");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::FunctionCall>("Plus",
			{ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("x")}),
			ast::Node::make<ast::FunctionCall>("List")}) );
}

BOOST_AUTO_TEST_CASE( Infinity_parsed_as_Identifier ) {
	boost::optional<ast::Node> tree = ast::parseInput("Infinity");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::Identifier>("Infinity") );
}

BOOST_AUTO_TEST_CASE( Inf_parsed_as_Identifier ) {
	boost::optional<ast::Node> tree = ast::parseInput("Inf");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::Identifier>("Inf") );
}

BOOST_AUTO_TEST_CASE( nan_parsed_as_Identifier ) {
	boost::optional<ast::Node> tree = ast::parseInput("nan");

	BOOST_REQUIRE( tree );

	BOOST_CHECK_EQUAL( tree.get(), ast::Node::make<ast::Identifier>("nan") );
}

BOOST_AUTO_TEST_SUITE_END()
