
#include "Parser.hpp"
#include "math/Rational.hpp"
#include "math/Real.hpp"
#include "eval/Identifiers.hpp"

#include <cassert>

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>

namespace tungsten { namespace io {
/**
\brief Main Namespace for Abstract Syntax Tree Building

**/
namespace ids = eval::ids;

namespace spirit = boost::spirit;
namespace qi = spirit::qi;
namespace phx = boost::phoenix;

//FIXME: get rid of this global
static const ast::Identifier parenthesesIdentityFunction("#");

void makeIdentifier(ast::Node& result, const std::vector<char>& name) {
	result = ast::Node::make<ast::Identifier>(name.begin(), name.end());
}

void makeInteger(ast::Node& result, const math::Integer& number) {
	result = ast::Node::make<math::Rational>(number);
}

void makeReal(ast::Node& result, const math::Real& number) {
	result = ast::Node::make<math::Real>(number);
}

void makeString(ast::Node& result, const ast::String& string) {
	result = ast::Node::make<ast::String>(string);
}

void removeParenthesesIdentityFunction(ast::Node& node) {
	assert( node.is<ast::FunctionCall>() );
	assert( node.get<ast::FunctionCall>().getFunction().is<ast::Identifier>() );
	assert( node.get<ast::FunctionCall>().getFunction().get<ast::Identifier>() == parenthesesIdentityFunction );
	assert( node.get<ast::FunctionCall>().getOperands().size() == 1 );

	//We want a copy here of the front() reference
	node = ast::Node(node.get<ast::FunctionCall>().getOperands().front());
}

void removeIfParenthesesIdentityFunction(ast::Node& node) {

	if ( 	node.is<ast::FunctionCall>() &&
			node.get<ast::FunctionCall>().getFunction().is<ast::Identifier>() &&
			node.get<ast::FunctionCall>().getFunction().get<ast::Identifier>() == parenthesesIdentityFunction )
	{
		removeParenthesesIdentityFunction(node);
	}
}


void createFunctionCall(ast::Node& result, const std::vector<ast::Node>& arguments) {
	removeIfParenthesesIdentityFunction(result);
	result = ast::Node::make<ast::FunctionCall>(result, arguments);
}


//rhs by value, so removeIfParenthesesIdentityFunction can manipulate it
void leftAssociativeListableOperator(const ast::Identifier& functionName, ast::Node& result, ast::Node rhs) {

	removeIfParenthesesIdentityFunction(rhs);

	if ( result.is<ast::FunctionCall>() && result.get<ast::FunctionCall>().getFunction().is<ast::Identifier>() ) {
		const ast::Identifier& functionIdentifier = result.get<ast::FunctionCall>().getFunction().get<ast::Identifier>();

		if ( functionIdentifier == functionName ) {
			result.getM<ast::FunctionCall>().getOperands().push_back(rhs);
			return;
		} else if ( functionIdentifier == parenthesesIdentityFunction ) {
			removeParenthesesIdentityFunction( result );
			//Fallthrough
		}

	}
	result = ast::Node::make<ast::FunctionCall>( functionName, {result, rhs} );
}

void rightAssociativeOperator(const ast::Node& function, ast::Node& result, ast::Node rhs) {
	removeIfParenthesesIdentityFunction(result);
	removeIfParenthesesIdentityFunction(rhs);

	result = ast::Node::make<ast::FunctionCall>( function, {result, rhs} );
}

void leftAssociativeOperator(const ast::Identifier& function, ast::Node& result, ast::Node rhs) {
	rightAssociativeOperator(ast::Node::make<ast::Identifier>(function), result, rhs); //currently it is the same
}

void rightAssociativeOperator(const ast::Identifier& functionName, ast::Node& result, const ast::Node& rhs) {
	rightAssociativeOperator(ast::Node::make<ast::Identifier>(functionName), result, rhs);
}

void operatorCompoundExpressionSequence(ast::Node& result, ast::Node rhs) {

	//This would basically be rightAssociativeListableOperator
	removeIfParenthesesIdentityFunction(result);

	if ( rhs.is<ast::FunctionCall>() && rhs.get<ast::FunctionCall>().getFunction().is<ast::Identifier>() ) {
		const ast::Identifier& functionIdentifier = rhs.get<ast::FunctionCall>().getFunction().get<ast::Identifier>();

		if ( functionIdentifier == ids::CompoundExpression ) {

			ast::Operands newOperands = rhs.get<ast::FunctionCall>().getOperands();
			newOperands.insert( newOperands.begin(), result );
			result = ast::Node::make<ast::FunctionCall>(ids::CompoundExpression, newOperands);
			return;
		} else if ( functionIdentifier == parenthesesIdentityFunction ) {
			removeParenthesesIdentityFunction(rhs);
			//Fallthrough
		}

	}
	result = ast::Node::make<ast::FunctionCall>(ids::CompoundExpression, {result, rhs});
}

void operatorCompoundExpressionNullEnd(ast::Node& result) {
	operatorCompoundExpressionSequence(result, ast::Node::make<ast::Identifier>(ids::Null));
//	result = ast::Node::make<ast::FunctionCall>(ids::CompoundExpression, {result, ast::Node::make<ast::Identifier>(ids::Null)});
}

void applyPostFixOperator(ast::Node& result, const ast::Node& function) {
	removeIfParenthesesIdentityFunction(result);
	result = ast::Node::make<ast::FunctionCall>(function, {result});
}

void operatorRepeated(ast::Node& result) {
	applyPostFixOperator( result, ast::Node::make<ast::Identifier>(ids::Repeated) );
}

void operatorRepeatedNull(ast::Node& result) {
	applyPostFixOperator( result, ast::Node::make<ast::Identifier>(ids::RepeatedNull) );
}

void operatorFactorial2(ast::Node& result) {
	applyPostFixOperator( result, ast::Node::make<ast::Identifier>(ids::Factorial2) );
}

void operatorFactorial(ast::Node& result) {
	applyPostFixOperator( result, ast::Node::make<ast::Identifier>(ids::Factorial) );
}

void operatorSet(ast::Node& result, const ast::Node& rhs) {
	rightAssociativeOperator( ids::Set, result, rhs );
}

void operatorSetDelayed(ast::Node& result, const ast::Node& rhs) {
	rightAssociativeOperator( ids::SetDelayed, result, rhs );
}

void operatorRule(ast::Node& result, const ast::Node& rhs) {
	rightAssociativeOperator( ids::Rule, result, rhs );
}

void operatorRuleDelayed(ast::Node& result, const ast::Node& rhs) {
	rightAssociativeOperator( ids::RuleDelayed, result, rhs );
}

void operatorPattern(ast::Node& result, const ast::Node& rhs) {
	assert(result.is<ast::Identifier>());
	result = ast::Node::make<ast::FunctionCall>( ids::Pattern, {result, rhs} );
}

void operatorPlus(ast::Node& result, const ast::Node& rhs) {
	leftAssociativeListableOperator( ids::Plus, result, rhs );
}

void operatorMinus(ast::Node& result, ast::Node rhs) {
	removeIfParenthesesIdentityFunction(rhs);
	operatorPlus( result, ast::Node::make<ast::FunctionCall>(ids::Times, {ast::Node::make<math::Rational>(-1), rhs}) );
}

void operatorTimes(ast::Node& result, const ast::Node& rhs) {
	leftAssociativeListableOperator( ids::Times, result, rhs );
}

void operatorDivide(ast::Node& result, ast::Node rhs) {
	removeIfParenthesesIdentityFunction(rhs);
	operatorTimes( result, ast::Node::make<ast::FunctionCall>(ids::Power, {rhs, ast::Node::make<math::Rational>(-1)}) );
}

void operatorPower(ast::Node& result, const ast::Node& rhs) {
	rightAssociativeOperator( ids::Power, result, rhs );
}

void operatorAnd(ast::Node& result, const ast::Node& rhs) {
	leftAssociativeListableOperator( ids::And, result, rhs );
}

void operatorOr(ast::Node& result, const ast::Node& rhs) {
	leftAssociativeListableOperator( ids::Or, result, rhs );
}

void operatorAlternatives(ast::Node& result, const ast::Node& rhs) {
	leftAssociativeListableOperator( ids::Alternatives, result, rhs );
}

void operatorGreaterEqual(ast::Node& result, const ast::Node& rhs) {
	rightAssociativeOperator( ids::GreaterEqual, result, rhs );
}

void operatorGreater(ast::Node& result, const ast::Node& rhs) {
	rightAssociativeOperator( ids::Greater, result, rhs );
}

void operatorLessEqual(ast::Node& result, const ast::Node& rhs) {
	rightAssociativeOperator( ids::LessEqual, result, rhs );
}

void operatorLess(ast::Node& result, const ast::Node& rhs) {
	rightAssociativeOperator( ids::Less, result, rhs );
}

void operatorUnequal(ast::Node& result, const ast::Node& rhs) {
	rightAssociativeOperator( ids::Unequal, result, rhs );
}

void operatorEqual(ast::Node& result, const ast::Node& rhs) {
	rightAssociativeOperator( ids::Equal, result, rhs );
}

void operatorMap(ast::Node& result, const ast::Node& rhs) {
	rightAssociativeOperator( ids::Map, result, rhs );
}

void operatorApply(ast::Node& result, const ast::Node& rhs) {
	rightAssociativeOperator( ids::Apply, result, rhs );
}

void operatorReplaceAll(ast::Node& result, const ast::Node& rhs) {
	leftAssociativeOperator( ids::ReplaceAll, result, rhs );
}

void operatorReplaceRepeated(ast::Node& result, const ast::Node& rhs) {
	leftAssociativeOperator( ids::ReplaceRepeated, result, rhs );
}

void operatorCondition(ast::Node& result, const ast::Node& rhs) {
	leftAssociativeOperator( ids::Condition, result, rhs );
}

void operatorPrefixAt(ast::Node& result, ast::Node rhs) {
	removeIfParenthesesIdentityFunction(result);
	removeIfParenthesesIdentityFunction(rhs);
	result = ast::Node::make<ast::FunctionCall>(result, {rhs});
}

void operatorPostFixAt(ast::Node& result, ast::Node rhs) {
	removeIfParenthesesIdentityFunction(result);
	removeIfParenthesesIdentityFunction(rhs);
	result = ast::Node::make<ast::FunctionCall>(rhs, {result});
}

void operatorPatternTest(ast::Node& result, ast::Node rhs) {
	removeIfParenthesesIdentityFunction(result);
	removeIfParenthesesIdentityFunction(rhs);
	result = ast::Node::make<ast::FunctionCall>(ids::PatternTest, {result, rhs});
}

void operatorLambdaFunction(ast::Node& result) {
	applyPostFixOperator( result, ast::Node::make<ast::Identifier>(ids::Function) );
}

void operatorParentheses(ast::Node& result, const ast::Node& expression) {
	//Don't do anything for multiple, paralell parentheses
	if ( expression.is<ast::FunctionCall>() && expression.get<ast::FunctionCall>().getFunction() == ast::Node::make<ast::Identifier>(parenthesesIdentityFunction) ) {
		result = expression;
	} else {
		result = ast::Node::make<ast::FunctionCall>( parenthesesIdentityFunction, {expression} );
	}
}

void operatorUnaryMinus(ast::Node& result, const ast::Node& operand) {
	//TODO "- 1" should be parsed as -1 directly (and not Times[-1, 1] (low priority)
	result = ast::Node::make<math::Rational>(-1);
	operatorTimes(result, operand);
	operatorParentheses(result, result);
}

void operatorNot(ast::Node& result, ast::Node operand) {
	removeIfParenthesesIdentityFunction(result);
	removeIfParenthesesIdentityFunction(operand);
	result = ast::Node::make<ast::FunctionCall>(ids::Not, {operand});
	operatorParentheses(result, result);
}

void makeBlankPattern(ast::Node& result, const boost::optional<std::vector<char>>& name, const boost::optional<std::vector<char>>& headType, const ast::Identifier& functionName) {

	auto blankPatternLambda = [&] {
		if (headType) {
			return ast::Node::make<ast::FunctionCall>( functionName, {ast::Node::make<ast::Identifier>(headType->begin(), headType->end())} );
		}
		return ast::Node::make<ast::FunctionCall>( functionName );
	};

	if ( name ) {
		result = ast::Node::make<ast::FunctionCall>( ids::Pattern, {ast::Node::make<ast::Identifier>(name->begin(), name->end()), blankPatternLambda()} );
	} else {
		result = blankPatternLambda();
	}
}

void makeSlot(ast::Node& result, boost::optional<math::Integer> n, const ast::Identifier& functionName) {
	if ( !n ) {
		n = 1;
	}
	assert(n && n >= 0);
	result = ast::Node::make<ast::FunctionCall>( functionName, {ast::Node::make<math::Rational>(*n)} );
}

void createFunctionCallFromNode(ast::Node& result, const ast::Node& function) {
	result = ast::Node::make<ast::FunctionCall>( function );
}

void createFunctionCallFromString(ast::Node& result, const std::string& name) {
	result = ast::Node::make<ast::FunctionCall>( ast::Node::make<ast::Identifier>(name) );
}

void fillFunctionCall(ast::Node& result, const ast::Operands& operands) {
	assert( result.is<ast::FunctionCall>() );
	assert( result.get<ast::FunctionCall>().getOperands().empty() );
	result.getM<ast::FunctionCall>().getOperands() = operands;
}

void createPartExpression(ast::Node& indexable, ast::Operands index) {
	index.insert( index.begin(), indexable );
	indexable = ast::Node::make<ast::FunctionCall>( ids::Part, index );
}

void finishingTouches(ast::Node& result, const ast::Node& wholeExpression) {
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

typedef boost::spirit::ascii::space_type delimiter;

template<class Iterator>
struct TungstenGrammar : boost::spirit::qi::grammar<Iterator, ast::Node(), delimiter> {

	TungstenGrammar() : TungstenGrammar::base_type(start) {

		using qi::_1;
		using qi::_2;
		using qi::_val;
		using qi::alpha;
		using qi::alnum;
		using qi::print;
		using qi::char_;
		using qi::eps;
		using qi::lit;
		using qi::lexeme;
		using qi::no_skip;
		using qi::omit;

		start = expression[_val = _1] | qi::eoi[_val = ast::Node::make<ast::Identifier>(ids::Null)];

		expression = compoundExpression[phx::bind(&finishingTouches, _val, _1)];

		//Tree : ---

		compoundExpression =
				equalsToExpression[_val = _1] >> (
					';' >> compoundExpression[phx::bind(&operatorCompoundExpressionSequence, _val, _1)] |
					char_(';')[phx::bind(&operatorCompoundExpressionNullEnd, _val)] |
					eps
				);

		equalsToExpression =
				postFixAtExpression[_val = _1] >>
				('=' >> equalsToExpression[phx::bind(&operatorSet, _val, _1)] |
				":=" >> equalsToExpression[phx::bind(&operatorSetDelayed, _val, _1)] |
				eps);

		postFixAtExpression =
				lamdaFunctionExpression[_val = _1] >>
				*( "//" >> lamdaFunctionExpression[phx::bind(&operatorPostFixAt, _val, _1)] );

		lamdaFunctionExpression =
				replaceAllExpression[_val = _1] >> *(
				lit("&")[phx::bind(&operatorLambdaFunction, _val)]);

		replaceAllExpression =
				ruleExpression[_val = _1] >> *(
				"/." >> ruleExpression[phx::bind(&operatorReplaceAll, _val, _1)] |
				"//." >> ruleExpression[phx::bind(&operatorReplaceRepeated, _val, _1)]);

		ruleExpression =
				conditionExpression[_val = _1] >>
				("->" >> ruleExpression[phx::bind(&operatorRule, _val, _1)] |
				":>" >> ruleExpression[phx::bind(&operatorRuleDelayed, _val, _1)] |
				eps);

		conditionExpression =
				patternExpression[_val = _1] >> *(
				"/;" >> patternExpression[phx::bind(&operatorCondition, _val, _1)]);

		patternExpression =
				identifier[_val = _1] >> ':' >> alternativesExpression[phx::bind(&operatorPattern, _val, _1)] |
				alternativesExpression[_val = _1];

		alternativesExpression =
				repeatedExpression[_val = _1] >>
				*( '|' >> repeatedExpression[phx::bind(&operatorAlternatives, _val, _1)]);

		repeatedExpression =
				orExpression[_val = _1] >> *(
					lit("...")[phx::bind(&operatorRepeatedNull, _val)] |
					lit("..")[phx::bind(&operatorRepeated, _val)]
					);

		orExpression =
				andExpression[_val = _1] >>
				*(  "||" >> andExpression[phx::bind(&operatorOr, _val, _1)] );

		andExpression =
				notExpression[_val = _1] >>
				*(  "&&" >> notExpression[phx::bind(&operatorAnd, _val, _1)] );

		notExpression = relationalExpression[_val = _1] |
				'!' >> notExpression[phx::bind(&operatorNot, _val, _1)];


		relationalExpression =
				additiveExpression[_val = _1] >> (
				"==" >> additiveExpression[phx::bind(&operatorEqual, _val, _1)] |
				"!=" >> additiveExpression[phx::bind(&operatorUnequal, _val, _1)] |
				"<=" >> additiveExpression[phx::bind(&operatorLessEqual, _val, _1) ] |
				">=" >> additiveExpression[phx::bind(&operatorGreaterEqual, _val, _1)] |
				'<' >> additiveExpression[phx::bind(&operatorLess, _val, _1)] |
				'>' >> additiveExpression[phx::bind(&operatorGreater, _val, _1)] |
				eps);

		additiveExpression =
				multiplicativeExpression[_val = _1] >>
				*(  '+' >> multiplicativeExpression[phx::bind(&operatorPlus, _val, _1)] |
					'-' >> multiplicativeExpression[phx::bind(&operatorMinus, _val, _1)] );

		multiplicativeExpression =
				unaryPlusMinusOperator[_val = _1] >>
				*(  '*' >> unaryPlusMinusOperator[phx::bind(&operatorTimes, _val, _1)] |
					'/' >> unaryPlusMinusOperator[phx::bind(&operatorDivide, _val, _1)] |
					!(char_('+') | char_('-')) >> unaryPlusMinusOperator[phx::bind(&operatorTimes, _val, _1)] ); //TODO all unrary operators which can be binary operators are required here

		unaryPlusMinusOperator =
				powerExpression[_val = _1] |
				'-' >> unaryPlusMinusOperator[phx::bind(&operatorUnaryMinus, _val, _1)] |
				'+' >> unaryPlusMinusOperator[_val = _1];

		powerExpression =
				factorialExpression[_val = _1] >> (
						'^' >> powerExpression[phx::bind(&operatorPower, _val, _1)] |
						eps);

		factorialExpression =
				applyExpression[_val = _1] >> *(
						lit("!!")[phx::bind(&operatorFactorial2, _val)] |
						lit("!")[phx::bind(&operatorFactorial, _val)]
						);

		applyExpression =
				prefixAtExpression[_val = _1] >> (
				"@@" >> applyExpression[phx::bind(&operatorApply, _val, _1)] |
				"/@" >> applyExpression[phx::bind(&operatorMap, _val, _1)] |
				eps);

		prefixAtExpression =
				functionCallAndPartExpression[_val = _1] >> (
				"@" >> prefixAtExpression[phx::bind(&operatorPrefixAt, _val, _1)] |
				eps);

		functionCallAndPartExpression =
				patternTestExpression[_val = _1] >> (
	                *(("[[" >> argumentList >> "]]")[phx::bind(&createPartExpression, _val, _1)] |
					('[' >> argumentList >> ']')[phx::bind(&createFunctionCall, _val, _1)]  )
				);

		patternTestExpression =
				primary[_val = _1] >> -('?' >> primary[phx::bind(&operatorPatternTest, _val, _1)]); //Cannot be chained

		//Primaries : ---
		signedInteger = signedIntegerParser[phx::bind(&makeInteger, _val, _1)];
		unsignedInteger = unsignedIntegerParser[phx::bind(&makeInteger, _val, _1)];
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

		list =
				eps[phx::bind(&createFunctionCallFromString, _val, ids::List)] >>
				'{' >>
				argumentList[phx::bind(&fillFunctionCall, _val, _1)] >>
				'}';

		//TODO remove backtracking here
		blankPattern =
				( ((-variable) >> "___" >> (-variable))[phx::bind(&makeBlankPattern, _val, _1, _2, ids::BlankNullSequence)] ) |
				( ((-variable) >> "__" >> (-variable))[phx::bind(&makeBlankPattern, _val, _1, _2, ids::BlankSequence)] ) |
				( ((-variable) >> '_' >> (-variable))[phx::bind(&makeBlankPattern, _val, _1, _2, ids::Blank)] );

		slotPattern =
				( "##" >> (-unsignedIntegerParser)[phx::bind(&makeSlot, _val, _1, ids::SlotSequence)] ) |
				( '#' >> (-unsignedIntegerParser)[phx::bind(&makeSlot, _val, _1, ids::Slot)] );



		parenthesizedExpression = '(' >> expression[phx::bind(&operatorParentheses, _val, _1)] >> ')';

		primary %= real | signedInteger | string | blankPattern | slotPattern | parenthesizedExpression | list | identifier;

	}

	qi::int_parser< math::Integer > signedIntegerParser;
	qi::uint_parser< math::Integer > unsignedIntegerParser;
	qi::real_parser< math::Real, OnlyNumericRealPolicies<math::Real> > realParser;


	qi::rule<Iterator, ast::Node(), delimiter> start;
	qi::rule<Iterator, ast::Node(), delimiter> expression;
	qi::rule<Iterator, ast::Node(), delimiter> compoundExpression;
	qi::rule<Iterator, ast::Node(), delimiter> relationalExpression;
	qi::rule<Iterator, ast::Node(), delimiter> equalsToExpression;
	qi::rule<Iterator, ast::Node(), delimiter> postFixAtExpression; // expr1 // expr2
	qi::rule<Iterator, ast::Node(), delimiter> ruleExpression;
	qi::rule<Iterator, ast::Node(), delimiter> patternExpression;
	qi::rule<Iterator, ast::Node(), delimiter> additiveExpression;
	qi::rule<Iterator, ast::Node(), delimiter> multiplicativeExpression;
	qi::rule<Iterator, ast::Node(), delimiter> powerExpression;
	qi::rule<Iterator, ast::Node(), delimiter> applyExpression;
	qi::rule<Iterator, ast::Node(), delimiter> prefixAtExpression; // expr1 @ expr2
	qi::rule<Iterator, ast::Node(), delimiter> factorialExpression;
	qi::rule<Iterator, ast::Node(), delimiter> lamdaFunctionExpression; // expr &
	qi::rule<Iterator, ast::Node(), delimiter> notExpression;
	qi::rule<Iterator, ast::Node(), delimiter> andExpression;
	qi::rule<Iterator, ast::Node(), delimiter> orExpression;
	qi::rule<Iterator, ast::Node(), delimiter> patternTestExpression; // a?b
	qi::rule<Iterator, ast::Node(), delimiter> replaceAllExpression; // expr /. patt
	qi::rule<Iterator, ast::Node(), delimiter> conditionExpression; // patt /; test
	qi::rule<Iterator, ast::Node(), delimiter> alternativesExpression;
	qi::rule<Iterator, ast::Node(), delimiter> repeatedExpression;

	qi::rule<Iterator, ast::Node()> blankPattern;
	qi::rule<Iterator, ast::Node()> slotPattern;

	qi::rule<Iterator, std::vector<char>()> variable;
	qi::rule<Iterator, ast::Operands(), delimiter> argumentList;

	qi::symbols<ast::String::value_type, ast::String::value_type> unescapedCharacters;
	qi::rule<Iterator, ast::String()> unescapedString;
	qi::rule<Iterator, ast::Node(), delimiter> string;

	qi::rule<Iterator, ast::Node(), delimiter> identifier;
	qi::rule<Iterator, ast::Node(), delimiter> signedInteger;
	qi::rule<Iterator, ast::Node(), delimiter> unsignedInteger;
	qi::rule<Iterator, ast::Node(), delimiter> real;
	qi::rule<Iterator, ast::Node(), delimiter> functionCallAndPartExpression;
	qi::rule<Iterator, ast::Node(), delimiter> list;
	qi::rule<Iterator, ast::Node(), delimiter> unaryPlusMinusOperator;
	qi::rule<Iterator, ast::Node(), delimiter> parenthesizedExpression;
	qi::rule<Iterator, ast::Node(), delimiter> primary;

};

boost::optional<ast::Node> parseInput(const std::string& input) {
	ast::Node result;

	std::string::const_iterator begin = input.cbegin();
	std::string::const_iterator end = input.cend();

	TungstenGrammar<std::string::const_iterator> grammar;

	bool success = qi::phrase_parse(
		begin, end,
		grammar,
		delimiter(),
		result);
	if(success && begin == end){
		return result;
	} else {
		return boost::optional<ast::Node>();
	}
}


}} //namespace tungsten::io

