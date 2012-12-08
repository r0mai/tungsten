
#ifndef AST_NODETYPES_HPP_
#define AST_NODETYPES_HPP_

#include <string>
#include <vector>
#include <utility>

#include <boost/operators.hpp>

#include "math/Types.hpp"

namespace tungsten { namespace ast {

//Fwd declare
class Node;

//These types are used in Node (along with the Rational and Real from math/Types.hpp

//String type //note: std::string should be used when strings outside an Ast needed
//Making an extra classes so type resolution works correctly
struct String : std::string {
	//No constructor inheritance support
	template<class... Ts>
	String(Ts&&... args) : std::string(std::forward<Ts>(args)...) {}
};


struct Identifier : std::string {
	//No constructor inheritance support
	template<class... Ts>
	Identifier(Ts&&... args) : std::string(std::forward<Ts>(args)...) {}
};


//Function
typedef std::string FunctionName;
typedef std::vector<Node> Operands;

struct Function : boost::equality_comparable<Function> {

	Function() {}
	Function(const FunctionName& name) : name(name) {}
	Function(const FunctionName& name, const Operands& operands) :
		name(name), operands(operands) {}

	bool operator==(const Function& other) const {
		return name == other.name && operands == other.operands;
	}

	FunctionName name;
	Operands operands;
};



}} //namespace tungsten::ast


#endif /* AST_NODETYPES_HPP_ */
