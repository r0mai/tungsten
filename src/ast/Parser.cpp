
#include "Parser.hpp"
#include "math/Rational.hpp"
#include "math/Real.hpp"
#include "eval/Identifiers.hpp"

#include <cassert>

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>

namespace tungsten { namespace ast {
/** 
\brief Main Namespace for Abstract Syntax Tree Building

**/
namespace ids = eval::ids;

namespace spirit = boost::spirit;
namespace qi = spirit::qi;
namespace phx = boost::phoenix;

//FIXME: get rid of this global
static const Identifier parenthesesIdentityFunction("#");

void makeIdentifier(Node& result, const std::vector<char>& name) {
	result = Node::make<Identifier>(name.begin(), name.end());
}

void makeInteger(Node& result, const math::Integer& number) {
	result = Node::make<math::Rational>(number);
}

void makeReal(Node& result, const math::Real& number) {
	result = Node::make<math::Real>(number);
}

void makeString(Node& result, const String& string) {
	result = Node::make<String>(string);
}

void removeParenthesesIdentityFunction(Node& node) {
	assert( node.is<FunctionCall>() );
	assert( node.get<FunctionCall>().getFunction().is<Identifier>() );
	assert( node.get<FunctionCall>().getFunction().get<Identifier>() == parenthesesIdentityFunction );
	assert( node.get<FunctionCall>().getOperands().size() == 1 );

	node = Node(node.get<FunctionCall>().getOperands().front());
}

void removeIfParenthesesIdentityFunction(Node& node) {

	if ( 	node.is<FunctionCall>() &&
			node.get<FunctionCall>().getFunction().is<Identifier>() &&
			node.get<FunctionCall>().getFunction().get<Identifier>() == parenthesesIdentityFunction )
	{
		removeParenthesesIdentityFunction(node);
	}
}

//rhs by value, so removeIfParenthesesIdentityFunction can manipulate it
void leftAssociativeListableOperator(const Identifier& functionName, Node& result, Node rhs) {

	removeIfParenthesesIdentityFunction(rhs);

	if ( result.is<FunctionCall>() && result.get<FunctionCall>().getFunction().is<Identifier>() ) {
		const Identifier& functionIdentifier = result.get<FunctionCall>().getFunction().get<Identifier>();

		if ( functionIdentifier == functionName ) {
			result.get<FunctionCall>().getOperands().push_back(rhs);
			return;
		} else if ( functionIdentifier == parenthesesIdentityFunction ) {
			removeParenthesesIdentityFunction( result );
			//Fallthrough
		}

	}
	result = Node::make<FunctionCall>( functionName, {result, rhs} );
}

void rightAssociativeOperator(const Identifier& functionName, Node& result, Node rhs) {
	removeIfParenthesesIdentityFunction(result);
	removeIfParenthesesIdentityFunction(rhs);

	result = Node::make<FunctionCall>( functionName, {result, rhs} );
}

void operatorSet(Node& result, const Node& rhs) {
	rightAssociativeOperator( ids::Set, result, rhs );
}

void operatorPlus(Node& result, const Node& rhs) {
	leftAssociativeListableOperator( ids::Plus, result, rhs );
}

void operatorMinus(Node& result, Node rhs) {
	removeIfParenthesesIdentityFunction(rhs);
	operatorPlus( result, Node::make<FunctionCall>(ids::Times, {Node::make<math::Rational>(-1), rhs}) );
}

void operatorTimes(Node& result, const Node& rhs) {
	leftAssociativeListableOperator( ids::Times, result, rhs );
}

void operatorDivide(Node& result, Node rhs) {
	removeIfParenthesesIdentityFunction(rhs);
	operatorTimes( result, Node::make<FunctionCall>(ids::Power, {rhs, Node::make<math::Rational>(-1)}) );
}

void operatorPower(Node& result, const Node& rhs) {
	rightAssociativeOperator( ids::Power, result, rhs );
}

void operatorParentheses(Node& result, const Node& expression) {
	//Don't do anything for multiple, paralell parentheses
	if ( expression.is<FunctionCall>() && expression.get<FunctionCall>().getFunction() == Node::make<Identifier>(parenthesesIdentityFunction) ) {
		result = expression;
	} else {
		result = Node::make<FunctionCall>( parenthesesIdentityFunction, {expression} );
	}
}

void operatorUnaryMinus(Node& result, const Node& operand) {
	//TODO "- 1" should be parsed as -1 directly (and not Times[-1, 1] (low priority)
	result = Node::make<math::Rational>(-1);
	operatorTimes(result, operand);
	operatorParentheses(result, result);
}

void createFunctionCallFromString(Node& result, const std::string& name) {
	result = Node::make<FunctionCall>( Node::make<Identifier>(name) );
}

void createFunctionCallFromVector(Node& result, const std::vector<char>& name) {
	createFunctionCallFromString(result, std::string(name.begin(), name.end()));
}

void fillFunctionCall(Node& result, const std::vector<Node>& operands) {
	assert( result.is<FunctionCall>() );
	assert( result.get<FunctionCall>().getOperands().empty() );
	result.get<FunctionCall>().getOperands() = operands;
}

void finishingTouches(Node& result, const Node& wholeExpression) {
	result = wholeExpression;
	removeIfParenthesesIdentityFunction(result);
}

template<class T>
struct OnlyNumericRealPolicies : qi::strict_real_policies<T> {

    template<class Iterator>
    static bool parse_exp(Iterator& /*first*/, const Iterator& /*last*/) {
        return false;
    }

    template<class Iterator, class Attribute>
    static bool parse_exp_n(Iterator& /*first*/, const Iterator& /*last*/, const Attribute& /*attribute*/) {
        return false;
    }

