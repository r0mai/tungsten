
#include "functions.hpp"
#include "eval/SessionEnvironment.hpp"

#include <utility>

namespace tungsten { namespace eval { namespace builtin {

OptionalNode TrueQ(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment) {
	if ( operands.size() != 1 ) {
		sessionEnvironment.raiseMessage( Message(ids::TrueQ, ids::argx, {
				ast::Node::make<ast::Identifier>( ids::TrueQ ),
				ast::Node::make<math::Rational>( operands.size() )
		} ));
		return EvaluationFailure();
	}

	if ( operands[0].is<ast::Identifier>(ids::True) ) {
		return ast::Node::make<ast::Identifier>(ids::True);
	}
	return ast::Node::make<ast::Identifier>(ids::False);
}

OptionalNode Not(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment) {
	if ( operands.size() != 1 ) {
		sessionEnvironment.raiseMessage( Message(ids::TrueQ, ids::argx, {
				ast::Node::make<ast::Identifier>( ids::TrueQ ),
				ast::Node::make<math::Rational>( operands.size() )
		} ));
		return EvaluationFailure();
	}

	const ast::Node& operand = operands[0];

	if ( operand.is<ast::Identifier>(ids::True) ) {
		return ast::Node::make<ast::Identifier>(ids::False);
	} else if ( operand.is<ast::Identifier>(ids::False) ) {
		return ast::Node::make<ast::Identifier>(ids::True);
	} else if ( operand.isFunctionCall(ids::Not) && operand.get<ast::FunctionCall>().getOperands().size() == 1 ) {
		return operand.get<ast::FunctionCall>().getOperands()[0];
	} else if ( operand.isFunctionCall(ids::Less) && operand.get<ast::FunctionCall>().getOperands().size() == 2 ) {
		return ast::Node::make<ast::FunctionCall>( ids::GreaterEqual, operand.get<ast::FunctionCall>().getOperands() );
	} else if ( operand.isFunctionCall(ids::Greater) && operand.get<ast::FunctionCall>().getOperands().size() == 2 ) {
		return ast::Node::make<ast::FunctionCall>( ids::LessEqual, operand.get<ast::FunctionCall>().getOperands() );
	} else if ( operand.isFunctionCall(ids::GreaterEqual) && operand.get<ast::FunctionCall>().getOperands().size() == 2 ) {
		return ast::Node::make<ast::FunctionCall>( ids::Less, operand.get<ast::FunctionCall>().getOperands() );
	} else if ( operand.isFunctionCall(ids::LessEqual) && operand.get<ast::FunctionCall>().getOperands().size() == 2 ) {
		return ast::Node::make<ast::FunctionCall>( ids::Greater, operand.get<ast::FunctionCall>().getOperands() );
	} else if ( operand.isFunctionCall(ids::Equal) && operand.get<ast::FunctionCall>().getOperands().size() == 2 ) {
		return ast::Node::make<ast::FunctionCall>( ids::Unequal, operand.get<ast::FunctionCall>().getOperands() );
	} else if ( operand.isFunctionCall(ids::Unequal) && operand.get<ast::FunctionCall>().getOperands().size() == 2 ) {
		return ast::Node::make<ast::FunctionCall>( ids::Equal, operand.get<ast::FunctionCall>().getOperands() );
	}

	return ast::Node::make<ast::FunctionCall>( ids::Not, operands );
}

OptionalNode And(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment) {

	ast::Operands resultOperands;

	for ( const ast::Node& operand : operands ) {
		ast::Node term = sessionEnvironment.recursiveEvaluate( operand );
		if ( term.is<ast::Identifier>(ids::False) ) {
			return ast::Node::make<ast::Identifier>(ids::False);
		}
		if ( !term.is<ast::Identifier>(ids::True) ) {
			resultOperands.push_back( std::move(term) );
		}
	}

	if ( resultOperands.empty() ) {
		return ast::Node::make<ast::Identifier>(ids::True);
	}
	if ( resultOperands.size() == 1 ) {
		return resultOperands.back();
	}
	return ast::Node::make<ast::FunctionCall>(ids::And, std::move(resultOperands));
}

OptionalNode Or(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment) {

	ast::Operands resultOperands;

	for ( const ast::Node& operand : operands ) {
		ast::Node term = sessionEnvironment.recursiveEvaluate( operand );
		if ( term.is<ast::Identifier>(ids::True) ) {
			return ast::Node::make<ast::Identifier>(ids::True);
		}
		if ( !term.is<ast::Identifier>(ids::False) ) {
			resultOperands.push_back( std::move(term) );
		}
	}

	if ( resultOperands.empty() ) {
		return ast::Node::make<ast::Identifier>(ids::False);
	}
	if ( resultOperands.size() == 1 ) {
		return resultOperands.back();
	}
	return ast::Node::make<ast::FunctionCall>(ids::Or, std::move(resultOperands));
}

OptionalNode Boole(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment) {
	if ( operands.size() != 1 ) {
		sessionEnvironment.raiseMessage( Message(ids::TrueQ, ids::argx, {
				ast::Node::make<ast::Identifier>( ids::TrueQ ),
				ast::Node::make<math::Rational>( operands.size() )
		} ));
		return EvaluationFailure();
	}

	if ( operands[0].is<ast::Identifier>(ids::True) ) {
		return ast::Node::make<math::Rational>(1);
	} else if ( operands[0].is<ast::Identifier>(ids::False) ) {
		return ast::Node::make<math::Rational>(0);
	}
	return ast::Node::make<ast::FunctionCall>(ids::Boole, operands);
}

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

	// TODO return symbolic result if indeterminate

	for(const auto& element: list) {
		const auto& returnValue = sessionEnvironment.recursiveEvaluate(
				ast::Node::make<ast::FunctionCall>(predicate, {element}));
		if(!returnValue.is<ast::Identifier>() || returnValue.get<ast::Identifier>() != ids::True) {
			return ast::Node::make<ast::Identifier>(ids::False);
		}
	}

	return ast::Node::make<ast::Identifier>(ids::True);
}

}}} //namespace tungsten::eval::builtin
