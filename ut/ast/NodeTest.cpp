
#include <boost/test/unit_test.hpp>

#include "ast/Node.hpp"

BOOST_AUTO_TEST_SUITE( NodeTest )

using namespace tungsten;

BOOST_AUTO_TEST_CASE( makeReal_creates_Real ) {
	ast::Node node = ast::Node::make<math::Real>(1.5);

	BOOST_REQUIRE( node.is<math::Real>() );
	BOOST_REQUIRE( node.is<math::Real>() );

	BOOST_CHECK_EQUAL( node.get<math::Real>(), 1.5 );
}

BOOST_AUTO_TEST_CASE( makeRational_creates_Rational ) {
	ast::Node node = ast::Node::make<math::Rational>(1, 3);

	BOOST_REQUIRE( node.is<math::Rational>() );
	BOOST_REQUIRE( node.is<math::Rational>() );

	BOOST_CHECK_EQUAL( node.get<math::Rational>(), math::Rational(1,3) );
}

BOOST_AUTO_TEST_CASE( makeFunctionCall_creates_FunctionCall_with_paramters ) {
	ast::Node node = ast::Node::make<ast::FunctionCall>( "abc", { ast::Node::make<math::Rational>(1, 3), ast::Node::make<math::Rational>(2, 3) } );

	BOOST_REQUIRE( node.is<ast::FunctionCall>() );
	BOOST_REQUIRE( node.is<ast::FunctionCall>() );

	BOOST_REQUIRE( node.get<ast::FunctionCall>().getFunction().is<ast::Identifier>() );
	BOOST_REQUIRE( node.get<ast::FunctionCall>().getFunction().is<ast::Identifier>() );

	BOOST_CHECK_EQUAL( node.get<ast::FunctionCall>().getFunction().get<ast::Identifier>(), "abc" );
	BOOST_CHECK_EQUAL( node.get<ast::FunctionCall>().getFunction().get<ast::Identifier>(), "abc" );

	BOOST_REQUIRE_EQUAL( node.get<ast::FunctionCall>().getOperands().size(), 2 );

	BOOST_REQUIRE( node.get<ast::FunctionCall>().getOperands()[0].is<math::Rational>() );
	BOOST_CHECK_EQUAL( node.get<ast::FunctionCall>().getOperands()[0].get<math::Rational>(), math::Rational(1, 3) );

	BOOST_REQUIRE( node.get<ast::FunctionCall>().getOperands()[1].is<math::Rational>() );
	BOOST_CHECK_EQUAL( node.get<ast::FunctionCall>().getOperands()[1].get<math::Rational>(), math::Rational(2, 3) );

}

BOOST_AUTO_TEST_CASE( makeFunctionCall_creates_FunctionCall_with_non_Identifier_function ) {
	ast::Node node = ast::Node::make<ast::FunctionCall>( ast::Node::make<math::Rational>(1, 3) );

	BOOST_REQUIRE( node.is<ast::FunctionCall>() );

	BOOST_REQUIRE( node.get<ast::FunctionCall>().getFunction().is<math::Rational>() );

	BOOST_CHECK_EQUAL( node.get<ast::FunctionCall>().getFunction().get<math::Rational>(), math::Rational(1, 3) );

	BOOST_REQUIRE_EQUAL( node.get<ast::FunctionCall>().getOperands().size(), 0 );

}

BOOST_AUTO_TEST_CASE( makeString_creates_String ) {
	ast::Node node = ast::Node::make<ast::String>( "345" );

	BOOST_REQUIRE( node.is<ast::String>() );

	BOOST_CHECK_EQUAL( node.get<ast::String>(), "345" );

}

BOOST_AUTO_TEST_CASE( makeIdentifier_creates_Identifier ) {
	ast::Node node = ast::Node::make<ast::Identifier>( "Pi" );

	BOOST_REQUIRE( node.is<ast::Identifier>() );

	BOOST_CHECK_EQUAL( node.get<ast::Identifier>(), "Pi" );

}

BOOST_AUTO_TEST_CASE( toString_output_is_correct_for_function ) {
	ast::Node node = ast::Node::make<ast::FunctionCall>( "Func", { ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::Identifier>("y") } );

	BOOST_CHECK_EQUAL(node.toString(), "Func[x, y]");
}

BOOST_AUTO_TEST_CASE( toString_output_is_correct_for_nested_function ) {
	ast::Node node = ast::Node::make<ast::FunctionCall>(
			"f", { ast::Node::make<ast::FunctionCall>("g", { ast::Node::make<math::Rational>(1,5) }), ast::Node::make<ast::Identifier>("y") } );

	BOOST_CHECK_EQUAL(node.toString(), "f[g[1/5], y]");
}

