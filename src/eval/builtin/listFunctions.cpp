
#include "functions.hpp"
#include "eval/SessionEnvironment.hpp"

#include <utility>
#include <deque>

namespace tungsten {
namespace eval {
namespace builtin {

OptionalNode AllTrue(const ast::Operands& operands,
		     eval::SessionEnvironment& sessionEnvironment) {
    if (operands.size() != 2) {
		sessionEnvironment.raiseMessage(
			Message(ids::AllTrue, ids::argrx,
				{ast::Node::make<ast::Identifier>(ids::AllTrue),
				 ast::Node::make<math::Rational>(operands.size()),
				 ast::Node::make<math::Rational>(2)}));
		return EvaluationFailure();
    }

	if( !operands.front().isFunctionCall(ids::List) ) {
		sessionEnvironment.raiseMessage(
				Message(ids::AllTrue, ids::lvlist,
					{operands.front()}));

		return EvaluationFailure();
	}
	const auto& list = operands.front().get<ast::FunctionCall>().getOperands();
	const auto& predicate = operands.back();

	if(list.empty()) {
		return ast::Node::make<ast::Identifier>(ids::True);
	}

	std::deque<ast::Node> nonTrues;

	for(const auto& element: list) {
		auto returnValue = sessionEnvironment.recursiveEvaluate(
				ast::Node::make<ast::FunctionCall>(predicate, {element}));
		if(returnValue.is<ast::Identifier>() && returnValue.get<ast::Identifier>() == ids::False) {
			return returnValue; // ids::False
		}
		if(!returnValue.is<ast::Identifier>() || returnValue.get<ast::Identifier>() != ids::True) {
			nonTrues.push_back(std::move(returnValue));
		}
	}

	if(!nonTrues.empty()) {
		auto first = std::move(nonTrues.front());
		nonTrues.pop_front();

		ast::FunctionCall andFunction = ids::And;
		andFunction.getOperands().push_back(std::move(first));
		andFunction.getOperands().push_back(
		    ast::Node::make<ast::Identifier>(ids::True));

		for(auto& nonTrue: nonTrues) {
			auto rightMost = andFunction.getOperands().back();
			ast::Node newOp = ast::Node::make<ast::FunctionCall>(ids::And, {
					std::move(nonTrue),
					std::move(rightMost)
			});
			andFunction.getOperands().back() = std::move(newOp);
			andFunction.getOperands().push_back(
			    ast::Node::make<ast::Identifier>(ids::True));
		}

		return sessionEnvironment.recursiveEvaluate(
		    ast::Node::make<ast::FunctionCall>(andFunction));

	} else {
		return ast::Node::make<ast::Identifier>(ids::True);
	}
}
}
}
}  // namespace tungsten::eval::builtin
