
#include "IterationSpecifier.hpp"
#include "getHead.hpp"
#include "ast/Node.hpp"
#include "Identifiers.hpp"
#include "eval/numericNodeEvaluation.hpp"
#include "eval/createRange.hpp"

namespace tungsten { namespace eval {

namespace detail {


MinMaxIteration::MinMaxIteration() :
		min( ast::Node::make<math::Rational>(0) ),
		max( ast::Node::make<math::Rational>(0) ),
		step( ast::Node::make<math::Rational>(1) ) {}

MinMaxIteration::MinMaxIteration(const ast::Node& min, const ast::Node& max, const ast::Node& step) :
		min( min ),
		max( max ),
		step( step ) {}


ListIteration::ListIteration() {}

ListIteration::ListIteration(const ast::Operands& iterationValues) :
		iterationValues(iterationValues) {}

} //namespace detail

ast::Node IterationSpecifier::Iterator::current() const {
	assert( !isEnd() );
	return iterationValues[currentIndex];
}

bool IterationSpecifier::Iterator::isEnd() const {
	return currentIndex >= iterationValues.size();
}

void IterationSpecifier::Iterator::advance() {
	++currentIndex;
}

IterationSpecifier::Iterator::Iterator() :
		currentIndex(0), iterationValues() {}

IterationSpecifier::Iterator::Iterator(const ast::Operands& iterationValues) :
		currentIndex(0), iterationValues(iterationValues) {}



IterationSpecifier::IterationSpecifier() {}

ast::Node tryConvertToNumeric(ast::Node node, SessionEnvironment& sessionEnvironment) {
	node = sessionEnvironment.recursiveEvaluate(node);
    if ( node.isNumeric() ) {
        return node;
    }
    ast::Node numericNode = numericNodeEvaluation(node, sessionEnvironment);
    if ( numericNode.isNumeric() ) {
        return numericNode;
    }
    return node;
}

boost::optional<IterationSpecifier> IterationSpecifier::fromNode(const ast::Node& node, SessionEnvironment& sessionEnvironment) {
	if ( !node.isFunctionCall(ids::List) ) {
		return boost::none_t(); //failure
	}

	ast::Operands listOperands = node.get<ast::FunctionCall>().getOperands();

	IterationSpecifier iterationSpecifier;

	switch( listOperands.size() ) {
	default:
		return boost::none_t();

	case 1:
		{
			ast::Node& listOperand0 = listOperands.front();
			listOperand0 = sessionEnvironment.recursiveEvaluate(listOperand0); 
			if ( listOperand0.isFunctionCall(ids::List) ) {
				iterationSpecifier.iteration = detail::ListIteration( listOperand0.get<ast::FunctionCall>().getOperands() );
			} else {
				iterationSpecifier.iteration = detail::MinMaxIteration(
					ast::Node::make<math::Rational>(1), //min
					listOperand0, //max
					ast::Node::make<math::Rational>(1) //step
				);
			}
		}
		break;

	case 2:
		{
			ast::Node& listOperand0 = listOperands.front();
			if ( !listOperand0.is<ast::Identifier>() ) {
				return boost::none_t();
			}
			iterationSpecifier.optionalVariable = listOperand0.get<ast::Identifier>();

			ast::Node& listOperand1 = listOperands.back();
			listOperand1 = sessionEnvironment.recursiveEvaluate(listOperand1); 

			if ( listOperand1.isFunctionCall(ids::List) ) {
				iterationSpecifier.iteration = detail::ListIteration( listOperand1.get<ast::FunctionCall>().getOperands() );
			} else {
				iterationSpecifier.iteration = detail::MinMaxIteration(
					ast::Node::make<math::Rational>(1), //min
					listOperand1, //max
					ast::Node::make<math::Rational>(1) //step
				);
			} 
		}
		break;
	case 3:
		{
			ast::Node& listOperand0 = listOperands.front();
			if ( !listOperand0.is<ast::Identifier>() ) {
				return boost::none_t();
			}
			iterationSpecifier.optionalVariable = listOperand0.get<ast::Identifier>();

			ast::Node& listOperand1 = listOperands[1];
			ast::Node& listOperand2 = listOperands.back();

			listOperand1 = sessionEnvironment.recursiveEvaluate(listOperand1); 
			listOperand2 = sessionEnvironment.recursiveEvaluate(listOperand2); 

			iterationSpecifier.iteration = detail::MinMaxIteration(
					listOperand1, //min
					listOperand2, //max
				ast::Node::make<math::Rational>(1) //step
			);
		}
		break;
	case 4:
		{
			ast::Node& listOperand0 = listOperands.front();

			if ( !listOperand0.is<ast::Identifier>() ) {
				return boost::none_t();
			}
			ast::Node& listOperand1 = listOperands[1];
			ast::Node& listOperand2 = listOperands[2];
			ast::Node& listOperand3 = listOperands.back();

			listOperand1 = sessionEnvironment.recursiveEvaluate(listOperand1); 
			listOperand2 = sessionEnvironment.recursiveEvaluate(listOperand2); 
			listOperand3 = sessionEnvironment.recursiveEvaluate(listOperand3); 

			iterationSpecifier.optionalVariable = listOperand0.get<ast::Identifier>();
			iterationSpecifier.iteration = detail::MinMaxIteration(
				listOperand1, //min
				listOperand2, //max
				listOperand3 //step
			);
		}
		break;
	}
	return iterationSpecifier;

}

bool IterationSpecifier::hasVariable() const {
	return optionalVariable.is_initialized();
}

ast::Identifier IterationSpecifier::getVariable() const {
	assert(hasVariable());
	return optionalVariable.get();
}


struct MakeIteratorVisitor : boost::static_visitor<boost::optional<ast::Operands>> {

	MakeIteratorVisitor(SessionEnvironment& sessionEnvironment) : sessionEnvironment(sessionEnvironment) {}

	boost::optional<ast::Operands> operator()(const detail::MinMaxIteration& minMaxIteration) {
		return createRange(minMaxIteration.min, minMaxIteration.max, minMaxIteration.step, sessionEnvironment);
	}

	boost::optional<ast::Operands> operator()(const detail::ListIteration& listIteration) {
		return listIteration.iterationValues;
	}

	SessionEnvironment& sessionEnvironment;
};

boost::optional<IterationSpecifier::Iterator> IterationSpecifier::makeIterator(SessionEnvironment& sessionEnvironment) const {
	MakeIteratorVisitor makeIteratorVisitor{sessionEnvironment};
	boost::optional<ast::Operands> optionalResult = boost::apply_visitor( makeIteratorVisitor, iteration );
	if ( optionalResult ) {
		return IterationSpecifier::Iterator( *optionalResult );
	}
	return boost::none_t();
}

}} //namespace tungsten::eval
