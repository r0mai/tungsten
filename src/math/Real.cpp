
#include "Real.hpp"

#include <mpfr.h>

#include <cassert>
#include <sstream>

namespace tungsten { namespace math {

std::string toString(const Real& real) {
	return real.str(20);
}

Real power(const Real& base, const Real& exponent) {
	return boost::multiprecision::pow(base, exponent);
}

bool isInteger(const Real& n) {
	return mpfr_integer_p( n.backend().data() ) != 0;
}

}} //namespace tungsten::math
