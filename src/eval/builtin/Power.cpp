#include <iostream>
#include "functions.hpp"

#include <cassert>

#include <boost/range/algorithm/transform.hpp>
#include <boost/variant/get.hpp>

#include "math/mathFunctions.hpp"
#include "eval/SessionEnvironment.hpp"
#include "eval/orderNode.hpp"

namespace tungsten { namespace eval { namespace builtin {

struct PowerVisitor : boost::static_visitor<ast::Node> {

	PowerVisitor(SessionEnvironment& sessionEnvironment) : sessionEnvironment(sessionEnvironment) {}

	//Base case: we can't do any simplifications
	template<class T, class U>
	ast::Node operator()(const T& base, const U& exponent) {
		return ast::Node::make<ast::FunctionCall>(ids::Power, {
				ast::Node::make<T>(base),
				ast::Node::make<U>(exponent)});
	}

	ast::Node operator()(const math::Rational& base, const math::Rational& exponent) {


		if ( base < 0 && !math::isInteger(exponent) ) {
			//result is Complex TODO
			return operator()<>(base, exponent);
		}

		assert( (base < 0 && math::isInteger(exponent)) || base > 0 );

		math::Integer exponentNumerator = math::numerator(exponent);
		math::Integer exponentDenominator = math::denominator(exponent);


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


		if ( !math::fits<long>(exponentNumerator) ) {
			sessionEnvironment.raiseMessage( Message(ids::General, ids::ovfl, {}) );

			return ast::Node::make<ast::FunctionCall>(ids::Overflow);
		}

		math::Rational baseExponentation = math::power(base, math::as<long>(exponentNumerator));

		if ( exponentDenominator == 1 ) {
			return ast::Node::make<math::Rational>(baseExponentation);
		}

		math::Rational newExponent(math::Integer(1), exponentDenominator);

		if ( !math::fits<unsigned long>(exponentDenominator) ) {
			return ast::Node::make<ast::FunctionCall>(ids::Power, {
					ast::Node::make<math::Rational>(baseExponentation),
					ast::Node::make<math::Rational>(newExponent)});
		}

		boost::optional<math::Integer> baseNumeratorRoot = math::tryNthRoot( math::numerator(baseExponentation), math::as<unsigned long>(exponentDenominator) );
		boost::optional<math::Integer> baseDenominatorRoot = math::tryNthRoot( math::denominator(baseExponentation), math::as<unsigned long>(exponentDenominator) );

		if ( !baseNumeratorRoot && !baseDenominatorRoot ) {
			return ast::Node::make<ast::FunctionCall>(ids::Power, {
					ast::Node::make<math::Rational>(baseExponentation),
					ast::Node::make<math::Rational>(newExponent)});
		}
		if ( baseNumeratorRoot && baseDenominatorRoot ) {
			return ast::Node::make<math::Rational>(*baseNumeratorRoot, *baseDenominatorRoot);
		}
		if ( baseNumeratorRoot ) {
			if ( *baseNumeratorRoot != 1 ) {
				ast::Operands timesOperands = {
						ast::Node::make<math::Rational>(*baseNumeratorRoot),
						ast::Node::make<ast::FunctionCall>(ids::Power, {
							ast::Node::make<math::Rational>(math::denominator(baseExponentation)),
							 ast::Node::make<math::Rational>(-newExponent)})};
				//std::sort(timesOperands.begin(), timesOperands.end(), NodeComparatorLess{});
				return ast::Node::make<ast::FunctionCall>(ids::Times, timesOperands);
			}
			return ast::Node::make<ast::FunctionCall>(ids::Power, {
					ast::Node::make<math::Rational>(math::denominator(baseExponentation)), ast::Node::make<math::Rational>(-newExponent)});
		}

		assert( baseDenominatorRoot );
		if ( *baseDenominatorRoot != 1 ) {
			ast::Operands timesOperands = {
					ast::Node::make<math::Rational>(math::Integer(1), *baseDenominatorRoot),
					ast::Node::make<ast::FunctionCall>(ids::Power, {
						ast::Node::make<math::Rational>(math::numerator(baseExponentation)),
						ast::Node::make<math::Rational>(newExponent)})};
			//std::sort(timesOperands.begin(), timesOperands.end(), NodeComparatorLess{});
			return ast::Node::make<ast::FunctionCall>(ids::Times, timesOperands);
		}
		return ast::Node::make<ast::FunctionCall>(ids::Power, {ast::Node::make<math::Rational>(math::numerator(baseExponentation)), ast::Node::make<math::Rational>(newExponent)});

	}

