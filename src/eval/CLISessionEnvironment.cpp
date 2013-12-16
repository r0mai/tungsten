
#include "CLISessionEnvironment.hpp"

#include <iostream>
#include <string>
#include <fstream>

#include <readline/history.h>
#include <readline/readline.h>

namespace tungsten { namespace eval {

CLISessionEnvironment::CLISessionEnvironment() {}

CLISessionEnvironment::~CLISessionEnvironment() {}

void CLISessionEnvironment::printToStdout(const ast::Operands& nodes) {
    for ( const ast::Node& node : nodes ) {
        std::cout << node << " ";
    }
    std::cout << std::endl;
}

void CLISessionEnvironment::handleMessageString(const ast::String& messageString) {
	std::cout << "\033[1;31m" << messageString << "\033[0;00m" << std::endl;
}

void CLISessionEnvironment::run() {

	using_history();

	readHistoryFromFile(".tungsten");
	for ( int i = 1; ; ++i ) {
		std::string prompt = "In[" + std::to_string(i) + "] :=   ";

		char *input = readline( prompt.c_str() );

		if (!input) {
			std::cout << std::endl;
			break;
		}

		addToReadlineHistory(input);

		ast::Node result = evaluate(std::string(input));

		if ( !result.is<ast::Identifier>(ids::Null) ) {
			std::cout << "Out[" << i << "] =   " << result << std::endl;
		}

		std::free(input);
	}
	writeHistoryToFile(".tungsten");
}

void CLISessionEnvironment::addToReadlineHistory(const std::string& line) {
	add_history(line.c_str()); //readline
	history.push_back(line);
}

void CLISessionEnvironment::readHistoryFromFile(const std::string& fileName) {
	std::ifstream historyFile(fileName);
	if ( historyFile.is_open() ) {
		std::string line;
		while ( std::getline(historyFile, line) ) {
			addToReadlineHistory(line.c_str());
		}
	}
}


void CLISessionEnvironment::writeHistoryToFile(const std::string& fileName) {
	std::ofstream historyFile(fileName);
	if ( historyFile.is_open() ) {
		for ( const std::string& line : history ) {
			historyFile << line << '\n';
		}
	}
}

}} //namespace tungsten::eval

