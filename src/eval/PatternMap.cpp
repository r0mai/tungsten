
#include "PatternMap.hpp"
#include "patternMatching.hpp"
#include "Identifiers.hpp"
#include "SessionEnvironment.hpp"

namespace tungsten { namespace eval {


bool tryPattern(const ast::Node& node, const ast::Node& pattern, std::map<ast::Identifier, ast::Node>& patterns);
ast::Node replaceAll(const ast::Node& node, const ast::Identifier& what, const ast::Node& with);

PatternMap::PatternMap() {}

PatternMap PatternMap::makeDefault() {
	PatternMap patternMap;
	patternMap.addPattern(
			ast::Node::make<ast::Identifier>( ids::Infinity ),
			ast::Node::make<ast::FunctionCall>( ids::DirectedInfinity, {ast::Node::make<math::Rational>(1)} ) );
	patternMap.addPattern(
			ast::Node::make<ast::Identifier>( ids::ComplexInfinity ),
			ast::Node::make<ast::FunctionCall>( ids::DirectedInfinity, {} ) );

	patternMap.addPattern(ast::Node::make<ast::Identifier>(ids::Red), ast::Node::make<ast::FunctionCall>(ids::RGBColor, {ast::Node::make<math::Rational>(1), ast::Node::make<math::Rational>(0), ast::Node::make<math::Rational>(0)}));
	patternMap.addPattern(ast::Node::make<ast::Identifier>(ids::Green), ast::Node::make<ast::FunctionCall>(ids::RGBColor, {ast::Node::make<math::Rational>(0), ast::Node::make<math::Rational>(1), ast::Node::make<math::Rational>(0)}));
	patternMap.addPattern(ast::Node::make<ast::Identifier>(ids::Blue), ast::Node::make<ast::FunctionCall>(ids::RGBColor, {ast::Node::make<math::Rational>(0), ast::Node::make<math::Rational>(0), ast::Node::make<math::Rational>(1)}));
	patternMap.addPattern(ast::Node::make<ast::Identifier>(ids::Black), ast::Node::make<ast::FunctionCall>(ids::GrayLevel, {ast::Node::make<math::Rational>(0)}));
	patternMap.addPattern(ast::Node::make<ast::Identifier>(ids::White), ast::Node::make<ast::FunctionCall>(ids::GrayLevel, {ast::Node::make<math::Rational>(1)}));
	patternMap.addPattern(ast::Node::make<ast::Identifier>(ids::Gray), ast::Node::make<ast::FunctionCall>(ids::GrayLevel, {ast::Node::make<math::Real>(0.5)}));
	patternMap.addPattern(ast::Node::make<ast::Identifier>(ids::Cyan), ast::Node::make<ast::FunctionCall>(ids::RGBColor, {ast::Node::make<math::Rational>(0), ast::Node::make<math::Rational>(1), ast::Node::make<math::Rational>(1)}));
	patternMap.addPattern(ast::Node::make<ast::Identifier>(ids::Magenta), ast::Node::make<ast::FunctionCall>(ids::RGBColor, {ast::Node::make<math::Rational>(1), ast::Node::make<math::Rational>(0), ast::Node::make<math::Rational>(1)}));
	patternMap.addPattern(ast::Node::make<ast::Identifier>(ids::Yellow), ast::Node::make<ast::FunctionCall>(ids::RGBColor, {ast::Node::make<math::Rational>(1), ast::Node::make<math::Rational>(1), ast::Node::make<math::Rational>(0)}));
	patternMap.addPattern(ast::Node::make<ast::Identifier>(ids::Brown), ast::Node::make<ast::FunctionCall>(ids::RGBColor, {ast::Node::make<math::Real>(0.6), ast::Node::make<math::Real>(0.4), ast::Node::make<math::Real>(0.2)}));
	patternMap.addPattern(ast::Node::make<ast::Identifier>(ids::Orange), ast::Node::make<ast::FunctionCall>(ids::RGBColor, {ast::Node::make<math::Rational>(1), ast::Node::make<math::Real>(0.5), ast::Node::make<math::Rational>(0)}));
	patternMap.addPattern(ast::Node::make<ast::Identifier>(ids::Pink), ast::Node::make<ast::FunctionCall>(ids::RGBColor, {ast::Node::make<math::Rational>(1), ast::Node::make<math::Real>(0.5), ast::Node::make<math::Real>(0.5)}));
	patternMap.addPattern(ast::Node::make<ast::Identifier>(ids::Purple), ast::Node::make<ast::FunctionCall>(ids::RGBColor, {ast::Node::make<math::Real>(0.5), ast::Node::make<math::Rational>(0), ast::Node::make<math::Real>(0.5)}));
	patternMap.addPattern(ast::Node::make<ast::Identifier>(ids::LightRed), ast::Node::make<ast::FunctionCall>(ids::RGBColor, {ast::Node::make<math::Rational>(1), ast::Node::make<math::Real>(0.85), ast::Node::make<math::Real>(0.85)}));
	patternMap.addPattern(ast::Node::make<ast::Identifier>(ids::LightGreen), ast::Node::make<ast::FunctionCall>(ids::RGBColor, {ast::Node::make<math::Real>(0.88), ast::Node::make<math::Rational>(1), ast::Node::make<math::Real>(0.88)}));
	patternMap.addPattern(ast::Node::make<ast::Identifier>(ids::LightBlue), ast::Node::make<ast::FunctionCall>(ids::RGBColor, {ast::Node::make<math::Real>(0.87), ast::Node::make<math::Real>(0.94), ast::Node::make<math::Rational>(1)}));
	patternMap.addPattern(ast::Node::make<ast::Identifier>(ids::LightGray), ast::Node::make<ast::FunctionCall>(ids::GrayLevel, {ast::Node::make<math::Real>(0.85)}));
	patternMap.addPattern(ast::Node::make<ast::Identifier>(ids::LightCyan), ast::Node::make<ast::FunctionCall>(ids::RGBColor, {ast::Node::make<math::Real>(0.9), ast::Node::make<math::Rational>(1), ast::Node::make<math::Rational>(1)}));
	patternMap.addPattern(ast::Node::make<ast::Identifier>(ids::LightMagenta), ast::Node::make<ast::FunctionCall>(ids::RGBColor, {ast::Node::make<math::Rational>(1), ast::Node::make<math::Real>(0.9), ast::Node::make<math::Rational>(1)}));
	patternMap.addPattern(ast::Node::make<ast::Identifier>(ids::LightYellow), ast::Node::make<ast::FunctionCall>(ids::RGBColor, {ast::Node::make<math::Rational>(1), ast::Node::make<math::Rational>(1), ast::Node::make<math::Real>(0.85)}));
	patternMap.addPattern(ast::Node::make<ast::Identifier>(ids::LightBrown), ast::Node::make<ast::FunctionCall>(ids::RGBColor, {ast::Node::make<math::Real>(0.94), ast::Node::make<math::Real>(0.91), ast::Node::make<math::Real>(0.88)}));
	patternMap.addPattern(ast::Node::make<ast::Identifier>(ids::LightOrange), ast::Node::make<ast::FunctionCall>(ids::RGBColor, {ast::Node::make<math::Rational>(1), ast::Node::make<math::Real>(0.9), ast::Node::make<math::Real>(0.8)}));
	patternMap.addPattern(ast::Node::make<ast::Identifier>(ids::LightPink), ast::Node::make<ast::FunctionCall>(ids::RGBColor, {ast::Node::make<math::Rational>(1), ast::Node::make<math::Real>(0.925), ast::Node::make<math::Real>(0.925)}));
	patternMap.addPattern(ast::Node::make<ast::Identifier>(ids::LightPurple), ast::Node::make<ast::FunctionCall>(ids::RGBColor, {ast::Node::make<math::Real>(0.94), ast::Node::make<math::Real>(0.88), ast::Node::make<math::Real>(0.94)}));
	patternMap.addPattern(ast::Node::make<ast::Identifier>(ids::Transparent), ast::Node::make<ast::FunctionCall>(ids::GrayLevel, {ast::Node::make<math::Rational>(0), ast::Node::make<math::Rational>(0)}));
	patternMap.addPattern(ast::Node::make<ast::Identifier>(ids::Thick), ast::Node::make<ast::FunctionCall>(ids::Thickness, {ast::Node::make<ast::Identifier>(ids::Large)}));
	patternMap.addPattern(ast::Node::make<ast::Identifier>(ids::Thin), ast::Node::make<ast::FunctionCall>(ids::Thickness, {ast::Node::make<ast::Identifier>(ids::Tiny)}));
	patternMap.addPattern(ast::Node::make<ast::Identifier>(ids::Dashed), ast::Node::make<ast::FunctionCall>(ids::Dashing, {ast::Node::make<ast::FunctionCall>(ids::List, {ast::Node::make<ast::Identifier>(ids::Small), ast::Node::make<ast::Identifier>(ids::Small)})}));
	patternMap.addPattern(ast::Node::make<ast::Identifier>(ids::Dotted), ast::Node::make<ast::FunctionCall>(ids::Dashing, {ast::Node::make<ast::FunctionCall>(ids::List, {ast::Node::make<math::Rational>(0), ast::Node::make<ast::Identifier>(ids::Small)})}));
	patternMap.addPattern(ast::Node::make<ast::Identifier>(ids::DotDashed), ast::Node::make<ast::FunctionCall>(ids::Dashing, {ast::Node::make<ast::FunctionCall>(ids::List, {ast::Node::make<math::Rational>(0), ast::Node::make<ast::Identifier>(ids::Small), ast::Node::make<ast::Identifier>(ids::Small), ast::Node::make<ast::Identifier>(ids::Small)})}));
	patternMap.addPattern(ast::Node::make<ast::Identifier>(ids::I), ast::Node::make<math::ComplexRational>(math::Rational{0}, math::Rational{1}));

	return patternMap;
}

void PatternMap::addPattern(const ast::Node& pattern, const ast::Node& replacement) {
	Storage::iterator location = std::find_if( storage.begin(), storage.end(), [&pattern](const Storage::value_type& p) { return p.first == pattern; } );
	if ( location != storage.end() ) {
		storage.erase(location);
	}
	storage.push_back( std::make_pair(pattern, replacement) );
}

boost::optional<ast::Node> PatternMap::getPatternReplacement(const ast::Node& pattern) const {
	Storage::const_iterator location = std::find_if( storage.begin(), storage.end(), [&pattern](const Storage::value_type& p) { return p.first == pattern; } );
	if ( location == storage.end() ) {
		return boost::none_t();
	}
	return location->second;
}

void PatternMap::removePattern(const ast::Node& pattern) {
	Storage::iterator location = std::find_if( storage.begin(), storage.end(), [&pattern](const Storage::value_type& p) { return p.first == pattern; } );
	if ( location != storage.end() ) {
		storage.erase(location);
	}
}

bool PatternMap::applyPatterns(const ast::Node& node, ast::Node& result, eval::SessionEnvironment& sessionEnvironment) const {

	for ( const std::pair<ast::Node, ast::Node>& assignmentPattern : storage ) {
		MatchedPatternMap matchedPatternMap;
		if ( doesPatternMatch(node, assignmentPattern.first, matchedPatternMap, sessionEnvironment) ) {
			result = applyPatternMapImmutable(assignmentPattern.second, matchedPatternMap);
			return true;
		}
	}
	return false;
}

}} //namespace tungsten::eval
