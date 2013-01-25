
#include "functions.hpp"

#include <iterator>

#include <boost/range/algorithm/copy.hpp>
#include <boost/range/adaptor/transformed.hpp>
#include <boost/range/adaptor/filtered.hpp>

#include "eval/isSuperficiallyNegative.hpp"
#include "eval/SessionEnvironment.hpp"

namespace tungsten { namespace eval { namespace builtin {

struct DenominatorVisitor : boost::static_visitor<ast::Node> {

	DenominatorVisitor(SessionEnvironment& sessionEnvironment) : sessionEnvironment(sessionEnvironment) {}

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

			boost::copy(
					operands |
					boost::adaptors::filtered([](const ast::Node& node) {
						return node.is<ast::FunctionCall>() &&
								node.get<ast::FunctionCall>().getFunction().is<ast::Identifier>( ids::Power ) &&
								node.get<ast::FunctionCall>().getOperands().size() == 2 &&
								isSuperficiallyNegative(node.get<ast::FunctionCall>().getOperands()[1]);
					}) |
					boost::adaptors::transformed([this](const ast::Node& node) {
						return sessionEnvironment.recursiveEvaluate(
								ast::Node::make<ast::FunctionCall>(ids::Power, {
										node.get<ast::FunctionCall>().getOperands()[0],
										ast::Node::make<ast::FunctionCall>(ids::Times, {
												ast::Node::make<math::Rational>(-1),
												node.get<ast::FunctionCall>().getOperands()[1]
										})
								}));
					}),
					std::back_inserter(numeratorOperands) );

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

ast::Node Denominator(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment) {
	if ( operands.size() != 1 ) {
		//TODO issue warning
		return ast::Node::make<ast::FunctionCall>( ids::Denominator, operands );
	}

	DenominatorVisitor denominatorVisitor(sessionEnvironment);
	return ast::applyVisitor( operands[0], denominatorVisitor );
}

}}} //namespace tungsten::eval::builtin
