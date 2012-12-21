
#include "String.hpp"

#include <sstream>

#include <boost/range/algorithm.hpp>
#include <boost/range/adaptors.hpp>

namespace tungsten { namespace ast {

struct StringEscaper {

	typedef std::string result_type;

	std::string operator()(char ch) const {
		switch (ch) {
		default:
			return std::string(1, ch);
		case '\\':
			return "\\\\";
		case '\"':
			return "\\\"";
		case '\'':
			return "\\'";
		case '\n':
			return "\\n";
		case '\f':
			return "\\f";
		case '\t':
			return "\\t";
		case '\v':
			return "\\v";
		//TODO make sure that's all
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

std::ostream& operator<<(std::ostream& os, const String& string) {
	os << string.toString();
	return os;
}

}} //namespace tungsten::ast