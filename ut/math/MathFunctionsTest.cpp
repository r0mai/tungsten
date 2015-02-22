
#include <boost/test/unit_test.hpp>

#include <boost/math/constants/constants.hpp>

#include "math/mathFunctions.hpp"

BOOST_AUTO_TEST_SUITE( MathFunctionsTest )

using namespace tungsten;

BOOST_AUTO_TEST_CASE( RationalNear_of_Integer_should_be_integer ) {
	math::Rational x = 10;
	math::Real xr = x;
	BOOST_CHECK_EQUAL(math::findRationalNear(xr), x);
}

BOOST_AUTO_TEST_CASE( RationalNear_of_Rational_should_be_integer ) {
	math::Rational x(10, 3);
	math::Real xr = x;
	BOOST_CHECK_EQUAL(math::findRationalNear(xr), x);
}

BOOST_AUTO_TEST_CASE( RationalNear_of_Pi_should_be_close_to_Pi ) {
	math::Real realPi = boost::math::constants::pi<double>();
	const auto result = math::findRationalNear(realPi);
	BOOST_CHECK_LE(abs(realPi - result), math::Real(1e-04));
}

BOOST_AUTO_TEST_CASE( RationalNear_of_Pi_with_01_tolerance_should_be_22_7 ) {
	math::Real realPi = boost::math::constants::pi<double>();
	const auto result = math::findRationalNear(realPi, 0.01);
	BOOST_CHECK_EQUAL(result, math::Rational(22,7));
}

BOOST_AUTO_TEST_CASE( RationalNear_of_Pi_with_001_tolerance_should_be_333_106 ) {
	math::Real realPi = boost::math::constants::pi<double>();
	const auto result = math::findRationalNear(realPi, 0.001);
	BOOST_CHECK_EQUAL(result, math::Rational(333,106));
}

BOOST_AUTO_TEST_CASE( getContinuedFraction_of_3_245_should_be_3_4_12_4 ) {
	math::Rational x(649, 200); // 3+49/200 == 3.245
	const std::vector<math::Integer> expected = {3, 4, 12, 3, 1};
	const auto result = math::getContinuedFraction(math::Real{x});

	BOOST_CHECK_EQUAL_COLLECTIONS(result.begin(), result.end(), expected.begin(), expected.end());
}

BOOST_AUTO_TEST_CASE( getContinuedFraction_of_2_and_one_half_should_be_2_2 ) {
	math::Rational x(5,2);
	const std::vector<math::Integer> expected = {2, 2};
	const auto result = math::getContinuedFraction(math::Real{x});

	BOOST_CHECK_EQUAL_COLLECTIONS(result.begin(), result.end(), expected.begin(), expected.end());
}

BOOST_AUTO_TEST_CASE( getContinuedFraction_of_Integer_should_be_one_element_long ) {
	math::Rational x(5);
	const auto result = math::getContinuedFraction(math::Real{x});
	BOOST_CHECK_EQUAL(result.size(), 1);
}

BOOST_AUTO_TEST_CASE( evaluateContinuedFraction_of_0_1_should_be_1 ) {
	const auto result = math::evaluateContinuedFraction( { 0, 1 } );
	BOOST_CHECK_EQUAL(result, 1);
}

BOOST_AUTO_TEST_CASE( evaluateContinuedFraction_of_empty_vector_should_be_0 ) {
	const auto result = math::evaluateContinuedFraction( { } );
	BOOST_CHECK_EQUAL(result, 0);
}

BOOST_AUTO_TEST_CASE( evaluateContinuedFraction_of_4_should_be_4 ) {
	const auto result = math::evaluateContinuedFraction( {4} );
	BOOST_CHECK_EQUAL(result, 4);
}

BOOST_AUTO_TEST_SUITE_END()
