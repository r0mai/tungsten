
#include <boost/test/unit_test.hpp>

#include "math/mathFunctions.hpp"

BOOST_AUTO_TEST_SUITE( MathFunctionsTest )

using namespace tungsten;

BOOST_AUTO_TEST_CASE( getContinuedFraction_of_3_245_should_be_3_4_12_4 ) {
	math::Rational x(649, 200); // 3+49/200 == 3.245
	const std::vector<math::Integer> expected = {3, 4, 12, 3, 1};
	const auto result = math::getContinuedFraction(math::Real{x});

	BOOST_CHECK_EQUAL_COLLECTIONS(result.begin(), result.end(), expected.begin(), expected.end());
}

BOOST_AUTO_TEST_CASE( getContinuesFraction_of_2_and_one_half_should_be_2_2 ) {
	math::Rational x(5,2);
	const std::vector<math::Integer> expected = {2, 2};
	const auto result = math::getContinuedFraction(math::Real{x});

	BOOST_CHECK_EQUAL_COLLECTIONS(result.begin(), result.end(), expected.begin(), expected.end());
}

BOOST_AUTO_TEST_SUITE_END()
