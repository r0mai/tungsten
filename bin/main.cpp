
#include <boost/program_options.hpp>

#include <string>
#include <iostream>

#include "eval/ArgSessionEnvironment.hpp"
#include "eval/CLISessionEnvironment.hpp"

int main(int argc, char **argv) {

	namespace po = boost::program_options;

	po::options_description desc("Allowed options");
	desc.add_options()
	    ("help", "print this message")
	    ("eval", po::value<std::string>(), "evaluate an expression")
	;

	po::variables_map vm;
	po::store(po::parse_command_line(argc, argv, desc), vm);
	po::notify(vm);

	if (vm.count("help")) {
	    std::cout << desc << std::endl;
	    return 1;
	}

	if (vm.count("eval")) {
		tungsten::eval::ArgSessionEnvironment argSessionEnvironment;
		std::cout << argSessionEnvironment.evaluateArg(vm["eval"].as<std::string>()) << std::endl;
	} else {
		tungsten::eval::CLISessionEnvironment environment;
		environment.run();
	}




}
