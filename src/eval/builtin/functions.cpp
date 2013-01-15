
#include "functions.hpp"

namespace tungsten { namespace eval { namespace builtin {

Functions createFunctions() {
	Functions result;
	result[ids::Plus] = &Plus;
	result[ids::Times] = &Times;
	result[ids::Power] = &Power;
	return result;
}

}}} //namespace tungsten::eval::builtin




