
#include "FileSessionEnvironment.hpp"

#include <fstream>
#include <iostream>

#include "Identifiers.hpp"

namespace tungsten { namespace eval {

FileSessionEnvironment::FileSessionEnvironment(const std::string& fileName) : fileName(fileName) {}

void FileSessionEnvironment::handleMessageString(const ast::String& messageString) {
	std::cout << "\033[1;31m" << messageString << "\033[0;00m" << std::endl;
}

void FileSessionEnvironment::run() {
	std::fstream in(fileName);
	if ( !in.is_open() ) {
		raiseMessage(Message(ids::General, ids::General, {}));
		return;
	}

	std::string contents;
	std::string line;
	while (std::getline(in, line)) {
		contents += line;
		contents += "\n";
	}

	std::cout << evaluate(contents) << std::endl;
}

}} //namespace tungsten::eval
