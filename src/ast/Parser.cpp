
#include "Parser.hpp"
#include "math/Rational.hpp"
#include "math/Real.hpp"

#include <cassert>

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>

namespace tungsten { namespace ast {

namespace spirit = boost::spirit;
namespace qi = spirit::qi;
namespace phx = boost::phoenix;

//FIXME: get rid of this global
static const Identifier parenthesesIdentityFunction("#");

void makeIdentifier(Node& result, const std::vector<char>& name) {
	result = Node::makeIdentifier(name.begin(), name.end());
}

void makeInteger(Node& result, const math::Integer& number) {
	result = Node::makeRational(number);
}

void makeReal(Node& result, const math::Real& number) {
	result = Node::makeReal(number);
}

void makeString(Node& result, const String& string) {
	result = Node::makeString(string);
}

void removeParenthesesIdentityFunction(Node& node) {
	assert( node.isFunctionCall() );
	assert( node.getFunctionCall().getFunction().isIdentifier() );
	assert( node.getFunctionCall().getFunction().getIdentifier() == parenthesesIdentityFunction );
	assert( node.getFunctionCall().getOperands().size() == 1 );

	node = Node(node.getFunctionCall().getOperands().front());
}

void removeIfParenthesesIdentityFunction(Node& node) {

	if ( 	node.isFunctionCall() &&
			node.getFunctionCall().getFunction().isIdentifier() &&
			node.getFunctionCall().getFunction().getIdentifier() == parenthesesIdentityFunction )
	{
		removeParenthesesIdentityFunction(node);
	}
}

//rhs by value, so removeIfParenthesesIdentityFunction can manipulate it
void leftAssociativeListableOperator(const Identifier& functionName, Node& result, Node rhs) {

	removeIfParenthesesIdentityFunction(rhs);

	if ( result.isFunctionCall() && result.getFunctionCall().getFunction().isIdentifier() ) {
		const Identifier& functionIdentifier = result.getFunctionCall().getFunction().getIdentifier();

		if ( functionIdentifier == functionName ) {
			result.getFunctionCall().getOperands().push_back(rhs);
			return;
		} else if ( functionIdentifier == parenthesesIdentityFunction ) {
			removeParenthesesIdentityFunction( result );
			//Fallthrough
		}

	}
	result = Node::makeFunctionCall( functionName, {result, rhs} );
}

void rightAssociativeOperator(const Identifier& functionName, Node& result, Node rhs) {
	removeIfParenthesesIdentityFunction(result);
	removeIfParenthesesIdentityFunction(rhs);

	result = Node::makeFunctionCall( functionName, {result, rhs} );
}

void operatorPlus(Node& result, const Node& rhs) {
	leftAssociativeListableOperator( "Plus", result, rhs );
}

void operatorMinus(Node& result, Node rhs) {
	removeIfParenthesesIdentityFunction(rhs);
	operatorPlus( result, Node::makeFunctionCall("Times", {Node::makeRational(-1), rhs}) );
}

void operatorTimes(Node& result, const Node& rhs) {
	leftAssociativeListableOperator( "Times", result, rhs );
}

void operatorDivide(Node& result, Node rhs) {
	removeIfParenthesesIdentityFunction(rhs);
	operatorTimes( result, Node::makeFunctionCall("Power", {rhs, Node::makeRational(-1)}) );
}

void operatorPower(Node& result, const Node& rhs) {
	rightAssociativeOperator( "Power", result, rhs );
}

void operatorParentheses(Node& result, const Node& expression) {
	//Don't do anything for multiple, paralell parentheses
	if ( expression.isFunctionCall() && expression.getFunctionCall().getFunction() == Node::makeIdentifier(parenthesesIdentityFunction) ) {
		result = expression;
	} else {
		result = Node::makeFunctionCall( parenthesesIdentityFunction, {expression} );
	}
}

void operatorUnaryMinus(Node& result, const Node& operand) {
	//TODO "- 1" should be parsed as -1 directly (and not Times[-1, 1] (low priority)
	result = Node::makeRational(-1);
	operatorTimes(result, operand);
	operatorParentheses(result, result);
}

void createFunctionCallFromString(Node& result, const std::string& name) {
	result = Node::makeFunctionCall( Node::makeIdentifier(name) );
}

void createFunctionCallFromVector(Node& result, const std::vector<char>& name) {
	createFunctionCallFromString(result, std::string(name.begin(), name.end()));
}

void fillFunctionCall(Node& result, const std::vector<Node>& operands) {
	assert( result.isFunctionCall() );
	assert( result.getFunctionCall().getOperands().empty() );
	result.getFunctionCall().getOperands() = operands;
}

void finishingTouches(Node& result, const Node& wholeExpression) {
	result = wholeExpression;
	removeIfParenthesesIdentityFunction(result);
}

typedef boost::spirit::ascii::blank_type delimiter;

template<class Iterator>
struct TungstenGrammar : boost::spirit::qi::grammar<Iterator, Node(), delimiter> {

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

		expression = additiveExpression[phx::bind(&finishingTouches, _val, _1)];

		//Tree : ---

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
				(alpha | char_('$') | char_('_') ) >>
				*(alnum | char_('$') | char_('_'));

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
				eps[phx::bind(&createFunctionCallFromString, _val, "List")] >>
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
	qi::real_parser< double, qi::strict_real_policies<double> > realParser;


	qi::rule<Iterator, Node(), delimiter> start;
	qi::rule<Iterator, Node(), delimiter> expression;

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

