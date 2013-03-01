
#include "FunctionOptions.hpp"
#include "Identifiers.hpp"

namespace tungsten { namespace eval {

FunctionOptions::FunctionOptions(const IdentifierNodeMap& identifierNodeMap) :
		identifierNodeMap(identifierNodeMap) {}

bool FunctionOptions::addFromNodeRange(ast::Operands::const_iterator begin, ast::Operands::const_iterator end) {
	for ( ; begin != end; ++begin ) {
		if ( !addFromNode(*begin) ) {
			return false;
		}
	}
	return true;
}

bool FunctionOptions::addFromNode(const ast::Node& node) {
	if ( !node.is<ast::FunctionCall>() || !node.get<ast::FunctionCall>().getFunction().is<ast::Identifier>()) {
		return false;
	}
	const ast::Identifier& functionName = node.get<ast::FunctionCall>().getFunction().get<ast::Identifier>();
	const ast::Operands& operands = node.get<ast::FunctionCall>().getOperands();

	if ( functionName == ids::List ) {
		return addFromNodeRange( operands.begin(), operands.end() );
	}
	if ( functionName == ids::Rule || functionName == ids::RuleDelayed ) {
		if ( operands.size() != 2 || !operands[0].is<ast::Identifier>() ) {
			return false;
		}
		identifierNodeMap[operands[0].get<ast::Identifier>()] = operands[1];
		return true;
	}
	return false;
}

bool FunctionOptions::hasOption(const ast::Identifier& key) const {
	return identifierNodeMap.find(key) != identifierNodeMap.end();
}

const ast::Node& FunctionOptions::getOption(const ast::Identifier& key) const {
	assert(hasOption(key));
	return identifierNodeMap.find(key)->second;
}

}} //namespace tungsten::eval
