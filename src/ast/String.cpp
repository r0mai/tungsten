
#include "String.hpp"

#include <sstream>

namespace tungsten { namespace ast {

std::string String::toString() const {
	std::stringstream ss;
	ss << '"' << static_cast<std::string>(*this) << '"';
	return ss.str();
}

std::ostream& operator<<(std::ostream& os, const String& string) {
	os << string.toString();
	return os;
}

}} //namespace tungsten::ast
