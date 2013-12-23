
#ifndef EVAL_CLASSIFY_OPERANDS_
#define EVAL_CLASSIFY_OPERANDS_

#include "ast/FunctionCall.hpp"

namespace tungsten { namespace eval {

enum class NumericalClassification {
	HAS_SYMBOLIC,
	ALL_RATIONAL,
	ALL_REAL,
	ALL_NUMERIC
};

std::ostream& operator<<(std::ostream& os, NumericalClassification numericalClassification);

NumericalClassification classifyNumerically(const ast::Operands& operands);

}} //namespace tungsten::eval

#endif

