
#include "Environment.hpp"

#include <iterator>
#include <vector>
#include <functional>

#include <boost/bind.hpp>
#include <boost/range/algorithm/transform.hpp>

namespace tungsten { namespace eval {

const builtin::Functions Environment::builtinFunctions(builtin::createFunctions());

Environment::Environment() {}

Environment::~Environment() {}

ast::Node Environment::evaluate(const ast::Node& node) {
	//TODO update history
	return recursiveEvaluate(node);
}

struct Environment::EvaluateVisitor : boost::static_visitor<ast::Node> {

	EvaluateVisitor(Environment& environment) : environment(environment) {}

	ast::Node operator()(const math::Real& real) {
		return ast::Node::makeReal(real);
	}

	ast::Node operator()(const math::Rational& rational) {
		return ast::Node::makeRational(rational);
	}

	ast::Node operator()(const ast::FunctionCall& functionCall) {
		ast::Node function = environment.recursiveEvaluate(functionCall.getFunction());
		ast::Operands operands;

		boost::transform(
				functionCall.getOperands(),
				std::back_inserter(operands),
				boost::bind(&Environment::recursiveEvaluate, boost::ref(environment), _1) );

		if ( function.isIdentifier() ) {
			builtin::Functions::const_iterator it = builtinFunctions.find(function.getIdentifier());
			if ( it != builtinFunctions.end() ) {
				return (it->second)(operands, environment);
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
	Environment& environment;
};

ast::Node Environment::recursiveEvaluate(const ast::Node& node) {
	EvaluateVisitor evaluateVisitor{*this};
	return ast::applyVisitor(node, evaluateVisitor);
}

}} //namespace tungsten::eval


