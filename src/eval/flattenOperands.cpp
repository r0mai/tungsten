

#include "flattenOperands.hpp"

namespace tungsten { namespace eval {

ast::Operands flattenOperands(const ast::Node& function, const ast::Operands& operands) {
	ast::Operands result;

	//TODO eliminate loop, with some clever boost stuff
	for ( unsigned i = 0; i < operands.size(); ++i ) {
		if ( operands[i].isFunctionCall(function) ) {
			const ast::Operands& nestedOperands = flattenOperands(function, operands[i].get<ast::FunctionCall>().getOperands());
			result.insert( result.end(), nestedOperands.begin(), nestedOperands.end() );
		} else {
			result.push_back( operands[i] );
		}
	}

	return result;
}

}} //namespace tungsten::eval

