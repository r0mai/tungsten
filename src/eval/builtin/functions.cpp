
#include "functions.hpp"

namespace tungsten { namespace eval { namespace builtin {

Functions createFunctions() {
	Functions result;
	result["Plus"] = &Plus;
	result["Times"] = &Times;
	result["Power"] = &Power;
	return result;
}

}}} //namespace tungsten::eval::builtin




