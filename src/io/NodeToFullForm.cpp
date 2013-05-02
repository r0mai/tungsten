
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

template<class Iterator>
struct FullFormGrammar : karma::grammar<Iterator, ast::Node()> {

	FullFormGrammar() : FullFormGrammar::base_type(start) {
		using karma::_1;
		using karma::double_;
		using karma::_val;
		using karma::eps;
		using karma::stream;

		start = eps(phx::bind(&isRational, _val)) << double_[phx::bind(&setRational, _1, _val)];

		functionCallRule = start[_1 = phx::bind((const ast::Node& (ast::FunctionCall::*)() const)(&ast::FunctionCall::getFunction), _val)];


	}
	
	karma::rule<Iterator, ast::Node()> start;
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