BOOST_AUTO_TEST_CASE( toString_output_is_correct_for_function_with_no_parameters  ) {
	ast::Node node = ast::Node::make<ast::FunctionCall>("h");

	BOOST_CHECK_EQUAL(node.toString(), "h[]");
}

BOOST_AUTO_TEST_CASE( toString_output_is_correct_for_string_with_normal_characters ) {
	ast::Node node = ast::Node::make<ast::String>("abc d efg");

	BOOST_CHECK_EQUAL(node.toString(), "\"abc d efg\"");
}

BOOST_AUTO_TEST_CASE( toString_output_is_correct_for_string_with_escaped_bell ) {
	ast::Node node = ast::Node::make<ast::String>("abc\a");

	BOOST_CHECK_EQUAL(node.toString(), "\"abc\\a\"");
}

BOOST_AUTO_TEST_CASE( toString_output_is_correct_for_string_with_escaped_backspace ) {
	ast::Node node = ast::Node::make<ast::String>("abc\b");

	BOOST_CHECK_EQUAL(node.toString(), "\"abc\\b\"");
}

BOOST_AUTO_TEST_CASE( toString_output_is_correct_for_string_with_escaped_formfeed ) {
	ast::Node node = ast::Node::make<ast::String>("abc\f");

	BOOST_CHECK_EQUAL(node.toString(), "\"abc\\f\"");
}

BOOST_AUTO_TEST_CASE( toString_output_is_correct_for_string_with_escaped_newline ) {
	ast::Node node = ast::Node::make<ast::String>("abc\n");

	BOOST_CHECK_EQUAL(node.toString(), "\"abc\\n\"");
}

BOOST_AUTO_TEST_CASE( toString_output_is_correct_for_string_with_escaped_carrige_return ) {
	ast::Node node = ast::Node::make<ast::String>("abc\r");

	BOOST_CHECK_EQUAL(node.toString(), "\"abc\\r\"");
}

BOOST_AUTO_TEST_CASE( toString_output_is_correct_for_string_with_escaped_horizontal_tab ) {
	ast::Node node = ast::Node::make<ast::String>("abc\t");

	BOOST_CHECK_EQUAL(node.toString(), "\"abc\\t\"");
}

BOOST_AUTO_TEST_CASE( toString_output_is_correct_for_string_with_escaped_vertical_tab ) {
	ast::Node node = ast::Node::make<ast::String>("abc\v");

	BOOST_CHECK_EQUAL(node.toString(), "\"abc\\v\"");
}

BOOST_AUTO_TEST_CASE( toString_output_is_correct_for_string_with_escaped_backslash ) {
	ast::Node node = ast::Node::make<ast::String>("abc\\");

	BOOST_CHECK_EQUAL(node.toString(), "\"abc\\\\\"");
}

BOOST_AUTO_TEST_CASE( toString_output_is_correct_for_string_with_escaped_double_quote ) {
	ast::Node node = ast::Node::make<ast::String>("abc\"");

	BOOST_CHECK_EQUAL(node.toString(), "\"abc\\\"\"");
}


BOOST_AUTO_TEST_CASE( toString_output_is_correct_for_string_with_escaped_characters ) {
	ast::Node node = ast::Node::make<ast::String>("\tc\n \"d");

	BOOST_CHECK_EQUAL(node.toString(), "\"\\tc\\n \\\"d\"");
}


//EQUALITY TESTS

BOOST_AUTO_TEST_CASE( equality_test_real ) {
	BOOST_CHECK_EQUAL(ast::Node::make<math::Real>(5.0), ast::Node::make<math::Real>(5.0));
}

BOOST_AUTO_TEST_CASE( non_equality_test_real ) {
	BOOST_CHECK_NE(ast::Node::make<math::Real>(6.0), ast::Node::make<math::Real>(5.0));
}

BOOST_AUTO_TEST_CASE( equality_test_rational ) {
	BOOST_CHECK_EQUAL(ast::Node::make<math::Rational>(1,3), ast::Node::make<math::Rational>(1,3));
}

BOOST_AUTO_TEST_CASE( non_equality_test_rational ) {
	BOOST_CHECK_NE(ast::Node::make<math::Rational>(1,4), ast::Node::make<math::Rational>(1,3));
}

BOOST_AUTO_TEST_CASE( equality_test_function ) {
	BOOST_CHECK_EQUAL(ast::Node::make<ast::FunctionCall>("h"), ast::Node::make<ast::FunctionCall>("h"));
}

