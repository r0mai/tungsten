

#ifndef MATH_REAL_HPP_
#define MATH_REAL_HPP_

#include <boost/multiprecision/mpfr.hpp>
#include <boost/type_traits/has_nothrow_copy.hpp>

namespace tungsten { namespace math {

typedef boost::multiprecision::mpfr_float Real;

std::string toString(const Real& real);

Real power(const Real& base, const Real& exponent);

bool isInteger(const Real& n);

Real nextReal(Real real);

Real previousReal(Real real);

}} //namespace tungsten::math

namespace boost {

template <>
struct has_nothrow_copy<tungsten::math::Real> : mpl::true_ {};

}

#endif /* MATH_REAL_HPP_ */
