
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
