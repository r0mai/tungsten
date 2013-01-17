
#include "ArgSessionEnvironment.hpp"

#include "ast/Parser.hpp"

#include <boost/optional.hpp>

namespace tungsten { namespace eval {

ArgSessionEnvironment::ArgSessionEnvironment() {}
ArgSessionEnvironment::~ArgSessionEnvironment() {}

std::string ArgSessionEnvironment::evaulateArg(const std::string& input) {
	boost::optional<ast::Node> expression = ast::parseInput(input);
	if ( !expression ) {
		handleMessage(Message{}); //TODO
		return "Some error occured";
	} else {
		ast::Node result = evaluate(*expression);
		return result.toString();
	}
}

}} //namespace tungsten::eval
