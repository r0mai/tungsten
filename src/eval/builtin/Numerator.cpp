
#include "functions.hpp"

#include <iterator>

#include <boost/range/algorithm/copy.hpp>
#include <boost/range/adaptor/filtered.hpp>

#include "eval/isSuperficiallyNegative.hpp"
#include "eval/SessionEnvironment.hpp"

namespace tungsten { namespace eval { namespace builtin {

struct NumeratorVisitor : boost::static_visitor<ast::Node> {

	NumeratorVisitor(SessionEnvironment& sessionEnvironment) : sessionEnvironment(sessionEnvironment) {}

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

ast::Node Numerator(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment) {
	if ( operands.size() != 1 ) {
		//TODO issue warning
		return ast::Node::make<ast::FunctionCall>( ids::Numerator, operands );
	}

	NumeratorVisitor numeratorVisitor(sessionEnvironment);
	return ast::applyVisitor( operands[0], numeratorVisitor);
}

}}} //namespace tungsten::eval::builtin
