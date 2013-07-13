
#include "functions.hpp"
#include "eval/SessionEnvironment.hpp"
#include "eval/IterationSpecifier.hpp"
#include "eval/createRange.hpp"

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
		return sessionEnvironment.recursiveEvaluate(operands.front());
	}

	if ( operands.size() > 2 ) {
		//Table[expr, lspec1, lspec2, ..., lspecn] ->
		//Table[Table[expr, lspec2, lspec3, ..., lspecn], lspec1]

		ast::Operands innerOperands( operands.size() - 1 );
		innerOperands.front() = operands.front();
		std::copy( std::next(operands.begin(), 2), operands.end(), std::next(innerOperands.begin(), 1) );

		return sessionEnvironment.recursiveEvaluate(
				ast::Node::make<ast::FunctionCall>(ids::Table, {
						ast::Node::make<ast::FunctionCall>(ids::Table, innerOperands),
						operands[1]
				})
		);
	}

	assert(operands.size() == 2);

	const ast::Node& expression = operands.front();
	const ast::Node& iterationSpecifierNode = operands.back();

	//Create IterationSpecifier
	boost::optional<eval::IterationSpecifier> iteration = eval::IterationSpecifier::fromNode(iterationSpecifierNode, sessionEnvironment);

	if ( !iteration ) {
		sessionEnvironment.raiseMessage( Message(ids::Table, ids::itform, {
				iterationSpecifierNode,
				ast::Node::make<math::Rational>( 2 )
		} ));
		return EvaluationFailure();
	}

	boost::optional<eval::IterationSpecifier::Iterator> iterator = iteration->makeIterator(sessionEnvironment);

	if ( !iterator ) {
		sessionEnvironment.raiseMessage( Message(ids::Table, ids::iterb, {
				iterationSpecifierNode,
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

	for ( ; !iterator->isEnd(); iterator->advance() ) {
		if ( iteration->hasVariable() ) {
			sessionEnvironment.addPattern( ast::Node::make<ast::Identifier>(iteration->getVariable()), iterator->current() );
		}

		resultListOperands.push_back(
				sessionEnvironment.recursiveEvaluate( expression )
		);
	}

	//Restoring iteration variable is done in BOOST_SCOPE_EXIT above
	return ast::Node::make<ast::FunctionCall>(ids::List, resultListOperands);

}


OptionalNode Range(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment) {

	if ( operands.empty() || operands.size() > 3 ) {
		sessionEnvironment.raiseMessage( Message(ids::Range, ids::argb, {
				ast::Node::make<ast::Identifier>( ids::Range ),
				ast::Node::make<math::Rational>( operands.size() ),
				ast::Node::make<math::Rational>( 1 ),
				ast::Node::make<math::Rational>( 3 )
		} ));
		return EvaluationFailure();
	}

	ast::Node min;
	ast::Node max;
	ast::Node step;

	switch ( operands.size() ) {
	default:
		assert(false);
	case 1:
		min = ast::Node::make<math::Rational>( 1 );
		max = operands.front();
		step = ast::Node::make<math::Rational>( 1 );
		break;
	case 2:
		min = operands.front();
		max = operands.back();
		step = ast::Node::make<math::Rational>( 1 );
		break;
	case 3:
		min = operands.front();
		max = operands[1];
		step = operands.back();
		break;
	}

	boost::optional<ast::Operands> range = createRange( min, max, step, sessionEnvironment );

	if ( !range ) {
		sessionEnvironment.raiseMessage( Message(ids::Range, ids::itform, {
				ast::Node::make<ast::FunctionCall>(ids::List, operands),
				ast::Node::make<math::Rational>( 2 )
		} ));
		return EvaluationFailure();
	}

	return ast::Node::make<ast::FunctionCall>( ids::List, *range );
}

}}} //namespace tungsten::eval::builtin
