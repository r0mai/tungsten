
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

Rational Rational::toThePower(long exponent) const {

	Integer numerator = this->numerator();
	Integer denominator = this->denominator();

	if ( exponent < 0 ) {
		std::swap( numerator, denominator );
		exponent = -exponent;
	}

	Rational result(numerator.toThePower(exponent), denominator.toThePower(exponent));
	result.canonicalize();

	return result;
}

std::string Rational::toString() const {
	std::stringstream ss;
	ss << *this;
	return ss.str();
}

}} //namespace tungsten::math
