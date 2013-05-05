
#include "NodeToFullForm.hpp"

#include <iterator>
#include <boost/spirit/include/karma.hpp>
#include <boost/spirit/include/phoenix.hpp>

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

void setFunctionCall(ast::FunctionCall& functionCall, const ast::Node& node) {
	assert(node.is<ast::FunctionCall>());
	functionCall = node.get<ast::FunctionCall>();
}

bool isFunctionCall(const ast::Node& node) {
	return node.is<ast::FunctionCall>();
}

void setFunction(ast::Node& function, const ast::FunctionCall& functionCall) {
	function = functionCall.getFunction();
}

void setOperands(ast::Operands& operands, const ast::FunctionCall& functionCall) {
	operands = functionCall.getOperands();
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

		start = nodeRule.alias();

		nodeRule = 
			eps(phx::bind(&isFunctionCall, _val)) << functionCallRule[phx::bind(&setFunctionCall, _1, _val)] |
			eps(phx::bind(&isRational, _val)) << char_[_1 = 'c'];

		functionCallRule = nodeRule[phx::bind(&setFunction, _1, _val)] << '[' << (nodeRule % ", ")[phx::bind(&setOperands, _1, _val)] << ']';


	}
	
	karma::rule<Iterator, ast::Node()> start;
	karma::rule<Iterator, ast::Node()> nodeRule;
	karma::rule<Iterator, ast::FunctionCall()> functionCallRule; 
};


FullFormString NodeToFullForm(const ast::Node& node) {
	FullFormGrammar<std::back_insert_iterator<FullFormString>> fullFormGrammar;
	FullFormString result;
	std::back_insert_iterator<FullFormString> sink(result);
	karma::generate(sink, fullFormGrammar, node);
	return result;
}

}} //namespace tungsten::io

