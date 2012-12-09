
#include <boost/test/unit_test.hpp>

#include <boost/math/constants/constants.hpp>

#include "math/Pi.hpp"

BOOST_AUTO_TEST_SUITE( MathPiTest )

using namespace tungsten;


BOOST_AUTO_TEST_CASE( Pi_Precision_test ) {

	math::Real realPi = boost::math::constants::pi<double>();

	BOOST_CHECK_LE(abs(math::calculatePi(1) - realPi), math::Real(0.5) );

	BOOST_CHECK_LE(abs(math::calculatePi(2) - realPi), math::Real(0.05) );

	BOOST_CHECK_LE(abs(math::calculatePi(3) - realPi), math::Real(0.005) );
}


BOOST_AUTO_TEST_SUITE_END()




