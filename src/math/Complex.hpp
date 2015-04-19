
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

size_t getByteCount(const ComplexRational& rational);
size_t getByteCount(const ComplexReal& real);

namespace detail {
template<typename T, typename U>
struct areOperandsComplex {
	static constexpr bool value =
			std::is_same<T, math::ComplexReal>::value ||
			std::is_same<T, math::ComplexRational>::value ||
			std::is_same<U, math::ComplexReal>::value ||
			std::is_same<U, math::ComplexRational>::value;
};

template<typename T, typename U>
struct areOperandsIrrational {
	static constexpr bool value =
			std::is_same<T, math::Real>::value ||
			std::is_same<T, math::ComplexReal>::value ||
			std::is_same<U, math::Real>::value ||
			std::is_same<U, math::ComplexReal>::value;
};

template<typename T>
struct RemoveComplex { using type = T; };

template<typename T>
struct RemoveComplex<std::complex<T>> { using type = T; };

template<typename T>
typename std::enable_if<!areOperandsComplex<T, T>::value, T>::type
getRealPart(const T& t) {
	return t;
}

template<typename T>
typename std::enable_if<areOperandsComplex<T, T>::value, typename RemoveComplex<T>::type>::type
getRealPart(const T& t) {
	return std::real(t);
}

template<typename T>
typename std::enable_if<!areOperandsComplex<T, T>::value, T>::type
getImaginaryPart(const T& t) {
	return T{0};
}

template<typename T>
typename std::enable_if<areOperandsComplex<T, T>::value, typename RemoveComplex<T>::type>::type
getImaginaryPart(const T& t) {
	return std::imag(t);
}


} // namespace detail

ComplexReal ln(const ComplexReal& z);
ComplexReal exp(const ComplexReal& z);
ComplexRational power(const ComplexRational& base, unsigned long exponent);
ComplexReal power(const ComplexReal& base, const ComplexReal& exponent);

}} //namespace tungsten::math

#endif /* MATH_COMPLEX_HPP_ */
