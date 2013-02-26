
#ifndef EVAL_FILESESSIONENVIRONMENT_HPP_
#define EVAL_FILESESSIONENVIRONMENT_HPP_

#include "SessionEnvironment.hpp"

namespace tungsten { namespace eval {

class FileSessionEnvironment : public SessionEnvironment {
public:
	FileSessionEnvironment(const std::string& fileName);

	virtual void handleMessageString(const ast::String& messageString) override;

	void run();
private:
	std::string fileName;
};

}} //namespace tungsten::eval

#endif /* EVAL_FILESESSIONENVIRONMENT_HPP_ */
