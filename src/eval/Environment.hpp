
#ifndef EVAL_ENVIRONMENT_HPP_
#define EVAL_ENVIRONMENT_HPP_

#include "ast/Node.hpp"
#include "Message.hpp"

namespace tungsten { namespace eval {

class Environment {
public:
	Environment();
	virtual ~Environment();

	ast::Node evaluate(const ast::Node& node);
protected:
	virtual void handleMessage(const Message& /*message*/) {}


	//History
	//Symbols
	//builtin functions

};

}} //namespace tungsten::eval

#endif /* EVAL_ENVIRONMENT_HPP_ */
