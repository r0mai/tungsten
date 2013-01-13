
#include <boost/test/unit_test.hpp>

#include "math/Types.hpp"

#include <limits>

BOOST_AUTO_TEST_SUITE( MathTypesTest )

using namespace tungsten;


BOOST_AUTO_TEST_CASE( Integer_fitsUL_works ) {
	math::Integer maxUL = std::numeric_limits<unsigned long>::max();
	math::Integer minUL = std::numeric_limits<unsigned long>::min();
	math::Integer overMaxUL = maxUL + 1;
	math::Integer underMinUL = minUL - 1;

	BOOST_CHECK( maxUL.fitsUL() );
	BOOST_CHECK( !overMaxUL.fitsUL() );

	BOOST_CHECK( minUL.fitsUL() );
	BOOST_CHECK( !underMinUL.fitsUL() );

}

BOOST_AUTO_TEST_CASE( Integer_fitsSL_works ) {
	math::Integer maxSL = std::numeric_limits<signed long>::max();
	math::Integer minSL = std::numeric_limits<signed long>::min();
	math::Integer overMaxSL = maxSL + 1;
	math::Integer underMinSL = minSL - 1;

	BOOST_CHECK( maxSL.fitsSL() );
	BOOST_CHECK( !overMaxSL.fitsSL() );

	BOOST_CHECK( minSL.fitsSL() );
	BOOST_CHECK( !underMinSL.fitsSL() );

}

BOOST_AUTO_TEST_CASE( Integer_asUL_works ) {
	math::Integer n = 123;

	BOOST_REQUIRE( n.fitsUL() );

	BOOST_CHECK_EQUAL( n.asUL(), 123UL );
}

BOOST_AUTO_TEST_CASE( Integer_asSI_works_for_positive ) {
	math::Integer n = 123;

	BOOST_REQUIRE( n.fitsSL() );

	BOOST_CHECK_EQUAL( n.asSL(), 123UL );
}

BOOST_AUTO_TEST_CASE( Integer_asSI_works_for_negative ) {
	math::Integer n = -123;

	BOOST_REQUIRE( n.fitsSL() );

	BOOST_CHECK_EQUAL( n.asSL(), -123L );
}

BOOST_AUTO_TEST_CASE( Integer_2_toThePower_6 ) {
	math::Integer n = 2;

	BOOST_CHECK_EQUAL( n.toThePower(6), 64 );
}

BOOST_AUTO_TEST_CASE( Integer_minus_2_toThePower_6 ) {
	math::Integer n = -2;

	BOOST_CHECK_EQUAL( n.toThePower(6), 64 );
}

BOOST_AUTO_TEST_CASE( Integer_minus_2_toThePower_5 ) {
	math::Integer n = -2;

	BOOST_CHECK_EQUAL( n.toThePower(5), -32 );
}

BOOST_AUTO_TEST_CASE( Rational_isInteger_works ) {
	math::Rational q(1,2);
	math::Rational z(2,1);
	math::Rational y(0,2);

	y.canonicalize();

	BOOST_CHECK( !q.isInteger() );
	BOOST_CHECK( z.isInteger() );
	BOOST_CHECK( y.isInteger() );
}

BOOST_AUTO_TEST_CASE( Rational_asInteger_works ) {
	math::Rational z(2,1);

	BOOST_REQUIRE( z.isInteger() );

	BOOST_CHECK_EQUAL( z.asInteger(), math::Integer(2) );
}

BOOST_AUTO_TEST_CASE( Rational_2_3_toThePower_3 ) {
	math::Rational n(2, 3);

	BOOST_CHECK_EQUAL( n.toThePower(3), math::Rational(8, 27) );
}

BOOST_AUTO_TEST_CASE( Rational_2_3_toThePower_minus_3 ) {
	math::Rational n(2, 3);

	BOOST_CHECK_EQUAL( n.toThePower(-3), math::Rational(27, 8) );
}

BOOST_AUTO_TEST_CASE( Rational_minus_2_3_toThePower_3 ) {
	math::Rational n(-2, 3);

	BOOST_CHECK_EQUAL( n.toThePower(3), math::Rational(-8, 27) );
}

BOOST_AUTO_TEST_CASE( Rational_minus_2_3_toThePower_minus_3 ) {
	math::Rational n(-2, 3);

	BOOST_CHECK_EQUAL( n.toThePower(-3), math::Rational(-27, 8) );
}

BOOST_AUTO_TEST_CASE( Rational_reciprocal_works ) {
	math::Rational n(2, 3);

	BOOST_CHECK_EQUAL( n.reciprocal(), math::Rational(3, 2) );
}

BOOST_AUTO_TEST_SUITE_END()




