
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
	return result;
}

}}} //namespace tungsten::eval::builtin




