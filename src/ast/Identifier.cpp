
#include "Identifier.hpp"

namespace tungsten { namespace ast {

std::string Identifier::toString() const { return *this; }

std::size_t Identifier::getByteCount() const {
	return sizeof(char)*capacity();
}

std::ostream& operator<<(std::ostream& os, const Identifier& identifier) {
	os << identifier.toString();
	return os;
}

}} //namespace tungsten::ast
