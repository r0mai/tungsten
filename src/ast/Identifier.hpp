
#ifndef AST_IDENTIFIER_HPP_
#define AST_IDENTIFIER_HPP_

#include <string>
#include <utility>

namespace tungsten { namespace ast {

struct Identifier : std::string {
	//No constructor inheritance support
	template<class... Ts>
	Identifier(Ts&&... args) : std::string(std::forward<Ts>(args)...) {}
};

}} //namespace tungsten::ast

#endif /* AST_IDENTIFIER_HPP_ */