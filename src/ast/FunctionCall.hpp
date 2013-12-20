
#ifndef AST_FUNCTIONCALL_HPP_
#define AST_FUNCTIONCALL_HPP_

#include <memory>
#include <vector>
#include <functional>
#include <ostream>
#include <initializer_list>

#include <boost/operators.hpp>
#include <boost/type_traits/has_nothrow_copy.hpp>

#include "NodeFwd.hpp"
#include "Identifier.hpp"

namespace tungsten { namespace ast {

typedef std::vector<Node> Operands;

struct FunctionCall :
		boost::less_than_comparable<FunctionCall,
		boost::equality_comparable<FunctionCall>> {

	FunctionCall();
	FunctionCall(const FunctionCall& other);
	FunctionCall(const Identifier& name);
	FunctionCall(const Identifier& name, const Operands& operands);
	FunctionCall(const Identifier& name, std::initializer_list<Node> operands);
	FunctionCall(const Node& function);
	FunctionCall(const Node& function, const Operands& operands);
	FunctionCall(const Node& name, std::initializer_list<Node> operands);

	FunctionCall& operator=(FunctionCall other);

	bool operator==(const FunctionCall& other) const;
	bool operator<(const FunctionCall& rhs) const;

	Node& getFunction();
	const Node& getFunction() const;

	Operands& getOperands();
	const Operands& getOperands() const;

	std::string toString() const;

	friend void swap(FunctionCall& fc1, FunctionCall& fc2);

private:

	NodePtr function;
	Operands operands;
};

std::ostream& operator<<(std::ostream& os, const FunctionCall& fc);

}} //namespace tungsten::ast

namespace boost {

template <>
struct has_nothrow_copy<tungsten::ast::FunctionCall> : mpl::true_ {};

}

#endif /* AST_FUNCTIONCALL_HPP_ */
