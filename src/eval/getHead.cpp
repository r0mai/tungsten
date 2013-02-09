
#include "getHead.hpp"

#include "Identifiers.hpp"

namespace tungsten { namespace eval {

struct GetHeadVisitor : boost::static_visitor<ast::Node> {
	ast::Node operator()(const math::Rational& rational) const {
		if ( math::isInteger(rational) ) {
			return ast::Node::make<ast::Identifier>(ids::Integer);
		}
		return ast::Node::make<ast::Identifier>(ids::Rational);
	}

	ast::Node operator()(const math::Real& /*real*/) const {
		return ast::Node::make<ast::Identifier>(ids::Real);
	}

	ast::Node operator()(const ast::String& /*string*/) const {
		return ast::Node::make<ast::Identifier>(ids::String);
	}

	ast::Node operator()(const ast::Identifier& /*identifier*/) const {
		return ast::Node::make<ast::Identifier>(ids::Symbol);
	}

	ast::Node operator()(const ast::FunctionCall& functionCall) const {
		return functionCall.getFunction();
	}
};

ast::Node getHead(const ast::Node& node) {
	return ast::applyVisitor(node, GetHeadVisitor{});
}

}} //namespace tungsten::eval
