
#include "functions.hpp"
#include "eval/SessionEnvironment.hpp"

#include <stack>

namespace tungsten { namespace eval { namespace builtin {

OptionalNode Function(const ast::Operands& operands, eval::SessionEnvironment& /*sessionEnvironment*/) {
	return ast::Node::make<ast::FunctionCall>( ids::Function, operands );
}

OptionalNode evaluateFunction(const ast::Operands& functionOperands, const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment) {
	if ( functionOperands.size() != 1 ) {
		sessionEnvironment.raiseMessage( Message(ids::Function, ids::argx, {
				ast::Node::make<ast::Identifier>( ids::Function ),
				ast::Node::make<math::Rational>( operands.size() )
		} ));
		return EvaluationFailure();
	}

	ast::Node lamdbaFunction = functionOperands[0];

	//Replace Slot[n]s
	std::stack<ast::Node*> toTraverseNodes;
	toTraverseNodes.push(&lamdbaFunction);

	while ( !toTraverseNodes.empty() ) {
		ast::Node *current = toTraverseNodes.top();
		toTraverseNodes.pop();

		if ( current->isFunctionCall( ids::Slot ) && current->get<ast::FunctionCall>().getOperands().size() == 1 ) {
			const ast::Node& slotNumber = current->get<ast::FunctionCall>().getOperands()[0];
			if ( !slotNumber.is<math::Rational>() ||
					!math::isInteger(slotNumber.get<math::Rational>()) ||
					operands.size() < math::asInteger( slotNumber.get<math::Rational>() ) )
			{
				sessionEnvironment.raiseMessage( Message(ids::Function, ids::slot, {} ));
			} else {
				assert( math::fits<std::size_t>(math::asInteger( slotNumber.get<math::Rational>() )) );
				std::size_t slotNumberSizeT = math::as<std::size_t>(math::asInteger( slotNumber.get<math::Rational>() ));
				assert( slotNumberSizeT <= operands.size() );

				if ( slotNumberSizeT == 0 ) {
					*current = ast::Node::make<ast::FunctionCall>(ids::Function, functionOperands);
				} else {
					*current = operands[slotNumberSizeT-1];
				}
			}
		} else if ( current->isFunctionCall(ids::Function) ) {
			/*do nothing*/
		} else if ( current->is<ast::FunctionCall>() ) {
			toTraverseNodes.push( &current->get<ast::FunctionCall>().getFunction() );
			for ( ast::Node& node : current->get<ast::FunctionCall>().getOperands() ) {
				toTraverseNodes.push( &node );
			}
		}
	}

	return sessionEnvironment.recursiveEvaluate( lamdbaFunction );
}

}}} //namespace tungsten::eval::builtin

