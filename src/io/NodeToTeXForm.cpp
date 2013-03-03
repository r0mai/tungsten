
#include "NodeToTeXForm.hpp"

#include "eval/Identifiers.hpp"
#include "eval/getNodeNumerator.hpp"
#include "eval/getNodeDenominator.hpp"

#include <boost/bind.hpp>
#include <boost/algorithm/string/join.hpp>
#include <boost/range/adaptor/transformed.hpp>

namespace tungsten { namespace io {

TeXFormString NodeToTeXForm(const ast::Node& node, eval::SessionEnvironment& sessionEnvironment) {
	return NodeToTeXFormRecursive(node, sessionEnvironment, -1);
}

struct NodeToTeXFormVisitor : boost::static_visitor<TeXFormString> {

	NodeToTeXFormVisitor(eval::SessionEnvironment& sessionEnvironment, int precedence) :
		sessionEnvironment(sessionEnvironment), precedence(precedence) {}

	TeXFormString operator()(const ast::String& string) {
		return string.toString();
	}

	TeXFormString operator()(const math::Real& real) {
		return math::toString(real);
	}

	TeXFormString operator()(const math::Rational& rational) {
		assert(math::isInteger(rational));
		return math::toString(rational);
	}

	TeXFormString operator()(const ast::Identifier& identifier) {
		return identifier.toString();
	}

	TeXFormString operator()(const ast::FunctionCall& functionCall) {
		const ast::Node& function = functionCall.getFunction();
		const ast::Operands& operands = functionCall.getOperands();

		TeXFormString result;

		const std::string leftParentheses = "\\left(";
		const std::string rightParentheses = "\\right)";

		if ( function == ast::Node::make<ast::Identifier>( eval::ids::Plus ) ) {

			if ( precedence >= 0 ) { result += leftParentheses; }

			result += boost::join( operands | boost::adaptors::transformed( boost::bind( &NodeToTeXFormRecursive, _1, boost::ref(sessionEnvironment), 0 ) ), "+" );

			if ( precedence >= 0 ) { result += rightParentheses; }

		} else if ( function == ast::Node::make<ast::Identifier>( eval::ids::Times ) ) {

			if ( precedence >= 1 ) { result += leftParentheses; }

			result += boost::join( operands | boost::adaptors::transformed( boost::bind( &NodeToTeXFormRecursive, _1, boost::ref(sessionEnvironment), 1 ) ), " " );

			if ( precedence >= 1 ) { result += rightParentheses; }

		} else if ( function == ast::Node::make<ast::Identifier>( eval::ids::Power ) ) {

			if ( precedence >= 2 ) { result += leftParentheses; }

			//Might no be the best solution
			result += "{" + boost::join( operands | boost::adaptors::transformed( boost::bind( &NodeToTeXFormRecursive, _1, boost::ref(sessionEnvironment), 2 ) ), "}^{" ) + "}";

			if ( precedence >= 2 ) { result += rightParentheses; }

		} else if ( function == ast::Node::make<ast::Identifier>( eval::ids::List ) ) {

			result += "\\left \\{";

			result += boost::join( operands | boost::adaptors::transformed( boost::bind( &NodeToTeXFormRecursive, _1, boost::ref(sessionEnvironment), -1 ) ), ", " );

			result += "\\right \\}";

		} else {

			//TODO 3 is good here?
			result += NodeToTeXFormRecursive(functionCall.getFunction(), sessionEnvironment, 3) +
					leftParentheses +
					boost::join( operands | boost::adaptors::transformed( boost::bind( &NodeToTeXFormRecursive, _1, boost::ref(sessionEnvironment), -1 ) ), ", " ) +
					rightParentheses;

		}

		return result;
	}

	eval::SessionEnvironment& sessionEnvironment;
	int precedence;
};


TeXFormString NodeToTeXFormRecursive(const ast::Node& node, eval::SessionEnvironment& sessionEnvironment, int precedence) {

	ast::Node numerator = eval::getNodeNumerator( node, sessionEnvironment );
	ast::Node denominator = eval::getNodeDenominator( node, sessionEnvironment );

	if ( denominator == ast::Node::make<math::Rational>(1) ) {
		NodeToTeXFormVisitor nodeToTeXFormVisitor(sessionEnvironment, precedence);
		return ast::applyVisitor( node, nodeToTeXFormVisitor );
	} else {
		return "\\frac{" + NodeToTeXFormRecursive(numerator, sessionEnvironment, -1) + "}{" + NodeToTeXFormRecursive(denominator, sessionEnvironment, -1) + "}";
	}




}

}} //namespace tungsten::io
