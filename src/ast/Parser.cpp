
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

Node makeReal(double r) {
	return Node::makeReal(r);
}

Node makeString(const std::vector<char>& v){
	return Node::makeString( v.begin(), v.end() );
}

Node makeIdentifier(const std::vector<char>& v){
	return Node::makeIdentifier( v.begin(), v.end() );
}

Node makeFunction(const std::string& s, const Node& n1, const Node& n2){
	return Node::makeFunctionCall(s, {n1, n2} );
}

typedef boost::spirit::ascii::blank_type delimiter;

template<class Iterator>
struct TungstenGrammar : boost::spirit::qi::grammar<Iterator, Node(), delimiter> {

	TungstenGrammar() : TungstenGrammar::base_type(start) {
		using qi::_1;
		start %= powerExpression.alias();
		primary %= approximate | exact | parenthesis | stringLiteral | variable;
		approximate = realParser[ qi::_val = phx::bind(&makeReal, _1) ];
		exact = integerParser[ qi::_val = phx::bind(&Node::makeRational<math::Rational>, _1) ];
		parenthesis = ( '(' >> start >> ')' );
		stringLiteral = '"' >> (*qi::alnum)[ qi::_val = phx::bind(&makeString , _1) ] >> '"';
		
		
		additiveExpression = 
			primary[qi::_val = _1] >> *(
			'+' >> primary[phx::bind(&makeFunction, "Plus", qi::_val, _1) ] |
			'-' >> primary[phx::bind(&makeFunction, "Minus", qi::_val, _1) ]
		);

		
		multiplicativeExpression = 
			additiveExpression[qi::_val = _1] >> *(
			'*' >> additiveExpression[qi::_val = phx::bind(&makeFunction, "Times", qi::_val, _1 )] |
			'/' >> additiveExpression[qi::_val = phx::bind(&makeFunction, "Divide", qi::_val, _1)]
			);

		
		powerExpression = 
			multiplicativeExpression[qi::_val = _1] >> *(
			'^' >> multiplicativeExpression[qi::_val = phx::bind(&makeFunction, "Pow", qi::_val, _1) ]
			);
		
	//	variable = (*qi::alnum)[qi::_val = phx::bind(&makeIdentifier , _1) ];
	}


	qi::uint_parser< math::Rational > integerParser;
	qi::real_parser< double, qi::strict_ureal_policies<double> > realParser;
	
	qi::rule<Iterator, Node(), delimiter> start;
	qi::rule<Iterator, Node(), delimiter> primary;
	qi::rule<Iterator, Node(), delimiter> functionCall;
	qi::rule<Iterator, Node(), delimiter> variable;
	qi::rule<Iterator, Node(), delimiter> parenthesis;
	qi::rule<Iterator, Node(), delimiter> exact;
	qi::rule<Iterator, Node(), delimiter> approximate;
	qi::rule<Iterator, Node(), delimiter> text;
	qi::rule<Iterator, Node(), delimiter> stringLiteral;
	qi::rule<Iterator, Node(), delimiter> sign;
	qi::rule<Iterator, Node(), delimiter> multiplicativeExpression;
	qi::rule<Iterator, Node(), delimiter> additiveExpression;
	qi::rule<Iterator, Node(), delimiter> powerExpression;

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


}} //namespace tungsten::ast

