
#ifndef EVAL_SESSIONENVIRONMENT_HPP_
#define EVAL_SESSIONENVIRONMENT_HPP_

#include "ast/Node.hpp"
#include "Message.hpp"
#include "builtin/functions.hpp"
#include "SessionEnvironmentFwd.hpp"
#include "Attribute.hpp"
#include "PatternMap.hpp"
#include "Random.hpp"

//TODO maybe this stuff should be moved outside to a session directory

namespace tungsten { namespace eval {

class SessionEnvironment {
public:
	SessionEnvironment();
	virtual ~SessionEnvironment();

	ast::Node evaluate(const ast::Node& node);

	virtual void handleMessage(const Message& /*message*/) {}

	void addPattern(const ast::Node& pattern, const ast::Node& replacement);
	RandomEngine& getRandomEngine();

	ast::Node recursiveEvaluate(const ast::Node& node);

protected:
	AttributeMap attributeMap;
	const builtin::Functions builtinFunctions;
	PatternMap patternMap;
	RandomEngine randomEngine;

private:
	struct EvaluateVisitor;

};

}} //namespace tungsten::eval

#endif /* EVAL_SESSIONENVIRONMENT_HPP_ */
