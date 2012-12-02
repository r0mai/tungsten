
#include "AstParser.hpp"

//#include <boost/phoenix/function.hpp>
//#include <boost/spirit/include/qi.hpp>

namespace tungsten {

//struct MakeInt {
//	template <typename T>
//	struct result { typedef AstNode type; };
//
//	AstNode operator()(int x) const
//	{
//		return AstNode::makeRational(x);
//	}
//};
//
//boost::phoenix::function<MakeInt> makeInt;
//
//template<class Iterator>
//struct TungstenGrammar : boost::spirit::qi::grammar<Iterator, AstNode(), boost::spirit::ascii::space_type> {
//
//	namespace qi = boost::spirit::qi;
//	namespace ascii = boost::spirit::ascii;
//	namespace phx = boost::phoenix;
//
//	TungstenGrammar() : TungstenGrammar::base_type(primary) {
//		primary = qi::int_[ qi::_val = makeInt(qi::_1) ];
//	}
//
//	qi::rule<Iterator, AstNode(), ascii::blank_type> primary;
//
//};

boost::optional<AstNode> parseInput(const std::string& input) {
	return boost::optional<AstNode>{};
}


} //namespace tungsten

