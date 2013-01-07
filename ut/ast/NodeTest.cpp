
#include <boost/test/unit_test.hpp>

#include "ast/Node.hpp"

BOOST_AUTO_TEST_SUITE( NodeTest )

using namespace tungsten;

BOOST_AUTO_TEST_CASE( makeReal_creates_Real ) {
	ast::Node node = ast::Node::makeReal(1.5);

	BOOST_REQUIRE( node.isReal() );
	BOOST_REQUIRE( node.type() == ast::Node::Type::Real );

	BOOST_CHECK_EQUAL( node.getReal(), 1.5 );
}

BOOST_AUTO_TEST_CASE( makeRational_creates_Rational ) {
	ast::Node node = ast::Node::makeRational(1, 3);

	BOOST_REQUIRE( node.isRational() );
	BOOST_REQUIRE( node.type() == ast::Node::Type::Rational );

	BOOST_CHECK_EQUAL( node.getRational(), math::Rational(1,3) );
}

BOOST_AUTO_TEST_CASE( makeFunctionCall_creates_FunctionCall_with_paramters ) {
	ast::Node node = ast::Node::makeFunctionCall( "abc", { ast::Node::makeRational(1, 3), ast::Node::makeRational(2, 3) } );

	BOOST_REQUIRE( node.isFunctionCall() );
	BOOST_REQUIRE( node.type() == ast::Node::Type::FunctionCall );

	BOOST_REQUIRE( node.getFunctionCall().getFunction().isIdentifier() );

	BOOST_CHECK_EQUAL( node.getFunctionCall().getFunction().getIdentifier(), "abc" );

	BOOST_REQUIRE_EQUAL( node.getFunctionCall().getOperands().size(), 2 );

	BOOST_REQUIRE( node.getFunctionCall().getOperands()[0].isRational() );
	BOOST_CHECK_EQUAL( node.getFunctionCall().getOperands()[0].getRational(), math::Rational(1, 3) );

	BOOST_REQUIRE( node.getFunctionCall().getOperands()[1].isRational() );
	BOOST_CHECK_EQUAL( node.getFunctionCall().getOperands()[1].getRational(), math::Rational(2, 3) );

}

BOOST_AUTO_TEST_CASE( makeFunctionCall_creates_FunctionCall_with_non_Identifier_function ) {
	ast::Node node = ast::Node::makeFunctionCall( ast::Node::makeRational(1, 3) );

	BOOST_REQUIRE( node.isFunctionCall() );
	BOOST_REQUIRE( node.type() == ast::Node::Type::FunctionCall );

	BOOST_REQUIRE( node.getFunctionCall().getFunction().isRational() );

	BOOST_CHECK_EQUAL( node.getFunctionCall().getFunction().getRational(), math::Rational(1, 3) );

	BOOST_REQUIRE_EQUAL( node.getFunctionCall().getOperands().size(), 0 );

}

BOOST_AUTO_TEST_CASE( makeString_creates_String ) {
	ast::Node node = ast::Node::makeString( "345" );

	BOOST_REQUIRE( node.isString() );
	BOOST_REQUIRE( node.type() == ast::Node::Type::String );

	BOOST_CHECK_EQUAL( node.getString(), "345" );

}

BOOST_AUTO_TEST_CASE( makeIdentifier_creates_Identifier ) {
	ast::Node node = ast::Node::makeIdentifier( "Pi" );

	BOOST_REQUIRE( node.isIdentifier() );
	BOOST_REQUIRE( node.type() == ast::Node::Type::Identifier );

	BOOST_CHECK_EQUAL( node.getIdentifier(), "Pi" );

}

BOOST_AUTO_TEST_CASE( toString_output_is_correct_for_function ) {
	ast::Node node = ast::Node::makeFunctionCall( "Func", { ast::Node::makeIdentifier("x"), ast::Node::makeIdentifier("y") } );

	BOOST_CHECK_EQUAL(node.toString(), "Func[x, y]");
}

BOOST_AUTO_TEST_CASE( toString_output_is_correct_for_nested_function ) {
	ast::Node node = ast::Node::makeFunctionCall(
			"f", { ast::Node::makeFunctionCall("g", { ast::Node::makeRational(1,5) }), ast::Node::makeIdentifier("y") } );

	BOOST_CHECK_EQUAL(node.toString(), "f[g[1/5], y]");
}

