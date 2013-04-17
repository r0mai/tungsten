

#include <functional>
#include <boost/logic/tribool.hpp>

#include "functions.hpp"
#include "eval/SessionEnvironment.hpp"
#include "eval/numericNodeEvaluation.hpp"

namespace tungsten { namespace eval { namespace builtin {

template<class Func>
boost::tribool compareNodes(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment, Func func) {
	for ( unsigned i = 1; i < operands.size(); ++i ) {

		ast::Node lhs = numericNodeEvaluation(operands[i-1], sessionEnvironment);
		ast::Node rhs = numericNodeEvaluation(operands[i], sessionEnvironment);

		if ( !lhs.isNumeric() || !rhs.isNumeric() ) {
			return boost::indeterminate;
		}
		if ( !func(lhs.getNumeric(), rhs.getNumeric()) ) {
			return false;
		}
	}
	return true;
}

OptionalNode Equal(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment) {
	//TODO Indeterminate == Indeterminate
	if ( operands.size() != 2 ) {
		return EvaluationFailure();
	}
	const ast::Node& lhs = operands[0];
	const ast::Node& rhs = operands[1];
	boost::tribool result = boost::indeterminate;
	if ( lhs.is<math::Rational>() && rhs.is<math::Rational>() ) {
		result = lhs.get<math::Rational>() == rhs.get<math::Rational>();
	} else {
		ast::Node numericLhs = numericNodeEvaluation(lhs, sessionEnvironment);
		ast::Node numericRhs = numericNodeEvaluation(rhs, sessionEnvironment);
		if ( numericLhs.isNumeric() && numericRhs.isNumeric() ) {
			result = numericLhs == numericRhs;
		}
	}
	if ( result ) {
		return ast::Node::make<ast::Identifier>(ids::True);
	} else if ( !result ) {
		return ast::Node::make<ast::Identifier>(ids::False);
	} else {
		return EvaluationFailure();
	}
		
}

OptionalNode Unequal(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment) {
	//TODO Indeterminate == Indeterminate
	if ( operands.size() != 2 ) {
		return EvaluationFailure();
	}
	const ast::Node& lhs = operands[0];
	const ast::Node& rhs = operands[1];
	boost::tribool result = boost::indeterminate;
	if ( lhs.is<math::Rational>() && rhs.is<math::Rational>() ) {
		result = lhs.get<math::Rational>() != rhs.get<math::Rational>();
	} else {
		ast::Node numericLhs = numericNodeEvaluation(lhs, sessionEnvironment);
		ast::Node numericRhs = numericNodeEvaluation(rhs, sessionEnvironment);
		if ( numericLhs.isNumeric() && numericRhs.isNumeric() ) {
			result = numericLhs != numericRhs;
		}
	}
	if ( result ) {
		return ast::Node::make<ast::Identifier>(ids::True);
	} else if ( !result ) {
		return ast::Node::make<ast::Identifier>(ids::False);
	} else {
		return EvaluationFailure();
	}
}

OptionalNode Less(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment) {

	boost::tribool result = compareNodes( operands, sessionEnvironment, std::less<math::Real>() );

	if ( result ) {
		return ast::Node::make<ast::Identifier>(ids::True);
	} else if ( !result ) {
		return ast::Node::make<ast::Identifier>(ids::False);
	} else {
		return ast::Node::make<ast::FunctionCall>(ids::Less, operands);
	}

}

OptionalNode LessEqual(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment) {

	boost::tribool result = compareNodes( operands, sessionEnvironment, std::less_equal<math::Real>() );

	if ( result ) {
		return ast::Node::make<ast::Identifier>(ids::True);
	} else if ( !result ) {
		return ast::Node::make<ast::Identifier>(ids::False);
	} else {
		return ast::Node::make<ast::FunctionCall>(ids::LessEqual, operands);
	}

}


OptionalNode Greater(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment) {

	boost::tribool result = compareNodes( operands, sessionEnvironment, std::greater<math::Real>() );

	if ( result ) {
		return ast::Node::make<ast::Identifier>(ids::True);
	} else if ( !result ) {
		return ast::Node::make<ast::Identifier>(ids::False);
	} else {
		return ast::Node::make<ast::FunctionCall>(ids::Greater, operands);
	}

}


OptionalNode GreaterEqual(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment) {

	boost::tribool result = compareNodes( operands, sessionEnvironment, std::greater_equal<math::Real>() );

	if ( result ) {
		return ast::Node::make<ast::Identifier>(ids::True);
	} else if ( !result ) {
		return ast::Node::make<ast::Identifier>(ids::False);
	} else {
		return ast::Node::make<ast::FunctionCall>(ids::GreaterEqual, operands);
	}

}


}}}; // tungsten::eval::builtin;
