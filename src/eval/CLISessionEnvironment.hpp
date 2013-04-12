

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


};

}} //namespace tungsten::eval


#endif /* EVAL_CLISESSIONENVIRONMENT_HPP_ */
