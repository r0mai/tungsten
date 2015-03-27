
#include "Complex.hpp"
#include "Real.hpp"

#include <cassert>
#include <sstream>

namespace tungsten { namespace math {

size_t getByteCount(const math::ComplexReal& real) {
	return getByteCount(std::real(real)) + getByteCount(std::imag(real));
}

size_t getByteCount(const math::ComplexRational& rational) {
	return getByteCount(std::real(rational)) + getByteCount(std::imag(rational));
}

}} // namespace tungsten::math