BOOST_AUTO_TEST_CASE( toString_output_is_correct_for_function_with_no_parameters  ) {
	ast::Node node = ast::Node::makeFunctionCall("h");

	BOOST_CHECK_EQUAL(node.toString(), "h[]");
}

BOOST_AUTO_TEST_CASE( toString_output_is_correct_for_string_with_normal_characters ) {
	ast::Node node = ast::Node::makeString("abc d efg");

	BOOST_CHECK_EQUAL(node.toString(), "\"abc d efg\"");
}

BOOST_AUTO_TEST_CASE( toString_output_is_correct_for_string_with_escaped_bell ) {
	ast::Node node = ast::Node::makeString("abc\a");

	BOOST_CHECK_EQUAL(node.toString(), "\"abc\\a\"");
}

BOOST_AUTO_TEST_CASE( toString_output_is_correct_for_string_with_escaped_backspace ) {
	ast::Node node = ast::Node::makeString("abc\b");

	BOOST_CHECK_EQUAL(node.toString(), "\"abc\\b\"");
}

BOOST_AUTO_TEST_CASE( toString_output_is_correct_for_string_with_escaped_formfeed ) {
	ast::Node node = ast::Node::makeString("abc\f");

	BOOST_CHECK_EQUAL(node.toString(), "\"abc\\f\"");
}

BOOST_AUTO_TEST_CASE( toString_output_is_correct_for_string_with_escaped_newline ) {
	ast::Node node = ast::Node::makeString("abc\n");

	BOOST_CHECK_EQUAL(node.toString(), "\"abc\\n\"");
}

BOOST_AUTO_TEST_CASE( toString_output_is_correct_for_string_with_escaped_carrige_return ) {
	ast::Node node = ast::Node::makeString("abc\r");

	BOOST_CHECK_EQUAL(node.toString(), "\"abc\\r\"");
}

BOOST_AUTO_TEST_CASE( toString_output_is_correct_for_string_with_escaped_horizontal_tab ) {
	ast::Node node = ast::Node::makeString("abc\t");

	BOOST_CHECK_EQUAL(node.toString(), "\"abc\\t\"");
}

BOOST_AUTO_TEST_CASE( toString_output_is_correct_for_string_with_escaped_vertical_tab ) {
	ast::Node node = ast::Node::makeString("abc\v");

	BOOST_CHECK_EQUAL(node.toString(), "\"abc\\v\"");
}

BOOST_AUTO_TEST_CASE( toString_output_is_correct_for_string_with_escaped_backslash ) {
	ast::Node node = ast::Node::makeString("abc\\");

	BOOST_CHECK_EQUAL(node.toString(), "\"abc\\\\\"");
}

BOOST_AUTO_TEST_CASE( toString_output_is_correct_for_string_with_escaped_double_quote ) {
	ast::Node node = ast::Node::makeString("abc\"");

	BOOST_CHECK_EQUAL(node.toString(), "\"abc\\\"\"");
}


BOOST_AUTO_TEST_CASE( toString_output_is_correct_for_string_with_escaped_characters ) {
	ast::Node node = ast::Node::makeString("\tc\n \"d");

	BOOST_CHECK_EQUAL(node.toString(), "\"\\tc\\n \\\"d\"");
}


//EQUALITY TESTS

BOOST_AUTO_TEST_CASE( equality_test_real ) {
	BOOST_CHECK_EQUAL(ast::Node::makeReal(5.0), ast::Node::makeReal(5.0));
}

BOOST_AUTO_TEST_CASE( non_equality_test_real ) {
	BOOST_CHECK_NE(ast::Node::makeReal(6.0), ast::Node::makeReal(5.0));
}

BOOST_AUTO_TEST_CASE( equality_test_rational ) {
	BOOST_CHECK_EQUAL(ast::Node::makeRational(1,3), ast::Node::makeRational(1,3));
}

BOOST_AUTO_TEST_CASE( non_equality_test_rational ) {
	BOOST_CHECK_NE(ast::Node::makeRational(1,4), ast::Node::makeRational(1,3));
}

BOOST_AUTO_TEST_CASE( equality_test_function ) {
	BOOST_CHECK_EQUAL(ast::Node::makeFunctionCall("h"), ast::Node::makeFunctionCall("h"));
}

