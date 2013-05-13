
#ifndef EVAL_CLISESSIONENVIRONMENT_HPP_
#define EVAL_CLISESSIONENVIRONMENT_HPP_

#include "SessionEnvironment.hpp"

namespace tungsten { namespace eval {

class CLISessionEnvironment : public SessionEnvironment {
public:
	CLISessionEnvironment();
	virtual ~CLISessionEnvironment() override;

	virtual void handleMessageString(const ast::String& /*messageString*/) override;
    virtual void printToStdout(const ast::Operands& nodes) override;

	void run();

private:
	void addToReadlineHistory(const std::string& line);
	void readHistoryFromFile(const std::string& fileName);
	void writeHistoryToFile(const std::string& fileName);

	std::vector<std::string> history;
};

}} //namespace tungsten::eval


#endif /* EVAL_CLISESSIONENVIRONMENT_HPP_ */
