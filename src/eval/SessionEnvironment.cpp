
#include "SessionEnvironment.hpp"

#include <iterator>
#include <vector>
#include <functional>

#include <boost/bind.hpp>
#include <boost/range/algorithm/transform.hpp>

namespace tungsten { namespace eval {

SessionEnvironment::SessionEnvironment() : attributeMap(createDefaultAttributeMap()), builtinFunctions(builtin::createFunctions()) {}

SessionEnvironment::~SessionEnvironment() {}

ast::Node SessionEnvironment::evaluate(const ast::Node& node) {
	//TODO update history
	EvaluationEnvironment evaluationEnvironment;
	return recursiveEvaluate(node, evaluationEnvironment);
}

struct SessionEnvironment::EvaluateVisitor : boost::static_visitor<ast::Node> {

	EvaluateVisitor(SessionEnvironment& sessionEnvironment, EvaluationEnvironment& evaluationEnvironment) :
		sessionEnvironment(sessionEnvironment),
		evaluationEnvironment(evaluationEnvironment) {}

	ast::Node operator()(const math::Real& real) {
		return ast::Node::makeReal(real);
	}

	ast::Node operator()(const math::Rational& rational) {
		return ast::Node::makeRational(rational);
	}

	ast::Node operator()(const ast::FunctionCall& functionCall) {
		ast::Node function = sessionEnvironment.recursiveEvaluate(functionCall.getFunction(), evaluationEnvironment);
		ast::Operands operands;

		boost::transform(
				functionCall.getOperands(),
				std::back_inserter(operands),
				boost::bind(&SessionEnvironment::recursiveEvaluate, boost::ref(sessionEnvironment), _1, boost::ref(evaluationEnvironment)) );

		if ( function.isIdentifier() ) {
			builtin::Functions::const_iterator it = sessionEnvironment.builtinFunctions.find(function.getIdentifier());
			if ( it != sessionEnvironment.builtinFunctions.end() ) {
				return (it->second.regular)(operands, sessionEnvironment, evaluationEnvironment);
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
	EvaluationEnvironment& evaluationEnvironment;
};

ast::Node SessionEnvironment::recursiveEvaluate(const ast::Node& node, EvaluationEnvironment& evaluationEnvironment) {
	EvaluateVisitor evaluateVisitor{*this, evaluationEnvironment};
	return ast::applyVisitor(node, evaluateVisitor);
}

}} //namespace tungsten::eval


