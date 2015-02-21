#include "functions.hpp"
#include "eval/SessionEnvironment.hpp"

namespace tungsten { namespace eval { namespace builtin {

OptionalNode FindDivisions(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment) {
	if ( operands.size() != 2 ) {
		sessionEnvironment.raiseMessage( Message(ids::FindDivisions, ids::argrx, {
				ast::Node::make<ast::Identifier>( ids::FindDivisions ),
				ast::Node::make<math::Rational>( operands.size() ),
				ast::Node::make<math::Rational>( 2 )
		} ));
		return EvaluationFailure();
	}

	const auto range = operands[0];
	const auto n = operands[1];

	if ( !range.isFunctionCall(ids::List) || range.get<ast::FunctionCall>().getOperands().size() != 2) {
		sessionEnvironment.raiseMessage( Message(ids::FindDivisions, ids::fdargs, {
				range,
				ast::Node::make<ast::FunctionCall>( ids::FindDivisions, operands )
		} ));
		return EvaluationFailure();
	}

	if ( !n.isNumeric() ) {
		sessionEnvironment.raiseMessage( Message(ids::FindDivisions, ids::fdargs, {
				n,
				ast::Node::make<ast::FunctionCall>( ids::FindDivisions, operands )
		} ));
		return EvaluationFailure();
	}

	std::vector<ast::Node> listParams = range.get<ast::FunctionCall>().getOperands();

	auto endIt = std::find_if_not(listParams.begin(), listParams.end(), [](const ast::Node& param) {
			return param.isNumeric();
	});

	if (endIt != listParams.end()) {
		sessionEnvironment.raiseMessage( Message(ids::FindDivisions, ids::fdargs, {
				*endIt,
				ast::Node::make<ast::FunctionCall>( ids::FindDivisions, operands )
		} ));
		return EvaluationFailure();
	}

	std::vector<math::Real> intermediates;

	// Impl here

	ast::Operands elements;
	for(auto& intermediate: intermediates) {
		elements.push_back(ast::Node::make<math::Real>(intermediate));
	}
	return ast::Node::make<ast::FunctionCall>(ids::List, elements);
}

}}} // namespace tungsten::eval::builtin
