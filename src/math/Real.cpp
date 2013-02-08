
#include "Real.hpp"

#include <mpfr.h>

#include <cassert>
#include <sstream>

namespace tungsten { namespace math {

std::string toString(const Real& real) {
	return real.str();
}

Real power(const Real& base, const Real& exponent) {
	return boost::multiprecision::pow(base, exponent);
}

}} //namespace tungsten::math
