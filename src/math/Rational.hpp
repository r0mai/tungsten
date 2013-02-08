

#ifndef MATH_RATIONAL_HPP_
#define MATH_RATIONAL_HPP_

#include <cassert>
#include <string>

#include <boost/multiprecision/gmp.hpp>

#include "Integer.hpp"

namespace tungsten { namespace math {

typedef boost::multiprecision::mpq_rational Rational;

Integer numerator(const Rational& rational);
Integer denominator(const Rational& rational);

bool isInteger(const Rational& rational);
Integer asInteger(const Rational& rational);

Rational reciprocal(const Rational& rational);
Rational power(const Rational& base, long exponent);

std::string toString(const Rational& rational);

}} //namespace tungsten::math


#endif /* MATH_RATIONAL_HPP_ */
