#include <fstream>
#include <algorithm>
#include <iostream>
#include <boost/math/constants/constants.hpp>
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
			const auto minXT = numericNodeEvaluation(rangeOperands[1], sessionEnvironment).getNumeric();
			const auto maxXT = numericNodeEvaluation(rangeOperands[2], sessionEnvironment).getNumeric();

			auto minX = minXT>maxXT?maxXT:minXT;
			auto maxX = minXT>maxXT?minXT:maxXT;

			if(minX >= maxX){
				return EvaluationFailure();
			}
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

			const auto oldPatternForVariable = sessionEnvironment.getPatternReplacement(variable);

			for(unsigned i=0; i<768; ++i){
				currentX = i*advancement+minX;
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
					const auto isOnPreviousLine = [&currentLine](math::Real x, math::Real y) {
						math::Real previousX = currentLine.rbegin()[0].get<ast::FunctionCall>().getOperands()[0].getNumeric();
						math::Real previousY = currentLine.rbegin()[0].get<ast::FunctionCall>().getOperands()[1].getNumeric();
						math::Real previousPreviousX = currentLine.rbegin()[1].get<ast::FunctionCall>().getOperands()[0].getNumeric();
						math::Real previousPreviousY = currentLine.rbegin()[1].get<ast::FunctionCall>().getOperands()[1].getNumeric();

						return (y-previousY)/(x-previousX) == (y-previousPreviousY)/(x-previousPreviousX);
					};
					if(currentLine.size() < 2 || !isOnPreviousLine(currentX, currentY)) {
						currentLine.push_back(ast::Node::make<ast::FunctionCall>(ids::List, {
										ast::Node::make<math::Real>(currentX),
										ast::Node::make<math::Real>(currentY)
									}));
					} else {
						currentLine.back() = ast::Node::make<ast::FunctionCall>(ids::List, {
								ast::Node::make<math::Real>(currentX),
								ast::Node::make<math::Real>(currentY)
								});
					}
				} else {
					// break in function Line
					if(currentLine.size() >1){
						lineVector.push_back(
							ast::Node::make<ast::FunctionCall>(ids::Line, {
								ast::Node::make<ast::FunctionCall>(ids::List, std::move(currentLine))
							})
						);
					}
					currentLine.clear();
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

			if(oldPatternForVariable) {
				// if was already assigned, restore
				sessionEnvironment.addPattern(variable, *oldPatternForVariable);
			} else {
				sessionEnvironment.removePattern(variable);
			}

			if( (maxX - minX) / (maxY - minY) > boost::math::constants::phi<double>() ){
				// graph is very wide.
//				std::cout<<"wide"<<std::endl;
				const auto height = abs(maxY - minY);
				const auto desiredHeight = abs(maxX - minX) / boost::math::constants::phi<double>();
				const auto difference = desiredHeight - height;
				const math::Real differenceByTwo = difference/math::Real(2);
				maxY += differenceByTwo;
				minY -= differenceByTwo;

			} else if( (maxY - minY) / (maxX - minX) > boost::math::constants::phi<double>() ) {
				//graph is very tall
//				std::cout<<"tall"<<std::endl;
				const auto width = abs(maxX - minX);
				const auto desiredWidth = abs(maxY - minY) * boost::math::constants::phi<double>();
				const auto difference = desiredWidth - width;
				const math::Real differenceByTwo = difference/math::Real(2);
				maxX += differenceByTwo;
				minX -= differenceByTwo;

			}


			// line vector is now an array of Line[]-s
			// move it all to merged
			//
			// 0,0 may not be a part of the Plot[]
			//

			math::Real axisX, axisY;

			if( minX <= 0.0 && 0.0 <= maxX ){
				axisX = 0.0;
			} else {
				axisX = minX;
			}

			if( minY <= 0.0 && 0.0 <= maxY ){
				axisY = 0.0;
			} else {
				axisY = minY;
			}


			ast::Operands merged(std::move(lineVector));
			const auto xAxis =	ast::Node::make<ast::FunctionCall>(ids::Line, {
									ast::Node::make<ast::FunctionCall>(ids::List, {
										ast::Node::make<ast::FunctionCall>(ids::List, {
											ast::Node::make<math::Real>(minX), ast::Node::make<math::Real>(axisY)
										}),
										ast::Node::make<ast::FunctionCall>(ids::List, {
											ast::Node::make<math::Real>(maxX), ast::Node::make<math::Real>(axisY) // first coord X, second coord Y
										})
									})
								});
			const auto yAxis =	ast::Node::make<ast::FunctionCall>(ids::Line, {
									ast::Node::make<ast::FunctionCall>(ids::List, {
										ast::Node::make<ast::FunctionCall>(ids::List, {
											ast::Node::make<math::Real>(axisX), ast::Node::make<math::Real>(minY)
										}),
										ast::Node::make<ast::FunctionCall>(ids::List, {
											ast::Node::make<math::Real>(axisX), ast::Node::make<math::Real>(maxY)
										})
									})
								});
			merged.push_back(xAxis);
			merged.push_back(yAxis);

			// start work on labels.

			const auto xDivisions = sessionEnvironment.recursiveEvaluate(
					ast::Node::make<ast::FunctionCall>(ids::FindDivisions, {
							ast::Node::make<ast::FunctionCall>(ids::List, {
									ast::Node::make<math::Real>(minX),
									ast::Node::make<math::Real>(maxX)
							}),
							ast::Node::make<math::Rational>(8)
					})
			).get<ast::FunctionCall>().getOperands();

			for(const auto& tick: xDivisions) {
				merged.push_back(ast::Node::make<ast::FunctionCall>(ids::Line, {
						ast::Node::make<ast::FunctionCall>(ids::List, {
							ast::Node::make<ast::FunctionCall>(ids::List, {
									ast::Node::make<math::Real>(tick.getNumeric()),
									ast::Node::make<math::Real>(0.01 * (maxY - minY)+axisY)
							}),
							ast::Node::make<ast::FunctionCall>(ids::List, {
									ast::Node::make<math::Real>(tick.getNumeric()),
									ast::Node::make<math::Real>(-0.01 * (maxY - minY)+axisY)
							})
						})
				}));
			}


			const auto yDivisions = sessionEnvironment.recursiveEvaluate(
					ast::Node::make<ast::FunctionCall>(ids::FindDivisions, {
							ast::Node::make<ast::FunctionCall>(ids::List, {
									ast::Node::make<math::Real>(minY),
									ast::Node::make<math::Real>(maxY)
							}),
							ast::Node::make<math::Rational>(8)
					})
			).get<ast::FunctionCall>().getOperands();

			for(const auto& tick: yDivisions) {
				merged.push_back(ast::Node::make<ast::FunctionCall>(ids::Line, {
						ast::Node::make<ast::FunctionCall>(ids::List, {
							ast::Node::make<ast::FunctionCall>(ids::List, {
									ast::Node::make<math::Real>(0.01 * (maxX - minX)+axisX),
									ast::Node::make<math::Real>(tick.getNumeric())
							}),
							ast::Node::make<ast::FunctionCall>(ids::List, {
									ast::Node::make<math::Real>(-0.01 * (maxX - minX)),
									ast::Node::make<math::Real>(tick.getNumeric()+axisX)
							})
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


}}} // tungsten::eval::builtin
