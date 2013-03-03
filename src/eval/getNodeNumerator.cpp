
#include "getNodeNumerator.hpp"

#include <iterator>

#include <boost/range/algorithm/copy.hpp>
#include <boost/range/adaptor/transformed.hpp>
#include <boost/range/adaptor/filtered.hpp>

#include "eval/isSuperficiallyNegative.hpp"

namespace tungsten { namespace eval {

struct GetNodeNumeratorVisitor : boost::static_visitor<ast::Node> {

	template<class T>
	ast::Node operator()(const T& node) const {
		return ast::Node::make<T>(node);
	}

	ast::Node operator()(const math::Rational& rational) const {
		return ast::Node::make<math::Rational>(math::numerator(rational));
	}

	ast::Node operator()(const ast::FunctionCall& functionCall) const {
		const ast::Node& function = functionCall.getFunction();
		const ast::Operands& operands = functionCall.getOperands();

		if ( function.is<ast::Identifier>( ids::Times ) ) {
			ast::Operands numeratorOperands;

			boost::copy(
					operands |
					boost::adaptors::filtered([](const ast::Node& node) {
						return !node.is<ast::FunctionCall>() ||
								!node.get<ast::FunctionCall>().getFunction().is<ast::Identifier>( ids::Power ) ||
								node.get<ast::FunctionCall>().getOperands().size() != 2 ||
								!isSuperficiallyNegative(node.get<ast::FunctionCall>().getOperands()[1]);
					}) | boost::adaptors::transformed([](const ast::Node& node) -> ast::Node { //extra care must be taken for Rationals
						if ( node.is<math::Rational>() ) {
							return ast::Node::make<math::Rational>(math::numerator(node.get<math::Rational>()));
						}
						return node;
					}),
					std::back_inserter(numeratorOperands) );

			if ( numeratorOperands.empty() ) {
				return ast::Node::make<math::Rational>(1);
			}
			if ( numeratorOperands.size() == 1 ) {
				return numeratorOperands[0];
			}
			return ast::Node::make<ast::FunctionCall>( ids::Times, numeratorOperands );

		} else if ( function.is<ast::Identifier>( ids::Power ) ) {
			if ( operands.size() == 2 && isSuperficiallyNegative(operands[1]) ) {
				return ast::Node::make<math::Rational>(1);
			}

		}

		return operator()<>(functionCall);

	}

};

ast::Node getNodeNumerator(const ast::Node& node) {
	return ast::applyVisitor(node, GetNodeNumeratorVisitor{});
}

}} //namespace tungsten::eval

