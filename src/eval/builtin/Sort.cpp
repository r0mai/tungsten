
#include "functions.hpp"
#include "eval/SessionEnvironment.hpp"
#include "eval/orderNode.hpp"

namespace tungsten { namespace eval { namespace builtin {

struct CustomComparator {
	CustomComparator(const ast::Node& comparatorFunction,
			eval::SessionEnvironment& sessionEnvironment) :
				comparatorFunction(comparatorFunction), sessionEnvironment(sessionEnvironment) {}

	bool operator()(const ast::Node& lhs, const ast::Node& rhs) {
		ast::Node compareResult = sessionEnvironment.recursiveEvaluate(
			ast::Node::make<ast::FunctionCall>(comparatorFunction, {lhs, rhs})
		);

		if ( compareResult.is<ast::Identifier>(ids::False) ) {
			return false;
		}
		//If it doesn't return a True/False value, we take it as true
		return true;
	}

	ast::Node comparatorFunction;
	eval::SessionEnvironment& sessionEnvironment;
};

OptionalNode Sort(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment) {

	if ( operands.size() < 1 || operands.size() > 2 ) {

		sessionEnvironment.raiseMessage( Message(ids::Sort, ids::argt, {
				ast::Node::make<ast::Identifier>( ids::Sort ),
				ast::Node::make<math::Rational>( operands.size() ),
				ast::Node::make<math::Rational>( 1 ),
				ast::Node::make<math::Rational>( 2 )
		} ));

		return EvaluationFailure();
	}

	if ( !operands[0].is<ast::FunctionCall>() ) {
		sessionEnvironment.raiseMessage( Message(ids::Sort, ids::Normal, {
				ast::Node::make<math::Rational>( 1 ),
				ast::Node::make<ast::FunctionCall>( ids::Sort, operands )
		} ));

		return EvaluationFailure();
	}

	ast::Operands resultOperands = operands[0].get<ast::FunctionCall>().getOperands();

	if ( operands.size() == 1 ) {
		std::sort( resultOperands.begin(), resultOperands.end(), NodeComparatorLess{} );
	} else {
		assert(operands.size() == 2);
		CustomComparator customComparator{operands[1], sessionEnvironment};
		std::sort( resultOperands.begin(), resultOperands.end(), customComparator );
	}

	return ast::Node::make<ast::FunctionCall>( operands[0].get<ast::FunctionCall>().getFunction(), resultOperands );
}


OptionalNode OrderedQ(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment) {

	if ( operands.size() < 1 || operands.size() > 2 ) {

		sessionEnvironment.raiseMessage( Message(ids::OrderedQ, ids::argt, {
				ast::Node::make<ast::Identifier>( ids::OrderedQ ),
				ast::Node::make<math::Rational>( operands.size() ),
				ast::Node::make<math::Rational>( 1 ),
				ast::Node::make<math::Rational>( 2 )
		} ));

		return EvaluationFailure();
	}

	if ( !operands[0].is<ast::FunctionCall>() ) {
		sessionEnvironment.raiseMessage( Message(ids::OrderedQ, ids::Normal, {
				ast::Node::make<math::Rational>( 1 ),
				ast::Node::make<ast::FunctionCall>( ids::OrderedQ, operands )
		} ));

		return EvaluationFailure();
	}

	ast::Operands resultOperands = operands[0].get<ast::FunctionCall>().getOperands();

	bool result = true;

	if ( operands.size() == 1 ) {
		result = std::is_sorted( resultOperands.begin(), resultOperands.end(), NodeComparatorLess{} );
	} else {
		assert(operands.size() == 2);
		CustomComparator customComparator{operands[1], sessionEnvironment};
		result = std::is_sorted( resultOperands.begin(), resultOperands.end(), customComparator );
	}

	if ( result ) {
		return ast::Node::make<ast::Identifier>(ids::True);
	}
	return ast::Node::make<ast::Identifier>(ids::False);

}

}}} //namespace tungsten::eval::builtin




