
#include "NodeToInputForm.hpp"

#include "eval/Identifiers.hpp"

#include <boost/bind.hpp>
#include <boost/algorithm/string/join.hpp>
#include <boost/range/adaptor/transformed.hpp>

namespace tungsten { namespace io {

InputFormString NodeToInputForm(const ast::Node& node) {
	return NodeToInputFormRecursive(node, -1);
}

struct NodeToInputFormVisitor : boost::static_visitor<InputFormString> {

	NodeToInputFormVisitor(int precedence) : precedence(precedence) {}

	InputFormString operator()(const ast::String& string) const {
		return string.toString();
	}

	InputFormString operator()(const math::Real& real) const {
		return math::toString(real);
	}

	InputFormString operator()(const math::Rational& rational) const {
		if ( math::isInteger(rational) || precedence < 1 ) {
			return math::toString(rational);
		} else {
			return InputFormString(1, '(') + math::toString(rational) + InputFormString(1, ')');
		}
	}

	InputFormString operator()(const math::ComplexReal& real) const {
		if(!real.imag())
			return math::toString(real.real());
		return ast::applyVisitor(ast::Node::make<ast::FunctionCall>(eval::ids::Plus, {
					ast::Node::make<math::Real>(std::real(real)),
					ast::Node::make<ast::FunctionCall>(eval::ids::Times, {
							ast::Node::make<math::Real>(std::imag(real)),
							ast::Node::make<ast::Identifier>(eval::ids::I)
					})
		}), *this);
	}

	InputFormString operator()(const math::ComplexRational& rational) const {
		if(!rational.imag())
			return math::toString(rational.real());
		return ast::applyVisitor(ast::Node::make<ast::FunctionCall>(eval::ids::Plus, {
					ast::Node::make<math::Real>(std::real(rational)),
					ast::Node::make<ast::FunctionCall>(eval::ids::Times, {
							ast::Node::make<math::Real>(std::imag(rational)),
							ast::Node::make<ast::Identifier>(eval::ids::I)
					})
		}), *this);
	}

	InputFormString operator()(const ast::Identifier& identifier) const {
		return identifier.toString();
	}

	InputFormString operator()(const ast::FunctionCall& functionCall) const {
		const ast::Node& function = functionCall.getFunction();
		const ast::Operands& operands = functionCall.getOperands();

		InputFormString result;

		if ( function == ast::Node::make<ast::Identifier>( eval::ids::Plus ) ) {

			if ( precedence >= 0 ) { result += '('; }

			result += boost::join( operands | boost::adaptors::transformed( boost::bind( &NodeToInputFormRecursive, _1, 0 ) ), "+" );

			if ( precedence >= 0 ) { result += ')'; }

		} else if ( function == ast::Node::make<ast::Identifier>( eval::ids::Times ) ) {

			if ( precedence >= 1 ) { result += '('; }

			result += boost::join( operands | boost::adaptors::transformed( boost::bind( &NodeToInputFormRecursive, _1, 1 ) ), "*" );

			if ( precedence >= 1 ) { result += ')'; }

		} else if ( function == ast::Node::make<ast::Identifier>( eval::ids::Power ) ) {

			if ( precedence >= 2 ) { result += '('; }

			result += boost::join( operands | boost::adaptors::transformed( boost::bind( &NodeToInputFormRecursive, _1, 2 ) ), "^" );

			if ( precedence >= 2 ) { result += ')'; }

		} else if ( function == ast::Node::make<ast::Identifier>( eval::ids::List ) ) {

			result += '{';

			result += boost::join( operands | boost::adaptors::transformed( boost::bind( &NodeToInputFormRecursive, _1, -1 ) ), ", " );

			result += '}';

		} else {

			result = functionCall.toString();

		}

		return result;
	}

	int precedence;
};

InputFormString NodeToInputFormRecursive(const ast::Node& node, int precedence) {

	NodeToInputFormVisitor nodeToInputFormVisitor(precedence);

	return ast::applyVisitor( node, nodeToInputFormVisitor );
}

}} //namespace tungsten::io