BOOST_AUTO_TEST_CASE( non_equality_test_function ) {
	BOOST_CHECK_NE(ast::Node::makeFunctionCall("g"), ast::Node::makeFunctionCall("f"));
}

BOOST_AUTO_TEST_CASE( equality_test_nested_function ) {
	BOOST_CHECK_EQUAL(
			ast::Node::makeFunctionCall(
					"f", { ast::Node::makeFunctionCall("g", { ast::Node::makeRational(1,5) }), ast::Node::makeIdentifier("y") } ),
			ast::Node::makeFunctionCall(
					"f", { ast::Node::makeFunctionCall("g", { ast::Node::makeRational(1,5) }), ast::Node::makeIdentifier("y") } ));
}

BOOST_AUTO_TEST_CASE( non_equality_test_nested_function ) {
	BOOST_CHECK_NE(
			ast::Node::makeFunctionCall(
					"f", { ast::Node::makeFunctionCall("g", { ast::Node::makeRational(1,5) }), ast::Node::makeIdentifier("y") } ),
			ast::Node::makeFunctionCall(
					"f", { ast::Node::makeFunctionCall("h", { ast::Node::makeRational(1,5) }), ast::Node::makeIdentifier("y") } ));
}

BOOST_AUTO_TEST_CASE( equality_test_non_identifier_function_function_with_no_params ) {
	BOOST_CHECK_EQUAL(
			ast::Node::makeFunctionCall(
					ast::Node::makeFunctionCall( ast::Node::makeRational(1) )
			),
			ast::Node::makeFunctionCall(
					ast::Node::makeFunctionCall( ast::Node::makeRational(1) )
			)
	);
}

BOOST_AUTO_TEST_CASE( non_equality_test_with_different_function_types_in_function ) {
	BOOST_CHECK_NE(
			ast::Node::makeFunctionCall(
					ast::Node::makeFunctionCall( ast::Node::makeReal(1) )
			),
			ast::Node::makeFunctionCall(
					ast::Node::makeFunctionCall( ast::Node::makeRational(1) )
			)
	);
}

BOOST_AUTO_TEST_CASE( equality_test_non_identifier_function_function_with_params ) {
	BOOST_CHECK_EQUAL(
			ast::Node::makeFunctionCall(
					ast::Node::makeFunctionCall( ast::Node::makeRational(1) ), {ast::Node::makeRational(3,2)}
			),
			ast::Node::makeFunctionCall(
					ast::Node::makeFunctionCall( ast::Node::makeRational(1) ), {ast::Node::makeRational(3,2)}
			)
	);
}

BOOST_AUTO_TEST_CASE( equality_test_string ) {
	BOOST_CHECK_EQUAL(ast::Node::makeString( "abc d efg" ), ast::Node::makeString( "abc d efg" ));
}

BOOST_AUTO_TEST_CASE( equality_test_identifier ) {
	BOOST_CHECK_EQUAL(ast::Node::makeIdentifier( "Pi" ), ast::Node::makeIdentifier( "Pi" ));
}

BOOST_AUTO_TEST_CASE( non_equality_test_string_identifier ) {
	BOOST_CHECK_NE(ast::Node::makeIdentifier( "Pi" ), ast::Node::makeString( "Pi" ));
}

BOOST_AUTO_TEST_CASE( non_equality_test_different_function_params ) {
	BOOST_CHECK_NE(ast::Node::makeFunctionCall("h"), ast::Node::makeFunctionCall("h", {ast::Node::makeIdentifier("x")}));
}

BOOST_AUTO_TEST_CASE( non_equality_test_different_function_name ) {
	BOOST_CHECK_NE(ast::Node::makeFunctionCall("h"), ast::Node::makeFunctionCall("g"));
}

BOOST_AUTO_TEST_CASE( non_equality_test_real_Rational ) {
	//They're only equal in mathematical sense
	BOOST_CHECK_NE(ast::Node::makeReal(1), ast::Node::makeRational(1));
}

//ORDERING TESTS
BOOST_AUTO_TEST_CASE( different_Rational_ordering_test ) {
	ast::Node x = ast::Node::makeRational(1);
	ast::Node y = ast::Node::makeRational(2);

	BOOST_CHECK_NE(x, y); //x != y
	BOOST_CHECK_LT(x, y); //x < y
	BOOST_CHECK_LE(x, y); //x <= y
	BOOST_CHECK_GT(y, x); //y > x
	BOOST_CHECK_GE(y, x); //y >= x
}

