
#include "specialMathFunctions.hpp"
#include <cassert>

namespace tungsten { namespace math {

Rational gammaForHalfsSqrtPiRatio(long n) {
	if ( n > 0 ) {
		return Rational( factorial2(2*n-1), power(Integer(2), static_cast<unsigned long>(n)) );
	} else if ( n < 0 ) {
		return Rational( power(Integer(-2), static_cast<unsigned long>(-n)), factorial2(2*-n-1) );
	} else { //seperate case, because factorial2(-1) = 1 is non trivial
		assert( n == 0 );
		return 1;
	}
}

Real gamma(const Real& arg) {
	Real result;
	mpfr_gamma( result.backend().data(), arg.backend().data(), MPFR_RNDN );
	return result;
}

}} //namespace tungsten::math
