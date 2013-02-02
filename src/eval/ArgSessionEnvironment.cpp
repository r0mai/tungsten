
#include "ArgSessionEnvironment.hpp"

#include "ast/Parser.hpp"
#include "io/NodeToTeXForm.hpp"

#include <boost/optional.hpp>

namespace tungsten { namespace eval {

ArgSessionEnvironment::ArgSessionEnvironment() {}
ArgSessionEnvironment::~ArgSessionEnvironment() {}

std::string ArgSessionEnvironment::evaluateArg(const std::string& input) {
	boost::optional<ast::Node> expression = ast::parseInput(input);
	if ( !expression ) {
		//handleMessage(Message{}); //TODO
		return "Some error occured";
	} else {
		ast::Node result = evaluate(*expression);
		return io::NodeToTeXForm(result, *this);
	}
}

}} //namespace tungsten::eval
