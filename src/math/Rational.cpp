
#include "Rational.hpp"

#include <sstream>

namespace tungsten { namespace math {

std::string Rational::toString() const {
	std::stringstream ss;
	ss << *this;
	return ss.str();
}

}} //namespace tungsten::math
