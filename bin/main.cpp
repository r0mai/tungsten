
#include <iostream>
#include <string>

#include "ast/Parser.hpp"

int main() {

	std::string line;

	while ( std::getline(std::cin, line) ) {
		auto res = tungsten::ast::parseInput( line );

		if ( res ) {
			std::cout << *res << std::endl;
		} else {
			std::cout << "parse error" << std::endl;
		}
	}

}
