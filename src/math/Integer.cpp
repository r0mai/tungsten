
#include "Integer.hpp"

#include <sstream>

namespace tungsten { namespace math {

std::string Integer::toString() const {
	std::stringstream ss;
	ss << *this;
	return ss.str();
}

}} //namespace tungsten::math
