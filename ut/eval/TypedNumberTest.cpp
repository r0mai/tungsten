
#include <boost/test/unit_test.hpp>
#include <functional>

#include "eval/TypedNumber.hpp"

BOOST_AUTO_TEST_SUITE( TypedNumberTest )

using namespace tungsten;

BOOST_AUTO_TEST_CASE( constructing_from_Real_works ) {
	eval::TypedNumber x(math::Real(3.5));

	BOOST_CHECK( !x.is<math::Rational>() );
	BOOST_CHECK( x.is<math::Real>() );

	ast::Node node = x.toNode();

	BOOST_REQUIRE( node.is<math::Real>() );
	BOOST_CHECK_EQUAL( node.get<math::Real>(), 3.5 );
}

BOOST_AUTO_TEST_CASE( constructing_from_Rational_works ) {
	eval::TypedNumber x(math::Rational(5));

	BOOST_CHECK( x.is<math::Rational>() );
	BOOST_CHECK( !x.is<math::Real>() );

	ast::Node node = x.toNode();

	BOOST_REQUIRE( node.is<math::Rational>() );
	BOOST_CHECK_EQUAL( node.get<math::Rational>(), 5 );
}

BOOST_AUTO_TEST_CASE( default_constructing_works ) {
	eval::TypedNumber x;

	BOOST_CHECK( x.is<math::Rational>() );
	BOOST_CHECK( !x.is<math::Real>() );

	ast::Node node = x.toNode();

	BOOST_REQUIRE( node.is<math::Rational>() );
	BOOST_CHECK_EQUAL( node.get<math::Rational>(), 0 );
}

BOOST_AUTO_TEST_CASE( constructing_from_Rational_Node_works ) {
	eval::TypedNumber x(ast::Node::make<math::Rational>(5));

	BOOST_CHECK( x.is<math::Rational>() );
	BOOST_CHECK( !x.is<math::Real>() );

	ast::Node node = x.toNode();

	BOOST_REQUIRE( node.is<math::Rational>() );
	BOOST_CHECK_EQUAL( node.get<math::Rational>(), 5 );
}

BOOST_AUTO_TEST_CASE( constructing_from_Real_Node_works ) {
	eval::TypedNumber x(ast::Node::make<math::Real>(3.5));

	BOOST_CHECK( !x.is<math::Rational>() );
	BOOST_CHECK( x.is<math::Real>() );

	ast::Node node = x.toNode();

	BOOST_REQUIRE( node.is<math::Real>() );
	BOOST_CHECK_EQUAL( node.get<math::Real>(), 3.5 );
}

BOOST_AUTO_TEST_CASE( Rational_Rational_doPlus_results_in_Rational ) {
	eval::TypedNumber x(ast::Node::make<math::Rational>(5));
	eval::TypedNumber y(ast::Node::make<math::Rational>(10));

	eval::TypedNumber z = eval::TypedNumber::doPlus(x, y);

	BOOST_CHECK( z.is<math::Rational>() );

	ast::Node node = z.toNode();

	BOOST_REQUIRE( node.is<math::Rational>() );
	BOOST_CHECK_EQUAL( node.get<math::Rational>(), 15 );
}

BOOST_AUTO_TEST_CASE( Real_Rational_doPlus_results_in_Real ) {
	eval::TypedNumber x(ast::Node::make<math::Real>(5));
	eval::TypedNumber y(ast::Node::make<math::Rational>(10));

	eval::TypedNumber z = eval::TypedNumber::doPlus(x, y);

	BOOST_CHECK( z.is<math::Real>() );

	ast::Node node = z.toNode();

	BOOST_REQUIRE( node.is<math::Real>() );
	BOOST_CHECK_EQUAL( node.get<math::Real>(), 15 );
}

BOOST_AUTO_TEST_CASE( Rational_Real_doPlus_results_in_Real ) {
	eval::TypedNumber x(ast::Node::make<math::Rational>(5));
	eval::TypedNumber y(ast::Node::make<math::Real>(10));

	eval::TypedNumber z = eval::TypedNumber::doPlus(x, y);

	BOOST_CHECK( z.is<math::Real>() );

	ast::Node node = z.toNode();

	BOOST_REQUIRE( node.is<math::Real>() );
	BOOST_CHECK_EQUAL( node.get<math::Real>(), 15 );
}

BOOST_AUTO_TEST_CASE( Real_Real_doPlus_results_in_Real ) {
	eval::TypedNumber x(ast::Node::make<math::Real>(5));
	eval::TypedNumber y(ast::Node::make<math::Real>(10));

	eval::TypedNumber z = eval::TypedNumber::doPlus(x, y);

	BOOST_CHECK( z.is<math::Real>() );

	ast::Node node = z.toNode();

	BOOST_REQUIRE( node.is<math::Real>() );
	BOOST_CHECK_EQUAL( node.get<math::Real>(), 15 );
}

BOOST_AUTO_TEST_CASE( ComplexRational_Rational_do_Plus_results_in_ComplexRational ) {
	eval::TypedNumber x(ast::Node::make<math::ComplexRational>(4, 1));
	eval::TypedNumber y(ast::Node::make<math::Rational>(5));

	eval::TypedNumber z = eval::TypedNumber::doPlus(x, y);

	BOOST_CHECK( z.is<math::ComplexRational>() );

	ast::Node node = z.toNode();

	BOOST_REQUIRE( node.is<math::ComplexRational>() );
	BOOST_CHECK_EQUAL(node.get<math::ComplexRational>(), math::ComplexRational(9, 1));
}

BOOST_AUTO_TEST_CASE( ComplexRational_Real_do_Plus_results_in_ComplexReal ) {
	eval::TypedNumber x(ast::Node::make<math::ComplexRational>(4, 1));
	eval::TypedNumber y(ast::Node::make<math::Real>(5));

	eval::TypedNumber z = eval::TypedNumber::doPlus(x, y);

	BOOST_CHECK( z.is<math::ComplexReal>() );

	ast::Node node = z.toNode();

	BOOST_REQUIRE( node.is<math::ComplexReal>() );
	BOOST_CHECK_EQUAL(node.get<math::ComplexReal>(), math::ComplexReal(9, 1));
}

BOOST_AUTO_TEST_SUITE_END()
