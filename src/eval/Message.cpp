
#include "Message.hpp"

namespace tungsten { namespace eval {

Message::Message(const ast::Identifier& symbol, const ast::String& tag, const ast::Operands& arguments) :
		symbol(symbol), tag(tag), arguments(arguments) {}

Message::Message(const ast::Identifier& symbol, const ast::String& tag, std::initializer_list<ast::Node> arguments) :
		Message(symbol, tag, ast::Operands(arguments)) {}

const ast::Identifier& Message::getSymbol() const {
	return symbol;
}

const ast::String& Message::getTag() const {
	return tag;
}

const ast::Operands& Message::getArguments() const {
	return arguments;
}

}} //namespace tungsten::eval




