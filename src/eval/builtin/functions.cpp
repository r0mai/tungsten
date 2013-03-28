
#include "functions.hpp"

namespace tungsten { namespace eval { namespace builtin {

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
	result[ids::Sin] = &Sin;
	result[ids::Cos] = &Cos;
	result[ids::Tan] = &Tan;
	result[ids::Cot] = &Cot;
	result[ids::Sec] = &Sec;
	result[ids::Csc] = &Csc;
	result[ids::ArcSin] = &Sin;
	result[ids::ArcCos] = &Cos;
	result[ids::ArcTan] = &Tan;
	result[ids::Factorial] = &Factorial;
	result[ids::Factorial2] = &Factorial2;
	result[ids::Sqrt] = &Sqrt;
	result[ids::Flatten] = &Flatten;
	result[ids::Sort] = &Sort;
	result[ids::Plot] = &Plot;

	return result;
}

}}} //namespace tungsten::eval::builtin




