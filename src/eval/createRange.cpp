
#include "createRange.hpp"
#include "Identifiers.hpp"

namespace tungsten { namespace eval {

boost::optional<ast::Operands> createRange(const ast::Node& min, const ast::Node& max, const ast::Node& step, SessionEnvironment& sessionEnvironment) {
	if ( min == max ) {
		return ast::Operands({min});
	}

	ast::Node numberOfStepsNode = sessionEnvironment.recursiveEvaluate(
	ast::Node::make<ast::FunctionCall>(ids::Floor, {
		ast::Node::make<ast::FunctionCall>(ids::Times, {
			ast::Node::make<ast::FunctionCall>(ids::Plus, {
				ast::Node::make<ast::FunctionCall>(ids::Times, {
					min,
					ast::Node::make<math::Rational>(-1)
				}),
				max
			}),
			ast::Node::make<ast::FunctionCall>(ids::Power, {
				step,
				ast::Node::make<math::Rational>(-1)
			})
		})
	}));
	if ( !numberOfStepsNode.is<math::Rational>() ) {
		return boost::none_t();
	}
	assert( math::isInteger(numberOfStepsNode.get<math::Rational>()) );
	const math::Integer& numberOfStepsInteger = math::asInteger(numberOfStepsNode.get<math::Rational>());

	if ( numberOfStepsInteger < 0 ) {
		return ast::Operands();
	}

	if ( !math::fits<std::size_t>(numberOfStepsInteger+1) ) {
		return boost::none_t();
	}

	std::size_t resultSize = math::as<std::size_t>(numberOfStepsInteger)+1;
	ast::Operands result;
	result.reserve( resultSize );

	for ( std::size_t i = 0; i < resultSize; ++i ) {
		result.push_back( sessionEnvironment.recursiveEvaluate(
			ast::Node::make<ast::FunctionCall>(ids::Plus, {
				min,
				ast::Node::make<ast::FunctionCall>(ids::Times, {
					ast::Node::make<math::Rational>( i ),
					step,
				})
			})
		));
	}
	return result;

}

}} //namespace tungsten::eval
