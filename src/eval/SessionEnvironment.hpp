
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
	virtual void printToStdout(const ast::Operands& /*nodes*/) {}

	void addPattern(const ast::Node& pattern, const ast::Node& replacement);
	boost::optional<ast::Node> getPatternReplacement(const ast::Node& pattern);
	void removePattern(const ast::Node& pattern);

	RandomEngine& getRandomEngine();
	AttributeMap& getAttributeMap();
	const AttributeMap& getAttributeMap() const;

	AttributeSet getAttributeSetForFunction(const ast::Node& node) const;

	//Both can be called.
	//std::string version will raise syntax error messages
	ast::Node evaluate(const std::string& inputString);
	ast::Node evaluate(const ast::Node& node);

	//should not be called from the outside
	ast::Node recursiveEvaluate(const ast::Node& node);

	bool isReapStackEmpty() const;
	void pushReapStack();
	ast::Operands popReapStack();
	void sowToReapStack(const ast::Node& node);

	boost::optional<ast::Node> nthOutput(int n) const;
	boost::optional<ast::Node> nthInput(int n) const;

protected:
	AttributeMap attributeMap;
	const builtin::Functions builtinFunctions;
	PatternMap patternMap;
	ErrorMessageStringMap errorMessageStringMap;
	RandomEngine randomEngine;

	typedef std::vector<ast::Operands> ReapStack;
	ReapStack reapStack;

private:
	struct EvaluateVisitor;
	std::vector<ast::Node> inHistory;
	std::vector<ast::Node> outHistory;

};

}} //namespace tungsten::eval

#endif /* EVAL_SESSIONENVIRONMENT_HPP_ */
