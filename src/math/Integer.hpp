

#ifndef MATH_INTEGER_HPP_
#define MATH_INTEGER_HPP_

#include <cassert>
#include <string>
#include <limits>

#include <boost/multiprecision/gmp.hpp>

namespace tungsten { namespace math {

typedef boost::multiprecision::mpz_int Integer;

//Deprecated, replaced by fits<T>
bool fitsUL(const Integer& integer);
bool fitsSL(const Integer& integer);

//Deprecated, replaced by as<T>
unsigned long asUL(const Integer& integer);
signed long asSL(const Integer& integer);

template<class T>
bool fits(const Integer& integer) {

	static_assert( std::numeric_limits<T>::is_specialized, "fits<T>(Integer) called with non arithmetic T" );

	return integer <= std::numeric_limits<T>::max() &&
			integer >= std::numeric_limits<T>::min();
}

template<class T>
T as(const Integer& integer) {
	assert(fits<T>(integer));
	return integer.convert_to<T>();
}

Integer power(const Integer& base, unsigned long exponent);

std::string toString(const Integer& integer);

}} //namespace tungsten::math


#endif /* MATH_INTEGER_HPP_

 */
