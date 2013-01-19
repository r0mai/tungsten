

#ifndef EVAL_THREADLISTABLEOPERANDS_HPP_
#define EVAL_THREADLISTABLEOPERANDS_HPP_

#include "ast/Node.hpp"
#include "Identifiers.hpp"

namespace tungsten { namespace eval {

enum class ThreadListableOperandsReturnType {
	SUCCESSFUL, //Returned on success, resultOperands can be used to make a List as result
	UNSUCCESSFUL, //Returned when there are lists of no equal length in functionCall's arguments
	NOT_APPLICABLE //Returned when there are no lists in functionCall's arguments
};

//Tests are in ut/eval/ListableTest.cpp and ut/eval/threadListableOperandsTest.cpp
//Otherwise the result ast::Operands should be put into a FunctionCall(head)
ThreadListableOperandsReturnType threadListableOperands(const ast::FunctionCall& functionCall,
		ast::Operands& resultOperands,
		const ast::Node& head = ast::Node::make<ast::Identifier>(ids::List));

}} //namespace tungsten::eval

#endif /* EVAL_THREADLISTABLEOPERANDS_HPP_ */
