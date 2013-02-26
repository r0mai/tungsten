#include <Python.h>
#include <boost/python.hpp>
#include <string>
#include <vector>
#include <ctime>
#include <algorithm>
#include <boost/optional.hpp>
#include <boost/thread.hpp>
#include <chrono>

#include "ast/Parser.hpp"
#include "io/NodeToTeXForm.hpp"
#include "eval/ArgSessionEnvironment.hpp"
#include "eval/CLISessionEnvironment.hpp"
#include "io/Graphics.hpp"
#include "ast/Identifier.hpp"
#include "eval/getHead.hpp"
#include "io/NodeToTeXForm.hpp"


class WebOutput{
	std::string input;
	std::string output;
	std::string svg;
	std::vector<std::string> errors;
	public:
	WebOutput() : output() {};
	WebOutput(const std::string& input, const std::string& output, const std::string& svg, const std::vector<std::string>& errors) :
		input(input), output(output), svg(svg), errors(errors) { };

	std::string getOutputString() const {
		return output;
	}

	std::string getInputString() const {
		return input;
	}
	
	std::string getSVG() const {
		return svg;
	}

	std::string getErrorMessages() const {
		return std::accumulate(errors.begin(), errors.end(), std::string(""), [](std::string& tmp, const std::string& err){return tmp+"\n"+err;});
	}
};


class WebSessionEnvironment : public tungsten::eval::SessionEnvironment {
private:
	std::time_t lastAccess;
	std::vector<std::string> errors;
public:
	WebSessionEnvironment() : lastAccess(std::time(nullptr)), errors() {
	};

	WebSessionEnvironment(WebSessionEnvironment&& we) : lastAccess(we.lastAccess), errors(we.errors) {
	};

	virtual ~WebSessionEnvironment() noexcept override {
	};

	virtual void handleMessageString(const tungsten::ast::String& messageString) override {
		errors.push_back(messageString.toString());
	}

	bool isOld() const {
		return std::difftime(lastAccess, std::time(nullptr)) > 24*60*60;
		// true if over a day old.
	};

	WebOutput evaluate(const std::string& input) {
		time(&lastAccess);
		errors.clear();

		auto start = std::chrono::high_resolution_clock::now();
		boost::optional<tungsten::ast::Node> expression = tungsten::ast::parseInput(input);
		std::string TeXInput;
		std::string svg;
		std::string output;
		if(expression){
			auto evaluated = tungsten::eval::SessionEnvironment::evaluate(input);
			if(expression->is<tungsten::ast::FunctionCall>() && 
			expression->get<tungsten::ast::FunctionCall>().getFunction().is<tungsten::ast::Identifier>(tungsten::eval::ids::Graphics)) {
				// dealing with graphics
				tungsten::io::GraphicsObject graphics;
				makeGraphics(evaluated, *this, graphics);
				svg = graphics.toSVGString();
			} else if (expression->is<tungsten::ast::FunctionCall>() && false &&
			expression->get<tungsten::ast::FunctionCall>().getFunction().is<tungsten::ast::Identifier>(tungsten::eval::ids::Table)) {
				// todo table here (also remove false)
			} else { // no graphics or tables
				output = tungsten::io::NodeToTeXForm(evaluated, *this);
			}
			TeXInput = tungsten::io::NodeToTeXForm(*expression, *this); // create TeX
		} else { // if input was bad.
			TeXInput = input;
		}
		auto end = std::chrono::high_resolution_clock::now();
		auto elapsed = end - start;
		std::cout<<elapsed.count()<<std::endl;
		return WebOutput(TeXInput, output, svg, errors);
	};
};


class WebClassMonolith{

private:
	typedef std::string HashType;
	std::map<HashType, std::shared_ptr<WebSessionEnvironment> > storage;
	boost::upgrade_mutex access;
	WebClassMonolith(const WebClassMonolith&) = delete;
	void operator=(const WebClassMonolith&) = delete;
public:
	WebClassMonolith() : storage(), access() { };
	
	WebOutput evaluate(HashType id, const std::string& input){
		access.lock_shared(); // get read access.
		auto it = storage.find(id);
		if(it==storage.end()){
			// modifying begins here, gain write access.
			access.unlock_shared();
			access.lock();

			// No remove_if for associative containers, argh.
			// Following solution from SO:
			// http://stackoverflow.com/questions/800955/
			for(auto iter = storage.begin(); iter != storage.end(); ){
				if(iter->second->isOld())
					storage.erase(iter++);
				else
					++iter;
				}
				it=storage.insert(
				std::make_pair(id, std::make_shared<WebSessionEnvironment>())
				).first;
			access.unlock();
			access.lock_shared(); // fall back to read access
		}
		auto tmp = it->second->evaluate(input);
		access.unlock_shared(); // release read access.
		return tmp;
	}
	
	void deleteEnvironment(HashType id){
		access.lock();
		storage.erase(id);
		access.unlock();
	}
};

BOOST_PYTHON_MODULE(pytungsten){

	using namespace boost::python;
		class_<WebClassMonolith, boost::noncopyable>("tungsten")
			.def("evaluate", &WebClassMonolith::evaluate)
		;
		class_<WebOutput>("WebOutput")
			.def("getOutputString", &WebOutput::getOutputString)
			.def("getInputString", &WebOutput::getInputString)
			.def("getErrors", &WebOutput::getErrorMessages)
			.def("getSVG", &WebOutput::getSVG)
		;
}
