
#include "threadListableOperands.hpp"

#include <boost/range/algorithm/find_if.hpp>

#include "ast/Node.hpp"

namespace tungsten { namespace eval {

ThreadListableOperandsReturnType threadListableOperands(const ast::FunctionCall& functionCall, ast::Operands& resultOperands, const ast::Node& head) {

	const ast::Node& function = functionCall.getFunction();
	const ast::Operands& operands = functionCall.getOperands();

	ast::Operands::const_iterator firstListIt = boost::find_if(operands, [&head](const ast::Node& node) {
		return node.is<ast::FunctionCall>() && node.get<ast::FunctionCall>().getFunction() == head;
	});

	if ( firstListIt == operands.end() ) {
		return ThreadListableOperandsReturnType::NOT_APPLICABLE;
	}

	std::size_t targetListSize = firstListIt->get<ast::FunctionCall>().getOperands().size();

	ast::Operands::const_iterator errorneousListIt = boost::find_if(operands, [&targetListSize, &head](const ast::Node& node) -> bool {

		return (node.is<ast::FunctionCall>() &&
				node.get<ast::FunctionCall>().getFunction() == head &&
				node.get<ast::FunctionCall>().getOperands().size() != targetListSize);

	});

	if ( errorneousListIt != operands.end() ) {
		return ThreadListableOperandsReturnType::UNSUCCESSFUL;
	}

	resultOperands = ast::Operands( targetListSize/*, ast::Node::make<ast::FunctionCall>(function, ast::Operands(operands.size()))*/ );

	for ( unsigned i = 0; i < targetListSize; ++i ) {

		ast::Operands resultListOperands(operands.size());

		for ( unsigned j = 0; j < operands.size(); ++j ) {

			const ast::Node& node = operands[j];

			if ( node.is<ast::FunctionCall>() && node.get<ast::FunctionCall>().getFunction() == head ) {

				const ast::Operands& listOperands = node.get<ast::FunctionCall>().getOperands();

				assert( listOperands.size() == targetListSize );

				resultListOperands[j] = listOperands[i];

			} else {
				resultListOperands[j] = node;
			}
		}
		resultOperands[i] = ast::Node::make<ast::FunctionCall>(function, resultListOperands);
	}

	return ThreadListableOperandsReturnType::SUCCESSFUL;

}

}} //namespace tungsten::eval