BOOST_AUTO_TEST_CASE( same_Rational_ordering_test ) {
	ast::Node x = ast::Node::makeRational(1);
	ast::Node y = ast::Node::makeRational(1);

	BOOST_CHECK_EQUAL(x, y); //x != y
	BOOST_CHECK_LE(x, y); //x <= y
	BOOST_CHECK_GE(y, x); //y >= x

	BOOST_CHECK( !(x < y) );
	BOOST_CHECK( !(y < x) );
}

BOOST_AUTO_TEST_CASE( different_Real_ordering_test ) {
	ast::Node x = ast::Node::makeReal(1);
	ast::Node y = ast::Node::makeReal(2);

	BOOST_CHECK_NE(x, y); //x != y
	BOOST_CHECK_LT(x, y); //x < y
	BOOST_CHECK_LE(x, y); //x <= y
	BOOST_CHECK_GT(y, x); //y > x
	BOOST_CHECK_GE(y, x); //y >= x
}

BOOST_AUTO_TEST_CASE( same_Real_ordering_test ) {
	ast::Node x = ast::Node::makeReal(1);
	ast::Node y = ast::Node::makeReal(1);

	BOOST_CHECK_EQUAL(x, y); //x != y
	BOOST_CHECK_LE(x, y); //x <= y
	BOOST_CHECK_GE(x, y); //x >= y
	BOOST_CHECK_LE(y, x); //y <= x
	BOOST_CHECK_GE(y, x); //y >= x

	BOOST_CHECK( !(x < y) );
	BOOST_CHECK( !(y < x) );
}

BOOST_AUTO_TEST_CASE( Rational_and_Real_compares_by_value_test_1 ) {
	ast::Node x = ast::Node::makeReal(1);
	ast::Node y = ast::Node::makeRational(2);

	BOOST_CHECK_NE(x, y); //x != y
	BOOST_CHECK_LT(x, y); //x < y
	BOOST_CHECK_LE(x, y); //x <= y
	BOOST_CHECK_GT(y, x); //y > x
	BOOST_CHECK_GE(y, x); //y >= x
}

BOOST_AUTO_TEST_CASE( Rational_and_Real_compares_by_value_test_2 ) {
	ast::Node x = ast::Node::makeRational(1);
	ast::Node y = ast::Node::makeReal(2);

	BOOST_CHECK_NE(x, y); //x != y
	BOOST_CHECK_LT(x, y); //x < y
	BOOST_CHECK_LE(x, y); //x <= y
	BOOST_CHECK_GT(y, x); //y > x
	BOOST_CHECK_GE(y, x); //y >= x
}

BOOST_AUTO_TEST_CASE( Rational_is_smaller_than_Real_ordering_test ) {
	ast::Node x = ast::Node::makeRational(1);
	ast::Node y = ast::Node::makeReal(1);

	BOOST_CHECK_NE(x, y); //x != y
	BOOST_CHECK_LT(x, y); //x < y
	BOOST_CHECK_LE(x, y); //x <= y
	BOOST_CHECK_GT(y, x); //y > x
	BOOST_CHECK_GE(y, x); //y >= x
}

BOOST_AUTO_TEST_CASE( different_Identifier_ordering_test ) {
	ast::Node a = ast::Node::makeIdentifier( "a" );
	ast::Node b = ast::Node::makeIdentifier( "b" );

	BOOST_CHECK_NE(a, b);
	BOOST_CHECK_LT(a, b);
	BOOST_CHECK_LE(a, b);
	BOOST_CHECK_GT(b, a);
	BOOST_CHECK_GE(b, a);

}

// Phil does not know how to use the TCGenerator.nb :S

BOOST_AUTO_TEST_CASE( same_Function_ordering_test ) {
	ast::Node a1 = ast::Node::makeFunctionCall( "Pow" );
	ast::Node a2 = ast::Node::makeFunctionCall( "Pow" );

	BOOST_CHECK_LE(a1, a2);
	BOOST_CHECK_GE(a1, a2);

	BOOST_CHECK( !(a1 < a2) );
	BOOST_CHECK( !(a2 < a1) );
}
BOOST_AUTO_TEST_CASE( different_Function_ordering_test ) {
	ast::Node a1 = ast::Node::makeFunctionCall( "Pow" );
	ast::Node a2 = ast::Node::makeFunctionCall( "Times" );

	BOOST_CHECK_NE(a1, a2);
	BOOST_CHECK_GE(a1, a2);
	
	BOOST_CHECK( !(a1 < a2) );


}


