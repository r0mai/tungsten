
#include "isSuperficiallyNegative.hpp"

#include <boost/range/algorithm/find_if.hpp>

#include "Identifiers.hpp"

namespace tungsten { namespace eval {

struct IsSuperficiallyNegativeVisitor : boost::static_visitor<bool> {

	template<class T>
	bool operator()(const T&) const {
		return false;
	}

	bool operator()(const math::Rational& rational) const {
		return rational < 0;
	}

	bool operator()(const math::Real& real) const {
		return real < 0;
	}

	bool operator()(const ast::FunctionCall& functionCall) const {
		if ( !functionCall.getFunction().is<ast::Identifier>( ids::Times ) ) {
			return false;
		}

		const ast::Operands& operands = functionCall.getOperands();

		return boost::find_if(operands, [](const ast::Node& node) {
			return ast::applyVisitor(node, IsSuperficiallyNegativeVisitor{});
		}) != operands.end();
	}

};

bool isSuperficiallyNegative(const ast::Node& node) {
	return ast::applyVisitor(node, IsSuperficiallyNegativeVisitor{});
}

}} //namespace tungsten::eval




