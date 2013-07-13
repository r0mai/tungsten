

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

	for ( auto it = operands.begin(); it != operands.end(); ++it ) {
		if ( it->isFunctionCall(function) ) {
			ast::Operands nestedOperands = flattenOperands(function, it->get<ast::FunctionCall>().getOperands(), level-1);
			result.insert( result.end(), nestedOperands.begin(), nestedOperands.end() );
		} else {
			result.push_back( *it );
		}
	}

	return result;

}

}} //namespace tungsten::eval

