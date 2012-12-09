
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

BOOST_AUTO_TEST_CASE( makeFunction_creates_Function ) {
	ast::Node node = ast::Node::makeFunction( "abc", { ast::Node::makeRational(1, 3), ast::Node::makeRational(2, 3) } );

	BOOST_REQUIRE( node.isFunction() );
	BOOST_REQUIRE( node.type() == ast::Node::Type::FunctionCall );

	BOOST_REQUIRE( node.getFunction().getFunction().isIdentifier() );

	BOOST_CHECK_EQUAL( node.getFunction().getFunction().getIdentifier(), "abc" );

	BOOST_REQUIRE_EQUAL( node.getFunction().getOperands().size(), 2 );

	BOOST_REQUIRE( node[0].isRational() );
	BOOST_CHECK_EQUAL( node[0].getRational(), math::Rational(1, 3) );

	BOOST_REQUIRE( node[1].isRational() );
	BOOST_CHECK_EQUAL( node[1].getRational(), math::Rational(2, 3) );

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

BOOST_AUTO_TEST_CASE( toString_output_is_correct_1 ) {
	ast::Node node = ast::Node::makeFunction( "Func", { ast::Node::makeIdentifier("x"), ast::Node::makeIdentifier("y") } );

	BOOST_CHECK_EQUAL(node.toString(), "Func[x, y]");
}

BOOST_AUTO_TEST_CASE( toString_output_is_correct_2 ) {
	ast::Node node = ast::Node::makeFunction(
			"f", { ast::Node::makeFunction("g", { ast::Node::makeRational(1,5) }), ast::Node::makeIdentifier("y") } );

	BOOST_CHECK_EQUAL(node.toString(), "f[g[1/5], y]");
}

BOOST_AUTO_TEST_CASE( toString_output_is_correct_3 ) {
	ast::Node node = ast::Node::makeFunction("h");

	BOOST_CHECK_EQUAL(node.toString(), "h[]");
}

BOOST_AUTO_TEST_CASE( toString_output_is_correct_4 ) {
	ast::Node node = ast::Node::makeString("abc d efg");

	BOOST_CHECK_EQUAL(node.toString(), "\"abc d efg\"");
}

BOOST_AUTO_TEST_CASE( equality_test_real ) {
	BOOST_CHECK_EQUAL(ast::Node::makeReal(5.0), ast::Node::makeReal(5.0));
}

BOOST_AUTO_TEST_CASE( equality_test_rational ) {
	BOOST_CHECK_EQUAL(ast::Node::makeRational(1,3), ast::Node::makeRational(1,3));
}

BOOST_AUTO_TEST_CASE( equality_test_function ) {
	BOOST_CHECK_EQUAL(ast::Node::makeFunction("h"), ast::Node::makeFunction("h"));
}

BOOST_AUTO_TEST_CASE( equality_test_nested_function ) {
	BOOST_CHECK_EQUAL(
			ast::Node::makeFunction(
					"f", { ast::Node::makeFunction("g", { ast::Node::makeRational(1,5) }), ast::Node::makeIdentifier("y") } ),
			ast::Node::makeFunction(
					"f", { ast::Node::makeFunction("g", { ast::Node::makeRational(1,5) }), ast::Node::makeIdentifier("y") } ));
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
	BOOST_CHECK_NE(ast::Node::makeFunction("h"), ast::Node::makeFunction("h", {ast::Node::makeIdentifier("x")}));
}

BOOST_AUTO_TEST_CASE( non_equality_test_different_function_name ) {
	BOOST_CHECK_NE(ast::Node::makeFunction("h"), ast::Node::makeFunction("g"));
}

BOOST_AUTO_TEST_CASE( non_equality_test_real_rational ) {
	//They're only equal in mathematical sense
	BOOST_CHECK_NE(ast::Node::makeReal(1), ast::Node::makeRational(1));
}

BOOST_AUTO_TEST_SUITE_END()
