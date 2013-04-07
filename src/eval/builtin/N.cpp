
#include "functions.hpp"
#include "eval/SessionEnvironment.hpp"

#include <stack>

namespace tungsten { namespace eval { namespace builtin {

OptionalNode N(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment) {
	if ( operands.size() != 1 ) {
		sessionEnvironment.raiseMessage( Message(ids::N, ids::argx, {
				ast::Node::make<ast::Identifier>( ids::N ),
				ast::Node::make<math::Rational>( operands.size() )
		} ));
		return EvaluationFailure();
	}

	ast::Node operand = operands[0];

	std::stack<ast::Node*> toTraverseNodes;
	toTraverseNodes.push(&operand);

	while (!toTraverseNodes.empty()) {
		ast::Node *current = toTraverseNodes.top();
		toTraverseNodes.pop();

		//F
		if ( current->is<ast::FunctionCall>() ) {

			ast::Node& function = current->get<ast::FunctionCall>().getFunction();
			ast::Operands& functionOperands = current->get<ast::FunctionCall>().getOperands();

			AttributeSet functionAttributes = sessionEnvironment.getAttributeSetForFunction(function);

			//Attribute NHold*
			bool hasNHoldFirst = functionAttributes.count( ids::NHoldFirst );
			bool hasNHoldRest = functionAttributes.count( ids::NHoldRest );
			bool hasNHoldAll = functionAttributes.count( ids::NHoldAll );

			bool doNHoldFirst = hasNHoldFirst || hasNHoldAll;
			bool doNHoldRest = hasNHoldRest || hasNHoldAll;

			for ( unsigned i = 0; i < functionOperands.size(); ++i ) {
				if ( ((i != 0 || !doNHoldFirst) && (i == 0 || !doNHoldRest)) ) {
					toTraverseNodes.push( &functionOperands[i] );
				}
			}
		} else if ( current->is<math::Rational>() ) {
			*current = ast::Node::make<math::Real>(current->get<math::Rational>() );
		}

	}

	return sessionEnvironment.recursiveEvaluate(operand);
}

}}} //namespace tungsten::eval::builtin





