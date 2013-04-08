
#include "CLISessionEnvironment.hpp"

#include <iostream>
#include <string>

#include <readline/history.h>
#include <readline/readline.h>

namespace tungsten { namespace eval {

CLISessionEnvironment::CLISessionEnvironment() {}

CLISessionEnvironment::~CLISessionEnvironment() {}

void CLISessionEnvironment::handleMessageString(const ast::String& messageString) {
	std::cout << "\033[1;31m" << messageString << "\033[0;00m" << std::endl;
}

void CLISessionEnvironment::run() {

	using_history();

	for ( int i = 1; ; ++i ) {
		std::string prompt = "In[" + std::to_string(i) + "] :=   ";

		char *input = readline( prompt.c_str() );

		if (!input) {
			break;
		}

		add_history(input);

		ast::Node result = evaluate(std::string(input));

		std::cout << "Out[" << i << "] =   " << result << std::endl;

		std::free(input);
	}
}


}} //namespace tungsten::eval