BOOST_AUTO_TEST_CASE( non_equality_test_function ) {
	BOOST_CHECK_NE(ast::Node::make<ast::FunctionCall>("g"), ast::Node::make<ast::FunctionCall>("f"));
}

BOOST_AUTO_TEST_CASE( equality_test_nested_function ) {
	BOOST_CHECK_EQUAL(
			ast::Node::make<ast::FunctionCall>(
					"f", { ast::Node::make<ast::FunctionCall>("g", { ast::Node::make<math::Rational>(1,5) }), ast::Node::make<ast::Identifier>("y") } ),
			ast::Node::make<ast::FunctionCall>(
					"f", { ast::Node::make<ast::FunctionCall>("g", { ast::Node::make<math::Rational>(1,5) }), ast::Node::make<ast::Identifier>("y") } ));
}

BOOST_AUTO_TEST_CASE( non_equality_test_nested_function ) {
	BOOST_CHECK_NE(
			ast::Node::make<ast::FunctionCall>(
					"f", { ast::Node::make<ast::FunctionCall>("g", { ast::Node::make<math::Rational>(1,5) }), ast::Node::make<ast::Identifier>("y") } ),
			ast::Node::make<ast::FunctionCall>(
					"f", { ast::Node::make<ast::FunctionCall>("h", { ast::Node::make<math::Rational>(1,5) }), ast::Node::make<ast::Identifier>("y") } ));
}

BOOST_AUTO_TEST_CASE( equality_test_non_identifier_function_function_with_no_params ) {
	BOOST_CHECK_EQUAL(
			ast::Node::make<ast::FunctionCall>(
					ast::Node::make<ast::FunctionCall>( ast::Node::make<math::Rational>(1) )
			),
			ast::Node::make<ast::FunctionCall>(
					ast::Node::make<ast::FunctionCall>( ast::Node::make<math::Rational>(1) )
			)
	);
}

BOOST_AUTO_TEST_CASE( non_equality_test_with_different_function_types_in_function ) {
	BOOST_CHECK_NE(
			ast::Node::make<ast::FunctionCall>(
					ast::Node::make<ast::FunctionCall>( ast::Node::make<math::Real>(1) )
			),
			ast::Node::make<ast::FunctionCall>(
					ast::Node::make<ast::FunctionCall>( ast::Node::make<math::Rational>(1) )
			)
	);
}

BOOST_AUTO_TEST_CASE( equality_test_non_identifier_function_function_with_params ) {
	BOOST_CHECK_EQUAL(
			ast::Node::make<ast::FunctionCall>(
					ast::Node::make<ast::FunctionCall>( ast::Node::make<math::Rational>(1) ), {ast::Node::make<math::Rational>(3,2)}
			),
			ast::Node::make<ast::FunctionCall>(
					ast::Node::make<ast::FunctionCall>( ast::Node::make<math::Rational>(1) ), {ast::Node::make<math::Rational>(3,2)}
			)
	);
}

BOOST_AUTO_TEST_CASE( equality_test_string ) {
	BOOST_CHECK_EQUAL(ast::Node::make<ast::String>( "abc d efg" ), ast::Node::make<ast::String>( "abc d efg" ));
}

BOOST_AUTO_TEST_CASE( equality_test_identifier ) {
	BOOST_CHECK_EQUAL(ast::Node::make<ast::Identifier>( "Pi" ), ast::Node::make<ast::Identifier>( "Pi" ));
}

BOOST_AUTO_TEST_CASE( non_equality_test_string_identifier ) {
	BOOST_CHECK_NE(ast::Node::make<ast::Identifier>( "Pi" ), ast::Node::make<ast::String>( "Pi" ));
}

BOOST_AUTO_TEST_CASE( non_equality_test_different_function_params ) {
	BOOST_CHECK_NE(ast::Node::make<ast::FunctionCall>("h"), ast::Node::make<ast::FunctionCall>("h", {ast::Node::make<ast::Identifier>("x")}));
}

BOOST_AUTO_TEST_CASE( non_equality_test_different_function_name ) {
	BOOST_CHECK_NE(ast::Node::make<ast::FunctionCall>("h"), ast::Node::make<ast::FunctionCall>("g"));
}

BOOST_AUTO_TEST_CASE( non_equality_test_real_Rational ) {
	//They're only equal in mathematical sense
	BOOST_CHECK_NE(ast::Node::make<math::Real>(1), ast::Node::make<math::Rational>(1));
}

