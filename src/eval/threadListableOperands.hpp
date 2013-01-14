

#ifndef EVAL_THREADLISTABLEOPERANDS_HPP_
#define EVAL_THREADLISTABLEOPERANDS_HPP_

#include "ast/FunctionCall.hpp"

namespace tungsten { namespace eval {

enum class ThreadListableOperandsReturnType {
	SUCCESSFUL, //Returned on success, resultOperands can be used to make a List as result
	UNSUCCESSFUL, //Returned when there are lists of no equal length in functionCall's arguments
	NOT_APPLICABLE //Returned when there are no lists in functionCall's arguments
};

//Tests are in ut/eval/ListableTest.cpp
//Returns empty optional if threading is unsuccessful
//Otherwise the result ast::Operands should be put into a FunctionCall("List")
ThreadListableOperandsReturnType threadListableOperands(const ast::FunctionCall& functionCall, ast::Operands& resultOperands);

}} //namespace tungsten::eval

#endif /* EVAL_THREADLISTABLEOPERANDS_HPP_ */
