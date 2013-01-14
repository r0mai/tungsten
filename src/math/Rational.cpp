
#include "Rational.hpp"

#include <sstream>
#include <utility>

namespace tungsten { namespace math {

Rational Rational::reciprocal() const {
	assert( numerator() != 0 );
	Rational result;
	mpq_inv(result.get_mpq_t(), this->get_mpq_t());
	return result;
}

std::string Rational::toString() const {
	std::stringstream ss;
	ss << *this;
	return ss.str();
}

Rational power(const Rational& base, long exponent) {
	Integer numerator = base.numerator();
	Integer denominator = base.denominator();

	if ( exponent < 0 ) {
		std::swap( numerator, denominator );
		exponent = -exponent;
	}

	Rational result(
			power(numerator, static_cast<unsigned long>(exponent)),
			power(denominator, static_cast<unsigned long>(exponent))
			);
	result.canonicalize();

	return result;
}

}} //namespace tungsten::math
