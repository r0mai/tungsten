
#include "SessionEnvironment.hpp"

#include <iterator>
#include <vector>
#include <functional>

#include <boost/bind.hpp>
#include <boost/range/algorithm/transform.hpp>

namespace tungsten { namespace eval {

SessionEnvironment::SessionEnvironment() :
		attributeMap(AttributeMap::makeDefault()), builtinFunctions(builtin::createFunctions()) {}

SessionEnvironment::~SessionEnvironment() {}

ast::Node SessionEnvironment::evaluate(const ast::Node& node) {
	//TODO update history
	return recursiveEvaluate(node);
}

struct SessionEnvironment::EvaluateVisitor : boost::static_visitor<ast::Node> {

	EvaluateVisitor(SessionEnvironment& sessionEnvironment) :
		sessionEnvironment(sessionEnvironment) {}

	ast::Node operator()(const math::Real& real) {
		return ast::Node::makeReal(real);
	}

	ast::Node operator()(const math::Rational& rational) {
		return ast::Node::makeRational(rational);
	}

	ast::Node operator()(const ast::FunctionCall& functionCall) {
		ast::Node function = sessionEnvironment.recursiveEvaluate(functionCall.getFunction());
		ast::Operands operands(functionCall.getOperands().size());

		boost::transform(
				functionCall.getOperands(),
				operands.begin(),
				boost::bind(&SessionEnvironment::recursiveEvaluate, boost::ref(sessionEnvironment), _1) );

		if ( function.isIdentifier() ) {
			builtin::Functions::const_iterator it = sessionEnvironment.builtinFunctions.find(function.getIdentifier());
			if ( it != sessionEnvironment.builtinFunctions.end() ) {
				return (it->second)(operands, sessionEnvironment);
			}
		}

		return ast::Node::makeFunctionCall(function, operands);

	}

	ast::Node operator()(const ast::String& string) {
		return ast::Node::makeString(string);
	}

	ast::Node operator()(const ast::Identifier& identifier) {
		return ast::Node::makeIdentifier(identifier);
	}

private:
	SessionEnvironment& sessionEnvironment;
};

ast::Node SessionEnvironment::recursiveEvaluate(const ast::Node& node) {
	EvaluateVisitor evaluateVisitor{*this};
	return ast::applyVisitor(node, evaluateVisitor);
}

}} //namespace tungsten::eval


