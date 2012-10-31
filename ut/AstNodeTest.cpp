
#include <boost/test/unit_test.hpp>

#include "../src/AstNode.hpp"

BOOST_AUTO_TEST_SUITE( AstNodeTest )

using namespace tungsten;

BOOST_AUTO_TEST_CASE( makeReal_creates_Real ) {
	AstNode node = AstNode::makeReal(1.5);

	BOOST_REQUIRE( node.isReal() );
	BOOST_REQUIRE( node.type() == AstNode::Type::Real );

	BOOST_CHECK_EQUAL( node.getReal(), 1.5 );
}

BOOST_AUTO_TEST_CASE( makeRational_creates_Rational ) {
	AstNode node = AstNode::makeRational(1, 3);

	BOOST_REQUIRE( node.isRational() );
	BOOST_REQUIRE( node.type() == AstNode::Type::Rational );

	BOOST_CHECK_EQUAL( node.getRational(), Rational(1,3) );
}

BOOST_AUTO_TEST_CASE( makeFunction_creates_Function ) {
	AstNode node = AstNode::makeFunction( "abc", { AstNode::makeRational(1, 3), AstNode::makeRational(2, 3) } );

	BOOST_REQUIRE( node.isFunction() );
	BOOST_REQUIRE( node.type() == AstNode::Type::Function );

	BOOST_CHECK_EQUAL( node.getFunction().name, "abc" );

	BOOST_REQUIRE_EQUAL( node.getFunction().operands.size(), 2 );

	BOOST_REQUIRE( node[0].isRational() );
	BOOST_CHECK_EQUAL( node[0].getRational(), Rational(1, 3) );

	BOOST_REQUIRE( node[1].isRational() );
	BOOST_CHECK_EQUAL( node[1].getRational(), Rational(2, 3) );

}

BOOST_AUTO_TEST_CASE( makeString_creates_String ) {
	AstNode node = AstNode::makeString( "345" );

	BOOST_REQUIRE( node.isString() );
	BOOST_REQUIRE( node.type() == AstNode::Type::String );

	BOOST_CHECK_EQUAL( node.getString(), "345" );

}

BOOST_AUTO_TEST_CASE( makeIdentifier_creates_Identifier ) {
	AstNode node = AstNode::makeIdentifier( "Pi" );

	BOOST_REQUIRE( node.isIdentifier() );
	BOOST_REQUIRE( node.type() == AstNode::Type::Identifier );

	BOOST_CHECK_EQUAL( node.getIdentifier(), "Pi" );

}

BOOST_AUTO_TEST_CASE( toString_output_is_correct_1 ) {
	AstNode node = AstNode::makeFunction( "Func", { AstNode::makeIdentifier("x"), AstNode::makeIdentifier("y") } );

	BOOST_CHECK_EQUAL(node.toString(), "Func[x, y]");
}

BOOST_AUTO_TEST_CASE( toString_output_is_correct_2 ) {
	AstNode node = AstNode::makeFunction(
			"f", { AstNode::makeFunction("g", { AstNode::makeRational(1,5) }), AstNode::makeIdentifier("y") } );

	BOOST_CHECK_EQUAL(node.toString(), "f[g[1/5], y]");
}

BOOST_AUTO_TEST_CASE( toString_output_is_correct_3 ) {
	AstNode node = AstNode::makeFunction("h");

	BOOST_CHECK_EQUAL(node.toString(), "h[]");
}

BOOST_AUTO_TEST_CASE( toString_output_is_correct_4 ) {
	AstNode node = AstNode::makeString("abc d efg");

	BOOST_CHECK_EQUAL(node.toString(), "\"abc d efg\"");
}

BOOST_AUTO_TEST_SUITE_END()
