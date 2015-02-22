
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
	assert( isInteger( resultReal ) );
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

Rational findRationalNear(const Real& arg, const Real& dx) {
	const auto continuedFraction = getContinuedFraction(arg);
	Rational approximation;
	for(auto it=continuedFraction.begin()+1; it <= continuedFraction.end(); ++it) {
		approximation = evaluateContinuedFraction(continuedFraction.begin(), it);
		auto den = denominator(approximation);
		if(abs( approximation-arg ) < dx/den*den) {
			break;
		}
	}
	return approximation;
}

Rational evaluateContinuedFraction(std::vector<Integer> cf) {
	return evaluateContinuedFraction(cf.begin(), cf.end());
}

Rational evaluateContinuedFraction(std::vector<Integer>::const_iterator begin, std::vector<Integer>::const_iterator end) {
	if( begin == end ) { return 0; }
	const Integer first = *begin;
	++begin;
	if ( begin == end ) { return first; }
	return first + Rational{1} / evaluateContinuedFraction(begin, end);
}

void getContinuedFractionImpl(const Real& r, std::vector<Integer>& out) {
	Integer i = floor(r);
	Real f = r - Real{i};
	out.push_back(i);
	if (f < Real{1e-5} || (out.size() > 100)) { return; }
	getContinuedFractionImpl(1/f, out);
}

std::vector<Integer> getContinuedFraction(const Real& arg) {
	std::vector<Integer> answer;

	getContinuedFractionImpl(arg, answer);

	return answer;
}

boost::optional<Integer> tryNthRoot(const Integer& base, unsigned long n) {
	Integer result;
	if ( mpz_root(result.backend().data(), base.backend().data(), n) != 0 ) {
		return result;
	}
	return boost::none_t();
}

}} //namespace tungsten::math