	ast::Node operator()(const math::Real& base, const math::Real& exponent) {
		if ( base < 0 && !math::isInteger(exponent) ) {
			return operator()(math::ComplexReal{base, 0}, math::ComplexReal{exponent, 0});
		}
		return ast::Node::make<math::Real>(math::power(base, exponent));
	}

	ast::Node operator()(const math::Real& base, const math::Rational& exponent) {
		if ( math::isInteger(exponent) ) {
			return ast::Node::make<math::Real>(math::power(base, exponent));
		}
		return operator()(base, math::Real(exponent));
	}

	ast::Node operator()(const math::Rational& base, const math::Real& exponent) {
		return operator()(math::Real(base), exponent);
	}

	ast::Node operator()(const math::ComplexReal& base, const math::ComplexReal& exponent) {
		return ast::Node::make<math::ComplexReal>(math::power(base, exponent));
	}

	ast::Node operator()(const math::ComplexReal& base, const math::Real& exponent) {
		return ast::Node::make<math::ComplexReal>(math::power(base, exponent));
	}

	ast::Node operator()(const math::ComplexReal& base, const math::Rational& exponent) {
		return ast::Node::make<math::ComplexReal>(math::power(base,
							math::ComplexReal{exponent, math::Real{0}}));
	}

	ast::Node operator()(const math::ComplexReal& base, const math::ComplexRational& exponent) {
			return ast::Node::make<math::ComplexReal>(math::power(base,
							math::ComplexReal{exponent}));
	}

	ast::Node operator()(const math::ComplexRational& base, const math::ComplexReal& exponent) {
		return ast::Node::make<math::ComplexReal>(math::power(base,
					exponent));
	}

	ast::Node operator()(const math::ComplexRational& base, const math::Real& exponent) {
		return ast::Node::make<math::ComplexReal>(math::power(
					math::ComplexReal{base},
					math::ComplexReal{exponent}));
	}

	ast::Node operator()(const math::ComplexRational& base, const math::Rational& exponent) {
		if(math::isInteger(exponent) && exponent > 0) {
			return ast::Node::make<math::ComplexRational>(math::power(base, math::asInteger(exponent).convert_to<unsigned long>()));
		}
		return operator()<>(base, exponent);
	}

	ast::Node operator()(const math::ComplexRational& base, const math::ComplexRational& exponent) {
		return operator()<>(base, exponent);
	}

	ast::Node operator()(const ast::FunctionCall& function, const math::Rational& exponent) {
		if(function.getFunction() != ast::Node::make<ast::Identifier>(ids::DirectedInfinity)) {
			return ast::Node::make<ast::FunctionCall>(ids::Power, {
					ast::Node::make<ast::FunctionCall>(function),
					ast::Node::make<math::Real>(exponent)
			});
		}
		if(function.getOperands().empty()) {
			return ast::Node::make<ast::FunctionCall>(ids::DirectedInfinity, { });
		}
		assert(function.getOperands().size() == 1);
		return ast::Node::make<ast::FunctionCall>(ids::DirectedInfinity, {
				ast::Node::make<math::Real>(math::power(function.getOperands().front().getNumeric(), exponent))
		});
	}

