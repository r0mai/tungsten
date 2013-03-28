#include "functions.hpp"
#include "eval/getHead.hpp"
#include "eval/SessionEnvironment.hpp"
#include "eval/IterationSpecifier.hpp"

namespace tungsten { namespace eval { namespace builtin {

OptionalNode Plot(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment) {
//	std::cout<<"Plot"<<std::endl;
	using eval::getHead;
	if(operands.size()==2){
		const auto tableListOptional = 
			Table(operands, sessionEnvironment);	// TODO x should be identity function.
		if(tableListOptional){
//			std::cout<<"so far, so good."<<std::endl;
			const auto tableList = *tableListOptional;
			assert(getHead(tableList) == ast::Node::make<ast::Identifier>(eval::ids::List));
			const auto argumentList = tableList.get<ast::FunctionCall>().getOperands();
			ast::Operands graphicsOperands;
			boost::optional<eval::IterationSpecifier> iteration = eval::IterationSpecifier::fromNode(operands[1], sessionEnvironment);
			if(!iteration || !iteration->isFinite()){
				std::cout<<"NEAOOohoHhHHhhhhH :("<<std::endl;
				return EvaluationFailure();
			}

			auto it = iteration->makeIterator();
			auto previous = it.current();

			for(it.advance();!it.isEnd() ; previous = it.current(), it.advance()){
				ast::Node preVal, curVal;
				if(iteration -> hasVariable()) {
					sessionEnvironment.addPattern( ast::Node::make<ast::Identifier>(iteration->getVariable()), previous );
						preVal = sessionEnvironment.recursiveEvaluate(operands[0]);
					sessionEnvironment.addPattern( ast::Node::make<ast::Identifier>(iteration->getVariable()), it.current() );
						curVal = sessionEnvironment.recursiveEvaluate(operands[0]);
				}
				ast::Operands lineSegment = {ast::Node::make<ast::FunctionCall>(eval::ids::List, 
						{
						ast::Node::make<ast::FunctionCall>(eval::ids::List, { 
							previous, preVal 
							})
						,
						ast::Node::make<ast::FunctionCall>(eval::ids::List, {
							it.current(), curVal
							})
								
						})};
				graphicsOperands.push_back(ast::Node::make<ast::FunctionCall>(eval::ids::Line, lineSegment));

			} 
			sessionEnvironment.removePattern( ast::Node::make<ast::Identifier>(iteration->getVariable()) );
			const auto diff = 0.01;
			const auto GraphicsNode = ast::Node::make<ast::FunctionCall>(eval::ids::Graphics, 
					{ast::Node::make<ast::FunctionCall>(eval::ids::List,	graphicsOperands)});
			return GraphicsNode;
		}
		std::cout<<"a"<<std::endl;
	}
	return EvaluationFailure();
}



}}}; // tungsten::eval::builtin
