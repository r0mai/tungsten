
#ifndef EVAL_MESSAGE_HPP_
#define EVAL_MESSAGE_HPP_

#include <ast/Node.hpp>

#include <initializer_list>

namespace tungsten { namespace eval {

//This class represents the messages which gets raised during evaluation
class Message {
public:

	Message(const ast::Identifier& symbol, const ast::String& tag, const ast::Operands& arguments);
	Message(const ast::Identifier& symbol, const ast::String& tag, std::initializer_list<ast::Node> arguments);

	const ast::Identifier& getSymbol() const;
	const ast::String& getTag() const;
	const ast::Operands& getArguments() const;

private:
	//symbol::tag <e1,e2,...,eN>
	ast::Identifier symbol;
	ast::String tag;
	ast::Operands arguments;
};

}} //namespace tungsten::eval

#endif /* EVAL_MESSAGE_HPP_ */
