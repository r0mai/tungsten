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
				return EvaluationFailure();
			}

			auto it = iteration->makeIterator();
			auto previous = it.current();
			auto lastKnownName = ast::Node::make<ast::Identifier>(iteration->getVariable());
			ast::Node preVal, curVal;
			if(iteration -> hasVariable()){
				sessionEnvironment.addPattern(ast::Node::make<ast::Identifier>(iteration->getVariable()), previous);
					preVal = sessionEnvironment.recursiveEvaluate(operands[0]);
			}
			// get last known value for plot variable
			const auto lastKnownValue = sessionEnvironment.getPatternReplacement(ast::Node::make<ast::Identifier>(iteration->getVariable()));
			ast::Operands functionLine; 

			for(it.advance();!it.isEnd() ; previous = it.current(), it.advance(), preVal = curVal){
				if(iteration -> hasVariable()) {
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
				functionLine.push_back(ast::Node::make<ast::FunctionCall>(eval::ids::List, {it.current(), curVal}));

			}
			ast::Node functionLineList = ast::Node::make<ast::FunctionCall>(eval::ids::List, {});
			functionLineList.get<ast::FunctionCall>().getOperands() = std::move(functionLine);	
			graphicsOperands.push_back(ast::Node::make<ast::FunctionCall>(eval::ids::Line, {functionLineList}));

//			sessionEnvironment.removePattern( ast::Node::make<ast::Identifier>(iteration->getVariable()) );
//			^^ Don't remove, may not exist. //TODO Find way to query existance.
			if(lastKnownValue)	
				sessionEnvironment.addPattern( lastKnownName, *lastKnownValue);
			else
				sessionEnvironment.removePattern(lastKnownName);
			// restore variable.
			const auto GraphicsNode = ast::Node::make<ast::FunctionCall>(eval::ids::Graphics, 
					{ast::Node::make<ast::FunctionCall>(eval::ids::List,	graphicsOperands)});
			return GraphicsNode;
		}
	}
	return EvaluationFailure();
}



}}}; // tungsten::eval::builtin
