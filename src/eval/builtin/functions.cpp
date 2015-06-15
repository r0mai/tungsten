
#include "functions.hpp"

#include <boost/algorithm/string/predicate.hpp>

namespace tungsten { namespace eval { namespace builtin {

OptionalNode Plus(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment);
OptionalNode Times(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment);
OptionalNode Abs(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment);
OptionalNode Numerator(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment);
OptionalNode Denominator(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment);
OptionalNode Set(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment);
OptionalNode SetDelayed(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment);
OptionalNode RandomReal(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment);
OptionalNode Divide(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment);
OptionalNode Head(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment);
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
OptionalNode Print(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment);
OptionalNode Block(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment);
OptionalNode Map(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment);
OptionalNode MatchQ(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment);
OptionalNode ByteCount(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment);

// These are defined in InternalFunctions.cpp
OptionalNode Out(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment);
OptionalNode In(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment);

//These are defined in Replace.cpp
OptionalNode Replace(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment);
OptionalNode ReplaceAll(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment);
OptionalNode ReplaceRepeated(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment);

//These are defined in Part.cpp
OptionalNode Part(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment);
OptionalNode Length(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment);

//These are defined in Append.cpp
OptionalNode Append(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment);
OptionalNode Prepend(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment);

//These are defined in Power.cpp
OptionalNode Power(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment);
OptionalNode Sqrt(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment);

//These are defined in Factorial.cpp
OptionalNode Factorial(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment);
OptionalNode Factorial2(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment);

//These are defined in Table.cpp
OptionalNode Table(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment);
OptionalNode Range(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment);

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

// These are defined in sum.cpp
OptionalNode Sum(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment);

// Defined in relations.cpp
OptionalNode Equal(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment);
OptionalNode Unequal(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment);
OptionalNode Less(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment);
OptionalNode Greater(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment);
OptionalNode LessEqual(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment);
OptionalNode GreaterEqual(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment);

// Defined in booleanFunctions.cpp
OptionalNode TrueQ(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment);
OptionalNode Not(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment);
OptionalNode And(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment);
OptionalNode Or(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment);
OptionalNode Boole(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment);
OptionalNode AllTrue(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment);

// Defined in numericFunctions.cpp
OptionalNode Floor(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment);
OptionalNode Ceiling(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment);
OptionalNode Round(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment);
OptionalNode IntegerPart(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment);
OptionalNode FractionalPart(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment);
OptionalNode Re(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment);
OptionalNode Im(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment);
OptionalNode Complex(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment);

// Defined in Plot.cpp
OptionalNode Plot(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment);
OptionalNode Export(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment);

// Defined in FindDivisions.cpp
OptionalNode FindDivisions(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment);
OptionalNode ContinuedFraction(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment);
OptionalNode FromContinuedFraction(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment);

// Defined in timeFunctions.cpp
OptionalNode AbsoluteTime(const ast::Operands&, eval::SessionEnvironment&);
OptionalNode Timing(const ast::Operands&, eval::SessionEnvironment&);

// Defined in ReapSow.cpp
OptionalNode Reap(const ast::Operands&, eval::SessionEnvironment&);
OptionalNode Sow(const ast::Operands&, eval::SessionEnvironment&);

// Defined in stringAlgorithms.cpp
OptionalNode StringLength(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment);
OptionalNode Characters(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment);
OptionalNode StringJoin(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment);
OptionalNode StringInsert(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment);
OptionalNode StringTake(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment);
OptionalNode StringDrop(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment);
OptionalNode StringReverse(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment);

Functions createFunctions() {
	Functions result;
	result[ids::Plus] = &Plus;
	result[ids::Times] = &Times;
	result[ids::Power] = &Power;
	result[ids::Abs] = &Abs;
	result[ids::Numerator] = &Numerator;
	result[ids::Denominator] = &Denominator;
	result[ids::Replace] = &Replace;
	result[ids::Set] = &Set;
	result[ids::SetDelayed] = &SetDelayed;
	result[ids::RandomReal] = &RandomReal;
	result[ids::Divide] = &Divide;
	result[ids::Head] = &Head;
	result[ids::Table] = &Table;
	result[ids::CompoundExpression] = &CompoundExpression;
	result[ids::Minus] = &Minus;
	result[ids::Subtract] = &Subtract;
	result[ids::Apply] = &Apply;
	result[ids::Equal] = &Equal;
	result[ids::Unequal] = &Unequal;
	result[ids::Less] = &Less;
	result[ids::Greater] = &Greater;
	result[ids::LessEqual] = &LessEqual;
	result[ids::GreaterEqual] = &GreaterEqual;
	result[ids::Sin] = &Sin;
	result[ids::Cos] = &Cos;
	result[ids::Tan] = &Tan;
	result[ids::Cot] = &Cot;
	result[ids::Sec] = &Sec;
	result[ids::Csc] = &Csc;
	result[ids::ArcSin] = &ArcSin;
	result[ids::ArcCos] = &ArcCos;
	result[ids::ArcTan] = &ArcTan;
	result[ids::Factorial] = &Factorial;
	result[ids::Factorial2] = &Factorial2;
	result[ids::Sqrt] = &Sqrt;
	result[ids::Flatten] = &Flatten;
	result[ids::Sort] = &Sort;
	result[ids::Plot] = &Plot;
	result[ids::Evaluate] = &Evaluate;
	result[ids::N] = &N;
	result[ids::NumericQ] = &NumericQ;
	result[ids::OrderedQ] = &OrderedQ;
	result[ids::If] = &If;
	result[ids::TrueQ] = &TrueQ;
	result[ids::Not] = &Not;
	result[ids::And] = &And;
	result[ids::Or] = &Or;
	result[ids::Boole] = &Boole;
	result[ids::AllTrue] = &AllTrue;
	result[ids::While] = &While;
	result[ids::Attributes] = &Attributes;
	result[ids::Print] = &Print;
	result[ids::Part] = &Part;
	result[ids::Floor] = &Floor;
	result[ids::Ceiling] = &Ceiling;
	result[ids::Round] = &Round;
	result[ids::IntegerPart] = &IntegerPart;
	result[ids::FractionalPart] = &FractionalPart;
	result[ids::Re] = &Re;
	result[ids::Im] = &Im;
	result[ids::Complex] = &Complex;
	result[ids::Export] = &Export;
	result[ids::Append] = &Append;
	result[ids::Prepend] = &Prepend;
	result[ids::Length] = &Length;
	result[ids::Table] = &Table;
	result[ids::Range] = &Range;
	result[ids::Block] = &Block;
	result[ids::Map] = &Map;
	result[ids::Sum] = &Sum;
	result[ids::MatchQ] = &MatchQ;
	result[ids::ReplaceAll] = &ReplaceAll;
	result[ids::ReplaceRepeated] = &ReplaceRepeated;
	result[ids::AbsoluteTime] = &AbsoluteTime;
	result[ids::Reap] = &Reap;
	result[ids::Sow] = &Sow;
	result[ids::Timing] = &Timing;
	result[ids::ByteCount] = &ByteCount;
	result[ids::Out] = &Out;
	result[ids::In] = &In;
	result[ids::StringLength] = &StringLength;
	result[ids::Characters] = &Characters;
	result[ids::StringJoin] = &StringJoin;
	result[ids::StringTake] = &StringTake;
	result[ids::StringDrop] = &StringDrop;
	result[ids::StringInsert] = &StringInsert;
	result[ids::StringReverse] = &StringReverse;
	result[ids::FindDivisions] = &FindDivisions;
	result[ids::ContinuedFraction] = &ContinuedFraction;
	result[ids::FromContinuedFraction] = &FromContinuedFraction;
	return result;
}

std::vector<std::string> builtinFunctionCompletions(const std::string& textSoFar) {
	static const auto functionMap = createFunctions();
	std::vector<std::string> completions;

	for(const auto& functionPair : functionMap) {
		const std::string& functionName = functionPair.first.toString();
		if(boost::starts_with(functionName, textSoFar)) {
			completions.push_back(functionName);
		}
	}
	return completions;
}

}}} //namespace tungsten::eval::builtin



