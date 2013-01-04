
#include <boost/test/unit_test.hpp>

#include <functional>

#include "eval/RealRationalNumber.hpp"

BOOST_AUTO_TEST_SUITE( RealRationalNumberTest )

using namespace tungsten;

BOOST_AUTO_TEST_CASE( constructing_from_Real_works ) {
	eval::RealRationalNumber x(math::Real(3.5));

	BOOST_CHECK( !x.is<math::Rational>() );
	BOOST_CHECK( x.is<math::Real>() );

	ast::Node node = x.toNode();

	BOOST_REQUIRE( node.isReal() );
	BOOST_CHECK_EQUAL( node.getReal(), 3.5 );
}

BOOST_AUTO_TEST_CASE( constructing_from_Rational_works ) {
	eval::RealRationalNumber x(math::Rational(5));

	BOOST_CHECK( x.is<math::Rational>() );
	BOOST_CHECK( !x.is<math::Real>() );

	ast::Node node = x.toNode();

	BOOST_REQUIRE( node.isRational() );
	BOOST_CHECK_EQUAL( node.getRational(), 5 );
}

BOOST_AUTO_TEST_CASE( default_constructing_works ) {
	eval::RealRationalNumber x;

	BOOST_CHECK( x.is<math::Rational>() );
	BOOST_CHECK( !x.is<math::Real>() );

	ast::Node node = x.toNode();

	BOOST_REQUIRE( node.isRational() );
	BOOST_CHECK_EQUAL( node.getRational(), 0 );
}

BOOST_AUTO_TEST_CASE( constructing_from_Rational_Node_works ) {
	eval::RealRationalNumber x(ast::Node::makeRational(5));

	BOOST_CHECK( x.is<math::Rational>() );
	BOOST_CHECK( !x.is<math::Real>() );

	ast::Node node = x.toNode();

	BOOST_REQUIRE( node.isRational() );
	BOOST_CHECK_EQUAL( node.getRational(), 5 );
}

BOOST_AUTO_TEST_CASE( constructing_from_Real_Node_works ) {
	eval::RealRationalNumber x(ast::Node::makeReal(3.5));

	BOOST_CHECK( !x.is<math::Rational>() );
	BOOST_CHECK( x.is<math::Real>() );

	ast::Node node = x.toNode();

	BOOST_REQUIRE( node.isReal() );
	BOOST_CHECK_EQUAL( node.getReal(), 3.5 );
}

BOOST_AUTO_TEST_CASE( Rational_Rational_doOperation_results_in_Rational ) {
	eval::RealRationalNumber x(ast::Node::makeRational(5));
	eval::RealRationalNumber y(ast::Node::makeRational(10));

	eval::RealRationalNumber z = eval::RealRationalNumber::doOperation(x, y,
			[](const math::Rational& x, const math::Rational& y) { return x+y; },
			[](const math::Real& x, const math::Real& y) { return x+y; } );

	BOOST_CHECK( z.is<math::Rational>() );

	ast::Node node = z.toNode();

	BOOST_REQUIRE( node.isRational() );
	BOOST_CHECK_EQUAL( node.getRational(), 15 );
}

BOOST_AUTO_TEST_CASE( Real_Rational_doOperation_results_in_Real ) {
	eval::RealRationalNumber x(ast::Node::makeReal(5));
	eval::RealRationalNumber y(ast::Node::makeRational(10));

	eval::RealRationalNumber z = eval::RealRationalNumber::doOperation(x, y,
			[](const math::Rational& x, const math::Rational& y) { return x+y; },
			[](const math::Real& x, const math::Real& y) { return x+y; } );

	BOOST_CHECK( z.is<math::Real>() );

	ast::Node node = z.toNode();

	BOOST_REQUIRE( node.isReal() );
	BOOST_CHECK_EQUAL( node.getReal(), 15 );
}

BOOST_AUTO_TEST_CASE( Rational_Real_doOperation_results_in_Real ) {
	eval::RealRationalNumber x(ast::Node::makeRational(5));
	eval::RealRationalNumber y(ast::Node::makeReal(10));

	eval::RealRationalNumber z = eval::RealRationalNumber::doOperation(x, y,
			[](const math::Rational& x, const math::Rational& y) { return x+y; },
			[](const math::Real& x, const math::Real& y) { return x+y; } );

	BOOST_CHECK( z.is<math::Real>() );

	ast::Node node = z.toNode();

	BOOST_REQUIRE( node.isReal() );
	BOOST_CHECK_EQUAL( node.getReal(), 15 );
}

BOOST_AUTO_TEST_CASE( Real_Real_doOperation_results_in_Real ) {
	eval::RealRationalNumber x(ast::Node::makeReal(5));
	eval::RealRationalNumber y(ast::Node::makeReal(10));

	eval::RealRationalNumber z = eval::RealRationalNumber::doOperation(x, y,
			[](const math::Rational& x, const math::Rational& y) { return x+y; },
			[](const math::Real& x, const math::Real& y) { return x+y; } );

	BOOST_CHECK( z.is<math::Real>() );

	ast::Node node = z.toNode();

	BOOST_REQUIRE( node.isReal() );
	BOOST_CHECK_EQUAL( node.getReal(), 15 );
}

BOOST_AUTO_TEST_SUITE_END()
