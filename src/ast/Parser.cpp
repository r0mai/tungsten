
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

void makeFunction(const std::string& s, Node& n1, const Node& n2){
	if( n1.isFunctionCall() && Node::makeIdentifier(s) == n1.getFunctionCall().getFunction() ) {
			n1.getFunctionCall().getOperands().push_back(n2);
	} else {
		n1 = Node::makeFunctionCall(s, {n1, n2} );
	}
}

Node addToFunction(const Node& n1, const boost::optional<std::vector<Node> >& nodes) {
	if(nodes)
	    return Node::makeFunctionCall(n1, *nodes);
	else
		return Node::makeFunctionCall(n1);
}

typedef boost::spirit::ascii::blank_type delimiter;

template<class Iterator>
struct TungstenGrammar : boost::spirit::qi::grammar<Iterator, Node(), delimiter> {

	TungstenGrammar() : TungstenGrammar::base_type(start) {

		using qi::_1;
		using qi::_val;

		start %= expression.alias();
		expression %= functionCall | additiveExpression;
		primary %=  approximate | exact | parenthesis | stringLiteral | identifier;

		identifier = (*qi::ascii::alpha) [_val = phx::bind(&makeIdentifier , _1) ];
		approximate = realParser[_val = phx::bind(&makeReal, _1) ];
//		exact = integerParser[_val = phx::bind(&Node::makeRational<math::Rational>, _1) ];
		parenthesis = ( '(' >> start >> ')' );
		stringLiteral = '"' >> (*qi::alnum)[_val = phx::bind(&makeString , _1)] >> '"';
		
		functionCall = 
            additiveExpression[_val = _1] >> '[' >> -(expression % ',')[_val = phx::bind(&addToFunction, _val, _1)] >> ']';
            
		additiveExpression =
			multiplicativeExpression[_val = _1] >> *(
			'+' >> multiplicativeExpression[phx::bind(&makeFunction, "Plus", _val, _1) ] |
			'-' >> multiplicativeExpression[phx::bind(&makeFunction, "Minus", _val, _1) ]
			);

		multiplicativeExpression =
			powerExpression[_val = _1] >> *(
			'*' >> powerExpression[phx::bind(&makeFunction, "Times", _val, _1 )] |
			'/' >> powerExpression[phx::bind(&makeFunction, "Divide", _val, _1)]
			);
		
		powerExpression = 
			primary[_val = _1] >> *(
			'^' >> primary[phx::bind(&makeFunction, "Power", _val, _1) ]
			);
	}


	qi::uint_parser< math::Rational > integerParser;
	qi::real_parser< double, qi::strict_ureal_policies<double> > realParser;
	
	qi::rule<Iterator, Node(), delimiter> start;
	qi::rule<Iterator, Node(), delimiter> primary;
	qi::rule<Iterator, Node(), delimiter> functionCall;
	qi::rule<Iterator, Node(), delimiter> identifier;
	qi::rule<Iterator, Node(), delimiter> parenthesis;
	qi::rule<Iterator, Node(), delimiter> exact;
	qi::rule<Iterator, Node(), delimiter> approximate;
	qi::rule<Iterator, Node(), delimiter> text;
	qi::rule<Iterator, Node(), delimiter> stringLiteral;
	qi::rule<Iterator, Node(), delimiter> sign;
	qi::rule<Iterator, Node(), delimiter> multiplicativeExpression;
	qi::rule<Iterator, Node(), delimiter> additiveExpression;
	qi::rule<Iterator, Node(), delimiter> powerExpression;
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


}} //namespace tungsten::ast

