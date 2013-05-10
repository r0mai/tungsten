

#ifndef MATH_REAL_HPP_
#define MATH_REAL_HPP_

#include <boost/multiprecision/mpfr.hpp>

namespace tungsten { namespace math {

typedef boost::multiprecision::mpfr_float Real;

std::string toString(const Real& real);

Real power(const Real& base, const Real& exponent);

Real nextReal(Real real);

Real previousReal(Real real);

}} //namespace tungsten::math


#endif /* MATH_REAL_HPP_ */
