
#ifndef UTIL_RANGETOSTRING_HPP_
#define UTIL_RANGETOSTRING_HPP_

#include <sstream>
#include <string>
#include <ostream>

#include <boost/range.hpp>

namespace tungsten { namespace util {

template<class Range, class PrintFunction>
void rangeToStream(std::ostream& os,
		const Range& range,
		PrintFunction printFunction,
		const std::string& separator)
{
	typename boost::range_iterator<const Range>::type first = boost::begin(range);
	typename boost::range_iterator<const Range>::type last = boost::end(range);

	if ( first == last ) { return; }

	os << printFunction(*first++);

	while ( first != last ) {
		os << separator << printFunction(*first++);
	}

}

template<class Range>
void rangeToStream(std::ostream& os,
		const Range& range,
		const std::string& separator)
{
	rangeToStream(os, range, [](const typename Range::value_type& v) { return v; }, separator );
}

template<class Range, class PrintFunction>
std::string rangeToString(const Range& range, PrintFunction printFunction, const std::string& separator) {
	std::ostringstream ss;
	rangeToStream(ss, range, printFunction, separator);
	return ss.str();
}

template<class Range>
std::string rangeToString(const Range& range, const std::string& separator) {
	return rangeToString(range, [](const typename Range::value_type& v) { return v; }, separator );
}


}} //namespace tungsten::util

#endif /* UTIL_RANGETOSTRING_HPP_ */
