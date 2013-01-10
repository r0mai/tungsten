
#include "functions.hpp"

#include "eval/SessionEnvironment.hpp"

namespace tungsten { namespace eval { namespace builtin {

struct PowerVisitor : boost::static_visitor<void> {
//TODO have to do templated make in Node
};

ast::Node Power(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment) {

	if ( operands.empty() ) {
		return ast::Node::makeRational(1);
	}

	if ( operands.size() == 1 ) {
		return operands[0];
	}

	ast::Node base = operands[0];
	ast::Node exponent = operands[1];

	if ( operands.size() > 2 ) {
		//Power[x,y,z,...] == Power[x,Power[y,z,...]]
		exponent =
				sessionEnvironment.evaluate(
						ast::Node::makeFunctionCall("Power",
								ast::Operands( operands.begin()+1, operands.end() ) ) );
	}

	return ast::Node::makeFunctionCall("Power", {base, exponent});
}

}}} //namespace tungsten::eval::builtin
