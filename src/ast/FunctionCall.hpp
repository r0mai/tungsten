
#ifndef AST_FUNCTIONCALL_HPP_
#define AST_FUNCTIONCALL_HPP_

#include <memory>
#include <vector>
#include <functional>

#include <boost/operators.hpp>

#include "NodeFwd.hpp"
#include "Identifier.hpp"

namespace tungsten { namespace ast {

typedef std::vector<Node> Operands;

struct FunctionCall : boost::equality_comparable<FunctionCall> {

	FunctionCall();
	FunctionCall(const FunctionCall& other);
	FunctionCall(const Identifier& name);
	FunctionCall(const Identifier& name, const Operands& operands);
	FunctionCall(const Node& function);
	FunctionCall(const Node& function, const Operands& operands);

	FunctionCall& operator=(FunctionCall other);

	bool operator==(const FunctionCall& other) const;

	Node& getFunction();
	const Node& getFunction() const;

	Operands& getOperands();
	const Operands& getOperands() const;



	friend void swap(FunctionCall& fc1, FunctionCall& fc2);

private:

	NodePtr function;
	Operands operands;
};

}} //namespace tungsten::ast


#endif /* AST_FUNCTIONCALL_HPP_ */
