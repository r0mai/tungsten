
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
		return "\\unicode{x22}"+string.getRawString()+"\\unicode{x22}";
	}

	TeXFormString operator()(const math::Real& real) const {
		return math::toString(real);
	}

	TeXFormString operator()(const math::Rational& rational) const {
		assert(math::isInteger(rational));
		return math::toString(rational);
	}

	TeXFormString operator()(const math::ComplexReal& real) const {
		return ast::applyVisitor(ast::Node::make<ast::FunctionCall>(eval::ids::Plus, {
					ast::Node::make<math::Real>(std::real(real)),
					ast::Node::make<ast::FunctionCall>(eval::ids::Times, {
							ast::Node::make<math::Real>(std::imag(real)),
							ast::Node::make<ast::Identifier>(eval::ids::I)
					})
		}), *this);
	}

	TeXFormString operator()(const math::ComplexRational& rational) const {
		return ast::applyVisitor(ast::Node::make<ast::FunctionCall>(eval::ids::Plus, {
					ast::Node::make<math::Real>(std::real(rational)),
					ast::Node::make<ast::FunctionCall>(eval::ids::Times, {
							ast::Node::make<math::Real>(std::imag(rational)),
							ast::Node::make<ast::Identifier>(eval::ids::I)
					})
		}), *this);
	}


	TeXFormString operator()(const ast::Identifier& identifier) const {
		if ( identifier.size() == 1 ) {
			return identifier.toString();
		} else {
			if(identifier == eval::ids::Pi)
				return "\\pi";
			else if(identifier == eval::ids::Infinity)
				return "\\infty";
			else if(identifier == eval::ids::DirectedInfinity)
				return "\\infty";
			else
				return "\\text{" + identifier.toString() + "}";
		}

	}

	TeXFormString operator()(const ast::FunctionCall& functionCall) const {
		const ast::Node& function = functionCall.getFunction();
		const ast::Operands& operands = functionCall.getOperands();

		TeXFormString result;

		const std::string leftParentheses = " \\left(";
		const std::string rightParentheses = " \\right)";

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
				result += " \\sqrt{" + NodeToTeXFormRecursive(operands[0], -1) + "}";
			} else {

				if ( precedence >= 2 ) { result += leftParentheses; }

				//Might no be the best solution
				result += "{" + boost::join( operands | boost::adaptors::transformed( boost::bind( &NodeToTeXFormRecursive, _1, 2 ) ), "}^{" ) + "}";

				if ( precedence >= 2 ) { result += rightParentheses; }
			}

		} else if ( function == ast::Node::make<ast::Identifier>( eval::ids::List ) ) {

			result += " \\left \\{";

			result += boost::join( operands | boost::adaptors::transformed( boost::bind( &NodeToTeXFormRecursive, _1, -1 ) ), ", " );

			result += " \\right \\}";
		} else if ( function == ast::Node::make<ast::Identifier>( eval::ids::Sqrt ) && operands.size() == 1 ) {
			result += " \\sqrt{" + NodeToTeXFormRecursive(operands[0], -1) + "}";
		} else if ( function == ast::Node::make<ast::Identifier>( eval::ids::Less ) && operands.size() == 2) {
			result += NodeToTeXFormRecursive(operands[0], -1) + " \\lt " + NodeToTeXFormRecursive(operands[1], -1);
		} else if (function == ast::Node::make<ast::Identifier>( eval::ids::Greater) && operands.size() == 2) {
			result += NodeToTeXFormRecursive(operands[0], -1) + " \\gt " + NodeToTeXFormRecursive(operands[1], -1);
		} else if (function == ast::Node::make<ast::Identifier>( eval::ids::GreaterEqual) && operands.size() == 2) {
			result += NodeToTeXFormRecursive(operands[0], -1) + " \\ge " + NodeToTeXFormRecursive(operands[1], -1);
		} else if (function == ast::Node::make<ast::Identifier>( eval::ids::LessEqual) && operands.size() == 2) {
			result += NodeToTeXFormRecursive(operands[0], -1) + " \\le " + NodeToTeXFormRecursive(operands[1], -1);
		} else if (function == ast::Node::make<ast::Identifier>( eval::ids::Equal) && operands.size() == 2){
			result += NodeToTeXFormRecursive(operands[0], -1) + " == " + NodeToTeXFormRecursive(operands[1], -1);
		} else if (function == ast::Node::make<ast::Identifier>( eval::ids::Floor) && operands.size() == 1) {
			result += "\\lfloor " + NodeToTeXFormRecursive(operands[0], -1) + "\\rfloor ";
		} else if (function == ast::Node::make<ast::Identifier>( eval::ids::Ceiling) && operands.size() == 1) {
			result += "\\lceil " + NodeToTeXFormRecursive(operands[0], -1) + "\\rceil ";
		} else if (function == ast::Node::make<ast::Identifier>( eval::ids::Abs) && operands.size() == 1) {
			result += '|' + NodeToTeXFormRecursive(operands[0], -1) + '|';
		} else if (function == ast::Node::make<ast::Identifier>( eval::ids::DirectedInfinity) && operands.empty() ) {
			result += operator()(eval::ids::DirectedInfinity);
		} else if (function == ast::Node::make<ast::Identifier>( eval::ids::Rule) && operands.size() ==2 ) {
			result += NodeToTeXFormRecursive(operands[0], -1) + " \\rightarrow " + NodeToTeXFormRecursive(operands[1], -1);
		} else if (function == ast::Node::make<ast::Identifier>( eval::ids::CompoundExpression )) {
			for(unsigned i = 1; i< operands.size(); ++i){
				result += NodeToTeXFormRecursive(operands[i-1], -1) + ';';
			}
			if(operands.back() != ast::Node::make<ast::Identifier>(eval::ids::Null))
				result += NodeToTeXFormRecursive(operands.back(), -1);
		} else if (function == ast::Node::make<ast::Identifier>( eval::ids::Hyperlink ) && operands.size() != 0 && operands.size() <=2 && std::all_of(operands.begin(), operands.end(),
					[](const ast::Node& node){
						return node.is<ast::String>();
					}))
		{
			// allow 1 or 2 operands.
			// Hyperlink[uri]
			// Hyperlink[label, uri]
			std::string label, uri;
			if(operands.size() == 1){
				uri = operands[0].get<ast::String>().getRawString();
				label = uri;
			} else {
				label = operands[0].get<ast::String>().getRawString();
				uri = operands[1].get<ast::String>().getRawString();
			}
			result += " \\href{" + uri + "}{" + label + "}";
		} else if (function == ast::Node::make<ast::Identifier>( eval::ids::Factorial) && operands.size() == 1){
			result += NodeToTeXFormRecursive(operands[0], -1) + "! ";
		} else if (function == ast::Node::make<ast::Identifier>( eval::ids::Factorial2) && operands.size() == 1){
			result += NodeToTeXFormRecursive(operands[0], -1) + "!! ";
		}
		// i dont know.
		else if (function == ast::Node::make<ast::Identifier>( eval::ids::SetDelayed) && operands.size() == 2){
			result += NodeToTeXFormRecursive(operands[0], -1) + " := " + NodeToTeXFormRecursive(operands[1], -1);
		} else if (function == ast::Node::make<ast::Identifier>( eval::ids::Set) && operands.size() == 2){
			result += NodeToTeXFormRecursive(operands[0], -1) + " = " + NodeToTeXFormRecursive(operands[1], -1);
		} else if (function == ast::Node::make<ast::Identifier>( eval::ids::Function) && operands.size() == 1){
			result += NodeToTeXFormRecursive(operands[0], -1) + "\\unicode{x26}"; // fuck if I know. \\& becomes \&amp; in html.
		}
		// i do know
		else if (function == ast::Node::make<ast::Identifier>(eval::ids::Slot) && operands.size() == 1){
			result += " \\#" + NodeToTeXFormRecursive(operands[0], -1);
		} else if(function == ast::Node::make<ast::Identifier>(eval::ids::Sum) && operands.size() == 2 &&
					operands[1].isFunctionCall(eval::ids::List) && operands[1].get<ast::FunctionCall>().getOperands().size() == 3
			){
				const auto assignmentNode = ast::Node::make<ast::FunctionCall>(eval::ids::Set, {
						operands[1].get<ast::FunctionCall>().getOperands()[0], operands[1].get<ast::FunctionCall>().getOperands()[1]
						});
				result+="\\sum_{" + NodeToTeXFormRecursive(assignmentNode, -1)
								  +	"}^{" +
								  NodeToTeXFormRecursive(operands[1].get<ast::FunctionCall>().getOperands()[2], -1)
								  + "}{" +
								  NodeToTeXFormRecursive(operands[0], 0)
								  + '}';

		}
		else {

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

		std::string result;
		if ( operands.size() > 1 &&
			operands[0] == ast::Node::make<math::Rational>(-1) &&
			!operands[1].isNumeric() )
		{
			result = "-";
		} else {
			result = NodeToTeXFormRecursive(operands[0], 1);
		}

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
	boost::optional<ast::Node> optionalDenominator = eval::getPrintableNodeDenominator( node );

	if ( !optionalDenominator ) {
		return ast::applyVisitor( node, NodeToTeXFormVisitor{precedence} );
	} else {
		return " \\frac{" + NodeToTeXFormRecursive(numerator, -1) + "}{" + NodeToTeXFormRecursive(*optionalDenominator, -1) + "}";
	}




}

}} //namespace tungsten::io
