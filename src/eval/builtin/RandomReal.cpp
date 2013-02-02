
#include "functions.hpp"
#include "eval/SessionEnvironment.hpp"

namespace tungsten { namespace eval { namespace builtin {

ast::Node RandomReal(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment) {
	if ( !operands.empty() ) {
		//TODO issue error
		return ast::Node::make<ast::FunctionCall>( ids::RandomReal, operands );
	}

	//We should make it work with math::Real as well
	std::uniform_real_distribution<double> distribution(0, 1);

	return ast::Node::make<math::Real>( distribution( sessionEnvironment.getRandomEngine() ) );
}

}}} //namespace tungsten::eval::builtin





