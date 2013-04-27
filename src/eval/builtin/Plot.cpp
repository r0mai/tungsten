#include <fstream>
#include <algorithm>
#include "functions.hpp"
#include "eval/getHead.hpp"
#include "eval/SessionEnvironment.hpp"
#include "eval/IterationSpecifier.hpp"
#include "eval/numericNodeEvaluation.hpp"
#include "eval/orderNode.hpp"
#include "io/graphics/Primitives.hpp"
#include "io/graphics/Graphics.hpp"
#include "math/Real.hpp"

namespace tungsten { namespace eval { namespace builtin {

OptionalNode Plot(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment) {
	if(operands.size() == 2 && operands[1].isFunctionCall(ids::List)){
		const auto& function = operands[0]; // to be called lots and lots of times.
		const auto& rangeOperands = operands[1].get<ast::FunctionCall>().getOperands();
		if(rangeOperands.size() == 3 && 
			rangeOperands[0].is<ast::Identifier>() &&
			numericNodeEvaluation(rangeOperands[1], sessionEnvironment).isNumeric() &&
			numericNodeEvaluation(rangeOperands[2], sessionEnvironment).isNumeric() ){
			/* range is a-ok */
			const auto variable = rangeOperands[0]; // is an identifier.
			const auto minX = numericNodeEvaluation(rangeOperands[1], sessionEnvironment).getNumeric();
			const auto maxX = numericNodeEvaluation(rangeOperands[2], sessionEnvironment).getNumeric();
			const auto distance = maxX - minX;

		//	const math::Real aspectRatio;
			
			ast::Operands currentLine;				// List[List[x,y], ...] : need to enclose in List.
			ast::Operands lineVector;	// List[Line[^^^], ...] : need to enclise in List with other objects.
			
			math::Real advancement = distance/math::Real(768); // I like wierd numbers.
			math::Real currentX, currentY;
			//math::Real previousX, previousY;

			math::Real minY, maxY;
			minY = 0.0;
			maxY = 0.0;
			bool first=true; // signifies whether this is the first valid point on the function.

			for(currentX = minX; currentX <= maxX; currentX += advancement){
				sessionEnvironment.addPattern(variable, ast::Node::make<math::Real>(currentX));
				const auto currentYAttempt = numericNodeEvaluation(function, sessionEnvironment);
				if(currentYAttempt.isNumeric()){
					// continuous so far.
					currentY = currentYAttempt.getNumeric();
					if(!first){
						if(maxY<currentY) maxY = currentY;
						if(currentY<minY) minY = currentY; // minY = std::min(minY, currentY) for some reason causes NaNs.
					} else {
						minY = currentY;
						maxY = currentY;
						first = false;
					}
					currentLine.push_back(ast::Node::make<ast::FunctionCall>(ids::List, { 
									ast::Node::make<math::Real>(currentX), 
									ast::Node::make<math::Real>(currentY)  
								}));
				} else {
					// break in function Line
					if(!currentLine.empty()){
						lineVector.push_back(
							ast::Node::make<ast::FunctionCall>(ids::Line, {
								ast::Node::make<ast::FunctionCall>(ids::List, currentLine)
							})
						);
						currentLine.clear();
					}
				}
			} 
			if(!currentLine.empty()){
				lineVector.push_back(
					ast::Node::make<ast::FunctionCall>(ids::Line, {
						ast::Node::make<ast::FunctionCall>(ids::List, currentLine)
					})
				);
				currentLine.clear();
			}
			// line vector is now an array of Line[]-s
			// move it all to merged
			ast::Operands merged(std::move(lineVector));
			const auto xAxis =	ast::Node::make<ast::FunctionCall>(ids::Line, {
									ast::Node::make<ast::FunctionCall>(ids::List, {
										ast::Node::make<ast::FunctionCall>(ids::List, {
											ast::Node::make<math::Real>(minX), ast::Node::make<math::Real>(0.0)
										}),
										ast::Node::make<ast::FunctionCall>(ids::List, {
											ast::Node::make<math::Real>(maxX), ast::Node::make<math::Real>(0.0)
										})
									})
								});
			const auto yAxis =	ast::Node::make<ast::FunctionCall>(ids::Line, {
									ast::Node::make<ast::FunctionCall>(ids::List, {
										ast::Node::make<ast::FunctionCall>(ids::List, {
											ast::Node::make<math::Real>(0.0), ast::Node::make<math::Real>(minY)
										}),
										ast::Node::make<ast::FunctionCall>(ids::List, {
											ast::Node::make<math::Real>(0.0), ast::Node::make<math::Real>(maxY)
										})
									})
								});
			merged.push_back(xAxis);
			merged.push_back(yAxis);

			// start work on labels.
			//
			// 
			//
			const math::Real scaleX = ceil(pow(10, floor(log10(distance)))); // 
			const math::Real lineHeight = 0.04 * (maxY - minY);
			for(math::Real marker = ceil(minX/scaleX); marker <= floor(maxX)/scaleX; marker=ceil(marker+1)){
				if( marker < 0.9 && marker > -0.9)
					continue; // skip values close to 0.

				const auto tickNode =	ast::Node::make<ast::FunctionCall>(eval::ids::Line, {
											ast::Node::make<ast::FunctionCall>(eval::ids::List, {
												ast::Node::make<ast::FunctionCall>(eval::ids::List, {
													ast::Node::make<math::Real>(marker*scaleX), ast::Node::make<math::Real>(-lineHeight)
												}),
												ast::Node::make<ast::FunctionCall>(eval::ids::List, {
													ast::Node::make<math::Real>(marker*scaleX), ast::Node::make<math::Real>(lineHeight)
												})
											})
										});

				merged.push_back(tickNode);
				merged.push_back(ast::Node::make<ast::FunctionCall>(ids::Text, {
							ast::Node::make<math::Real>(marker*scaleX),
							ast::Node::make<ast::FunctionCall>(ids::List, {
								ast::Node::make<math::Real>(marker*scaleX), 
								ast::Node::make<math::Real>(0.0)
							})
						}));
			}

			const math::Real scaleY = ceil(pow(10, floor(log10(maxY-minY)))); // 
			const math::Real lineWidth = 0.04 * distance;
			for(math::Real marker = ceil(minY/scaleY); marker <= floor(maxY)/scaleY; marker=ceil(marker+1)){
				if( marker < 0.9 && marker > -0.9)
					continue; // skip values close to 0.

				const auto tickNode =	ast::Node::make<ast::FunctionCall>(eval::ids::Line, {
											ast::Node::make<ast::FunctionCall>(eval::ids::List, {
												ast::Node::make<ast::FunctionCall>(eval::ids::List, {
													ast::Node::make<math::Real>(-lineWidth), ast::Node::make<math::Real>(marker*scaleY)
												}),
												ast::Node::make<ast::FunctionCall>(eval::ids::List, {
													ast::Node::make<math::Real>(lineWidth), ast::Node::make<math::Real>(marker*scaleY) 
												})
											})
										});

				merged.push_back(tickNode);
				merged.push_back(ast::Node::make<ast::FunctionCall>(ids::Text, {
							ast::Node::make<math::Real>(marker*scaleY),
							ast::Node::make<ast::FunctionCall>(ids::List, {
								ast::Node::make<math::Real>(0.0),
								ast::Node::make<math::Real>(marker*scaleY)
							})
						}));
			}

			// merged now includes all function lines, and axes.
			const auto GraphicsNode = ast::Node::make<ast::FunctionCall>(ids::Graphics, 
					{ast::Node::make<ast::FunctionCall>(ids::List, merged )});
			return GraphicsNode;

		}
		return EvaluationFailure();
	}
	return EvaluationFailure();
}

OptionalNode Export(const ast::Operands& operands, SessionEnvironment& sessionEnvironment){
	if(operands.size()==2 && operands[0].is<ast::String>() ){
		io::graphics::GraphicsObject graphicsObject;
		makeGraphics(operands[1], sessionEnvironment, graphicsObject);
		const auto filename = [&]() -> const std::string {
			const auto filename = operands[0].get<ast::String>().toString();
			if(filename.size()>=2 && filename[0] == '"' && filename[filename.length()-1] == '"'){
				return filename.substr(1, filename.size() - 2);
			}
			return filename;
		}();
		graphicsObject.exportToSVG(filename);
		return (operands[0]);
	} 
	return EvaluationFailure();
}


}}}; // tungsten::eval::builtin
