
#include <stack>
#include <boost/math/constants/constants.hpp>

#include "numericNodeEvaluation.hpp"
#include "Identifiers.hpp"

namespace tungsten { namespace eval {

ast::Node numericNodeEvaluation(const ast::Node& node, eval::SessionEnvironment& sessionEnvironment) {

	ast::Node operand = node;

	std::stack<ast::Node*> toTraverseNodes;
	toTraverseNodes.push(&operand);

	while (!toTraverseNodes.empty()) {
		ast::Node *current = toTraverseNodes.top();
		toTraverseNodes.pop();

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
		} else if ( current->is<ast::Identifier>() ) {
			const ast::Identifier& identifier = current->get<ast::Identifier>();
			if ( identifier == ids::Pi ) {
				*current = ast::Node::make<math::Real>(boost::math::constants::pi<math::Real>());
			} else if ( identifier == ids::E ) {
				*current = ast::Node::make<math::Real>(boost::math::constants::e<math::Real>());
			}
		}

	}

	return sessionEnvironment.recursiveEvaluate(operand);
}

}} //namespace tungsten::eval



