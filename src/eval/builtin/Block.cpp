
#include "functions.hpp"
#include "eval/SessionEnvironment.hpp"

namespace tungsten { namespace eval { namespace builtin {

typedef std::pair<ast::Identifier, boost::optional<ast::Node>> IdentifierOptNodePair;

IdentifierOptNodePair localizeVariable(const ast::Node& identifier, eval::SessionEnvironment& sessionEnvironment) {
	assert( identifier.is<ast::Identifier>() );
	boost::optional<ast::Node> replacement = sessionEnvironment.getPatternReplacement(identifier);
	if (replacement) {
		sessionEnvironment.removePattern( identifier );
	}
	return std::make_pair(identifier.get<ast::Identifier>(), replacement);
}

OptionalNode Block(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment) {
	if ( operands.size() != 2 ) {
		sessionEnvironment.raiseMessage( Message( ids::Block, ids::argrx, {
			ast::Node::make<ast::Identifier>( ids::Block ),
			ast::Node::make<math::Rational>( operands.size() ),
			ast::Node::make<math::Rational>( 2 )
		} ));
		return EvaluationFailure();
	}

	const ast::Node& variablesList = operands.front();
	const ast::Node& blockBody = operands.back();

	if ( !variablesList.isFunctionCall(ids::List) ) {
		sessionEnvironment.raiseMessage( Message( ids::Block, ids::lvlist, {
			variablesList
		} ));
		return EvaluationFailure();
	}

	std::vector<std::pair<ast::Identifier, boost::optional<ast::Node>>> localizedVariables;	

	const ast::Operands& listOperands = variablesList.get<ast::FunctionCall>().getOperands();

	for ( const ast::Node& node : listOperands ) {
		ast::Identifier localVariable;
		if ( node.is<ast::Identifier>() ) {
			localVariable = node.get<ast::Identifier>();	
		} else if ( (node.isFunctionCall(ids::Set) || node.isFunctionCall(ids::SetDelayed)) ) {
			if ( node.get<ast::FunctionCall>().getOperands().empty() || !node.get<ast::FunctionCall>().getOperands().front().is<ast::Identifier>() ) {
				sessionEnvironment.raiseMessage( Message( ids::Block, ids::lvsym, {
					variablesList,
					node
				} ));
				return EvaluationFailure();
			}
			localVariable = node.get<ast::FunctionCall>().getOperands().front().get<ast::Identifier>();
		} else {
			sessionEnvironment.raiseMessage( Message( ids::Block, ids::lvsym, {
				variablesList,
				node
			} ));
			return EvaluationFailure();
		}

		boost::optional<ast::Node> replacement = sessionEnvironment.getPatternReplacement( ast::Node::make<ast::Identifier>(localVariable) );
		if (replacement) {
			sessionEnvironment.removePattern( ast::Node::make<ast::Identifier>(localVariable) );
		}
		if (!node.is<ast::Identifier>()) {
			assert(node.isFunctionCall(ids::Set) || node.isFunctionCall(ids::SetDelayed));
			//This will Set the variables correctly
			sessionEnvironment.recursiveEvaluate( node );
		}

		localizedVariables.push_back(std::make_pair(localVariable, replacement));
	}
	
	ast::Node returnNode = sessionEnvironment.recursiveEvaluate( blockBody );

	for ( const auto& idNodePair : localizedVariables ) {
		if ( idNodePair.second ) {
			sessionEnvironment.addPattern( ast::Node::make<ast::Identifier>( idNodePair.first ), *idNodePair.second );	
		} else {
			sessionEnvironment.removePattern( ast::Node::make<ast::Identifier>( idNodePair.first ) );	
		}
	}
	
	return sessionEnvironment.recursiveEvaluate( returnNode );
}

}}} //namespace tungsten::eval::builtin

