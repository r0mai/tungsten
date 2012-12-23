

#ifndef CLIENVIRONMENT_HPP_
#define CLIENVIRONMENT_HPP_

#include "Environment.hpp"

namespace tungsten { namespace eval {

class CLIEnvironment : public Environment {
public:
	CLIEnvironment();
	virtual ~CLIEnvironment() override;

	void run();

private:


};

}} //namespace tungsten::eval


#endif /* CLIENVIRONMENT_HPP_ */
