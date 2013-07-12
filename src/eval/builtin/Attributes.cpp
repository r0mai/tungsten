
#include "functions.hpp"
#include "eval/SessionEnvironment.hpp"

#include <algorithm>
#include <iterator>

namespace tungsten { namespace eval { namespace builtin {

OptionalNode Attributes(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment) {
	if ( operands.size() != 1 ) {
		sessionEnvironment.raiseMessage( Message(ids::Attributes, ids::argx, {
				ast::Node::make<ast::Identifier>( ids::Attributes ),
				ast::Node::make<math::Rational>( operands.size() )
		} ));
		return EvaluationFailure();
	}

	const ast::Node& operand = operands[0];

	ast::Identifier identifier;

	if ( operand.is<ast::Identifier>() ) {
		identifier = operand.get<ast::Identifier>();
	} else if ( operand.is<ast::String>() ) {
		identifier = operand.get<ast::String>();
	} else {
		sessionEnvironment.raiseMessage( Message(ids::Attributes, ids::ssle, {
				ast::Node::make<ast::FunctionCall>( ids::Attributes, operands ),
				ast::Node::make<math::Rational>( 1 )
		} ));
		return EvaluationFailure();
	}

	eval::AttributeSet attributeSet = sessionEnvironment.getAttributeSetForFunction( ast::Node::make<ast::Identifier>(identifier) );

	ast::Operands resultListOperands;
	std::transform( attributeSet.begin(), attributeSet.end(), std::back_inserter(resultListOperands),
			[](const ast::Identifier& identifier) { return ast::Node::make<ast::Identifier>(identifier); }
	);


	return ast::Node::make<ast::FunctionCall>(ids::List, resultListOperands);
}

}}} //namespace tungsten::eval::builtin

