
#include "NodeToFullForm.hpp"

#include <iterator>
#include <boost/fusion/sequence.hpp>
#include <boost/spirit/include/karma.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <boost/fusion/adapted/std_pair.hpp>
#include <boost/fusion/include/std_pair.hpp>

namespace tungsten { namespace io {

namespace spirit = boost::spirit;
namespace karma = spirit::karma;
namespace phx = boost::phoenix;

void setRational(double& rational, const ast::Node& node) {
	assert(node.is<math::Rational>());
	rational = node.get<math::Rational>().convert_to<double>();
}

bool isRational(const ast::Node& node) {
	return node.is<math::Rational>();
}
/*
void setIdentifier(ast::Identifier& identifier, const ast::Node& node) {
	assert(node.is<ast::Identifier>());
	rational = node.get<math::Rational>().convert_to<double>();
}

bool isRational(const ast::Node& node) {
	return node.is<math::Rational>();
}*/

template<class T>
bool is(const ast::Node& node) {
	return node.is<T>();
}

template<class T>
void set(T& element, const ast::Node& node) {
	assert(node.is<T>());
	element = node.get<T>();
}

void setFunction(ast::Node& function, const ast::FunctionCall& functionCall) {
	function = functionCall.getFunction();
}

void setOperands(ast::Operands& operands, const ast::FunctionCall& functionCall) {
	operands = functionCall.getOperands();
}

bool isRationalInteger(const math::Rational& rational) {
	return math::isInteger(rational);
}

void getNumerator(math::Integer& numerator, const math::Rational& rational) {
	numerator = math::numerator(rational);
}

void getDenominator(math::Integer& denominator, const math::Rational& rational) {
	denominator = math::denominator(rational);
}

void functionCallToRawForm(std::pair<ast::Node, ast::Operands>& rawForm, const ast::FunctionCall& functionCall) {
	rawForm = std::make_pair(functionCall.getFunction(), functionCall.getOperands());
}

template<class Iterator>
struct FullFormGrammar : karma::grammar<Iterator, ast::Node()> {

	FullFormGrammar() : FullFormGrammar::base_type(start) {
		using karma::_1;
		using karma::double_;
		using karma::char_;
		using karma::_val;
		using karma::eps;
		using karma::stream;
		using karma::string;

		start = nodeRule.alias();

		nodeRule = 
			eps(phx::bind(&is<ast::FunctionCall>, _val)) << functionCallRule[phx::bind(&set<ast::FunctionCall>, _1, _val)] |
			eps(phx::bind(&is<math::Rational>, _val)) << rationalRule[phx::bind(&set<math::Rational>, _1, _val)] |
			eps(phx::bind(&is<math::Real>, _val)) << realRule[phx::bind(&set<math::Real>, _1, _val)] |
			eps(phx::bind(&is<ast::String>, _val)) << stringRule[phx::bind(&set<ast::String>, _1, _val)] |
			eps(phx::bind(&is<ast::Identifier>, _val)) << identifierRule[phx::bind(&set<ast::Identifier>, _1, _val)];

		functionCallRule = rawFunctionCallRule[phx::bind(&functionCallToRawForm, _1, _val)];
		rawFunctionCallRule = nodeRule << '[' << (nodeRule % ", ") << ']';

		rationalRule = 
			eps(phx::bind(&isRationalInteger, _val)) << integerRule[phx::bind(&getNumerator, _1, _val)] |
			"Rational[" << integerRule[phx::bind(&getNumerator, _1, _val)] << ", " << integerRule[phx::bind(&getDenominator, _1, _val)] << "]";
				
		integerRule = string[_1 = "integer"];

		realRule = string[_1 = "real"];
		
		stringRule = string[_1 = "string"];

		identifierRule = string[_1 = _val];

	}
	
	karma::rule<Iterator, ast::Node()> start;
	karma::rule<Iterator, ast::Node()> nodeRule;
	karma::rule<Iterator, ast::FunctionCall()> functionCallRule;
	karma::rule<Iterator, std::pair<ast::Node, ast::Operands>()> rawFunctionCallRule;
	karma::rule<Iterator, ast::String()> stringRule;
	karma::rule<Iterator, math::Rational()> rationalRule;
	karma::rule<Iterator, math::Real()> realRule;
	karma::rule<Iterator, ast::Identifier()> identifierRule;

	karma::rule<Iterator, math::Integer()> integerRule;
};


FullFormString NodeToFullForm(const ast::Node& node) {
	FullFormGrammar<std::back_insert_iterator<FullFormString>> fullFormGrammar;
	FullFormString result;
	std::back_insert_iterator<FullFormString> sink(result);
	karma::generate(sink, fullFormGrammar, node);
	return result;
}

}} //namespace tungsten::io

