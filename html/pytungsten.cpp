#include <Python.h>
#include <boost/python.hpp>
#include <string>
#include <mutex>
#include "eval/ArgSessionEnvironment.hpp"
#include "eval/CLISessionEnvironment.hpp"

class WebOutput{
	std::string output;
public:
	WebOutput() : output() {};
	WebOutput(const std::string& output) : output(output) { };
	WebOutput(std::string&& output) : output(std::move(output)) { };
	char const * getOutputString() const {
		return output.c_str();
	}
};


class WebSessionEnvironment : public tungsten::eval::ArgSessionEnvironment {
private:
	std::mutex lock;
public:
	WebSessionEnvironment() : lock(){
	};
	
	WebSessionEnvironment(WebSessionEnvironment&& we) : lock() {
	}
	virtual ~WebSessionEnvironment() noexcept override {
	};
	WebOutput evaluate(const std::string& input) {
		lock.lock();
		std::string str = evaulateArg(input);
		lock.unlock();
		return WebOutput(std::move(str));
	}
};


class WebClassMonolith{

private:
	typedef int HashType;
	std::map<HashType, std::shared_ptr<WebSessionEnvironment> > storage;
public:
	WebOutput evaluate(HashType id, char const * in){
		std::string input(in);
		auto it = storage.find(id);
		if(it==storage.end()){
			it=storage.insert(
			std::make_pair(id, std::make_shared<WebSessionEnvironment>())
			).first;
		}
		return it->second->evaluate(input);	
	}
};


char const* evaluate(char const* in){
        std::string input(in);
        tungsten::eval::ArgSessionEnvironment aSE;
        return aSE.evaulateArg(input).c_str();
}

BOOST_PYTHON_MODULE(pytungsten)
{
    using namespace boost::python;
    def("evaluate", evaluate);
	class_<WebClassMonolith, boost::noncopyable>("tungsten")
		.def("evaluate", &WebClassMonolith::evaluate);
	class_<WebOutput>("WebOutput")
		.def("getOutputString", &WebOutput::getOutputString);
}
