
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
	AstNode node = AstNode::makeRational( 1, 3 );

	BOOST_REQUIRE( node.isRational() );
	BOOST_REQUIRE( node.type() == AstNode::Type::Rational );

	BOOST_CHECK_EQUAL( node.getRational(), Rational(1,3) );
}

BOOST_AUTO_TEST_CASE( makeFunction_creates_Function ) {
	AstNode node = AstNode::makeFunction( "abc", Operands{1} );

	BOOST_REQUIRE( node.isFunction() );
	BOOST_REQUIRE( node.type() == AstNode::Type::Function );

	BOOST_CHECK_EQUAL( node.getFunction().name, "abc" );
	BOOST_CHECK_EQUAL( node.getFunction().operands.size(), 1 );
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

BOOST_AUTO_TEST_SUITE_END()
