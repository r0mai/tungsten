

#ifndef EVAL_BUILTIN_FUNCTIONS_HPP_
#define EVAL_BUILTIN_FUNCTIONS_HPP_

#include "ast/Node.hpp"
#include "eval/SessionEnvironmentFwd.hpp"
#include "eval/Identifiers.hpp"

#include <map>
#include <functional>

#include <boost/optional.hpp>

namespace tungsten { namespace eval { namespace builtin {

typedef boost::optional<ast::Node> OptionalNode;
typedef boost::none_t EvaluationFailure;

typedef std::function<OptionalNode(const ast::Operands&, eval::SessionEnvironment&)> FunctionPtr;

typedef std::map<ast::Identifier, FunctionPtr> Functions;

Functions createFunctions();

OptionalNode Plus(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment);
OptionalNode Times(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment);
OptionalNode Abs(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment);
OptionalNode Numerator(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment);
OptionalNode Denominator(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment);
OptionalNode Replace(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment);
OptionalNode Set(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment);
OptionalNode SetDelayed(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment);
OptionalNode RandomReal(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment);
OptionalNode Divide(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment);
OptionalNode Head(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment);
OptionalNode Table(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment);
OptionalNode CompoundExpression(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment);
OptionalNode Minus(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment);
OptionalNode Subtract(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment);
OptionalNode Apply(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment);
OptionalNode Flatten(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment);
OptionalNode Evaluate(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment);
OptionalNode N(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment);
OptionalNode NumericQ(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment);
OptionalNode If(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment);
OptionalNode While(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment);
OptionalNode Attributes(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment);

//These are defined in Power.cpp
OptionalNode Power(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment);
OptionalNode Sqrt(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment);

//These are defined in Factorial.cpp
OptionalNode Factorial(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment);
OptionalNode Factorial2(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment);

//These are defined in trigonometricFunctions.cpp
OptionalNode Sin(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment);
OptionalNode Cos(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment);
OptionalNode Tan(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment);
OptionalNode Cot(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment);
OptionalNode Sec(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment);
OptionalNode Csc(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment);
OptionalNode ArcSin(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment);
OptionalNode ArcCos(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment);
OptionalNode ArcTan(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment);

//These are defined in Sort.cpp
OptionalNode Sort(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment);
OptionalNode OrderedQ(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment);

OptionalNode Function(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment);
OptionalNode evaluateFunction(const ast::Operands& functionOperands, const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment);

// Defined in relations.cpp
OptionalNode Equal(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment);
OptionalNode Unequal(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment);
OptionalNode Less(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment);
OptionalNode Greater(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment);
OptionalNode LessEqual(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment);
OptionalNode GreaterEqual(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment);

//Defined in booleanFunctions.cpp
OptionalNode TrueQ(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment);
OptionalNode Not(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment);
OptionalNode And(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment);
OptionalNode Or(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment);
OptionalNode Boole(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment);

// Defined in Plot.cpp
OptionalNode Plot(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment);

}}} //namespace tungsten::eval::builtin

#endif /* EVAL_BUILTIN_FUNCTIONS_HPP_ */
