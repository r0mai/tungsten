
#ifndef AST_STRING_HPP_
#define AST_STRING_HPP_

#include <string>
#include <utility>
#include <ostream>

namespace tungsten { namespace ast {

//String type //note: std::string should be used when strings outside an Ast needed
//Making an extra classes so type resolution works correctly
struct String : std::string {
	//No constructor inheritance support
	template<class... Ts>
	String(Ts&&... args) : std::string(std::forward<Ts>(args)...) {}

	std::string toString() const;
};

std::ostream& operator<<(std::ostream& os, const String& string);

}} //namespace tungsten::ast

#endif /* AST_STRING_HPP_ */
