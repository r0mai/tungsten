
#include "PatternMap.hpp"

#include "Identifiers.hpp"

namespace tungsten { namespace eval {


bool tryPattern(const ast::Node& node, const ast::Node& pattern, std::map<ast::Identifier, ast::Node>& patterns);
ast::Node replaceAll(const ast::Node& node, const ast::Identifier& what, const ast::Node& with);

PatternMap::PatternMap() {}

PatternMap PatternMap::makeDefault() {
	PatternMap patternMap;
	patternMap.addPattern(
			ast::Node::make<ast::Identifier>( ids::Infinity ),
			ast::Node::make<ast::FunctionCall>( ids::DirectedInfinity, {ast::Node::make<math::Rational>(1)} ) );
	return patternMap;
}

void PatternMap::addPattern(const ast::Node& pattern, const ast::Node& replacement) {
	storage[pattern] = replacement;
}

bool PatternMap::applyPatterns(const ast::Node& node, ast::Node& result) const {
#if 0

	result = node;
	for ( Storage::value_type patternPair : storage ) {

		std::map<ast::Identifier, ast::Node> patterns;
		if ( tryPattern(node, patternPair.first, patterns) ) {

			for ( const std::pair<ast::Identifier, ast::Node>& replacementPair : patterns ) {
				result = replaceAll( result, replacementPair.first, replacementPair.second );
			}

			std::cout << "result : " << result << std::endl;
			return true;
		}
	}
	return false;
#else
	Storage::const_iterator it = storage.find(node);

	if ( it != storage.cend() ) {
		result = it->second;
		return true;
	}
	result = node;
	return false;
#endif
}

bool isBlank(const ast::Node& pattern, boost::optional<ast::Identifier>& name) {
	name = boost::optional<ast::Identifier>();
	if ( pattern.is<ast::FunctionCall>( ids::Blank ) && pattern.get<ast::FunctionCall>().getOperands().empty() ) {
		return true;
	}
	if ( pattern.is<ast::FunctionCall>( ids::Pattern ) &&
			pattern.get<ast::FunctionCall>().getOperands().size() == 2 &&
			pattern.get<ast::FunctionCall>().getOperands()[0].is<ast::Identifier>() &&
			pattern.get<ast::FunctionCall>().getOperands()[1].is<ast::FunctionCall>( ids::Blank ) &&
			pattern.get<ast::FunctionCall>().getOperands()[1].get<ast::FunctionCall>().getOperands().empty() )
	{
		name = pattern.get<ast::FunctionCall>().getOperands()[0].get<ast::Identifier>();
		return true;
	}
	return false;
}

bool tryPattern(const ast::Node& node, const ast::Node& pattern, std::map<ast::Identifier, ast::Node>& patterns) {
	boost::optional<ast::Identifier> blankName;
	if ( isBlank(pattern, blankName) ) {
		if ( blankName ) {
			patterns[*blankName] = node;
		}
		return true;
	}

	if ( node.is<ast::FunctionCall>() && pattern.is<ast::FunctionCall>() ) {

		const ast::Node& nodeFunction = node.get<ast::FunctionCall>().getFunction();
		const ast::Node& patternFunction = pattern.get<ast::FunctionCall>().getFunction();
		const ast::Operands& nodeOperands = node.get<ast::FunctionCall>().getOperands();
		const ast::Operands& patternOperands = pattern.get<ast::FunctionCall>().getOperands();

		if ( !tryPattern( nodeFunction, patternFunction, patterns) ) {
			return false;
		}

		if ( nodeOperands.size() != patternOperands.size() ) {
			return false;
		}

		for ( ast::Operands::const_iterator
				nodeIterator = nodeOperands.cbegin(), patternIterator = patternOperands.cbegin();
				nodeIterator != nodeOperands.cend();
				++nodeIterator, ++patternIterator )
		{
			if ( !tryPattern( *nodeIterator, *patternIterator, patterns ) ) {
				return false;
			}

		}
		return true;
	}

	return node == pattern;
}

ast::Node replaceAll(const ast::Node& node, const ast::Identifier& what, const ast::Node& with) {
	if ( node.is<ast::Identifier>(what) ) {
		return with;
	}

	if ( node.is<ast::FunctionCall>() ) {
		ast::Node function = replaceAll(node.get<ast::FunctionCall>().getFunction(), what, with);
		ast::Operands operands = node.get<ast::FunctionCall>().getOperands();

		for ( ast::Node& operand : operands ) {
			operand = replaceAll(operand, what, with);
		}

		return ast::Node::make<ast::FunctionCall>(function, operands);
	}
	return node;
}

}} //namespace tungsten::eval
