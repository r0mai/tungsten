
#include "SessionEnvironment.hpp"

#include <iterator>
#include <vector>
#include <functional>

#include <boost/bind.hpp>
#include <boost/range/algorithm/transform.hpp>

#include "flattenOperands.hpp"

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
		return ast::Node::make<math::Real>(real);
	}

	ast::Node operator()(const math::Rational& rational) {
		return ast::Node::make<math::Rational>(rational);
	}

	ast::Node operator()(const ast::FunctionCall& functionCall) {
		ast::Node function = sessionEnvironment.recursiveEvaluate(functionCall.getFunction());
		ast::Operands operands(functionCall.getOperands().size());

		//TODO Hold*

		boost::transform(
				functionCall.getOperands(),
				operands.begin(),
				boost::bind(&SessionEnvironment::recursiveEvaluate, boost::ref(sessionEnvironment), _1) );


		//Attribute Flat:
		if (
			function.is<ast::Identifier>() &&
			sessionEnvironment.attributeMap.hasAttribute(function.get<ast::Identifier>(), "Flat") )
		{
			operands = flattenOperands( function.get<ast::Identifier>(), operands );
		}


		//TODO Listable

		if ( function.is<ast::Identifier>() ) {
			builtin::Functions::const_iterator it = sessionEnvironment.builtinFunctions.find(function.get<ast::Identifier>());
			if ( it != sessionEnvironment.builtinFunctions.end() ) {
				return (it->second)(operands, sessionEnvironment);
			}
		}

		return ast::Node::make<ast::FunctionCall>(function, operands);

	}

	ast::Node operator()(const ast::String& string) {
		return ast::Node::make<ast::String>(string);
	}

	ast::Node operator()(const ast::Identifier& identifier) {
		//TODO
		return ast::Node::make<ast::Identifier>(identifier);
	}

private:
	SessionEnvironment& sessionEnvironment;
};

ast::Node SessionEnvironment::recursiveEvaluate(const ast::Node& node) {
	EvaluateVisitor evaluateVisitor{*this};
	ast::Node result = ast::applyVisitor(node, evaluateVisitor);

	//Sort if the result is Orderless function
	//Maybe this should be in FunctionCall branch of the Visitor
	if (
			result.is<ast::FunctionCall>() &&
			result.get<ast::FunctionCall>().getFunction().is<ast::Identifier>() &&
			attributeMap.hasAttribute(result.get<ast::FunctionCall>().getFunction().get<ast::Identifier>(), "Orderless") )
	{
		ast::Operands& operands = result.get<ast::FunctionCall>().getOperands();
		std::sort( operands.begin(), operands.end() );
	}

	return result;
}

}} //namespace tungsten::eval


