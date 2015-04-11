
#include "Complex.hpp"
#include "Real.hpp"

#include <cassert>

namespace tungsten { namespace math {

size_t getByteCount(const math::ComplexReal& real) {
	return getByteCount(std::real(real)) + getByteCount(std::imag(real));
}

size_t getByteCount(const math::ComplexRational& rational) {
	return getByteCount(std::real(rational)) + getByteCount(std::imag(rational));
}

math::Real arg(const ComplexReal& z) {
	return boost::multiprecision::atan2(std::imag(z), std::real(z));
}

math::Real abs(const ComplexReal& z) {
	math::Real realPart = z.real()*z.real();
	math::Real imagPart = z.imag()*z.imag();
	math::Real result = boost::multiprecision::sqrt(realPart+imagPart);
	return result;
}

ComplexReal ln(const ComplexReal& z) {
	const auto arg_ = arg(z);
	const auto abs_ = abs(z);

	const auto ln_abs = boost::multiprecision::log(abs_);

	return ComplexReal{ln_abs, arg_};

}

ComplexReal exp(const ComplexReal& z) {
	// E^(a+ib) = E^a * Cos[b] + i*E^a*Sin[a]

	const math::Real a = z.real();
	const math::Real b = z.imag();

	const math::Real cos_b = boost::multiprecision::cos(b);
	const math::Real sin_a = boost::multiprecision::sin(a);
	const math::Real exp_a = boost::multiprecision::exp(a);

	return ComplexReal{exp_a*cos_b, exp_a*sin_a};
}

ComplexRational power(const ComplexRational& base, unsigned long exponent) {
	// goodness me I hate this
	assert(exponent >= 0);
	ComplexRational result = math::Rational{1};
	for (long i=0;i<exponent;++i) {
		result *= base;
	}
	return result;
}

ComplexReal power(const ComplexReal& base, const ComplexReal& exponent) {
	return exp(exponent*ln(base));
}

}} // namespace tungsten::math
