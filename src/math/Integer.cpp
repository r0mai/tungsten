
#include "Integer.hpp"

#include <sstream>
#include <limits>

namespace tungsten { namespace math {

bool fitsUL(const Integer& integer) {
	return integer <= std::numeric_limits<unsigned long>::max() &&
			integer >= std::numeric_limits<unsigned long>::min();
}

bool fitsSL(const Integer& integer) {
	return integer <= std::numeric_limits<signed long>::max() &&
			integer >= std::numeric_limits<signed long>::min();
}

unsigned long asUL(const Integer& integer) {
	assert(fitsUL(integer));
	return integer.convert_to<unsigned long>();
}

signed long asSL(const Integer& integer) {
	assert(fitsSL(integer));
	return integer.convert_to<signed long>();
}

std::string toString(const Integer& integer) {
	return integer.str();
}

Integer power(const Integer& base, unsigned long exponent) {
	//TODO without backend
	Integer result;
	mpz_pow_ui(result.backend().data(), base.backend().data(), exponent);
	return result;
}

}} //namespace tungsten::math
