
#include "Real.hpp"

#include <sstream>

namespace tungsten { namespace math {

std::string Real::toString() const {
	std::stringstream ss;
	ss << *this;
	return ss.str();
}

}} //namespace tungsten::math
