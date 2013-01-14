
#include "Real.hpp"

#include <mpfr.h>

#include <cassert>
#include <sstream>

namespace tungsten { namespace math {

std::string Real::toString() const {
	std::stringstream ss;
	ss << *this;
	return ss.str();
}

Real Real::toThePower(const Real& exponent) const {
	const Real& base = *this;

	mpfr_t mpfrBase, mpfrExponent, mpfrResult;
	mpfr_init_set_f(mpfrBase, base.get_mpf_t(), MPFR_RNDN);
	mpfr_init_set_f(mpfrExponent, exponent.get_mpf_t(), MPFR_RNDN);
	mpfr_init(mpfrResult);

	mpfr_pow(mpfrResult, mpfrBase, mpfrExponent, MPFR_RNDN);
	Real result;
	mpfr_get_f(result.get_mpf_t(), mpfrResult, MPFR_RNDN);

	mpfr_clear(mpfrResult);
	mpfr_clear(mpfrExponent);
	mpfr_clear(mpfrBase);

	return result;
}

}} //namespace tungsten::math
