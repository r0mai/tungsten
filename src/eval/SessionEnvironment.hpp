
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

	void raiseMessage(const Message& message);
	virtual void handleMessageString(const ast::String& /*messageString*/) {}

	void addPattern(const ast::Node& pattern, const ast::Node& replacement);
	RandomEngine& getRandomEngine();

	//Both can be called.
	//std::string version will raise syntax error messages
	ast::Node evaluate(const std::string& inputString);
	ast::Node evaluate(const ast::Node& node);

	//should not be called from the outside
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
