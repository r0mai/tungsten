
#include "functions.hpp"
#include "eval/SessionEnvironment.hpp"
#include "eval/IterationSpecifier.hpp"

#include <algorithm>
#include <cassert>

#include <boost/scope_exit.hpp>

namespace tungsten { namespace eval { namespace builtin {

OptionalNode Table(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment) {

	if ( operands.size() == 0 ) {
		sessionEnvironment.raiseMessage( Message(ids::Table, ids::argm, {
				ast::Node::make<ast::Identifier>( ids::Table ),
				ast::Node::make<math::Rational>( operands.size() ),
				ast::Node::make<math::Rational>( 1 )
		} ));
		return EvaluationFailure();
	}

	if ( operands.size() == 1 ) {
		return sessionEnvironment.evaluate(operands[0]);
	}

	if ( operands.size() > 2 ) {
		//Table[expr, lspec1, lspec2, ..., lspecn] ->
		//Table[Table[expr, lspec2, lspec3, ..., lspecn], lspec1]

		ast::Operands innerOperands( operands.size() - 1 );
		innerOperands[0] = operands[0];
		std::copy( operands.begin() + 2, operands.end(), innerOperands.begin() + 1 );

		return sessionEnvironment.recursiveEvaluate(
				ast::Node::make<ast::FunctionCall>(ids::Table, {
						ast::Node::make<ast::FunctionCall>(ids::Table, innerOperands),
						operands[1]
				})
		);
	}

	assert(operands.size() == 2);

	const ast::Node& expression = operands[0];
	ast::Node iterationSpecifierNode = operands[1];

	//Create IterationSpecifier
	boost::optional<eval::IterationSpecifier> iteration = eval::IterationSpecifier::fromNode(iterationSpecifierNode, sessionEnvironment);

	if ( !iteration ) {
		sessionEnvironment.raiseMessage( Message(ids::Table, ids::itform, {
				operands[1],
				ast::Node::make<math::Rational>( 2 )
		} ));
		return EvaluationFailure();
	}

	if ( !iteration->isFinite() ) {
		sessionEnvironment.raiseMessage( Message(ids::Table, ids::iterb, {
				operands[1]
		} ));
		return EvaluationFailure();
	}

	//Save iteration variable;
	boost::optional<ast::Node> savedVariableReplacement;
	if ( iteration->hasVariable() ) {
		savedVariableReplacement = sessionEnvironment.getPatternReplacement(ast::Node::make<ast::Identifier>(iteration->getVariable()));
	}

	//Restore iteration variable at end of scope
	BOOST_SCOPE_EXIT(&savedVariableReplacement, &sessionEnvironment, &iteration) {
		if ( iteration->hasVariable() ) {
			if ( savedVariableReplacement ) {
				sessionEnvironment.addPattern( ast::Node::make<ast::Identifier>(iteration->getVariable()), *savedVariableReplacement );
			} else {
				sessionEnvironment.removePattern( ast::Node::make<ast::Identifier>(iteration->getVariable()) );
			}
		}
	} BOOST_SCOPE_EXIT_END

	ast::Operands resultListOperands;
	eval::IterationSpecifier::Iterator iterator = iteration->makeIterator();

	for ( ; !iterator.isEnd(); iterator.advance() ) {
		if ( iteration->hasVariable() ) {
			sessionEnvironment.addPattern( ast::Node::make<ast::Identifier>(iteration->getVariable()), iterator.current() );
		}

		resultListOperands.push_back(
				sessionEnvironment.recursiveEvaluate( expression )
		);
	}

	//Restoring iteration variable is done in BOOST_SCOPE_EXIT above
	return ast::Node::make<ast::FunctionCall>(ids::List, resultListOperands);

}

}}} //namespace tungsten::eval::builtin
