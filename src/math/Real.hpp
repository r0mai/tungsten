

#ifndef MATH_REAL_HPP_
#define MATH_REAL_HPP_

#include <gmpxx.h>

#include <utility>

namespace tungsten { namespace math {

class Real : public mpf_class {
public:

	template<class... Ts>
	Real(Ts&&... args) : mpf_class(std::forward<Ts>(args)...) {}
};

}} //namespace tungsten::math


#endif /* MATH_REAL_HPP_ */
