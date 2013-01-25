
#include <boost/test/unit_test.hpp>

#include "eval/isSuperficiallyNegative.hpp"

BOOST_AUTO_TEST_SUITE( isSuperficiallyNegativeTest )

using namespace tungsten;

BOOST_AUTO_TEST_CASE( Real_0_is_not_negatve ) {
	ast::Node node = ast::Node::make<math::Real>(0);

	BOOST_CHECK( !eval::isSuperficiallyNegative( node ) );
}

BOOST_AUTO_TEST_CASE( Rational_0_is_not_negatve ) {
	ast::Node node = ast::Node::make<math::Rational>(0);

	BOOST_CHECK( !eval::isSuperficiallyNegative( node ) );
}

BOOST_AUTO_TEST_CASE( Negative_Real_is_negatve ) {
	ast::Node node = ast::Node::make<math::Real>(-1);

	BOOST_CHECK( eval::isSuperficiallyNegative( node ) );
}

BOOST_AUTO_TEST_CASE( Negative_Rational_is_negatve ) {
	ast::Node node = ast::Node::make<math::Rational>(-1);

	BOOST_CHECK( eval::isSuperficiallyNegative( node ) );
}

BOOST_AUTO_TEST_CASE( Positive_Real_is_not_negatve ) {
	ast::Node node = ast::Node::make<math::Real>(1);

	BOOST_CHECK( !eval::isSuperficiallyNegative( node ) );
}

BOOST_AUTO_TEST_CASE( Positive_Rational_is_not_negatve ) {
	ast::Node node = ast::Node::make<math::Rational>(1);

	BOOST_CHECK( !eval::isSuperficiallyNegative( node ) );
}

BOOST_AUTO_TEST_CASE( String_is_not_negative ) {
	ast::Node node = ast::Node::make<ast::String>("abc");

	BOOST_CHECK( !eval::isSuperficiallyNegative( node ) );
}

BOOST_AUTO_TEST_CASE( Identifier_is_not_negative ) {
	ast::Node node = ast::Node::make<ast::Identifier>("x");

	BOOST_CHECK( !eval::isSuperficiallyNegative( node ) );
}

BOOST_AUTO_TEST_CASE( minus_x_is_negative ) {
	ast::Node node = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<math::Rational>(-1), ast::Node::make<ast::Identifier>("x")});

	BOOST_CHECK( eval::isSuperficiallyNegative( node ) );
}

BOOST_AUTO_TEST_CASE( three_x_is_not_negative ) {
	ast::Node node = ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<math::Rational>(3), ast::Node::make<ast::Identifier>("x")});

	BOOST_CHECK( !eval::isSuperficiallyNegative( node ) );
}

BOOST_AUTO_TEST_SUITE_END()
