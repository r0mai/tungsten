#include <Python.h>
#include <boost/python.hpp>
#include <string>
#include <mutex>
#include <ctime>
#include <boost/optional.hpp>

#include "ast/Parser.hpp"
#include "io/NodeToTeXForm.hpp"
#include "eval/ArgSessionEnvironment.hpp"
#include "eval/CLISessionEnvironment.hpp"


class WebOutput{
        std::string output;
		std::string input;
		std::string errors;
public:
        WebOutput() : output() {};
        WebOutput(const std::string& input, const std::string& output, const std::string& errors) : 
			input(input), output(output), errors(errors) { };
			
        WebOutput(std::string&& output) : output(std::move(output)) { };
		
        std::string getOutputString() const {
			return output;
		}
		
		std::string getInputString() const {
			return input;
		}
		
		std::string getErrorMessages() const {
			return errors;
		}
};


class WebSessionEnvironment : public tungsten::eval::ArgSessionEnvironment {
private:
        std::mutex lock;
		std::time_t lastAccess;
public:
        WebSessionEnvironment() : lock(), lastAccess(std::time(nullptr)){
        };
        
        WebSessionEnvironment(WebSessionEnvironment&& we) : lock() {
        };
		
        virtual ~WebSessionEnvironment() noexcept override {
        };
		
		bool isOld() const {
			return std::difftime(lastAccess, std::time(nullptr)) > 24*60*60; 
			// true if over a day old.
		};
		
        WebOutput evaluate(const std::string& input) {
                lock.lock();
				time(&lastAccess);
				boost::optional<tungsten::ast::Node> expression = tungsten::ast::parseInput(input);
                std::string output = evaulateArg(input);
				std::string TexInput = expression?tungsten::io::NodeToTeXForm(*expression, *this):input;
                lock.unlock();
                return WebOutput(std::move(TexInput), std::move(output), "");
        };
};


class WebClassMonolith{

private:
        typedef std::string HashType;
        std::map<HashType, std::shared_ptr<WebSessionEnvironment> > storage;
		std::mutex writeLock;
		WebClassMonolith(const WebClassMonolith&) = delete;
		void operator=(const WebClassMonolith&) = delete;
public:
		WebClassMonolith() : storage(), writeLock() { };
        WebOutput evaluate(HashType id, const std::string& input){
                auto it = storage.find(id);
                if(it==storage.end()){
						writeLock.lock();
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
						writeLock.unlock();
                }
                return it->second->evaluate(input);
        }
		void deleteEnvironment(HashType id){
			writeLock.lock();
			storage.erase(id);
			writeLock.unlock();
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
	;
}
