
#include "Integer.hpp"

#include <sstream>

namespace tungsten { namespace math {

std::string Integer::toString() const {
	std::stringstream ss;
	ss << *this;
	return ss.str();
}

Integer power(const Integer& base, unsigned long exponent) {
	Integer result;
	mpz_pow_ui(result.get_mpz_t(), base.get_mpz_t(), exponent);
	return result;
}

}} //namespace tungsten::math
