
#include "NodeToFullForm.hpp"

#include <iterator>
#include <boost/spirit/include/karma.hpp>
#include <boost/spirit/include/phoenix.hpp>

namespace tungsten { namespace io {

namespace karma = boost::spirit::karma;

template<class Iterator>
struct FullFormGrammar : karma::grammar<Iterator, ast::Node()> {
	FullFormGrammar() : FullFormGrammar::base_type(start) {
		using karma::_1;
		using karma::char_;
		using karma::_val;
		start = char_[_1 = 'c'];

	}

	karma::rule<Iterator, ast::Node()> start;
	karma::rule<Iterator, char> test;
};


FullFormString NodeToFullForm(const ast::Node& node) {
	FullFormGrammar<std::back_insert_iterator<FullFormString>> fullFormGrammar;
	FullFormString result;
	std::back_insert_iterator<FullFormString> sink(result);
	karma::generate(sink, fullFormGrammar, node);
	return result;
}

}} //namespace tungsten::io

