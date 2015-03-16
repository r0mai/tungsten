#include <boost/lexical_cast.hpp>
#include <boost/multiprecision/integer.hpp>

#include "functions.hpp"
#include "eval/overload.hpp"
#include "eval/SessionEnvironment.hpp"
#include "math/mathFunctions.hpp"

namespace tungsten { namespace eval { namespace builtin {

OptionalNode FindDivisions(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment) {
	if ( operands.size() != 2 ) {
		sessionEnvironment.raiseMessage( Message(ids::FindDivisions, ids::argrx, {
				ast::Node::make<ast::Identifier>( ids::FindDivisions ),
				ast::Node::make<math::Rational>( operands.size() ),
				ast::Node::make<math::Rational>( 2 )
		} ));
		return EvaluationFailure();
	}

	const auto range = operands[0];
	const auto numberOfElements = operands[1];

	if ( !range.isFunctionCall(ids::List) || range.get<ast::FunctionCall>().getOperands().size() != 2) {
		sessionEnvironment.raiseMessage( Message(ids::FindDivisions, ids::fdargs, {
				range,
				ast::Node::make<ast::FunctionCall>( ids::FindDivisions, operands )
		} ));
		return EvaluationFailure();
	}

	if ( !numberOfElements.is<math::Rational>() || !math::isInteger(numberOfElements.get<math::Rational>()) ) {
		sessionEnvironment.raiseMessage( Message(ids::FindDivisions, ids::fdargs, {
				numberOfElements,
				ast::Node::make<ast::FunctionCall>( ids::FindDivisions, operands )
		} ));
		return EvaluationFailure();
	}

	std::vector<ast::Node> listParams = range.get<ast::FunctionCall>().getOperands();

	auto endIt = std::find_if_not(listParams.begin(), listParams.end(), [](const ast::Node& param) {
			return param.isNumeric();
	});

	if (endIt != listParams.end()) {
		sessionEnvironment.raiseMessage( Message(ids::FindDivisions, ids::fdargs, {
				*endIt,
				ast::Node::make<ast::FunctionCall>( ids::FindDivisions, operands )
		} ));
		return EvaluationFailure();
	}

	const math::Real precision = (listParams[1].getNumeric() - listParams[0].getNumeric())/numberOfElements.getInteger();

	const math::Rational left = math::findRationalNear(listParams[0].getNumeric(), precision);
	const math::Rational right = math::findRationalNear(listParams[1].getNumeric(), precision);

	std::vector<math::Rational> intermediates;

	// Impl here

	intermediates.push_back(left);

	const math::Rational distance = right - left;

	std::vector<math::Rational> multipliersbase = {1, 2, 5};
	std::vector<math::Rational> multipliers;

	for(int i=-2;i<2;++i) {
		std::vector<math::Rational> newValues(multipliersbase.begin(), multipliersbase.end());
		math::Rational magnitude = math::power(math::Rational{10}, i);
		for(auto& nv: newValues) { nv*=magnitude; }
		multipliers.insert(multipliers.end(), newValues.begin(), newValues.end());
	}

	const auto multiplierIt = std::find_if(multipliers.begin(), multipliers.end(), [&](const math::Rational& multiplier) {
			// return true if multiplier would result in less ticks that requested
			return (math::Real{distance}/multiplier) < numberOfElements.getNumeric();
	});


	const auto multiplier = *(multiplierIt-1);
	for(math::Rational next = left + multiplier; next <= right ; next += multiplier) {
		intermediates.push_back(next);
	}

	ast::Operands elements;
	for(auto& intermediate: intermediates) {
		elements.push_back(ast::Node::make<math::Rational>(intermediate));
	}
	return ast::Node::make<ast::FunctionCall>(ids::List, elements);
}

namespace ContinuedFractionImpl {

template<typename... Ts>
OptionalNode continuedFraction(eval::SessionEnvironment& sessionEnvironment, const Ts&...) {
	return EvaluationFailure();
}

template<>
OptionalNode continuedFraction<math::Real>(eval::SessionEnvironment& sessionEnvironment, const math::Real& r) {
	auto cf = math::getContinuedFraction(r);

	ast::Operands result;
	result.reserve(cf.size());

	for(auto& element: cf) {
		result.push_back(ast::Node::make<math::Rational>(std::move(element)));
	}

	return ast::Node::make<ast::FunctionCall>(ids::List, result);

}

template<>
OptionalNode continuedFraction<math::Real, math::Rational>(eval::SessionEnvironment& sessionEnvironment, const math::Real& r, const math::Rational& n) {
	if(n < 0 || ! math::isInteger(n)) {
		return EvaluationFailure();
	}
	auto cf = math::getContinuedFraction(r);

	auto elementsToKeep = n.convert_to<std::size_t>();

	ast::Operands result;
	result.reserve(std::min(cf.size(), elementsToKeep));

	for(int i=0; i<std::min(cf.size(), elementsToKeep); ++i) {
		result.push_back(ast::Node::make<math::Rational>(std::move(cf[i])));
	}

	return ast::Node::make<ast::FunctionCall>(ids::List, result);
}

} // namespace ContinuedFractionImpl

struct ContinuedFractionType {
	template<typename... Ts>
	OptionalNode operator()(eval::SessionEnvironment& sessionEnvironment, const Ts&... ts) {
		return ContinuedFractionImpl::continuedFraction<typename std::decay<Ts>::type...>(sessionEnvironment, ts...);
	}
};


OptionalNode ContinuedFraction(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment) {
	return eval::Dispatcher<ContinuedFractionType>{sessionEnvironment}(operands);
}

}}} // namespace tungsten::eval::builtin
