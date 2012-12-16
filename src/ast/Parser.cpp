
#include "Parser.hpp"
#include "math/Rational.hpp"
#include "math/Real.hpp"

//#include <boost/phoenix/function.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>

namespace tungsten { namespace ast {
namespace spirit = boost::spirit;
namespace qi = spirit::qi;
namespace phx = boost::phoenix;

Node makeRational(const math::Rational& r) {
	return Node::makeRational(r);
}

Node makeReal(const math::Real& r) {
	return Node::makeReal(r);
}

template<class Iterator>
struct TungstenGrammar : boost::spirit::qi::grammar<Iterator, Node(), boost::spirit::ascii::blank_type> {
typedef boost::spirit::ascii::blank_type delimiter;


TungstenGrammar() : TungstenGrammar::base_type(start) {
	using qi::_1;
	start %= constant | parenthesis;
//	approximate = realParser[ qi::_val = phx::bind(&makeReal, _1) ];
    constant = integerParser[ qi::_val = phx::bind(&makeRational, _1) ];
    parenthesis = ( '(' >> start >> ')' );
}
	

qi::uint_parser< math::Rational > integerParser;
qi::real_parser< math::Real > realParser;

qi::rule<Iterator, Node(), delimiter> start;
qi::rule<Iterator, Node(), delimiter> primary;
qi::rule<Iterator, Node(), delimiter> functionCall;
qi::rule<Iterator, Node(), delimiter> variable;
qi::rule<Iterator, Node(), delimiter> parenthesis;
qi::rule<Iterator, Node(), delimiter> constant;
qi::rule<Iterator, Node(), delimiter> approximate;
qi::rule<Iterator, Node(), delimiter> expression;

};

boost::optional<Node> parseInput(const std::string& input) {
	Node result;
	
	std::string::const_iterator begin = input.cbegin();
	std::string::const_iterator end = input.cend();
	
	TungstenGrammar<std::string::const_iterator> grammar;
	
	bool success = qi::phrase_parse(
		begin, end,
		grammar,
		spirit::ascii::blank,
		result);
	if(success && begin == end){
		return result;
	} else {
		return boost::optional<Node>();
	}
}


}
} //namespace tungsten::ast