	SessionEnvironment& sessionEnvironment;
};

OptionalNode Power(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment) {

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
				sessionEnvironment.recursiveEvaluate(
						ast::Node::make<ast::FunctionCall>(ids::Power,
								ast::Operands( operands.begin()+1, operands.end() ) ) );
	}

	//Special cases:
	if( base.is<ast::Identifier>(ids::I) ) {
		base = ast::Node::make<math::ComplexRational>(math::ImaginaryUnit<math::Rational>());
	}

	if( exponent.is<ast::Identifier>(ids::I) ) {
		exponent = ast::Node::make<math::ComplexRational>(math::ImaginaryUnit<math::Rational>());
	}

	//c.isInteger() : (a*b)^c => a^c * b^c
	if ( exponent.is<math::Rational>() && math::isInteger(exponent.get<math::Rational>()) &&
			base.is<ast::FunctionCall>() && base.get<ast::FunctionCall>().getFunction().is<ast::Identifier>(ids::Times) )
	{
		const ast::Operands& baseTimesOperands = base.get<ast::FunctionCall>().getOperands();

		ast::Operands resultTimesOperands( baseTimesOperands.size() );

		boost::transform(baseTimesOperands, resultTimesOperands.begin(),
				[&](const ast::Node& node) {
					return ast::Node::make<ast::FunctionCall>( ids::Power, {node, exponent} );
				});

		return sessionEnvironment.recursiveEvaluate(ast::Node::make<ast::FunctionCall>( ids::Times, resultTimesOperands ));
	}


	//c.isInteger() : (a^b)^c => (a^(b*c))
	//or
	//c.isRational() && b.isRational()
	if ( base.isFunctionCall(ids::Power) &&
			((exponent.is<math::Rational>() && math::isInteger(exponent.get<math::Rational>())) ||
			(base.get<ast::FunctionCall>().getOperands()[1].is<math::Rational>() && exponent.is<math::Rational>()))
		) {
		assert( base.get<ast::FunctionCall>().getOperands().size() == 2 );

		exponent = sessionEnvironment.recursiveEvaluate( ast::Node::make<ast::FunctionCall>(ids::Times, {
				base.get<ast::FunctionCall>().getOperands()[1], //b
				exponent //c
		}) );

		base = ast::Node(base.get<ast::FunctionCall>().getOperands()[0]); //a (have to copy, creepy things happen otherwise)
	}

	//0^0 => Indeterminate
	//0^x && x < 0 => DirectedInfinity[]
	if ( base.isNumeric(0) && exponent.isNumeric() ) {

		math::Real exponentReal = exponent.getNumeric();
		if ( exponentReal > 0 ) {
			return ast::Node::make<math::Rational>(0);
		} else if ( exponentReal < 0 ) {

			sessionEnvironment.raiseMessage( Message(ids::Power, ids::infy, {
					ast::Node::make<ast::FunctionCall>(ids::Power, {base, exponent})
			}) );

			return ast::Node::make<ast::FunctionCall>(ids::DirectedInfinity);
		} else { //exponentReal == 0

			sessionEnvironment.raiseMessage( Message(ids::Power, ids::indet, {
					ast::Node::make<ast::FunctionCall>(ids::Power, {base, exponent})
			}) );

			return ast::Node::make<ast::Identifier>(ids::Indeterminate);
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

OptionalNode Sqrt(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment) {
	if ( operands.size() != 1 ) {
		sessionEnvironment.raiseMessage( Message(ids::Sqrt, ids::argx, {
				ast::Node::make<ast::Identifier>( ids::Sqrt ),
				ast::Node::make<math::Rational>( operands.size() )
		} ));
		return EvaluationFailure();
	}

	return sessionEnvironment.recursiveEvaluate(
			ast::Node::make<ast::FunctionCall>(ids::Power, {
					operands[0],
					ast::Node::make<math::Rational>(1,2)
			})
		);
}

}}} //namespace tungsten::eval::builtin
