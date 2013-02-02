

#ifndef EVAL_ARGSESSIONENVIRONMENT_HPP_
#define EVAL_ARGSESSIONENVIRONMENT_HPP_

#include "SessionEnvironment.hpp"

#include <string>

namespace tungsten { namespace eval {

class ArgSessionEnvironment : public SessionEnvironment {
public:
	ArgSessionEnvironment();
	virtual ~ArgSessionEnvironment() override;

	std::string evaluateArg(const std::string& input);
};

}} //namespace tungsten::eval

#endif /* EVAL_ARGSESSIONENVIRONMENT_HPP_ */
