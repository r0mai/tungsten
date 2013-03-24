
#include "IterationSpecifier.hpp"
#include "getHead.hpp"
#include "ast/Node.hpp"
#include "Identifiers.hpp"


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

ListIteration::ListIteration(const std::vector<ast::Node>& iterationValues) :
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

IterationSpecifier::Iterator::Iterator(const std::vector<ast::Node>& iterationValues) :
		currentIndex(0), iterationValues(iterationValues) {}



IterationSpecifier::IterationSpecifier() {}

boost::optional<IterationSpecifier> IterationSpecifier::fromNode(const ast::Node& node, SessionEnvironment& sessionEnvironment) {
	if ( getHead(node) != ast::Node::make<ast::Identifier>(ids::List) ) {
		return boost::none_t(); //failure
	}

	ast::Operands listOperands = node.get<ast::FunctionCall>().getOperands();

	IterationSpecifier iterationSpecifier;

	switch( listOperands.size() ) {
	default:
		return boost::none_t();

	case 1:
		listOperands[0] = sessionEnvironment.recursiveEvaluate(listOperands[0]); //min
		if ( getHead(listOperands[0]) == ast::Node::make<ast::Identifier>(ids::List) ) {
			iterationSpecifier.iteration = detail::ListIteration( listOperands[0].get<ast::FunctionCall>().getOperands() );
		} else if ( listOperands[0].isNumeric() ) {
			iterationSpecifier.iteration = detail::MinMaxIteration(
				ast::Node::make<math::Rational>(1), //min
				//Not evaulatiing these here, they will be evaulated anyway
				sessionEnvironment.recursiveEvaluate(listOperands[0]), //max
				ast::Node::make<math::Rational>(1) //step
			);
		}
		break;

	case 2:
		if ( !listOperands[0].is<ast::Identifier>() ) {
			return boost::none_t();
		}
		iterationSpecifier.optionalVariable = listOperands[0].get<ast::Identifier>();

		listOperands[1] = sessionEnvironment.recursiveEvaluate(listOperands[1]); //max

		if ( getHead(listOperands[1]) == ast::Node::make<ast::Identifier>(ids::List) ) {
			iterationSpecifier.iteration = detail::ListIteration( listOperands[1].get<ast::FunctionCall>().getOperands() );
		} else if ( listOperands[1].isNumeric() ) {
			iterationSpecifier.iteration = detail::MinMaxIteration(
				ast::Node::make<math::Rational>(1), //min
				//Not evaulatiing these here, they will be evaulated anyway
				sessionEnvironment.recursiveEvaluate(listOperands[1]), //max
				ast::Node::make<math::Rational>(1) //step
			);
		} else {
			return boost::none_t();
		}
		break;

	case 3:
		listOperands[1] = sessionEnvironment.recursiveEvaluate(listOperands[1]); //min
		listOperands[2] = sessionEnvironment.recursiveEvaluate(listOperands[2]); //max
		if ( !listOperands[0].is<ast::Identifier>() ||
				!listOperands[1].isNumeric() ||
				!listOperands[2].isNumeric() )
		{
			return boost::none_t();
		}
		iterationSpecifier.optionalVariable = listOperands[0].get<ast::Identifier>();
		iterationSpecifier.iteration = detail::MinMaxIteration(
				listOperands[1], //min
				listOperands[2], //max
			ast::Node::make<math::Rational>(1) //step
		);
		break;
	case 4:
		listOperands[1] = sessionEnvironment.recursiveEvaluate(listOperands[1]); //min
		listOperands[2] = sessionEnvironment.recursiveEvaluate(listOperands[2]); //max
		listOperands[3] = sessionEnvironment.recursiveEvaluate(listOperands[3]); //step
		if ( !listOperands[0].is<ast::Identifier>() ||
				!listOperands[1].isNumeric() ||
				!listOperands[2].isNumeric() ||
				!listOperands[3].isNumeric() )
		{
			return boost::none_t();
		}
		iterationSpecifier.optionalVariable = listOperands[0].get<ast::Identifier>();
		iterationSpecifier.iteration = detail::MinMaxIteration(
			listOperands[1], //min
			listOperands[2], //max
			listOperands[3] //step
		);
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

struct IsFiniteVisitor : boost::static_visitor<bool> {
	bool operator()(const detail::MinMaxIteration& minMaxIteration) const {
		if ( !minMaxIteration.min.isNumeric() ||
				!minMaxIteration.max.isNumeric() ||
				!minMaxIteration.step.isNumeric() )
		{
			return false;
		}

		//{x,1,1,0} is OK, {x,1,2,0} is NOK also it is NOK if any of them is Real
		if ( minMaxIteration.step.getNumeric() == 0.0 ) {
			if ( minMaxIteration.step.is<math::Rational>() &&
					minMaxIteration.min.is<math::Rational>() &&
					minMaxIteration.max.is<math::Rational>() &&
					minMaxIteration.min.get<math::Rational>() == minMaxIteration.max.get<math::Rational>())
			{
				return true;
			}
			return false;
		}

		return true;
	}

	bool operator()(const detail::ListIteration& /*listIteration*/) const {
		return true;
	}
};

bool IterationSpecifier::isFinite() const {
	return boost::apply_visitor( IsFiniteVisitor{}, iteration );
}

template<class Number>
std::vector<ast::Node> minMaxIterationCreator(const Number& min, const Number& max, const Number& step) {
	if ( step == 0 && min == max ) {
		return std::vector<ast::Node>({ast::Node::make<Number>(min)});
	}

	if ( (min < max && step < 0) || (min > max && step > 0) ) {
		return std::vector<ast::Node>({});
	}

	std::vector<ast::Node> resultIteration;
	for ( Number i = min; i <= max; i += step ) {
		resultIteration.push_back( ast::Node::make<Number>(i) );
	}
	return resultIteration;
}

struct MakeIteratorVisitor : boost::static_visitor<std::vector<ast::Node>> {
	std::vector<ast::Node> operator()(const detail::MinMaxIteration& minMaxIteration) const {
		if ( minMaxIteration.max.is<math::Rational>() &&
				minMaxIteration.min.is<math::Rational>() &&
				minMaxIteration.step.is<math::Rational>() )
		{
			return minMaxIterationCreator<math::Rational>(
					minMaxIteration.min.get<math::Rational>(),
					minMaxIteration.max.get<math::Rational>(),
					minMaxIteration.step.get<math::Rational>());
		}

		return minMaxIterationCreator<math::Real>(
				minMaxIteration.min.getNumeric(),
				minMaxIteration.max.getNumeric(),
				minMaxIteration.step.getNumeric());
	}

	std::vector<ast::Node> operator()(const detail::ListIteration& listIteration) const {
		return listIteration.iterationValues;
	}
};

IterationSpecifier::Iterator IterationSpecifier::makeIterator() const {
	assert( isFinite() );
	return boost::apply_visitor( MakeIteratorVisitor{}, iteration );
}

}} //namespace tungsten::eval
