
#ifndef AST_IDENTIFIER_HPP_
#define AST_IDENTIFIER_HPP_

#include <string>
#include <utility>

#include <boost/type_traits/has_nothrow_copy.hpp>

namespace tungsten { namespace ast {

struct Identifier : std::string {
	//No constructor inheritance support
	template<class... Ts>
	Identifier(Ts&&... args) : std::string(std::forward<Ts>(args)...) {}

	std::string toString() const;

	std::size_t getByteCount() const;
};

std::ostream& operator<<(std::ostream& os, const Identifier& identifier);

}} //namespace tungsten::ast

namespace boost {

template <>
struct has_nothrow_copy<tungsten::ast::Identifier> : mpl::true_ {};

}

#endif /* AST_IDENTIFIER_HPP_ */
