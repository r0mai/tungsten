
#include "NodeToTeXForm.hpp"

#include "eval/Identifiers.hpp"
#include "eval/getNodeNumerator.hpp"
#include "eval/getNodeDenominator.hpp"

#include <boost/bind.hpp>
#include <boost/algorithm/string/join.hpp>
#include <boost/range/adaptor/transformed.hpp>

namespace tungsten { namespace io {

TeXFormString NodeToTeXForm(const ast::Node& node) {
	return NodeToTeXFormRecursive(node, -1);
}

struct NodeToTeXFormVisitor : boost::static_visitor<TeXFormString> {

	NodeToTeXFormVisitor(int precedence) : precedence(precedence) {}

	TeXFormString operator()(const ast::String& string) const {
		return string.toString();
	}

	TeXFormString operator()(const math::Real& real) const {
		return math::toString(real);
	}

	TeXFormString operator()(const math::Rational& rational) const {
		assert(math::isInteger(rational));
		return math::toString(rational);
	}

	TeXFormString operator()(const ast::Identifier& identifier) const {
		if ( identifier.size() == 1 ) {
			return identifier.toString();
		} else {
			return "\\text{" + identifier.toString() + "}";
		}

	}

	TeXFormString operator()(const ast::FunctionCall& functionCall) const {
		const ast::Node& function = functionCall.getFunction();
		const ast::Operands& operands = functionCall.getOperands();

		TeXFormString result;

		const std::string leftParentheses = "\\left(";
		const std::string rightParentheses = "\\right)";

		if ( function == ast::Node::make<ast::Identifier>( eval::ids::Plus ) ) {

			if ( precedence >= 0 ) { result += leftParentheses; }

			result += boost::join( operands | boost::adaptors::transformed( boost::bind( &NodeToTeXFormRecursive, _1, 0 ) ), "+" );

			if ( precedence >= 0 ) { result += rightParentheses; }

		} else if ( function == ast::Node::make<ast::Identifier>( eval::ids::Times ) ) {

			if ( precedence >= 1 ) { result += leftParentheses; }

			//result += boost::join( operands | boost::adaptors::transformed( boost::bind( &NodeToTeXFormRecursive, _1, 1 ) ), " " );
			result += printPrettyTimes( operands );

			if ( precedence >= 1 ) { result += rightParentheses; }

		} else if ( function == ast::Node::make<ast::Identifier>( eval::ids::Power ) ) {

			if ( operands.size() == 2 && operands[1].is<math::Rational>( math::Rational(1,2) ) ) {
				result += "\\sqrt{" + NodeToTeXFormRecursive(operands[0], -1) + "}";
			} else {

				if ( precedence >= 2 ) { result += leftParentheses; }

				//Might no be the best solution
				result += "{" + boost::join( operands | boost::adaptors::transformed( boost::bind( &NodeToTeXFormRecursive, _1, 2 ) ), "}^{" ) + "}";

				if ( precedence >= 2 ) { result += rightParentheses; }
			}

		} else if ( function == ast::Node::make<ast::Identifier>( eval::ids::List ) ) {

			result += "\\left \\{";

			result += boost::join( operands | boost::adaptors::transformed( boost::bind( &NodeToTeXFormRecursive, _1, -1 ) ), ", " );

			result += "\\right \\}";
		} else if ( function == ast::Node::make<ast::Identifier>( eval::ids::Sqrt ) && operands.size() == 1 ) {
			result += "\\sqrt{" + NodeToTeXFormRecursive(operands[0], -1) + "}";
		} else {

			//TODO 3 is good here?
			result += NodeToTeXFormRecursive(functionCall.getFunction(), 3) +
					leftParentheses +
					boost::join( operands | boost::adaptors::transformed( boost::bind( &NodeToTeXFormRecursive, _1, -1 ) ), ", " ) +
					rightParentheses;

		}

		return result;
	}

	std::string printPrettyTimes(const ast::Operands& operands) const {
		if ( operands.empty() ) {
			return "";
		}

		std::string result = NodeToTeXFormRecursive(operands[0], 1);

		for ( unsigned i = 1; i < operands.size(); ++i ) {
			const ast::Node& prev = operands[i-1];
			const ast::Node& current = operands[i];

			if ( prev.isNumeric() && current.isNumeric() ) {
				result += " \\cdot ";
			} else {
				result += " ";
			}
			result += NodeToTeXFormRecursive(current, 1);
		}
		return result;
	}

	int precedence;
};


TeXFormString NodeToTeXFormRecursive(const ast::Node& node, int precedence) {

	ast::Node numerator = eval::getNodeNumerator( node );
	ast::Node denominator = eval::getNodeDenominator( node );

	if ( denominator == ast::Node::make<math::Rational>(1) ) {
		return ast::applyVisitor( node, NodeToTeXFormVisitor{precedence} );
	} else {
		return "\\frac{" + NodeToTeXFormRecursive(numerator, -1) + "}{" + NodeToTeXFormRecursive(denominator, -1) + "}";
	}




}

}} //namespace tungsten::io
