

#include "flattenOperands.hpp"

#include <limits>

namespace tungsten { namespace eval {

ast::Operands flattenOperands(const ast::Node& function, const ast::Operands& operands) {

	return flattenOperands(function, operands, std::numeric_limits<unsigned long>::max());


}

//FIXME lot of copying goes on here
ast::Operands flattenOperands(const ast::Node& function, const ast::Operands& operands, unsigned long level) {
	if ( level == 0 ) {
		return operands;
	}

	ast::Operands result;

	for ( const ast::Node& node : operands ) {
		if ( node.isFunctionCall(function) ) {
			ast::Operands nestedOperands = flattenOperands(function, node.get<ast::FunctionCall>().getOperands(), level-1);
			result.insert( result.end(), nestedOperands.begin(), nestedOperands.end() );
		} else {
			result.push_back( node );
		}
	}

	return result;

}

}} //namespace tungsten::eval

