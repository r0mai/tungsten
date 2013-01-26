
#include "getNodeDenominator.hpp"

#include <iterator>

#include <boost/range/algorithm/copy.hpp>
#include <boost/range/adaptor/transformed.hpp>
#include <boost/range/adaptor/filtered.hpp>

#include "eval/isSuperficiallyNegative.hpp"

namespace tungsten { namespace eval {

struct GetNodeDenominatorVisitor : boost::static_visitor<ast::Node> {

	GetNodeDenominatorVisitor(SessionEnvironment& sessionEnvironment) : sessionEnvironment(sessionEnvironment) {}

	template<class T>
	ast::Node operator()(const T& /*node*/) {
		return ast::Node::make<math::Rational>(1);
	}

	ast::Node operator()(const math::Rational& rational) {
		return ast::Node::make<math::Rational>(rational.denominator());
	}

	ast::Node operator()(const ast::FunctionCall& functionCall) {
		const ast::Node& function = functionCall.getFunction();
		const ast::Operands& operands = functionCall.getOperands();

		if ( function.is<ast::Identifier>( ids::Times ) ) {
			ast::Operands numeratorOperands;

			for ( const ast::Node& node : operands ) {
				if ( node.is<ast::FunctionCall>() &&
						node.get<ast::FunctionCall>().getFunction().is<ast::Identifier>( ids::Power ) &&
						node.get<ast::FunctionCall>().getOperands().size() == 2 &&
						isSuperficiallyNegative(node.get<ast::FunctionCall>().getOperands()[1]) )
				{
					numeratorOperands.push_back(
						sessionEnvironment.recursiveEvaluate(
							ast::Node::make<ast::FunctionCall>(ids::Power, {
									node.get<ast::FunctionCall>().getOperands()[0],
									ast::Node::make<ast::FunctionCall>(ids::Times, {
											ast::Node::make<math::Rational>(-1),
											node.get<ast::FunctionCall>().getOperands()[1]
									})
							}))
						);
				} else if ( node.is<math::Rational>() ) {
					numeratorOperands.push_back(
						ast::Node::make<math::Rational>(node.get<math::Rational>().denominator())
					);
				}
			}

			return sessionEnvironment.recursiveEvaluate(ast::Node::make<ast::FunctionCall>( ids::Times, numeratorOperands )); //shouldn't need eval

		} else if ( function.is<ast::Identifier>( ids::Power ) ) {
			if ( operands.size() == 2 && isSuperficiallyNegative(operands[1]) ) {
				return sessionEnvironment.recursiveEvaluate(
						ast::Node::make<ast::FunctionCall>(ids::Power, {
								operands[0],
								ast::Node::make<ast::FunctionCall>(ids::Times, {
										ast::Node::make<math::Rational>(-1),
										operands[1]
								})
						}));
			}

		}

		return operator()<>(functionCall);
	}

	SessionEnvironment& sessionEnvironment;
};

ast::Node getNodeDenominator(const ast::Node& node, SessionEnvironment& sessionEnvironment) {
	GetNodeDenominatorVisitor getNodeDenominatorVisitor(sessionEnvironment);
	return ast::applyVisitor(node, getNodeDenominatorVisitor);
}

}} //namespace tungsten::eval

