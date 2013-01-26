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
		if(r>0)
			return ast::Node::make<math::Real>(r);
		else
			return sessionEnvironment.evaluate(
			ast::Node::make<ast::FunctionCall>(ids::Times, {
				ast::Node::make<math::Real>(r),
				ast::Node::make<math::Real>(-1)
			}));
	}
	
	ast::Node operator()(const math::Rational& r) {
		if(r>0)
			return ast::Node::make<math::Rational>(r);
		else
			return sessionEnvironment.evaluate(
			ast::Node::make<ast::FunctionCall>(ids::Times, {
				ast::Node::make<math::Rational>(r),
				ast::Node::make<math::Rational>(-1)
			}));
	}
	
	ast::Node operator()(const ast::FunctionCall& functionCall) {
		if ( functionCall.getFunction().is<ast::Identifier>( ids::Abs ) ) {
			return ast::Node::make<ast::FunctionCall>( ids::Abs, functionCall.getOperands() );
		}
		return operator()<>(functionCall);
	}
	
	SessionEnvironment& sessionEnvironment;
};


ast::Node Abs(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment) {
	AbsVisitor absVisitor {sessionEnvironment};
	if(operands.size()==1){ return ast::applyVisitor(operands[0], absVisitor); }
	else { return ast::Node::make<ast::FunctionCall>(ids::Abs, operands); }
	


}


}}} //namespace tungsten::eval::builtin
