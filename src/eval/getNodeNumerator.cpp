
#include "getNodeNumerator.hpp"

#include <iterator>

#include <boost/range/algorithm/copy.hpp>
#include <boost/range/adaptor/filtered.hpp>

#include "eval/isSuperficiallyNegative.hpp"

namespace tungsten { namespace eval {

struct GetNodeNumeratorVisitor : boost::static_visitor<ast::Node> {

	GetNodeNumeratorVisitor(SessionEnvironment& sessionEnvironment) : sessionEnvironment(sessionEnvironment) {}

	template<class T>
	ast::Node operator()(const T& node) {
		return ast::Node::make<T>(node);
	}

	ast::Node operator()(const math::Rational& rational) {
		return ast::Node::make<math::Rational>(rational.numerator());
	}

	ast::Node operator()(const ast::FunctionCall& functionCall) {
		const ast::Node& function = functionCall.getFunction();
		const ast::Operands& operands = functionCall.getOperands();

		if ( function.is<ast::Identifier>( ids::Times ) ) {
			ast::Operands numeratorOperands;
			//TODO fix x/3 -> Numerator = 1/3 * x, should be x
			boost::copy(
					operands |
					boost::adaptors::filtered([](const ast::Node& node) {
						return !node.is<ast::FunctionCall>() ||
								!node.get<ast::FunctionCall>().getFunction().is<ast::Identifier>( ids::Power ) ||
								node.get<ast::FunctionCall>().getOperands().size() != 2 ||
								!isSuperficiallyNegative(node.get<ast::FunctionCall>().getOperands()[1]);
					}),
					std::back_inserter(numeratorOperands) );

			return sessionEnvironment.recursiveEvaluate(ast::Node::make<ast::FunctionCall>( ids::Times, numeratorOperands )); //shouldn't need eval

		} else if ( function.is<ast::Identifier>( ids::Power ) ) {
			if ( operands.size() == 2 && isSuperficiallyNegative(operands[1]) ) {
				return ast::Node::make<math::Rational>(1);
			}

		}

		return operator()<>(functionCall);

	}

	SessionEnvironment& sessionEnvironment;
};

ast::Node getNodeNumerator(const ast::Node& node, SessionEnvironment& sessionEnvironment) {
	GetNodeNumeratorVisitor getNodeNumeratorVisitor(sessionEnvironment);
	return ast::applyVisitor(node, getNodeNumeratorVisitor);
}

}} //namespace tungsten::eval

