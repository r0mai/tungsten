
#include "CLISessionEnvironment.hpp"

#include <iostream>
#include <string>

namespace tungsten { namespace eval {

CLISessionEnvironment::CLISessionEnvironment() {}

CLISessionEnvironment::~CLISessionEnvironment() {}

void CLISessionEnvironment::handleMessageString(const ast::String& messageString) {
	std::cout << "\033[1;31m" << messageString << "\033[0;00m" << std::endl;
}

void CLISessionEnvironment::run() {


	for ( int i = 1; ; ++i ) {
		std::cout << "In[" << i << "] :=   ";

		std::string line;
		if (!std::getline(std::cin, line)) {
			break;
		}

		ast::Node result = evaluate(line);
		std::cout << "Out[" << i << "] =   " << result << std::endl;
	}
}


}} //namespace tungsten::eval

