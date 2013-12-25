
#ifndef AST_STRING_HPP_
#define AST_STRING_HPP_

#include <string>
#include <utility>
#include <ostream>

#include <boost/type_traits/has_nothrow_copy.hpp>

namespace tungsten { namespace ast {

//String type //note: std::string should be used when strings outside an Ast needed
//Making an extra classes so type resolution works correctly
struct String : std::string {
	//No constructor inheritance support
	template<class... Ts>
	String(Ts&&... args) : std::string(std::forward<Ts>(args)...) {}

	//This returns the string without the " marks
	const std::string& getRawString() const;
	std::string& getRawString();

	//For debug purposes, returns a pretty version of the string with escapes and "s
	std::string toString() const;

	std::size_t getByteCount() const;
};

std::ostream& operator<<(std::ostream& os, const String& string);

}} //namespace tungsten::ast

namespace boost {

template <>
struct has_nothrow_copy<tungsten::ast::String> : mpl::true_ {};

}

#endif /* AST_STRING_HPP_ */

