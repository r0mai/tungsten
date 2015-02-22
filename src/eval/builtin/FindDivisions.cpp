#include <boost/lexical_cast.hpp>
#include <boost/multiprecision/integer.hpp>

#include "functions.hpp"
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

	const math::Rational left = math::findRationalNear(listParams[0].getNumeric());
	const math::Rational right = math::findRationalNear(listParams[1].getNumeric());

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

}}} // namespace tungsten::eval::builtin
