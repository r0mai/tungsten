
#include "mathFunctions.hpp"
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

Integer floor(const Real& arg) {
    Real resultReal;
    Integer resultInteger;
    mpfr_floor( resultReal.backend().data(), arg.backend().data() );
    assert( mpfr_integer_p( resultReal.backend().data() ) != 0 );
    mpfr_get_z( resultInteger.backend().data(), resultReal.backend().data(), MPFR_RNDN );
    return resultInteger;
}

Integer ceiling(const Real& arg) {
    Real resultReal;
    Integer resultInteger;
    mpfr_ceil( resultReal.backend().data(), arg.backend().data() );
    assert( mpfr_integer_p( resultReal.backend().data() ) != 0 );
    mpfr_get_z( resultInteger.backend().data(), resultReal.backend().data(), MPFR_RNDN );
    return resultInteger;
}

Integer round(const Real& arg) {
    Real resultReal;
    Integer resultInteger;
    mpfr_rint( resultReal.backend().data(), arg.backend().data(), MPFR_RNDN );
    assert( mpfr_integer_p( resultReal.backend().data() ) != 0 );
    mpfr_get_z( resultInteger.backend().data(), resultReal.backend().data(), MPFR_RNDN );
    return resultInteger;
}


}} //namespace tungsten::math

