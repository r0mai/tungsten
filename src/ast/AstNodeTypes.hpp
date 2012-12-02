
#ifndef ASTNODETYPES_HPP_
#define ASTNODETYPES_HPP_

#include <string>
#include <vector>
#include <utility>

#include <gmpxx.h>

#include <boost/operators.hpp>

namespace tungsten {

//Fwd declare
class AstNode;

//These types should are the ones used in AstNode.

//Numbers
typedef mpz_class Integer;
typedef mpq_class Rational;
typedef mpf_class Real;

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
typedef std::vector<AstNode> Operands;

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



} //namespace tungsten


#endif /* ASTNODETYPES_HPP_ */
