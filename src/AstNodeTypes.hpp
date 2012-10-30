
#ifndef ASTNODETYPES_HPP_
#define ASTNODETYPES_HPP_

#include <gmpxx.h>

#include <string>
#include <vector>

namespace tungsten {

//Fwd declare
class AstNode;

//These types should are the ones used in AstNode.

//Numbers
typedef mpz_class Integer;
typedef mpq_class Rational;
typedef mpf_class Real;

//String type //note: std::string should be used when strings outside an Ast needed
typedef std::string String;

//Identifier (symbols like "Pi", and variables like "x")
typedef std::string Identifier;

//Function
typedef std::string FunctionName;
typedef std::vector<AstNode> Operands;

struct Function {

	Function() {}
	Function(const FunctionName& name) : name(name) {}
	Function(const FunctionName& name, const Operands& operands) :
		name(name), operands(operands) {}

	FunctionName name;
	Operands operands;
};



} //namespace tungsten


#endif /* ASTNODETYPES_HPP_ */