BOOST_AUTO_TEST_CASE( Strings_compares_lexicographically_a_b ) {
	ast::Node a = ast::Node::makeString( "a" );
	ast::Node b = ast::Node::makeString( "b" );

	BOOST_CHECK_NE(a, b);
	BOOST_CHECK_LT(a, b);
	BOOST_CHECK_LE(a, b);
	BOOST_CHECK_GT(b, a);
	BOOST_CHECK_GE(b, a);
}

BOOST_AUTO_TEST_CASE( empty_String_is_less_than_any_other ) {
	ast::Node e = ast::Node::makeString( "" );
	ast::Node b = ast::Node::makeString( "b" );

	BOOST_CHECK_NE(e, b);
	BOOST_CHECK_LT(e, b);
	BOOST_CHECK_LE(e, b);
	BOOST_CHECK_GT(b, e);
	BOOST_CHECK_GE(b, e);
}

BOOST_AUTO_TEST_CASE( Rational_is_smaller_than_Identifier ) {
	ast::Node r = ast::Node::makeRational( 3, 2 );
	ast::Node i = ast::Node::makeIdentifier( "a" );

	BOOST_CHECK_NE(r, i);
	BOOST_CHECK_LT(r, i);
	BOOST_CHECK_LE(r, i);
	BOOST_CHECK_GT(i, r);
	BOOST_CHECK_GE(i, r);
}

BOOST_AUTO_TEST_CASE( Real_is_smaller_than_Identifier ) {
	ast::Node r = ast::Node::makeReal( 1.5 );
	ast::Node i = ast::Node::makeIdentifier( "a" );

	BOOST_CHECK_NE(r, i);
	BOOST_CHECK_LT(r, i);
	BOOST_CHECK_LE(r, i);
	BOOST_CHECK_GT(i, r);
	BOOST_CHECK_GE(i, r);
}

BOOST_AUTO_TEST_CASE( Rational_is_smaller_than_String ) {
	ast::Node r = ast::Node::makeRational( -3, 2 );
	ast::Node s = ast::Node::makeString( "string" );

	BOOST_CHECK_NE(r, s);
	BOOST_CHECK_LT(r, s);
	BOOST_CHECK_LE(r, s);
	BOOST_CHECK_GT(s, r);
	BOOST_CHECK_GE(s, r);
}

BOOST_AUTO_TEST_CASE( Real_is_smaller_than_String ) {
	ast::Node r = ast::Node::makeReal( -1.5 );
	ast::Node s = ast::Node::makeString( "string" );

	BOOST_CHECK_NE(r, s);
	BOOST_CHECK_LT(r, s);
	BOOST_CHECK_LE(r, s);
	BOOST_CHECK_GT(s, r);
	BOOST_CHECK_GE(s, r);
}


//FunctionCall related comparsions might change in the future
BOOST_AUTO_TEST_CASE( FunctionCalls_ordered_by_their_functions_first ) {
	ast::Node f = ast::Node::makeFunctionCall( "aaa", { ast::Node::makeReal( -1.5 ) } );
	ast::Node g = ast::Node::makeFunctionCall( "bbb", { } );

	BOOST_CHECK_NE(f, g);
	BOOST_CHECK_LT(f, g);
	BOOST_CHECK_LE(f, g);
	BOOST_CHECK_GT(g, f);
	BOOST_CHECK_GE(g, f);
}

BOOST_AUTO_TEST_CASE( FunctionCalls_ordered_by_their_parameters_lexicographically_next ) {
	ast::Node f = ast::Node::makeFunctionCall( "aaa", { ast::Node::makeString( "xxx" ) } );
	ast::Node g = ast::Node::makeFunctionCall( "aaa", { ast::Node::makeString( "yyy" ) } );

	BOOST_CHECK_NE(f, g);
	BOOST_CHECK_LT(f, g);
	BOOST_CHECK_LE(f, g);
	BOOST_CHECK_GT(g, f);
	BOOST_CHECK_GE(g, f);
}

BOOST_AUTO_TEST_SUITE_END()
