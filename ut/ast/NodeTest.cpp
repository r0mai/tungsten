
#include <boost/test/unit_test.hpp>

#include "ast/Node.hpp"

BOOST_AUTO_TEST_SUITE( NodeTest )

using namespace tungsten;
using namespace tungsten::ast;

BOOST_AUTO_TEST_CASE( makeReal_creates_Real ) {
	Node node = Node::makeReal(1.5);

	BOOST_REQUIRE( node.isReal() );
	BOOST_REQUIRE( node.type() == Node::Type::Real );

	BOOST_CHECK_EQUAL( node.getReal(), 1.5 );
}

BOOST_AUTO_TEST_CASE( makeRational_creates_Rational ) {
	Node node = Node::makeRational(1, 3);

	BOOST_REQUIRE( node.isRational() );
	BOOST_REQUIRE( node.type() == Node::Type::Rational );

	BOOST_CHECK_EQUAL( node.getRational(), math::Rational(1,3) );
}

BOOST_AUTO_TEST_CASE( makeFunction_creates_Function ) {
	Node node = Node::makeFunction( "abc", { Node::makeRational(1, 3), Node::makeRational(2, 3) } );

	BOOST_REQUIRE( node.isFunction() );
	BOOST_REQUIRE( node.type() == Node::Type::Function );

	BOOST_CHECK_EQUAL( node.getFunction().name, "abc" );

	BOOST_REQUIRE_EQUAL( node.getFunction().operands.size(), 2 );

	BOOST_REQUIRE( node[0].isRational() );
	BOOST_CHECK_EQUAL( node[0].getRational(), math::Rational(1, 3) );

	BOOST_REQUIRE( node[1].isRational() );
	BOOST_CHECK_EQUAL( node[1].getRational(), math::Rational(2, 3) );

}

BOOST_AUTO_TEST_CASE( makeString_creates_String ) {
	Node node = Node::makeString( "345" );

	BOOST_REQUIRE( node.isString() );
	BOOST_REQUIRE( node.type() == Node::Type::String );

	BOOST_CHECK_EQUAL( node.getString(), "345" );

}

BOOST_AUTO_TEST_CASE( makeIdentifier_creates_Identifier ) {
	Node node = Node::makeIdentifier( "Pi" );

	BOOST_REQUIRE( node.isIdentifier() );
	BOOST_REQUIRE( node.type() == Node::Type::Identifier );

	BOOST_CHECK_EQUAL( node.getIdentifier(), "Pi" );

}

BOOST_AUTO_TEST_CASE( toString_output_is_correct_1 ) {
	Node node = Node::makeFunction( "Func", { Node::makeIdentifier("x"), Node::makeIdentifier("y") } );

	BOOST_CHECK_EQUAL(node.toString(), "Func[x, y]");
}

BOOST_AUTO_TEST_CASE( toString_output_is_correct_2 ) {
	Node node = Node::makeFunction(
			"f", { Node::makeFunction("g", { Node::makeRational(1,5) }), Node::makeIdentifier("y") } );

	BOOST_CHECK_EQUAL(node.toString(), "f[g[1/5], y]");
}

BOOST_AUTO_TEST_CASE( toString_output_is_correct_3 ) {
	Node node = Node::makeFunction("h");

	BOOST_CHECK_EQUAL(node.toString(), "h[]");
}

BOOST_AUTO_TEST_CASE( toString_output_is_correct_4 ) {
	Node node = Node::makeString("abc d efg");

	BOOST_CHECK_EQUAL(node.toString(), "\"abc d efg\"");
}

BOOST_AUTO_TEST_CASE( equality_test_real ) {
	BOOST_CHECK_EQUAL(Node::makeReal(5.0), Node::makeReal(5.0));
}

BOOST_AUTO_TEST_CASE( equality_test_rational ) {
	BOOST_CHECK_EQUAL(Node::makeRational(1,3), Node::makeRational(1,3));
}

BOOST_AUTO_TEST_CASE( equality_test_function ) {
	BOOST_CHECK_EQUAL(Node::makeFunction("h"), Node::makeFunction("h"));
}

BOOST_AUTO_TEST_CASE( equality_test_nested_function ) {
	BOOST_CHECK_EQUAL(
			Node::makeFunction(
					"f", { Node::makeFunction("g", { Node::makeRational(1,5) }), Node::makeIdentifier("y") } ),
			Node::makeFunction(
					"f", { Node::makeFunction("g", { Node::makeRational(1,5) }), Node::makeIdentifier("y") } ));
}

BOOST_AUTO_TEST_CASE( equality_test_string ) {
	BOOST_CHECK_EQUAL(Node::makeString( "abc d efg" ), Node::makeString( "abc d efg" ));
}

BOOST_AUTO_TEST_CASE( equality_test_identifier ) {
	BOOST_CHECK_EQUAL(Node::makeIdentifier( "Pi" ), Node::makeIdentifier( "Pi" ));
}

BOOST_AUTO_TEST_CASE( non_equality_test_string_identifier ) {
	BOOST_CHECK_NE(Node::makeIdentifier( "Pi" ), Node::makeString( "Pi" ));
}

BOOST_AUTO_TEST_CASE( non_equality_test_different_function_params ) {
	BOOST_CHECK_NE(Node::makeFunction("h"), Node::makeFunction("h", {Node::makeIdentifier("x")}));
}

BOOST_AUTO_TEST_CASE( non_equality_test_different_function_name ) {
	BOOST_CHECK_NE(Node::makeFunction("h"), Node::makeFunction("g"));
}

BOOST_AUTO_TEST_CASE( non_equality_test_real_rational ) {
	//They're only equal in mathematical sense
	BOOST_CHECK_NE(Node::makeReal(1), Node::makeRational(1));
}

BOOST_AUTO_TEST_SUITE_END()
