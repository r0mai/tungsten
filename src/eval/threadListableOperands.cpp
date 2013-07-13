
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

	//resultOperands = ast::Operands( targetListSize/*, ast::Node::make<ast::FunctionCall>(function, ast::Operands(operands.size()))*/ );
	assert( resultOperands.empty() );


	for ( unsigned i = 0; i < targetListSize; ++i ) {

		ast::Operands resultListOperands;

		for ( const ast::Node& node : operands ) {

			if ( node.isFunctionCall(head) ) {

				const ast::Operands& listOperands = node.get<ast::FunctionCall>().getOperands();

				assert( listOperands.size() == targetListSize );

				resultListOperands.push_back(listOperands[i]); //TODO optimizing out this indexing would require a (spare) array of iterators

			} else {
				resultListOperands.push_back(node);
			}
		}
		resultOperands.push_back(ast::Node::make<ast::FunctionCall>(function, resultListOperands));
	}

	return ThreadListableOperandsReturnType::SUCCESSFUL;

}

}} //namespace tungsten::eval

