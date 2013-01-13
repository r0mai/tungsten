
#include "functions.hpp"

#include <cassert>

#include "eval/SessionEnvironment.hpp"

namespace tungsten { namespace eval { namespace builtin {

struct PowerVisitor : boost::static_visitor<ast::Node> {

	//Base case: we can't do any simplifications
	template<class T, class U>
	ast::Node operator()(const T& base, const U& exponent) {
		return ast::Node::make<ast::FunctionCall>("Power", {
				ast::Node::make<T>(base),
				ast::Node::make<U>(exponent)});
	}

//	template<class T>
//	ast::Node operator()(const T& base, const math::Rational& exponent) {
//
//	}

};

ast::Node Power(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment) {

	if ( operands.empty() ) {
		return ast::Node::make<math::Rational>(1);
	}

	if ( operands.size() == 1 ) {
		return operands[0];
	}

	ast::Node base = operands[0];
	ast::Node exponent = operands[1];

	if ( operands.size() > 2 ) {
		//Power[x,y,z,...] == Power[x,Power[y,z,...]]
		exponent =
				sessionEnvironment.evaluate(
						ast::Node::make<ast::FunctionCall>("Power",
								ast::Operands( operands.begin()+1, operands.end() ) ) );
	}

	//Special cases:


	//c.isInteger() : (a^b)^c => (a^(b*c))
	if ( exponent.is<math::Rational>() && exponent.get<math::Rational>().isInteger() &&
			base.is<ast::FunctionCall>() && base.get<ast::FunctionCall>().getFunction().is<ast::Identifier>("Power") )
	{
		assert( base.get<ast::FunctionCall>().getOperands().size() == 2 );

		exponent = sessionEnvironment.evaluate( ast::Node::make<ast::FunctionCall>("Times", {
				base.get<ast::FunctionCall>().getOperands()[1], //b
				exponent //c
		}) );

		base = base.get<ast::FunctionCall>().getOperands()[0]; //a
	}

	//0^0 => Indeterminate
	if ( base.isNumeric(0) && exponent.isNumeric(0) ) {
		//TODO raise Power::indet
		return ast::Node::make<ast::Identifier>("Indeterminate");
	}

	//x^0 => 1
	if ( exponent.is<math::Rational>(0) ) {
		return ast::Node::make<math::Rational>(1);
	}

	//x^0.0 => 1.0
	if ( exponent.is<math::Real>(0) ) {
		return ast::Node::make<math::Real>(1);
	}


	PowerVisitor powerVisitor;
	return ast::applyVisitor( base, exponent, powerVisitor );
}

}}} //namespace tungsten::eval::builtin
