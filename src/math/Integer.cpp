
#include "Integer.hpp"

#include <sstream>

namespace tungsten { namespace math {

std::string toString(const Integer& integer) {
	return integer.str();
}

Integer factorial(unsigned long n) {
	Integer result;
	mpz_fac_ui(result.backend().data(), n);
	return result;
}

Integer factorial2(unsigned long n) {
	Integer result;
	mpz_2fac_ui(result.backend().data(), n);
	return result;
}

Integer power(const Integer& base, unsigned long exponent) {
	//TODO without backend
	Integer result;
	mpz_pow_ui(result.backend().data(), base.backend().data(), exponent);
	return result;
}

}} //namespace tungsten::math
