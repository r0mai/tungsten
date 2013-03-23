
#include "functions.hpp"
#include "eval/SessionEnvironment.hpp"
#include "math/specialMathFunctions.hpp"

namespace tungsten { namespace eval { namespace builtin {

struct FactorialVisitor : boost::static_visitor<ast::Node> {

	FactorialVisitor(SessionEnvironment& sessionEnvironment) : sessionEnvironment(sessionEnvironment) {}

	template<class T>
	ast::Node operator()(const T& node) {
		return ast::Node::make<ast::FunctionCall>(ids::Factorial, {ast::Node::make<T>(node)});
	}

	ast::Node operator()(const math::Real& real) {
		math::Real result = math::gamma(1 + real);
		//gamma() can return nan on negative integers: (and it seems inf as well (-1)! : FIXME:why?)
		if ( boost::math::isnan(result) || boost::math::isinf(result) ) {
			return ast::Node::make<ast::FunctionCall>(ids::DirectedInfinity, {});
		}
		return ast::Node::make<math::Real>(result);
	}

	ast::Node operator()(const math::Rational& rational) {
		if ( math::isInteger(rational) ) {

			math::Integer integer = math::asInteger(rational);

			if ( math::fits<unsigned long>(integer) ) {
				return ast::Node::make<math::Rational>(math::factorial(math::as<unsigned long>(integer)));
			}

			if ( integer < 0 ) {
				return ast::Node::make<ast::FunctionCall>(ids::DirectedInfinity, {});
			}
		} else if ( math::denominator(rational) == 2 ) {
			assert( math::numerator(rational) % 2 != 0 );
			//(n/2)! = Gamma[n/2+1] = Gamma[1/2 + ((1+n)/2)] = (a/b)*Sqrt[Pi]
			math::Integer offset = (1+math::numerator(rational))/2;
			if ( math::fits<long>(offset) ) {
				math::Rational sqrtPiRatio = math::gammaForHalfsSqrtPiRatio( math::as<long>(offset) );
				return sessionEnvironment.recursiveEvaluate(ast::Node::make<ast::FunctionCall>(ids::Times, {
						ast::Node::make<math::Rational>(sqrtPiRatio),
						ast::Node::make<ast::FunctionCall>(ids::Power, {ast::Node::make<ast::Identifier>(ids::Pi), ast::Node::make<math::Rational>(1,2)})
				}));
			}

		}
		return operator()<>(rational);
	}

	SessionEnvironment& sessionEnvironment;
};

struct Factorial2Visitor : boost::static_visitor<ast::Node> {
	template<class T>
	ast::Node operator()(const T& node) const {
		return ast::Node::make<ast::FunctionCall>(ids::Factorial2, {ast::Node::make<T>(node)});
	}

	ast::Node operator()(const math::Rational& rational) const {
		if ( math::isInteger(rational) && math::fits<unsigned long>(math::asInteger(rational)) ) {
			return ast::Node::make<math::Rational>(math::factorial2(math::as<unsigned long>(math::asInteger(rational))));
		}
		return operator()<>(rational);
	}
};

OptionalNode Factorial(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment) {
	if ( operands.size() != 1 ) {
		sessionEnvironment.raiseMessage( Message(ids::Factorial, ids::argx, {
				ast::Node::make<ast::Identifier>( ids::Factorial ),
				ast::Node::make<math::Rational>( operands.size() )
		} ));
		return EvaluationFailure();
	}
	FactorialVisitor factorialVisitor(sessionEnvironment);

	return ast::applyVisitor(operands[0], factorialVisitor);
}

OptionalNode Factorial2(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment) {
	if ( operands.size() != 1 ) {
		sessionEnvironment.raiseMessage( Message(ids::Factorial2, ids::argx, {
				ast::Node::make<ast::Identifier>( ids::Factorial2 ),
				ast::Node::make<math::Rational>( operands.size() )
		} ));
		return EvaluationFailure();
	}
	return ast::applyVisitor(operands[0], Factorial2Visitor{});
}

}}} //namespace tungsten::eval::builtin

