

#ifndef MATH_RATIONAL_HPP_
#define MATH_RATIONAL_HPP_

#include <cassert>
#include <string>

#include <boost/optional.hpp>
#include <boost/multiprecision/gmp.hpp>
#include <boost/type_traits/has_nothrow_copy.hpp>

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

template<class T>
boost::optional<T> rationalToBuiltinInteger(const Rational& rational) {
	if ( isInteger(rational) && fits<T>( asInteger(rational) ) ) {
		return as<T>( asInteger(rational) );
	}
	return boost::none_t();
}

}} //namespace tungsten::math

namespace boost {

template <>
struct has_nothrow_copy<tungsten::math::Rational> : mpl::true_ {};

}

#endif /* MATH_RATIONAL_HPP_ */
