

#ifndef MATH_TYPES_HPP_
#define MATH_TYPES_HPP_

#include <gmpxx.h>

namespace tungsten { namespace math {

typedef mpz_class Integer;
typedef mpq_class Rational;
typedef mpf_class Real;

}} //namespace tungsten::math

#endif /* MATH_TYPES_HPP_ */