//ORDERING TESTS
BOOST_AUTO_TEST_CASE( different_Rational_ordering_test ) {
	ast::Node x = ast::Node::make<math::Rational>(1);
	ast::Node y = ast::Node::make<math::Rational>(2);

	BOOST_CHECK_NE(x, y); //x != y
	BOOST_CHECK_LT(x, y); //x < y
	BOOST_CHECK_LE(x, y); //x <= y
	BOOST_CHECK_GT(y, x); //y > x
	BOOST_CHECK_GE(y, x); //y >= x
}

BOOST_AUTO_TEST_CASE( same_Rational_ordering_test ) {
	ast::Node x = ast::Node::make<math::Rational>(1);
	ast::Node y = ast::Node::make<math::Rational>(1);

	BOOST_CHECK_EQUAL(x, y); //x != y
	BOOST_CHECK_LE(x, y); //x <= y
	BOOST_CHECK_GE(y, x); //y >= x

	BOOST_CHECK( !(x < y) );
	BOOST_CHECK( !(y < x) );
}

BOOST_AUTO_TEST_CASE( different_Real_ordering_test ) {
	ast::Node x = ast::Node::make<math::Real>(1);
	ast::Node y = ast::Node::make<math::Real>(2);

	BOOST_CHECK_NE(x, y); //x != y
	BOOST_CHECK_LT(x, y); //x < y
	BOOST_CHECK_LE(x, y); //x <= y
	BOOST_CHECK_GT(y, x); //y > x
	BOOST_CHECK_GE(y, x); //y >= x
}

BOOST_AUTO_TEST_CASE( same_Real_ordering_test ) {
	ast::Node x = ast::Node::make<math::Real>(1);
	ast::Node y = ast::Node::make<math::Real>(1);

	BOOST_CHECK_EQUAL(x, y); //x != y
	BOOST_CHECK_LE(x, y); //x <= y
	BOOST_CHECK_GE(x, y); //x >= y
	BOOST_CHECK_LE(y, x); //y <= x
	BOOST_CHECK_GE(y, x); //y >= x

	BOOST_CHECK( !(x < y) );
	BOOST_CHECK( !(y < x) );
}

BOOST_AUTO_TEST_CASE( Rational_and_Real_compares_by_value_test_1 ) {
	ast::Node x = ast::Node::make<math::Real>(1);
	ast::Node y = ast::Node::make<math::Rational>(2);

	BOOST_CHECK_NE(x, y); //x != y
	BOOST_CHECK_LT(x, y); //x < y
	BOOST_CHECK_LE(x, y); //x <= y
	BOOST_CHECK_GT(y, x); //y > x
	BOOST_CHECK_GE(y, x); //y >= x
}

BOOST_AUTO_TEST_CASE( Rational_and_Real_compares_by_value_test_2 ) {
	ast::Node x = ast::Node::make<math::Rational>(1);
	ast::Node y = ast::Node::make<math::Real>(2);

	BOOST_CHECK_NE(x, y); //x != y
	BOOST_CHECK_LT(x, y); //x < y
	BOOST_CHECK_LE(x, y); //x <= y
	BOOST_CHECK_GT(y, x); //y > x
	BOOST_CHECK_GE(y, x); //y >= x
}

BOOST_AUTO_TEST_CASE( Rational_is_smaller_than_Real_ordering_test ) {
	ast::Node x = ast::Node::make<math::Rational>(1);
	ast::Node y = ast::Node::make<math::Real>(1);

	BOOST_CHECK_NE(x, y); //x != y
	BOOST_CHECK_LT(x, y); //x < y
	BOOST_CHECK_LE(x, y); //x <= y
	BOOST_CHECK_GT(y, x); //y > x
	BOOST_CHECK_GE(y, x); //y >= x
}

BOOST_AUTO_TEST_CASE( different_Identifier_ordering_test ) {
	ast::Node a = ast::Node::make<ast::Identifier>( "a" );
	ast::Node b = ast::Node::make<ast::Identifier>( "b" );

	BOOST_CHECK_NE(a, b);
	BOOST_CHECK_LT(a, b);
	BOOST_CHECK_LE(a, b);
	BOOST_CHECK_GT(b, a);
	BOOST_CHECK_GE(b, a);

}

// Phil does not know how to use the TCGenerator.nb :S

BOOST_AUTO_TEST_CASE( same_Function_ordering_test ) {
	ast::Node a1 = ast::Node::make<ast::FunctionCall>( "Pow" );
	ast::Node a2 = ast::Node::make<ast::FunctionCall>( "Pow" );

	BOOST_CHECK_LE(a1, a2);
	BOOST_CHECK_GE(a1, a2);

	BOOST_CHECK( !(a1 < a2) );
	BOOST_CHECK( !(a2 < a1) );
}
BOOST_AUTO_TEST_CASE( different_Function_ordering_test ) {
	ast::Node a1 = ast::Node::make<ast::FunctionCall>( "Pow" );
	ast::Node a2 = ast::Node::make<ast::FunctionCall>( "Times" );

	BOOST_CHECK_NE(a1, a2);
	BOOST_CHECK_GE(a1, a2);
	
	BOOST_CHECK( !(a1 < a2) );


}


