
#include "classifyOperands.hpp"

#include <boost/range/adaptor/reversed.hpp>

#include "ast/Node.hpp"

namespace tungsten { namespace eval {

std::ostream& operator<<(std::ostream& os, NumericalClassification numericalClassification) {
	switch (numericalClassification) {
		case NumericalClassification::HAS_SYMBOLIC:
			os << "HAS_SYMBOLIC";
			break;
		case NumericalClassification::ALL_RATIONAL:
			os << "ALL_RATIONAL";
			break;
		case NumericalClassification::ALL_REAL:
			os << "ALL_REAL";
			break;
		case NumericalClassification::ALL_NUMERIC:
			os << "ALL_NUMERIC";
			break;
	}
	return os;
}

struct ClassifyNumericallyVisitor : boost::static_visitor<void> {
	bool allRational = true;
	bool allReal = true;
	bool allNumeric = true;

	void operator()(const math::Real&) {
		allRational = false;
	}
	void operator()(const math::Rational&) {
		allReal = false;
	}
	template<class T>
	void operator()(const T&) {
		allReal = false;
		allRational = false;
		allNumeric = false;
	}
};

NumericalClassification classifyNumerically(const ast::Operands& operands) {
	//Working from the back, because if operands are sorted, then symbolic
	//stuff are in the back, and we can return early
	ClassifyNumericallyVisitor classifyNumericallyVisitor;
	for ( const ast::Node& node : operands | boost::adaptors::reversed ) {
		applyVisitor(node, classifyNumericallyVisitor);
		if ( !classifyNumericallyVisitor.allNumeric ) {
			return NumericalClassification::HAS_SYMBOLIC;
		}
	}
	assert( classifyNumericallyVisitor.allNumeric );
	if ( classifyNumericallyVisitor.allRational ) {
		return NumericalClassification::ALL_RATIONAL;
	}
	if ( classifyNumericallyVisitor.allReal ) {
		return NumericalClassification::ALL_REAL;
	}
	return NumericalClassification::ALL_NUMERIC;
}

}} //namespace tungsten::eval

