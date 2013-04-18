
#include "LevelSpecifier.hpp"

#include <limits>

#include "Identifiers.hpp"
#include "getHead.hpp"

namespace tungsten { namespace eval {

LevelSpecifier::LevelSpecifier() : min(), max() {}
LevelSpecifier::LevelSpecifier(const Depth& min, const Depth& max) : min(min), max(max) {}

//If node is a rational, returns them converted to Depth
//If node is Infinity, or -Infinity, returns numeric_limits<>::min,max
boost::optional<Depth> nodeToSensibleLevelSpec(const ast::Node& node) {
	if ( node.is<math::Rational>() ) {

		if ( !math::isInteger(node.get<math::Rational>()) ) {
			return boost::none_t();
		}

		const math::Integer& level = math::asInteger(node.get<math::Rational>());

		if ( level > std::numeric_limits<Depth>::max() ) {
			return std::numeric_limits<Depth>::max();
		}
		if ( level < std::numeric_limits<Depth>::min() ) {
			return std::numeric_limits<Depth>::max();
		}
		assert( math::fits<Depth>(level) );

		return math::as<Depth>(level);
	}

	//TODO constants: could move out to a special header for constants
	const ast::Node infinity =
			ast::Node::make<ast::FunctionCall>( ids::DirectedInfinity, {ast::Node::make<math::Rational>(1)} );
	const ast::Node negativeInfinity =
			ast::Node::make<ast::FunctionCall>( ids::DirectedInfinity, {ast::Node::make<math::Rational>(-1)} );

	if ( node == infinity ) {
		return std::numeric_limits<Depth>::max();
	}

	if ( node == negativeInfinity ) {
		return std::numeric_limits<Depth>::min();
	}

	return boost::none_t();
}

boost::optional<LevelSpecifier> LevelSpecifier::fromNode(const ast::Node& node) {

	{
		boost::optional<Depth> optionalLevel = nodeToSensibleLevelSpec(node);
		if ( optionalLevel ) {
			return LevelSpecifier(1, *optionalLevel);
		}
	}

	if ( node.isFunctionCall(ids::List) ) {
		const ast::Operands& operands = node.get<ast::FunctionCall>().getOperands();
		switch ( operands.size() ) {
		default:
			return boost::none_t();
		case 0: //Not documented, but valid
			return LevelSpecifier( 0, 0 );
		case 1:
			{
				boost::optional<Depth> optionalLevel = nodeToSensibleLevelSpec(operands[0]);

				if ( !optionalLevel ) {
					return boost::none_t();
				}
				return LevelSpecifier( *optionalLevel, *optionalLevel );
			}
		case 2:
			{
				boost::optional<Depth> optionalLevelMin = nodeToSensibleLevelSpec(operands[0]);
				boost::optional<Depth> optionalLevelMax = nodeToSensibleLevelSpec(operands[1]);

				if ( !optionalLevelMin || !optionalLevelMax ) {
					return boost::none_t();
				}
				return LevelSpecifier( *optionalLevelMin, *optionalLevelMax );
			}
		}
	}
	return boost::none_t();
}

}} //namespace tungsten::eval
