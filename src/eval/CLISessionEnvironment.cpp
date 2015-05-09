
#include "CLISessionEnvironment.hpp"
#include "builtin/functions.hpp"

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

char* nextBuiltinCompletion(const char* textSoFar, int isOldWord) {
	static int lastIndex = 0;
	static std::vector<std::string> currentCompletions;
	if(!isOldWord) {
		lastIndex = 0;
		currentCompletions = builtin::builtinFunctionCompletions(textSoFar);
	}

	if(lastIndex >= currentCompletions.size()) {
		// no more matches
		return nullptr;
	}
	std::string match = currentCompletions[lastIndex++];
	match+='[';
	char* matchArray = new char[match.size()+1];
	std::memset(matchArray, 0, match.size()+1);
	std::memcpy(matchArray, match.c_str(), match.size());
	return matchArray;
}

char** builtinCompletion(const char* textSoFar, int, int) {
	return rl_completion_matches(textSoFar, nextBuiltinCompletion);
}

void CLISessionEnvironment::run() {

	using_history();

	readHistoryFromFile(".tungsten");
	rl_attempted_completion_function = builtinCompletion;

	for ( int i = 1; ; ++i ) {
		std::string prompt = "\e[0;97mIn[" + std::to_string(i) + "] :=   \e[0m";

		char *input = readline( prompt.c_str() );

		if (!input) {
			std::cout << std::endl;
			break;
		}

		addToReadlineHistory(input);

		ast::Node result = evaluate(std::string(input));

		if ( !result.is<ast::Identifier>(ids::Null) ) {
			std::cout << "\e[0;97mOut[" << i << "] =   \e[0m" << result << std::endl;
		}

		std::free(input);
	}
	writeHistoryToFile(".tungsten");
}

void CLISessionEnvironment::addToReadlineHistory(const std::string& line) {
	add_history(line.c_str()); //readline
	history.push_back(line);
}

std::string CLISessionEnvironment::getNthLatestLine(int index) const {
	return *(history.rbegin()+index);
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

