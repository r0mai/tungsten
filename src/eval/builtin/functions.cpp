
#include "functions.hpp"

namespace tungsten { namespace eval { namespace builtin {

BuiltinFunctionPair::BuiltinFunctionPair(FunctionPtr regular, FunctionPtr numeric) :
		regular(regular), numeric(numeric) {}

Functions createFunctions() {
	Functions result;
	result["Plus"] = BuiltinFunctionPair(&Plus, &Plus_N);
	return result;
}

}}} //namespace tungsten::eval::builtin




