#include <fstream>
#include <algorithm>
#include "functions.hpp"
#include "eval/getHead.hpp"
#include "eval/SessionEnvironment.hpp"
#include "eval/IterationSpecifier.hpp"
#include "eval/orderNode.hpp"
#include "io/graphics/Primitives.hpp"
#include "io/graphics/Graphics.hpp"
#include "math/Real.hpp"

namespace tungsten { namespace eval { namespace builtin {

OptionalNode Plot(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment) {
//	std::cout<<"Plot"<<std::endl;
	return EvaluationFailure();
#if 0
	using eval::getHead;
	if(operands.size()==2){
		ast::Node tableList = sessionEnvironment.recursiveEvaluate( ast::Node::make<ast::FunctionCall>( ids::Table, operands ) );// TODO x should be identity function.

		if(tableList.isFunctionCall(ids::List)){
//			std::cout<<"so far, so good."<<std::endl;
			assert(getHead(tableList) == ast::Node::make<ast::Identifier>(eval::ids::List));
			const auto argumentList = tableList.get<ast::FunctionCall>().getOperands();
			if(!operands[1].get<ast::FunctionCall>().getOperands()[1].isNumeric() || !operands[1].get<ast::FunctionCall>().getOperands()[2].isNumeric()){
				return EvaluationFailure();
			}
			const math::Real& start = operands[1].get<ast::FunctionCall>().getOperands()[1].getNumeric();
			const math::Real& end = operands[1].get<ast::FunctionCall>().getOperands()[2].getNumeric();

			const auto newRange = [&]() -> const ast::Node {
				if(operands[1].get<ast::FunctionCall>().getOperands().size()==4)
					return operands[1];
				auto copy = operands[1];
				copy.get<ast::FunctionCall>().getOperands().push_back(
					ast::Node::make<math::Real>((end-start)/math::Real(500.0))
				);
				return copy;
			}();
			boost::optional<eval::IterationSpecifier> iteration = eval::IterationSpecifier::fromNode(newRange, sessionEnvironment);
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
			std::vector<ast::Operands> functionLine; 
			functionLine.push_back(ast::Operands());
			const auto yRangeMultiplier = 0.5; // if 0.5, Plots will be square, increase for taller, decrease for wider.
			bool isValid = false;
			for(it.advance();!it.isEnd() ; previous = it.current(), it.advance(), preVal = curVal){
				if(iteration -> hasVariable()) {
					sessionEnvironment.addPattern( ast::Node::make<ast::Identifier>(iteration->getVariable()), it.current() );
						curVal = sessionEnvironment.recursiveEvaluate(operands[0]);
				}
				if(curVal.isNumeric() && 
						nodeLess(ast::Node::make<math::Real>(curVal.getNumeric()),ast::Node::make<math::Real>(yRangeMultiplier*(end-start))) && 
						nodeLess(ast::Node::make<math::Real>(-yRangeMultiplier*(end-start)), ast::Node::make<math::Real>(curVal.getNumeric())) )
				// if curval isn't stupidly big (or invalid) then add to function Line.	
				{
					functionLine.back().push_back(ast::Node::make<ast::FunctionCall>(eval::ids::List, {it.current(), curVal}));
					isValid = true;
				}
				else
			   	{
					if(isValid)
						functionLine.push_back(ast::Operands());
					isValid = false;
				} 
			}

			ast::Operands flatLine;
			for(const auto lineSegment : functionLine){
				for(const auto point : lineSegment){
					flatLine.push_back(point);
				}
			}

			ast::Node helperLine = ast::Node::make<ast::FunctionCall>(eval::ids::Line, {
					ast::Node::make<ast::FunctionCall>(eval::ids::List, flatLine)
			});
			
			const auto lineHelper = io::graphics::Line().fromOperands(helperLine.get<ast::FunctionCall>().getOperands(), sessionEnvironment);
			const auto box = lineHelper.getBoundingBox();
			ast::Node xAxis = ast::Node::make<ast::FunctionCall>(eval::ids::Arrow, {
						ast::Node::make<ast::FunctionCall>(eval::ids::List, {
								ast::Node::make<ast::FunctionCall>(eval::ids::List, {
									ast::Node::make<math::Real>(box.minX), ast::Node::make<math::Real>(0.0)
									}), // left-most coordinate of arrow.
								ast::Node::make<ast::FunctionCall>(eval::ids::List, {
									ast::Node::make<math::Real>(box.maxX), ast::Node::make<math::Real>(0.0)
									}) // right-most coordinate.
							})
					});
			ast::Node yAxis = ast::Node::make<ast::FunctionCall>(eval::ids::Arrow, {
						ast::Node::make<ast::FunctionCall>(eval::ids::List, {
							ast::Node::make<ast::FunctionCall>(eval::ids::List, {
								ast::Node::make<math::Real>(0.0), ast::Node::make<math::Real>(box.minY)
								}), // bottom most coordinate
							ast::Node::make<ast::FunctionCall>(eval::ids::List, {
								ast::Node::make<math::Real>(0.0), ast::Node::make<math::Real>(box.maxY)
								}) // top most coordinate
						})
					});
			
//			sessionEnvironment.removePattern( ast::Node::make<ast::Identifier>(iteration->getVariable()) );
//			^^ Don't remove, may not exist. //TODO Find way to query existance.
			if(lastKnownValue)	
				sessionEnvironment.addPattern( lastKnownName, *lastKnownValue);
			else
				sessionEnvironment.removePattern(lastKnownName);
			// restore variable.
			//
			const auto blue = ast::Node::make<ast::Identifier>(eval::ids::Blue);

			ast::Operands merged;
			merged.push_back(xAxis);
			merged.push_back(yAxis);
			merged.push_back(blue);

			for(const auto lineSegment : functionLine){
				merged.push_back(ast::Node::make<ast::FunctionCall>(eval::ids::Line, {
					ast::Node::make<ast::FunctionCall>(eval::ids::List, lineSegment)
				}));
			}

			const auto GraphicsNode = ast::Node::make<ast::FunctionCall>(eval::ids::Graphics, 
					{ast::Node::make<ast::FunctionCall>(eval::ids::List, merged )});
			return GraphicsNode;
		}
	}
	return EvaluationFailure();
#endif
}

OptionalNode Export(const ast::Operands& operands, SessionEnvironment& sessionEnvironment){
	if(operands.size()==2 && operands[0].is<ast::String>() ){
		io::graphics::GraphicsObject graphicsObject;
		makeGraphics(operands[1], sessionEnvironment, graphicsObject);
		const auto filename = [&]() -> const std::string {
			const auto filename = operands[0].get<ast::String>().toString();
			if(filename.size()>=2 && filename[0] == '"' && filename[filename.length()-1] == '"'){
				std::string realFilename;
				std::copy(filename.begin()+1, filename.end()-1, realFilename.begin());
				return realFilename;
			}
			return filename;
		}();
		graphicsObject.exportToSVG(filename);
		return (operands[0]);
	} 
	return EvaluationFailure();
}


}}}; // tungsten::eval::builtin
