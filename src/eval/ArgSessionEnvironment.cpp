
#include "ArgSessionEnvironment.hpp"

#include "io/Parser.hpp"
#include "io/NodeToTeXForm.hpp"

#include <boost/optional.hpp>

namespace tungsten { namespace eval {

ArgSessionEnvironment::ArgSessionEnvironment() {}
ArgSessionEnvironment::~ArgSessionEnvironment() {}

std::string ArgSessionEnvironment::evaluateArg(const std::string& input) {
	ast::Node result = evaluate(input);
	return io::NodeToTeXForm(result);

}

}} //namespace tungsten::eval
