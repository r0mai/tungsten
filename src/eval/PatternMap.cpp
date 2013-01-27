
#include "PatternMap.hpp"

#include "Identifiers.hpp"

namespace tungsten { namespace eval {

PatternMap::PatternMap() {}

PatternMap PatternMap::makeDefault() {
	PatternMap patternMap;
	patternMap.addPattern(
			ast::Node::make<ast::Identifier>( ids::Infinity ),
			ast::Node::make<ast::FunctionCall>( ids::DirectedInfinity, {ast::Node::make<math::Rational>(1) } ) );
	return patternMap;
}

void PatternMap::addPattern(const ast::Node& pattern, const ast::Node& replacement) {
	storage[pattern] = replacement;
}

ast::Node PatternMap::applyPatterns(const ast::Node& node) const {
	Storage::const_iterator it = storage.find(node);

	if ( it != storage.cend() ) {
		return it->second;
	}
	return node;
}

}} //namespace tungsten::eval
