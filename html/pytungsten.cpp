#include <Python.h>
#include <boost/python.hpp>
#include <string>
#include "eval/ArgSessionEnvironment.hpp"
#include "eval/CLISessionEnvironment.hpp"


char const* evaluate(char const* in){
	std::string input(in);
	tungsten::eval::ArgSessionEnvironment aSE;
	return aSE.evaulateArg(input).c_str();
}

BOOST_PYTHON_MODULE(pytungsten)
{
    using namespace boost::python;
    def("evaluate", evaluate);
}
