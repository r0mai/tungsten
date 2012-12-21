
#ifndef MATH_COMPLEX_HPP_
#define MATH_COMPLEX_HPP_

#include <complex>

#include "Integer.hpp"
#include "Rational.hpp"
#include "Real.hpp"

namespace tungsten { namespace math {

typedef std::complex<Integer> ComplexInteger;
typedef std::complex<Rational> ComplexRational;
typedef std::complex<Real> ComplexReal;

}} //namespace tungsten::math

#endif /* MATH_COMPLEX_HPP_ */
