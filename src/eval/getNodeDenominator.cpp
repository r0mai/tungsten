
#include "getNodeDenominator.hpp"

#include <iterator>

#include <boost/range/algorithm/copy.hpp>
#include <boost/range/adaptor/transformed.hpp>
#include <boost/range/adaptor/filtered.hpp>
#include <boost/range/algorithm/find_if.hpp>

#include "eval/isSuperficiallyNegative.hpp"

namespace tungsten { namespace eval {

struct GetPrintableNodeDenominatorVisitor : boost::static_visitor<boost::optional<ast::Node>> {

	template<class T>
	boost::optional<ast::Node> operator()(const T& /*node*/) const {
		return boost::none_t();
	}

	boost::optional<ast::Node> operator()(const math::Rational& rational) const {
		if ( math::denominator(rational) != 1 ) {
			return ast::Node::make<math::Rational>(math::denominator(rational));
		}
		return boost::none_t();
	}

	boost::optional<ast::Node> operator()(const ast::FunctionCall& functionCall) const {
		const ast::Node& function = functionCall.getFunction();
		const ast::Operands& operands = functionCall.getOperands();

		if ( function.is<ast::Identifier>( ids::Times ) ) {
			ast::Operands denominatorOperands;

			for ( const ast::Node& node : operands ) {
				if ( node.is<ast::FunctionCall>() &&
						node.get<ast::FunctionCall>().getFunction().is<ast::Identifier>( ids::Power ) &&
						node.get<ast::FunctionCall>().getOperands().size() == 2 &&
						isSuperficiallyNegative(node.get<ast::FunctionCall>().getOperands().back()) )
				{
					const ast::Node& base = node.get<ast::FunctionCall>().getOperands().front();
					const ast::Node& exponent = node.get<ast::FunctionCall>().getOperands().back();
					ast::Node negatedExponent;

					//TODO we're basically redoing what isSuperFiciallyNegative does. bad!
					if ( exponent.is<math::Rational>() ) {
						assert( exponent.get<math::Rational>() < 0 );
						negatedExponent = ast::Node::make<math::Rational>( -exponent.get<math::Rational>() );
					} else if ( exponent.is<math::Real>() ) {
						assert( exponent.get<math::Real>() < 0 );
						negatedExponent = ast::Node::make<math::Real>( -exponent.get<math::Real>() );
					} else {
						assert( exponent.isFunctionCall(ids::Times) );

						negatedExponent = exponent;
						ast::Operands& exponentTimesOperands = negatedExponent.getM<ast::FunctionCall>().getOperands();

						ast::Operands::iterator negativeTermIt = boost::find_if( exponentTimesOperands, [](const ast::Node& node) {
							return node.isNumeric() && node.getNumeric() < 0;
						});

						//isSuperficiallyNegative() guarantees thete is one in exponentTimesOperands
						assert( negativeTermIt != exponentTimesOperands.end() );

						if ( exponent.is<math::Rational>() ) {
							negativeTermIt->getM<math::Rational>() *= -1;
						} else if ( exponent.is<math::Real>() ) {
							negativeTermIt->getM<math::Real>() *= -1;
						} else {
							assert(false);
						}

					}

					if ( negatedExponent.is<math::Rational>(1) ) {
						denominatorOperands.push_back( base );
					} else {
						denominatorOperands.push_back( ast::Node::make<ast::FunctionCall>(ids::Power, {base, negatedExponent}) );
					}

				} else if ( node.is<math::Rational>() && !math::isInteger(node.get<math::Rational>()) ) {
					denominatorOperands.push_back(
						ast::Node::make<math::Rational>(math::denominator(node.get<math::Rational>()))
					);
				}
			}

			if ( denominatorOperands.empty() ) {
				return boost::none_t();
			}
			if ( denominatorOperands.size() == 1 ) {
				return denominatorOperands.front();
			}
			return ast::Node::make<ast::FunctionCall>( ids::Times, denominatorOperands );

		} else if ( function.is<ast::Identifier>( ids::Power ) ) {
			if ( operands.size() == 2 && isSuperficiallyNegative(operands.back()) ) {


				const ast::Node& base = operands.front();
				const ast::Node& exponent = operands.back();

				ast::Node negatedExponent;

				//TODO we're basically redoing what isSuperFiciallyNegative does. bad!
				if ( exponent.is<math::Rational>() ) {
					assert( exponent.get<math::Rational>() < 0 );
					negatedExponent = ast::Node::make<math::Rational>( -exponent.get<math::Rational>() );
				} else if ( exponent.is<math::Real>() ) {
					assert( exponent.get<math::Real>() < 0 );
					negatedExponent = ast::Node::make<math::Real>( -exponent.get<math::Real>() );
				} else {
					assert( exponent.isFunctionCall(ids::Times) );

					negatedExponent = exponent;
					ast::Operands& exponentTimesOperands = negatedExponent.getM<ast::FunctionCall>().getOperands();

					ast::Operands::iterator negativeTermIt = boost::find_if( exponentTimesOperands, [](const ast::Node& node) {
						return node.isNumeric() && node.getNumeric() < 0;
					});

					//isSuperficiallyNegative() guarantees thete is one in exponentTimesOperands
					assert( negativeTermIt != exponentTimesOperands.end() );

					if ( exponent.is<math::Rational>() ) {
						negativeTermIt->getM<math::Rational>() *= -1;
					} else if ( exponent.is<math::Real>() ) {
						negativeTermIt->getM<math::Real>() *= -1;
					} else {
						assert(false);
					}

				}

				if ( negatedExponent.is<math::Rational>(1) ) {
					return base;
				} else {
					return ast::Node::make<ast::FunctionCall>(ids::Power, {base, negatedExponent});
				}
			}

		}

		return operator()<>(functionCall);
	}
};

ast::Node getNodeDenominator(const ast::Node& node) {
	boost::optional<ast::Node> optionalDenominator = ast::applyVisitor(node, GetPrintableNodeDenominatorVisitor{});
	if ( !optionalDenominator ) {
		return ast::Node::make<math::Rational>(1);
	}
	return *optionalDenominator;
}

boost::optional<ast::Node> getPrintableNodeDenominator(const ast::Node& node) {
	return ast::applyVisitor(node, GetPrintableNodeDenominatorVisitor{});
}

}} //namespace tungsten::eval