    template<class Iterator, class Attribute>
    static bool parse_inf(Iterator& /*first*/, const Iterator& /*last*/, const Attribute& /*attribute*/) {
        return false;
    }

    template<class Iterator, class Attribute>
    static bool parse_nan(Iterator& /*first*/, const Iterator& /*last*/, const Attribute& /*attribute*/) {
        return false;
    }

};

typedef boost::spirit::ascii::blank_type delimiter;

template<class Iterator>
struct TungstenGrammar : boost::spirit::qi::grammar<Iterator, Node(), delimiter> {
/**
\brief Main grammar for parsing.



  \f[
    |I_2|=\left| \int_{0}^T \psi(t) 
             \left\{ 
                u(a,t)-
                \int_{\gamma(t)}^a 
                \frac{d\theta}{k(\theta,t)}
                \int_{a}^\theta c(\xi)u_t(\xi,t)\,d\xi
             \right\} dt
          \right|
  \f]
**/
	TungstenGrammar() : TungstenGrammar::base_type(start) {

		using qi::_1;
		using qi::_val;
		using qi::alpha;
		using qi::alnum;
		using qi::print;
		using qi::char_;
		using qi::eps;
		using qi::lit;

		start %= expression.alias();

		expression = equalsToExpression[phx::bind(&finishingTouches, _val, _1)];

		//Tree : ---

		equalsToExpression =
				additiveExpression[_val = _1] >>
				*(  '=' >> additiveExpression[phx::bind(&operatorSet, _val, _1)] );

		additiveExpression =
				multiplicativeExpression[_val = _1] >>
				*(  '+' >> multiplicativeExpression[phx::bind(&operatorPlus, _val, _1)] |
					'-' >> multiplicativeExpression[phx::bind(&operatorMinus, _val, _1)] );

		multiplicativeExpression =
				powerExpression[_val = _1] >>
				*(  '*' >> powerExpression[phx::bind(&operatorTimes, _val, _1)] |
					'/' >> powerExpression[phx::bind(&operatorDivide, _val, _1)] |
					!(char_('+') | char_('-')) >> powerExpression[phx::bind(&operatorTimes, _val, _1)] ); //TODO all unrary operators which can be binary operators are required here

		//right associative ( idea from : http://eli.thegreenplace.net/2009/03/14/some-problems-of-recursive-descent-parsers/ )
		powerExpression =
				primary[_val = _1] >> '^' >> powerExpression[phx::bind(&operatorPower, _val, _1)] |
				primary[_val = _1];

		//Primaries : ---
		integer = integerParser[phx::bind(&makeInteger, _val, _1)];
		real = realParser[phx::bind(&makeReal, _val, _1)];

		variable %=
				(alpha | char_('$')) >>
				*(alnum | char_('$'));

		identifier = variable[phx::bind(&makeIdentifier, _val, _1)];

		unescapedCharacters.add("\\a", '\a')("\\b", '\b')("\\f", '\f')("\\n", '\n')
                              ("\\r", '\r')("\\t", '\t')("\\v", '\v')
                              ("\\\\", '\\')/*("\\\'", '\'')*/("\\\"", '\"');

		unescapedString %=
				lit('"') >>
				*(unescapedCharacters | (print - '"')) >>
				lit('"');

		string = unescapedString[phx::bind(&makeString, _val, _1)];

		argumentList %= -(expression % ',');

		functionCall =
				(variable[phx::bind(&createFunctionCallFromVector, _val, _1)] >>
				'[' >>
				argumentList[phx::bind(&fillFunctionCall, _val, _1)] >>
				']');

		list =
				eps[phx::bind(&createFunctionCallFromString, _val, ids::List)] >>
				'{' >>
				argumentList[phx::bind(&fillFunctionCall, _val, _1)] >>
				'}';

		unaryOperator =
				'-' >> powerExpression[phx::bind(&operatorUnaryMinus, _val, _1)] |
				'+' >> powerExpression[_val = _1];

		parenthesizedExpression = '(' >> expression[phx::bind(&operatorParentheses, _val, _1)] >> ')';

		primary %= real | integer | string | unaryOperator | parenthesizedExpression | list | functionCall | identifier;

	}

	qi::int_parser< math::Integer > integerParser;
	qi::real_parser< double, OnlyNumericRealPolicies<double> > realParser;


	qi::rule<Iterator, Node(), delimiter> start;
	qi::rule<Iterator, Node(), delimiter> expression;

	qi::rule<Iterator, Node(), delimiter> equalsToExpression;
	qi::rule<Iterator, Node(), delimiter> additiveExpression;
	qi::rule<Iterator, Node(), delimiter> multiplicativeExpression;
	qi::rule<Iterator, Node(), delimiter> powerExpression;

	qi::rule<Iterator, std::vector<char>()> variable;
	qi::rule<Iterator, std::vector<Node>(), delimiter> argumentList;

	qi::symbols<String::value_type, String::value_type> unescapedCharacters;
	qi::rule<Iterator, String()> unescapedString;
	qi::rule<Iterator, Node(), delimiter> string;

	qi::rule<Iterator, Node(), delimiter> identifier;
	qi::rule<Iterator, Node(), delimiter> integer;
	qi::rule<Iterator, Node(), delimiter> real;
	qi::rule<Iterator, Node(), delimiter> functionCall;
	qi::rule<Iterator, Node(), delimiter> list;
	qi::rule<Iterator, Node(), delimiter> unaryOperator;
	qi::rule<Iterator, Node(), delimiter> parenthesizedExpression;
	qi::rule<Iterator, Node(), delimiter> primary;

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

