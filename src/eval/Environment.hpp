
#ifndef EVAL_ENVIRONMENT_HPP_
#define EVAL_ENVIRONMENT_HPP_

#include "ast/Node.hpp"
#include "Message.hpp"
#include "builtin/functions.hpp"
#include "EnvironmentFwd.hpp"
#include "Attribute.hpp"

namespace tungsten { namespace eval {

class Environment {
public:
	Environment();
	virtual ~Environment();

	ast::Node evaluate(const ast::Node& node);
protected:
	virtual void handleMessage(const Message& /*message*/) {}

	ast::Node recursiveEvaluate(const ast::Node& node);

	AttributeMap attributeMap;

	const builtin::Functions builtinFunctions;

	//History

private:
	struct EvaluateVisitor;

};

}} //namespace tungsten::eval

#endif /* EVAL_ENVIRONMENT_HPP_ */
