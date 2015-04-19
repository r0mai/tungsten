
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

	BOOST_CHECK( math::fits<unsigned long>(maxUL) );
	BOOST_CHECK_EQUAL(maxUL, math::as<unsigned long>(maxUL));
	BOOST_CHECK( !math::fits<unsigned long>(overMaxUL) );

	BOOST_CHECK( math::fits<unsigned long>(minUL) );
	BOOST_CHECK_EQUAL(minUL, math::as<unsigned long>(minUL));
	BOOST_CHECK( !math::fits<unsigned long>(underMinUL) );

}

BOOST_AUTO_TEST_CASE( Integer_fitsSL_works ) {
	math::Integer maxSL = std::numeric_limits<signed long>::max();
	math::Integer minSL = std::numeric_limits<signed long>::min();
	math::Integer overMaxSL = maxSL + 1;
	math::Integer underMinSL = minSL - 1;

	BOOST_CHECK( math::fits<signed long>(maxSL) );
	BOOST_CHECK_EQUAL(maxSL, math::as<signed long>(maxSL));
	BOOST_CHECK( !math::fits<signed long>(overMaxSL) );

	BOOST_CHECK( math::fits<signed long>(minSL) );
	BOOST_CHECK_EQUAL(minSL, math::as<signed long>(minSL));
	BOOST_CHECK( !math::fits<signed long>(underMinSL) );

}

BOOST_AUTO_TEST_CASE( Integer_asUL_works ) {
	math::Integer n = 123;

	BOOST_REQUIRE( math::fits<unsigned long>(n) );

	BOOST_CHECK_EQUAL( math::as<unsigned long>(n), 123UL );
}

BOOST_AUTO_TEST_CASE( Integer_asSL_works_for_positive ) {
	math::Integer n = 123;

	BOOST_REQUIRE( math::fits<signed long>(n) );

	BOOST_CHECK_EQUAL( math::as<signed long>(n), 123UL );
}

BOOST_AUTO_TEST_CASE( Integer_asSL_works_for_negative ) {
	math::Integer n = -123;

	BOOST_REQUIRE( math::fits<signed long>(n) );

	BOOST_CHECK_EQUAL( math::as<signed long>(n), -123L );
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

BOOST_AUTO_TEST_CASE( Complex_real_ln_test ) {
	const auto result = math::ln(math::ComplexReal{0, 2});
	BOOST_CHECK_CLOSE(std::real(result).convert_to<float>(), 0.69, 1.f);
	BOOST_CHECK_CLOSE(std::imag(result).convert_to<float>(), 1.57, 1.f);
}

BOOST_AUTO_TEST_CASE( Complex_rational_power_test ) {
	BOOST_CHECK_EQUAL( math::power(math::ComplexRational(1, 0), 0), math::ComplexRational(1) );
	BOOST_CHECK_EQUAL( math::power(math::ComplexRational(0, 1), 0), math::ComplexRational(1) );
	BOOST_CHECK_EQUAL( math::power(math::ComplexRational(0, 1), 1), math::ComplexRational(0, 1) );
	BOOST_CHECK_EQUAL( math::power(math::ComplexRational(0, 1), 2), math::ComplexRational(-1, 0) );
	BOOST_CHECK_EQUAL( math::power(math::ComplexRational(0, -1), 2), math::ComplexRational(-1, 0) );
	BOOST_CHECK_EQUAL( math::power(math::ComplexRational(1, 1), 2), math::ComplexRational(0, 2) );
	BOOST_CHECK_EQUAL( math::power(math::ComplexRational(1, -1), 2), math::ComplexRational(0, -2) );
	BOOST_CHECK_EQUAL( math::power(math::ComplexRational(-1, 1), 2), math::ComplexRational(0, -2) );
	BOOST_CHECK_EQUAL( math::power(math::ComplexRational(-1, -1), 2), math::ComplexRational(0, 2) );
}

BOOST_AUTO_TEST_CASE( Complex_real_power_test ) {
	BOOST_CHECK_EQUAL( math::power(math::ComplexReal(1, 0), math::ComplexReal(0)), math::ComplexReal(1) );
	BOOST_CHECK_EQUAL( math::power(math::ComplexReal(0, 1), math::ComplexReal(0)), math::ComplexReal(1) );
	BOOST_CHECK_EQUAL( math::power(math::ComplexReal(0, 1), math::ComplexReal(1)), math::ComplexReal(0, 1) );
	BOOST_CHECK_EQUAL( math::power(math::ComplexReal(0, 1), math::ComplexReal(2)), math::ComplexReal(-1, 0) );
	BOOST_CHECK_EQUAL( math::power(math::ComplexReal(0, -1), math::ComplexReal(2)), math::ComplexReal(-1, 0) );
	BOOST_CHECK_EQUAL( math::power(math::ComplexReal(1, 1), math::ComplexReal(2)), math::ComplexReal(0, 2) );
	BOOST_CHECK_EQUAL( math::power(math::ComplexReal(1, -1), math::ComplexReal(2)), math::ComplexReal(0, -2) );
	BOOST_CHECK_EQUAL( math::power(math::ComplexReal(-1, 1), math::ComplexReal(2)), math::ComplexReal(0, -2) );
	BOOST_CHECK_EQUAL( math::power(math::ComplexReal(-1, -1), math::ComplexReal(2)), math::ComplexReal(0, 2) );

	BOOST_CHECK_EQUAL( math::power(math::ComplexReal(1, 0), math::ComplexReal(0, 1)), math::ComplexReal(1, 0));
	BOOST_CHECK_EQUAL( math::power(math::ComplexReal(1, 0), math::ComplexReal(0, -1)), math::ComplexReal(1, 0));

}

BOOST_AUTO_TEST_SUITE_END()




