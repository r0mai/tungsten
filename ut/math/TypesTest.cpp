
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

	BOOST_CHECK( math::fitsUL(maxUL) );
	BOOST_CHECK_EQUAL(maxUL, math::asUL(maxUL));
	BOOST_CHECK( !math::fitsUL(overMaxUL) );

	BOOST_CHECK( math::fitsUL(minUL) );
	BOOST_CHECK_EQUAL(minUL, math::asUL(minUL));
	BOOST_CHECK( !math::fitsUL(underMinUL) );

}

BOOST_AUTO_TEST_CASE( Integer_fitsSL_works ) {
	math::Integer maxSL = std::numeric_limits<signed long>::max();
	math::Integer minSL = std::numeric_limits<signed long>::min();
	math::Integer overMaxSL = maxSL + 1;
	math::Integer underMinSL = minSL - 1;

	BOOST_CHECK( math::fitsSL(maxSL) );
	BOOST_CHECK_EQUAL(maxSL, math::asSL(maxSL));
	BOOST_CHECK( !math::fitsSL(overMaxSL) );

	BOOST_CHECK( math::fitsSL(minSL) );
	BOOST_CHECK_EQUAL(minSL, math::asSL(minSL));
	BOOST_CHECK( !math::fitsSL(underMinSL) );

}

BOOST_AUTO_TEST_CASE( Integer_asUL_works ) {
	math::Integer n = 123;

	BOOST_REQUIRE( math::fitsUL(n) );

	BOOST_CHECK_EQUAL( math::asUL(n), 123UL );
}

BOOST_AUTO_TEST_CASE( Integer_asSI_works_for_positive ) {
	math::Integer n = 123;

	BOOST_REQUIRE( math::fitsSL(n) );

	BOOST_CHECK_EQUAL( math::asSL(n), 123UL );
}

BOOST_AUTO_TEST_CASE( Integer_asSI_works_for_negative ) {
	math::Integer n = -123;

	BOOST_REQUIRE( math::fitsSL(n) );

	BOOST_CHECK_EQUAL( math::asSL(n), -123L );
}

BOOST_AUTO_TEST_CASE( Rational_isInteger_works ) {
	math::Rational q(1,2);
	math::Rational z(2,1);
	math::Rational y(0,2);

	BOOST_CHECK( !math::isInteger(q) );
	BOOST_CHECK( math::isInteger(z) );
	BOOST_CHECK( math::isInteger(y) );
}

BOOST_AUTO_TEST_CASE( Rational_asInteger_works ) {
	math::Rational z(2,1);

	BOOST_REQUIRE( math::isInteger(z) );

	BOOST_CHECK_EQUAL( math::asInteger(z), math::Integer(2) );
}

BOOST_AUTO_TEST_CASE( Rational_reciprocal_works ) {
	math::Rational n(2, 3);

	BOOST_CHECK_EQUAL( math::reciprocal(n), math::Rational(3, 2) );
}



BOOST_AUTO_TEST_CASE( Integer_power_test ) {
	BOOST_CHECK_EQUAL( math::power(math::Integer(2), math::Integer(6)), 64 );
	BOOST_CHECK_EQUAL( math::power(math::Integer(-2), math::Integer(6)), 64 );
	BOOST_CHECK_EQUAL( math::power(math::Integer(-2), math::Integer(5)), -32 );
}

BOOST_AUTO_TEST_CASE( Rational_power_test ) {
	BOOST_CHECK_EQUAL( math::power(math::Rational(2, 3), 3), math::Rational(8, 27) );
	BOOST_CHECK_EQUAL( math::power(math::Rational(2, 3), -3), math::Rational(27, 8) );
	BOOST_CHECK_EQUAL( math::power(math::Rational(-2, 3), 3), math::Rational(-8, 27) );
	BOOST_CHECK_EQUAL( math::power(math::Rational(-2, 3), -3), math::Rational(-27, 8) );
}

BOOST_AUTO_TEST_CASE( Real_power_test ) {
	BOOST_CHECK_EQUAL( math::power(math::Real(2), math::Real(3)), 8.0 );
}

BOOST_AUTO_TEST_SUITE_END()