BOOST_AUTO_TEST_CASE( Strings_compares_lexicographically_a_b ) {
	ast::Node a = ast::Node::make<ast::String>( "a" );
	ast::Node b = ast::Node::make<ast::String>( "b" );

	BOOST_CHECK_NE(a, b);
	BOOST_CHECK_LT(a, b);
	BOOST_CHECK_LE(a, b);
	BOOST_CHECK_GT(b, a);
	BOOST_CHECK_GE(b, a);
}

BOOST_AUTO_TEST_CASE( empty_String_is_less_than_any_other ) {
	ast::Node e = ast::Node::make<ast::String>( "" );
	ast::Node b = ast::Node::make<ast::String>( "b" );

	BOOST_CHECK_NE(e, b);
	BOOST_CHECK_LT(e, b);
	BOOST_CHECK_LE(e, b);
	BOOST_CHECK_GT(b, e);
	BOOST_CHECK_GE(b, e);
}

BOOST_AUTO_TEST_CASE( Rational_is_smaller_than_Identifier ) {
	ast::Node r = ast::Node::make<math::Rational>( 3, 2 );
	ast::Node i = ast::Node::make<ast::Identifier>( "a" );

	BOOST_CHECK_NE(r, i);
	BOOST_CHECK_LT(r, i);
	BOOST_CHECK_LE(r, i);
	BOOST_CHECK_GT(i, r);
	BOOST_CHECK_GE(i, r);
}

BOOST_AUTO_TEST_CASE( Real_is_smaller_than_Identifier ) {
	ast::Node r = ast::Node::make<math::Real>( 1.5 );
	ast::Node i = ast::Node::make<ast::Identifier>( "a" );

	BOOST_CHECK_NE(r, i);
	BOOST_CHECK_LT(r, i);
	BOOST_CHECK_LE(r, i);
	BOOST_CHECK_GT(i, r);
	BOOST_CHECK_GE(i, r);
}

BOOST_AUTO_TEST_CASE( Rational_is_smaller_than_String ) {
	ast::Node r = ast::Node::make<math::Rational>( -3, 2 );
	ast::Node s = ast::Node::make<ast::String>( "string" );

	BOOST_CHECK_NE(r, s);
	BOOST_CHECK_LT(r, s);
	BOOST_CHECK_LE(r, s);
	BOOST_CHECK_GT(s, r);
	BOOST_CHECK_GE(s, r);
}

BOOST_AUTO_TEST_CASE( Real_is_smaller_than_String ) {
	ast::Node r = ast::Node::make<math::Real>( -1.5 );
	ast::Node s = ast::Node::make<ast::String>( "string" );

	BOOST_CHECK_NE(r, s);
	BOOST_CHECK_LT(r, s);
	BOOST_CHECK_LE(r, s);
	BOOST_CHECK_GT(s, r);
	BOOST_CHECK_GE(s, r);
}


//FunctionCall related comparsions might change in the future
BOOST_AUTO_TEST_CASE( FunctionCalls_ordered_by_their_functions_first ) {
	ast::Node f = ast::Node::make<ast::FunctionCall>( "aaa", { ast::Node::make<math::Real>( -1.5 ) } );
	ast::Node g = ast::Node::make<ast::FunctionCall>( "bbb", { } );

	BOOST_CHECK_NE(f, g);
	BOOST_CHECK_LT(f, g);
	BOOST_CHECK_LE(f, g);
	BOOST_CHECK_GT(g, f);
	BOOST_CHECK_GE(g, f);
}

BOOST_AUTO_TEST_CASE( FunctionCalls_ordered_by_their_parameters_lexicographically_next ) {
	ast::Node f = ast::Node::make<ast::FunctionCall>( "aaa", { ast::Node::make<ast::String>( "xxx" ) } );
	ast::Node g = ast::Node::make<ast::FunctionCall>( "aaa", { ast::Node::make<ast::String>( "yyy" ) } );

	BOOST_CHECK_NE(f, g);
	BOOST_CHECK_LT(f, g);
	BOOST_CHECK_LE(f, g);
	BOOST_CHECK_GT(g, f);
	BOOST_CHECK_GE(g, f);
}

BOOST_AUTO_TEST_SUITE_END()
