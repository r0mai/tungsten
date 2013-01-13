
#include "Real.hpp"

#include <cassert>
#include <sstream>

namespace tungsten { namespace math {

std::string Real::toString() const {
	std::stringstream ss;
	ss << *this;
	return ss.str();
}

Real Real::toThePower(const Real& /*exponent*/) const {
	const Real& base = *this;

	assert(false && "Real::toThePower not yet implemented");

	return *this;
}

}} //namespace tungsten::math
