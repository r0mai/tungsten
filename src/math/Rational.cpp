
#include "Rational.hpp"

#include <sstream>
#include <utility>

namespace tungsten { namespace math {

Integer numerator(const Rational& rational) {
	return boost::multiprecision::numerator(rational);
}

Integer denominator(const Rational& rational) {
	return boost::multiprecision::denominator(rational);
}

bool isInteger(const Rational& rational) {
	return denominator(rational) == 1;
}

Integer asInteger(const Rational& rational) {
	assert( isInteger(rational) );
	return numerator(rational);
}

Rational reciprocal(const Rational& rational) {
	//TODO optimize
	return 1/rational;
}

Rational power(const Rational& base, long exponent) {
	Integer baseNumerator = numerator(base);
	Integer baseDenominator = denominator(base);

	if ( exponent < 0 ) {
		std::swap( baseNumerator, baseDenominator );
		exponent = -exponent;
	}

	return Rational(
			power(baseNumerator, static_cast<unsigned long>(exponent)),
			power(baseDenominator, static_cast<unsigned long>(exponent))
			);
	//TOOD needs canonicalize?
}

std::string toString(const Rational& rational) {
	return rational.str();
}

size_t getByteCount(const Rational& rational){
	//maybe _mp_alloc here?
	return mpq_numref(rational.backend().data())->_mp_alloc*sizeof(mp_limb_t) + mpq_denref(rational.backend().data())->_mp_alloc*sizeof(mp_limb_t);
}

}} //namespace tungsten::math
