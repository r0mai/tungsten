

#ifndef MATH_INTEGER_HPP_
#define MATH_INTEGER_HPP_

#include <gmpxx.h>

#include <cassert>

namespace tungsten { namespace math {

class Integer : public mpz_class {
public:

	template<class... Ts>
	Integer(Ts&&... args) : mpz_class(std::forward<Ts>(args)...) {}

	bool fitsUL() const { return fits_ulong_p();	}
	bool fitsSL() const { return fits_slong_p(); }

	unsigned long asUL() const { assert( fitsUL() );	return get_ui(); }
	signed long asSL() const { assert( fitsSL() ); return get_si(); }

};

}} //namespace tungsten::math


#endif /* MATH_INTEGER_HPP_

 */
