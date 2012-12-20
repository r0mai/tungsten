

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

	bool isInteger() const {
		return get_den() == 1;
	}

	Integer asInteger() const {
		assert( isInteger() );
		return get_num();
	}

	std::string toString() const;

};

}} //namespace tungsten::math


#endif /* MATH_RATIONAL_HPP_ */
