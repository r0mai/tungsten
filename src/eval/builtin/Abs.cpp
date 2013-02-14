#include "functions.hpp"

#include <cassert>

#include <boost/range/algorithm/transform.hpp>

#include "eval/SessionEnvironment.hpp"

namespace tungsten { namespace eval { namespace builtin {

struct AbsVisitor : boost::static_visitor<ast::Node> {

	AbsVisitor(SessionEnvironment& sessionEnvironment) : sessionEnvironment(sessionEnvironment) {}
	template<class T>
	ast::Node operator()(const T& parameter) {
		return ast::Node::make<ast::FunctionCall>(ids::Abs, {
			ast::Node::make<T>(parameter)}
		);
	}
	
	ast::Node operator()(const math::Real& r) {
		return ast::Node::make<math::Real>( abs(r) );
	}
	
	ast::Node operator()(const math::Rational& r) {
		return ast::Node::make<math::Rational>( abs(r) );
	}
	
	ast::Node operator()(const ast::FunctionCall& functionCall) {
		if ( functionCall.getFunction().is<ast::Identifier>( ids::Abs ) ) {
			return ast::Node::make<ast::FunctionCall>( ids::Abs, functionCall.getOperands() );
		} else if ( functionCall.getFunction().is<ast::Identifier>( ids::DirectedInfinity ) &&
				functionCall.getOperands().size() <= 1 )
		{
			return ast::Node::make<ast::FunctionCall>( ids::DirectedInfinity, {ast::Node::make<math::Rational>(1)} );
		}
		return operator()<>(functionCall);
	}
	
	SessionEnvironment& sessionEnvironment;
};


OptionalNode Abs(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment) {
	AbsVisitor absVisitor {sessionEnvironment};
	if(operands.size()==1){
		return ast::applyVisitor(operands[0], absVisitor); }
	else {
		sessionEnvironment.raiseMessage( Message(ids::Abs, ids::argx, {
				ast::Node::make<ast::Identifier>( ids::Abs ),
				ast::Node::make<math::Rational>( operands.size() )
		} ));

		return EvaluationFailure();
	}
	


}


}}} //namespace tungsten::eval::builtin
