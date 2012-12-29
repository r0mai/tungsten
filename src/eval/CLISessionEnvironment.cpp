
#include "CLISessionEnvironment.hpp"

#include <iostream>
#include <string>

#include "ast/Parser.hpp"

namespace tungsten { namespace eval {

CLISessionEnvironment::CLISessionEnvironment() {}

CLISessionEnvironment::~CLISessionEnvironment() {}

void CLISessionEnvironment::run() {

	std::string line;
	while ( std::getline(std::cin, line) ) {
		boost::optional<ast::Node> expression = ast::parseInput(line);
		if ( !expression ) {
			handleMessage(Message{}); //TODO
		} else {
			std::cout << "Input : " << *expression << std::endl;
			ast::Node result = evaluate(*expression);
			std::cout << "Output : " << result << std::endl;
		}
	}
}


}} //namespace tungsten::eval

