

#ifndef MATH_RATIONAL_HPP_
#define MATH_RATIONAL_HPP_

#include <gmpxx.h>

#include <cassert>
#include <utility>
#include <string>

#include "Integer.hpp"

namespace tungsten { namespace math {

class Rational : public mpq_class {
public:

	template<class... Ts>
	Rational(Ts&&... args) : mpq_class(std::forward<Ts>(args)...) {}

	Integer numerator() const { return get_num(); }
	Integer denominator() const { return get_den(); }

	bool isInteger() const { return denominator() == 1; }

	Integer asInteger() const {
		assert( isInteger() );
		return get_num();
	}

	Rational reciprocal() const;
	Rational toThePower(long exponent) const;

	std::string toString() const;

};

}} //namespace tungsten::math


#endif /* MATH_RATIONAL_HPP_ */
