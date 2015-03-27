
#include <algorithm>

#include "functions.hpp"
#include "eval/SessionEnvironment.hpp"

namespace tungsten { namespace eval { namespace builtin {

bool isNodeNumeric(const ast::Node& node, eval::SessionEnvironment& sessionEnvironment);

struct IsNumericVisitor : boost::static_visitor<bool> {

	IsNumericVisitor(SessionEnvironment& sessionEnvironment) : sessionEnvironment(sessionEnvironment) {}

	bool operator()(const math::Real& /*real*/) const {
		return true;
	}

	bool operator()(const math::Rational& /*rational*/) const {
		return true;
	}

	bool operator()(const math::ComplexReal& /*real*/) const {
		return true;
	}

	bool operator()(const math::ComplexRational& /*rational*/) const {
		return true;
	}

	bool operator()(const ast::Identifier& identifier) const {
		return identifier == ids::E ||
				identifier == ids::Pi ||
				identifier == ids::Degree ||
				identifier == ids::GoldenRatio ||
				identifier == ids::EulerGamma ||
				identifier == ids::Catalan ||
				identifier == ids::Khinchin ||
				identifier == ids::I ||
				identifier == ids::Glaisher;
	}

	bool operator()(const ast::FunctionCall& functionCall) const {
		//workaround: Complex is not an Atom here
		if ( functionCall.getFunction() == ast::Node::make<ast::Identifier>(ids::Complex) ) {
			return true;
		}

		if ( functionCall.getFunction().is<ast::Identifier>() &&
				sessionEnvironment.getAttributeMap().hasAttribute(
					functionCall.getFunction().get<ast::Identifier>(),
					ids::NumericFunction
				) && std::all_of(functionCall.getOperands().begin(), functionCall.getOperands().end(),
					[this](const ast::Node& node) {
						return isNodeNumeric(node, sessionEnvironment);
					}
				)
			)
		{
			return true;
		}

		return false;
	}

	bool operator()(const ast::String& /*string*/) const {
		return false;
	}

	SessionEnvironment& sessionEnvironment;
};

bool isNodeNumeric(const ast::Node& node, eval::SessionEnvironment& sessionEnvironment) {
	return ast::applyVisitor( node, IsNumericVisitor{sessionEnvironment} );
}

OptionalNode NumericQ(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment) {
	if ( operands.size() != 1 ) {
		sessionEnvironment.raiseMessage( Message(ids::NumericQ, ids::argx, {
				ast::Node::make<ast::Identifier>( ids::NumericQ ),
				ast::Node::make<math::Rational>( operands.size() )
		} ));
		return EvaluationFailure();
	}

	if ( isNodeNumeric( operands[0], sessionEnvironment ) ) {
		return ast::Node::make<ast::Identifier>(ids::True);
	}
	return ast::Node::make<ast::Identifier>(ids::False);
}

}}} //namespace tungsten::eval::builtin

