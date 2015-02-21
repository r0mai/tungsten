
#ifndef MATH_SPECIALMATHFUNCTIONS_HPP_
#define MATH_SPECIALMATHFUNCTIONS_HPP_

#include "Integer.hpp"
#include "Rational.hpp"
#include "Real.hpp"

#include <boost/optional.hpp>

namespace tungsten { namespace math {

/*
 * gamma[1/2 + n] = (a/b)*Sqrt[Pi]
 * this function returns a/b
 */
Rational gammaForHalfsSqrtPiRatio(long n);

/*
 * Returns nan on negative integers
 */
Real gamma(const Real& arg);

Integer floor(const Real& arg);
Integer ceiling(const Real& arg);

/*
 * On half integer cases, it rounds to even integer
 */
Integer round(const Real& arg);


/*
 * Find a rough rational approximation
 */
Rational findRationalNear(const Real& arg);

/*
 * Get continued fraction of a Real
 */
std::vector<Integer> getContinuedFraction(const Real& arg);

/*
 * Evaluate a continued fraction
 */
Rational evaluateContinuedFraction(std::vector<Integer> cf);

/*
 * Returns a valid optional if base^(1/n) is an integer
 */
boost::optional<Integer> tryNthRoot(const Integer& base, unsigned long n);

}} //namespace tungsten::math

#endif /* MATH_SPECIALMATHFUNCTIONS_HPP_ */
