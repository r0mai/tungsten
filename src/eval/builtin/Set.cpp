
#include "functions.hpp"
#include "eval/SessionEnvironment.hpp"

namespace tungsten { namespace eval { namespace builtin {

OptionalNode Set(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment) {
	if ( operands.size() != 2 ) {

		sessionEnvironment.raiseMessage( Message(ids::Set, ids::argx, {
				ast::Node::make<ast::Identifier>( ids::Set ),
				ast::Node::make<math::Rational>( operands.size() )
		} ));

		return EvaluationFailure();
	}
	if (operands[0].isNumeric()) {
		sessionEnvironment.raiseMessage( Message(ids::Set, ids::setraw, {
				operands[0]
		} ));

		return EvaluationFailure();
	}
	bool isProtected = false;
	if (operands[0].is<ast::FunctionCall>()) {
		const ast::Node& function = operands[0].get<ast::FunctionCall>().getFunction();
		auto attributeSet = sessionEnvironment.getAttributeSetForFunction(function);

		if (attributeSet.count(ids::Protected) > 0) {
			sessionEnvironment.raiseMessage( Message(ids::Set, ids::write, {
					function,
					operands[0]
			} ));
			return EvaluationFailure();
		}
	}
	if (operands[0].is<ast::Identifier>()) {
		auto attributeSet = sessionEnvironment.getAttributeSetForFunction(operands[0]);

		if (attributeSet.count(ids::Protected) > 0) {
			sessionEnvironment.raiseMessage( Message(ids::Set, ids::wrsym, {
					operands[0]
			} ));
			return EvaluationFailure();
		}
	}

	sessionEnvironment.addPattern(operands[0], operands[1]);
	return operands[1];
}

}}} //namespace tungsten::eval::builtin

