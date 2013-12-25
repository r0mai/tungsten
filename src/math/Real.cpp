
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

Real nextReal(Real real) {
	mpfr_nextabove(real.backend().data());
	return real;
}

Real previousReal(Real real) {
	mpfr_nextbelow(real.backend().data());
	return real;
}

size_t getByteCount(const Real& real) {
	return sizeof(mp_limb_t) * (real.backend().data()->_mpfr_prec / 8);
}

}} //namespace tungsten::math
