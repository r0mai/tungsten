
#include "Parser.hpp"

//#include <boost/phoenix/function.hpp>
//#include <boost/spirit/include/qi.hpp>

namespace tungsten { namespace ast {

//struct MakeInt {
//	template <typename T>
//	struct result { typedef Node type; };
//
//	Node operator()(int x) const
//	{
//		return Node::makeRational(x);
//	}
//};
//
//boost::phoenix::function<MakeInt> makeInt;
//
//template<class Iterator>
//struct TungstenGrammar : boost::spirit::qi::grammar<Iterator, Node(), boost::spirit::ascii::space_type> {
//
//	namespace qi = boost::spirit::qi;
//	namespace ascii = boost::spirit::ascii;
//	namespace phx = boost::phoenix;
//
//	TungstenGrammar() : TungstenGrammar::base_type(primary) {
//		primary = qi::int_[ qi::_val = makeInt(qi::_1) ];
//	}
//
//	qi::rule<Iterator, Node(), ascii::blank_type> primary;
//
//};

boost::optional<Node> parseInput(const std::string& /*input*/) {
	return boost::optional<Node>{};
}


}} //namespace tungsten::ast

