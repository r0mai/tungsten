
#include "getNodeDenominator.hpp"

#include <iterator>

#include <boost/range/algorithm/copy.hpp>
#include <boost/range/adaptor/transformed.hpp>
#include <boost/range/adaptor/filtered.hpp>
#include <boost/range/algorithm/find_if.hpp>

#include "eval/isSuperficiallyNegative.hpp"

namespace tungsten { namespace eval {

struct GetNodeDenominatorVisitor : boost::static_visitor<ast::Node> {

	template<class T>
	ast::Node operator()(const T& /*node*/) const {
		return ast::Node::make<math::Rational>(1);
	}

	ast::Node operator()(const math::Rational& rational) const {
		return ast::Node::make<math::Rational>(math::denominator(rational));
	}

	ast::Node operator()(const ast::FunctionCall& functionCall) const {
		const ast::Node& function = functionCall.getFunction();
		const ast::Operands& operands = functionCall.getOperands();

		if ( function.is<ast::Identifier>( ids::Times ) ) {
			ast::Operands denominatorOperands;

			for ( const ast::Node& node : operands ) {
				if ( node.is<ast::FunctionCall>() &&
						node.get<ast::FunctionCall>().getFunction().is<ast::Identifier>( ids::Power ) &&
						node.get<ast::FunctionCall>().getOperands().size() == 2 &&
						isSuperficiallyNegative(node.get<ast::FunctionCall>().getOperands()[1]) )
				{
					const ast::Node& base = node.get<ast::FunctionCall>().getOperands()[0];
					const ast::Node& exponent = node.get<ast::FunctionCall>().getOperands()[1];
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
						ast::Operands& exponentTimesOperands = negatedExponent.get<ast::FunctionCall>().getOperands();

						ast::Operands::iterator negativeTermIt = boost::find_if( exponentTimesOperands, [](const ast::Node& node) {
							return node.isNumeric() && node.getNumeric() < 0;
						});

						//isSuperficiallyNegative() guarantees thete is one in exponentTimesOperands
						assert( negativeTermIt != exponentTimesOperands.end() );

						if ( exponent.is<math::Rational>() ) {
							negativeTermIt->get<math::Rational>() *= -1;
						} else if ( exponent.is<math::Real>() ) {
							negativeTermIt->get<math::Real>() *= -1;
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
				return ast::Node::make<math::Rational>(1);
			}
			if ( denominatorOperands.size() == 1 ) {
				return denominatorOperands[0];
			}
			return ast::Node::make<ast::FunctionCall>( ids::Times, denominatorOperands );

		} else if ( function.is<ast::Identifier>( ids::Power ) ) {
			if ( operands.size() == 2 && isSuperficiallyNegative(operands[1]) ) {


				const ast::Node& base = operands[0];
				const ast::Node& exponent = operands[1];

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
					ast::Operands& exponentTimesOperands = negatedExponent.get<ast::FunctionCall>().getOperands();

					ast::Operands::iterator negativeTermIt = boost::find_if( exponentTimesOperands, [](const ast::Node& node) {
						return node.isNumeric() && node.getNumeric() < 0;
					});

					//isSuperficiallyNegative() guarantees thete is one in exponentTimesOperands
					assert( negativeTermIt != exponentTimesOperands.end() );

					if ( exponent.is<math::Rational>() ) {
						negativeTermIt->get<math::Rational>() *= -1;
					} else if ( exponent.is<math::Real>() ) {
						negativeTermIt->get<math::Real>() *= -1;
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
	return ast::applyVisitor(node, GetNodeDenominatorVisitor{});
}

}} //namespace tungsten::eval

