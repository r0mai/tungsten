#include <Python.h>
#include <boost/python.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <string>
#include <signal.h>
#include <vector>
#include <ctime>
#include <algorithm>
#include <fstream>
#include <boost/optional.hpp>
#include <boost/thread.hpp>
#include <mutex>

#include "io/Parser.hpp"
#include "io/NodeToTeXForm.hpp"
#include "eval/ArgSessionEnvironment.hpp"
#include "eval/CLISessionEnvironment.hpp"
#include "io/graphics/Graphics.hpp"
#include "ast/Identifier.hpp"
#include "eval/getHead.hpp"
#include "io/NodeToTeXForm.hpp"


std::vector<std::string>* logPtr;


void catcher(int param){

	//  std::exit(param);
	signal(param, SIG_IGN);
	std::cout<<"killed "<<param<<std::endl;
	//write to file from logPTR.
	std::ofstream out("log.txt");
	std::for_each(logPtr->begin(), logPtr->end(), [&out](const std::string& s){
				out<<s<<std::endl;
			});
	out.close();
	std::exit(param);

}


class WebOutput{
	std::string input;
	std::string TeXInput;
	std::string output;
	std::string svg;
	std::vector<std::string> errors;
	public:
	WebOutput() : output() {};
	WebOutput(const std::string& input, const std::string& TeXInput, const std::string& output, const std::string& svg, const std::vector<std::string>& errors) :
		input(input), TeXInput(TeXInput), output(output), svg(svg), errors(errors) { };

	std::string getOutputString() const {
		return output;
	}

	std::string getInputString() const {
		return input;
	}
	std::string getTeXInputString() const {
		return TeXInput;
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
	std::deque<std::pair<std::string, int>> runtimes;
	std::string ip = "";
	std::mutex evalLock;
public:
	WebSessionEnvironment() : lastAccess(std::time(nullptr)), errors() {
	};

	WebSessionEnvironment(WebSessionEnvironment&& we) : lastAccess(we.lastAccess), errors(we.errors) {
	};

	virtual ~WebSessionEnvironment() noexcept override {
	};

	const std::time_t& getLastAccess() const {
		return lastAccess;
	}

	const std::string& getIp() const {
		return ip;
	}

	void setIp(std::string ip_) {
		ip = std::move(ip_);
	}

	virtual void handleMessageString(const tungsten::ast::String& messageString) override {
		errors.push_back(messageString.toString());
	}

	bool isOld() const {
		return std::difftime(lastAccess, std::time(nullptr)) > 24*60*60;
		// true if over a day old.
	};

	const std::deque<std::pair<std::string, int>>& getRuntimes() const {
		return runtimes;
	}

	WebOutput evaluate(const std::string& input) {
		time(&lastAccess);
		errors.clear();

		auto startTime = boost::posix_time::microsec_clock::universal_time();

		boost::optional<tungsten::ast::Node> expression = tungsten::io::parseInput(input);
		std::string TeXInput;
		std::string svg;
		std::string output;
		if(expression){

			tungsten::ast::Node evaluated;

			{
				std::lock_guard<std::mutex> lock(evalLock);
				evaluated = tungsten::eval::SessionEnvironment::evaluate(*expression);
			}

			if(evaluated.is<tungsten::ast::FunctionCall>() &&
			evaluated.get<tungsten::ast::FunctionCall>().getFunction().is<tungsten::ast::Identifier>(tungsten::eval::ids::Graphics))
			{
				// dealing with graphics
				tungsten::io::graphics::GraphicsObject graphics;
				makeGraphics(evaluated, *this, graphics);
				svg = graphics.toSVGString();
			} else if (evaluated.is<tungsten::ast::FunctionCall>() && false &&
			evaluated.get<tungsten::ast::FunctionCall>().getFunction().is<tungsten::ast::Identifier>(tungsten::eval::ids::Table))
			{
				// todo table here (also remove false)
			} else { // no graphics or tables
				output = tungsten::io::NodeToTeXForm(evaluated);
			}
			TeXInput = tungsten::io::NodeToTeXForm(*expression); // create TeX

		} else { // if input was bad.
			TeXInput = "";
		}

		auto endTime = boost::posix_time::microsec_clock::universal_time();

		auto runtime = (endTime - startTime).total_milliseconds();
		runtimes.emplace_back(input, runtime);
		return WebOutput(input, TeXInput, output, svg, errors);
	};
};


class WebClassMonolith{

private:
	typedef std::string HashType;
	std::map<HashType, std::shared_ptr<WebSessionEnvironment> > storage;
	std::vector<std::string> log;
	boost::upgrade_mutex access;
	WebClassMonolith(const WebClassMonolith&) = delete;
	void operator=(const WebClassMonolith&) = delete;
public:
	WebClassMonolith() : storage(), access() {
		signal(SIGINT, catcher);
		// read into log from file.
		logPtr = &log;
		std::ifstream file("log.txt");
		std::string tmp;
		while(std::getline(file, tmp)){
			log.push_back(tmp);
		}
	};

	void getUsers() const {

		std::cout<<storage.size()<<" Users in system: "<<std::endl;

		for(const auto& userPair: storage) {

			std::cout << "User information for hash-id: " << userPair.first << '\n';
			std::cout << "Ip: " << userPair.second->getIp() << std::endl;
			const auto& runtimes = userPair.second->getRuntimes();

			std::uintmax_t totalRuntime = 0;

			for(const auto& runtimePair: runtimes) {

				std::cout << "\t" << runtimePair.first << "\n\t" <<
					runtimePair.second << "ms\n";
				totalRuntime += runtimePair.second;
			}

			if(!runtimes.empty()) {
				std::cout << "\tTotal: " << totalRuntime << "ms\n";
			}
			std::cout << std::endl;
		}
	}

	void setIp(HashType id, std::string ip) {
		access.lock();

		if(storage.find(id) != storage.end()) {
			// id is already present in storage, it may not be in some cases.
			storage[id]->setIp(std::move(ip));
		}
		access.unlock();
	}

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
		if(tmp.getTeXInputString().size())
			log.push_back(input);
		access.unlock_shared(); // release read access.
		return tmp;
	}

	void deleteEnvironment(HashType id){
		access.lock();
		storage.erase(id);
		access.unlock();
	}
	std::string getLog() const {
		std::string str;
		std::for_each(log.begin(), log.end(), [&str](const std::string& input){
					str.append(input+"\n");
				});
		return str;
	}
};

BOOST_PYTHON_MODULE(pytungsten){

	using namespace boost::python;
		class_<WebClassMonolith, boost::noncopyable>("tungsten")
			.def("evaluate", &WebClassMonolith::evaluate)
			.def("getUsers", &WebClassMonolith::getUsers)
			.def("getLog", &WebClassMonolith::getLog)
			.def("setIp", &WebClassMonolith::setIp);
		;
		class_<WebOutput>("WebOutput")
			.def("getOutputString", &WebOutput::getOutputString)
			.def("getInputString", &WebOutput::getInputString)
			.def("getTeXInputString", &WebOutput::getTeXInputString)
			.def("getErrors", &WebOutput::getErrorMessages)
			.def("getSVG", &WebOutput::getSVG)
		;
}
