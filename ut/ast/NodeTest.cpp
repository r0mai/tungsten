
#include <boost/test/unit_test.hpp>

#include "ast/Node.hpp"

BOOST_AUTO_TEST_SUITE( NodeTest )

using namespace tungsten;

BOOST_AUTO_TEST_CASE( makeReal_creates_Real ) {
	ast::Node node = ast::Node::make<math::Real>(1.5);

	BOOST_REQUIRE( node.is<math::Real>() );

	BOOST_CHECK_EQUAL( node.get<math::Real>(), 1.5 );
}

BOOST_AUTO_TEST_CASE( makeRational_creates_Rational ) {
	ast::Node node = ast::Node::make<math::Rational>(1, 3);

	BOOST_REQUIRE( node.is<math::Rational>() );

	BOOST_CHECK_EQUAL( node.get<math::Rational>(), math::Rational(1,3) );
}

BOOST_AUTO_TEST_CASE( makeFunctionCall_creates_FunctionCall_with_paramters ) {
	ast::Node node = ast::Node::make<ast::FunctionCall>( "abc", { ast::Node::make<math::Rational>(1, 3), ast::Node::make<math::Rational>(2, 3) } );

	BOOST_REQUIRE( node.is<ast::FunctionCall>() );

	BOOST_REQUIRE( node.get<ast::FunctionCall>().getFunction().is<ast::Identifier>() );

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

BOOST_AUTO_TEST_SUITE_END()
