
#include "functions.hpp"

#include <cassert>

#include <boost/range/algorithm/transform.hpp>

#include "eval/SessionEnvironment.hpp"

namespace tungsten { namespace eval { namespace builtin {

struct PowerVisitor : boost::static_visitor<ast::Node> {

	PowerVisitor(SessionEnvironment& sessionEnvironenment) : sessionEnvironenment(sessionEnvironenment) {}

	//Base case: we can't do any simplifications
	template<class T, class U>
	ast::Node operator()(const T& base, const U& exponent) {
		return ast::Node::make<ast::FunctionCall>(ids::Power, {
				ast::Node::make<T>(base),
				ast::Node::make<U>(exponent)});
	}

	ast::Node operator()(const math::Rational& base, const math::Rational& exponent) {


		if ( base < 0 && !exponent.isInteger() ) {
			//result is Complex TODO
			return operator()<>(base, exponent);
		}

		assert( (base < 0 && exponent.isInteger()) || base > 0 );

		math::Integer exponentNumerator = exponent.numerator();
		math::Integer exponentDenominator = exponent.denominator();


		/*
		 * goal:
		 *
		 *  baseNumerator^exponentNumerator
		 * (---------------------------------)^(1/exponentDenominator)
		 *  baseDenominator^exponentNumerator
		 *
		 * <=>
		 *
		 * (base^exponentNumerator)^(1/exponentDenominator)
		 *
		 */


		if ( !exponentNumerator.fitsSL() ) {
			//TODO issue General::ovfl
			return ast::Node::make<ast::FunctionCall>(ids::Overflow);
		}

		math::Rational baseExponentation = math::power(base, exponentNumerator.asSL());

		math::Rational newExponent(1, exponentDenominator);

		if ( newExponent == 1 ) {
			return ast::Node::make<math::Rational>(baseExponentation);
		}

		return ast::Node::make<ast::FunctionCall>(ids::Power, {
				ast::Node::make<math::Rational>(baseExponentation),
				ast::Node::make<math::Rational>(newExponent)});

	}

	ast::Node operator()(const math::Real& base, const math::Real& exponent) {
		//TODO complex case needs to be handled here
		return ast::Node::make<math::Real>(math::power(base, exponent));
	}

	ast::Node operator()(const math::Real& base, const math::Rational& exponent) {
		return operator()(base, math::Real(exponent));
	}

	ast::Node operator()(const math::Rational& base, const math::Real& exponent) {
		return operator()(math::Real(base), exponent);
	}

	SessionEnvironment& sessionEnvironenment;
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
						ast::Node::make<ast::FunctionCall>(ids::Power,
								ast::Operands( operands.begin()+1, operands.end() ) ) );
	}

	//Special cases:
	//c.isInteger() : (a*b)^c => a^c * b^c
	if ( exponent.is<math::Rational>() && exponent.get<math::Rational>().isInteger() &&
			base.is<ast::FunctionCall>() && base.get<ast::FunctionCall>().getFunction().is<ast::Identifier>(ids::Times) )
	{
		const ast::Operands& baseTimesOperands = base.get<ast::FunctionCall>().getOperands();

		ast::Operands resultTimesOperands( baseTimesOperands.size() );

		boost::transform(baseTimesOperands, resultTimesOperands.begin(),
				[&](const ast::Node& node) {
					return ast::Node::make<ast::FunctionCall>( ids::Power, {node, exponent} );
				});

		return sessionEnvironment.evaluate(ast::Node::make<ast::FunctionCall>( ids::Times, resultTimesOperands ));
	}


	//c.isInteger() : (a^b)^c => (a^(b*c))
	if ( exponent.is<math::Rational>() && exponent.get<math::Rational>().isInteger() &&
			base.is<ast::FunctionCall>() && base.get<ast::FunctionCall>().getFunction().is<ast::Identifier>(ids::Power) )
	{
		assert( base.get<ast::FunctionCall>().getOperands().size() == 2 );

		exponent = sessionEnvironment.evaluate( ast::Node::make<ast::FunctionCall>(ids::Times, {
				base.get<ast::FunctionCall>().getOperands()[1], //b
				exponent //c
		}) );

		base = base.get<ast::FunctionCall>().getOperands()[0]; //a
	}

	//0^0 => Indeterminate
	if ( base.isNumeric(0) && exponent.isNumeric() ) {

		math::Real exponentReal = exponent.getNumeric();
		if ( exponentReal == 0 ) {
			//TODO raise Power::indet
			return ast::Node::make<ast::Identifier>(ids::Indeterminate);
		} else if ( exponentReal < 0 ) {
			//TODO raise Power::infy
			return ast::Node::make<ast::FunctionCall>(ids::DirectedInfinity);
		}
	}

	//x^0 => 1
	if ( exponent.is<math::Rational>(0) ) {
		return ast::Node::make<math::Rational>(1);
	}

	//x^0.0 => 1.0
	if ( exponent.is<math::Real>(0) ) {
		return ast::Node::make<math::Real>(1);
	}

	//x^1 => x
	if ( exponent.is<math::Rational>(1) ) {
		return base;
	}

	PowerVisitor powerVisitor{sessionEnvironment};
	return ast::applyVisitor( base, exponent, powerVisitor );
}

}}} //namespace tungsten::eval::builtin
