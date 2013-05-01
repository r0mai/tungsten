
#include "ArgSessionEnvironment.hpp"

#include "io/Parser.hpp"
#include "io/NodeToTeXForm.hpp"
#include "io/NodeToFullForm.hpp"

#include <boost/optional.hpp>

namespace tungsten { namespace eval {

ArgSessionEnvironment::ArgSessionEnvironment() {}
ArgSessionEnvironment::~ArgSessionEnvironment() {}

std::string ArgSessionEnvironment::evaluateArg(const std::string& input) {
	ast::Node result = evaluate(input);
	return io::NodeToFullForm(result);

}

}} //namespace tungsten::eval
