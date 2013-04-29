
#include "String.hpp"

#include <sstream>

#include <boost/range/algorithm.hpp>
#include <boost/range/adaptors.hpp>

namespace tungsten { namespace ast {

struct StringEscaper {


	typedef std::string result_type;

	std::string operator()(char ch) const {
		switch (ch) {
		default: return std::string(1, ch);
		case '\\': return "\\\\";
		case '\"': return "\\\"";
		//case '\'': return "\\'";
		case '\a': return "\\a";
		case '\b': return "\\b";
		case '\n': return "\\n";
		case '\r': return "\\r";
		case '\f': return "\\f";
		case '\t': return "\\t";
		case '\v': return "\\v";
		}
	}
};

std::string String::toString() const {

	std::stringstream ss;
	ss << '"';
	boost::copy( *this | boost::adaptors::transformed( StringEscaper{} ),
			std::ostream_iterator<std::string>(ss) );
	ss << '"';
	return ss.str();
}

const std::string& String::getRawString() const {
	return *this;
}

std::string& String::getRawString() {
	return *this;
}

std::ostream& operator<<(std::ostream& os, const String& string) {
	os << string.toString();
	return os;
}

}} //namespace tungsten::ast
