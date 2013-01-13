
#include "Integer.hpp"

#include <sstream>

namespace tungsten { namespace math {

Integer Integer::toThePower(unsigned long exponent) const {
	Integer result;
	mpz_pow_ui(result.get_mpz_t(), this->get_mpz_t(), exponent);
	return result;
}

std::string Integer::toString() const {
	std::stringstream ss;
	ss << *this;
	return ss.str();
}

}} //namespace tungsten::math
