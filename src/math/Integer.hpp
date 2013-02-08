

#ifndef MATH_INTEGER_HPP_
#define MATH_INTEGER_HPP_

#include <cassert>
#include <string>

#include <boost/multiprecision/gmp.hpp>

namespace tungsten { namespace math {

typedef boost::multiprecision::mpz_int Integer;

bool fitsUL(const Integer& integer);
bool fitsSL(const Integer& integer);

unsigned long asUL(const Integer& integer);
signed long asSL(const Integer& integer);

Integer power(const Integer& base, unsigned long exponent);

std::string toString(const Integer& integer);

}} //namespace tungsten::math


#endif /* MATH_INTEGER_HPP_

 */
