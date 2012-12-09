
#include "Pi.hpp"

#include <boost/math/special_functions/round.hpp>

namespace tungsten { namespace math {

Real calculatePi(Precision precision) {

	assert( precision > 0 );

	Precision binaryPrecision = boost::math::lround(3.321928 * precision);

	Real result(3.1415, binaryPrecision);

	return result;
}

}} //namespace tungsten::math


