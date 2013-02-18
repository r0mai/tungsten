#include <string>
#include <iostream>
#include <boost/format.hpp>
#include "Graphics.hpp"

namespace tungsten { namespace io {


GraphicsPrimitive& GraphicsPrimitive::formatString(const std::string& format) {
	_formatString = format;
	return *this;
}

GraphicsPrimitive& GraphicsPrimitive::translate(const std::string& trans) {
	_translation = trans;
	return *this;
}


std::string GraphicsObject::toSVGString() const {
	std::stringstream _output;
	_output<<
	"<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" height=\"500\">"<<std::endl; // svg header in.
	for(const auto& shape : shapes){
		_output<<shape->toSVGString()<<std::endl;
	}		
	_output<<"</svg>";
	return _output.str();
}

	
std::string Circle::toSVGString() const {	
	return (boost::format(R"ro(<circle %1% cx="%2%" cy="%3%" r="%4%" %5% >)ro") %_translation %_x %_y %_r %_formatString).str();
}
		
Circle& Circle::radius(const math::Real& arg) {
	_r = arg;
	return *this;
}

Circle& Circle::center(const math::Real& arg1, const math::Real& arg2) {
	_x=arg1;
	_y=arg2;
	return *this;
}

std::string Rectangle::toSVGString() const {
	return (boost::format(R"ro(<rect %1% x="%2%" y="%3%" width="%4%" height="%5%" %6%>)ro") 
			% _translation
			% _topLeftX
			% _topLeftY
			% (_bottomRightY-_topLeftY)
			% (_bottomRightX-_topLeftX)
			% _formatString
			).str();
	
}
	
Rectangle& Rectangle::topLeft(const math::Real& arg1, const math::Real& arg2) {
	_topLeftX = arg1;
	_topLeftY = arg2;
	return *this;
}
	
Rectangle& Rectangle::bottomRight(const math::Real& arg1, const math::Real& arg2) {
	_bottomRightX = arg1;
	_bottomRightY = arg2;
	return *this;
}

std::string Ellipse::toSVGString() const {
	return (boost::format(R"ro(<ellipse %1% cx="%2%" cy="%3%" rx="%4%" ry="%5%" %6%>)ro")
		% _translation
		% _x
		% _y
		% _xRadius
		% _yRadius
		% _formatString
	).str();
}
	
Ellipse& Ellipse::center(const math::Real& x, const math::Real& y) {
	_x = x;
	_y = y;
	return *this;
}
	
Ellipse& Ellipse::radius(const math::Real& x, const math::Real& y) {
	_xRadius = x;
	_yRadius = y;
	return *this;
}

void makeGraphics(const ast::Node& node, eval::SessionEnvironment& e, GraphicsObject& graphics) {
	if(eval::getHead(node) == ast::Node::make<ast::Identifier>(eval::ids::Graphics)) {
	// Graphics[] should have exactly 1 parameter.
		if(node.get<ast::FunctionCall>().getOperands().size()!=1){
			e.raiseMessage(eval::Message(eval::ids::General, eval::ids::argx, {}));
		}
		else if (eval::getHead(node.get<ast::FunctionCall>().getOperands()[0]) != ast::Node::make<ast::Identifier>(eval::ids::List) ) {
			// 1 param, but its not a list.
			// call respective graphic object maker here.
			addGraphics(node.get<ast::FunctionCall>().getOperands()[0], e, graphics);
		}
		else {
			// 1 param, and its a list.
			// do iterative work here.
			const ast::Node listNode = node.get<ast::FunctionCall>().getOperands()[0];
			for(const auto& primitive : listNode.get<ast::FunctionCall>().getOperands()){
				// iterate over primitves here.
				addGraphics(primitive, e, graphics);

			} // end for loop
		}
	}	
}

void addGraphics(const ast::Node& primitive, eval::SessionEnvironment& e, GraphicsObject& graphics) {
	using eval::getHead;
	// TODO: add support for parametrisation.
	if(getHead(primitive) == ast::Node::make<ast::Identifier>(eval::ids::Circle)) {
		graphics.addShape(Circle().radius(10).center(15,20));
	}
	else if(getHead(primitive) == ast::Node::make<ast::Identifier>(eval::ids::Rectangle)) {
		graphics.addShape(Rectangle().topLeft(10,20).bottomRight(40,35));
	}
	else if(getHead(primitive) == ast::Node::make<ast::Identifier>(eval::ids::Ellipse)) {
		graphics.addShape(Ellipse().center(35,40).radius(60,12));
	}
	else {
		e.raiseMessage(eval::Message(eval::ids::General, eval::ids::argx, {} ));
		std::cout<<"Invalid graphics primitive occured!"<<std::endl;
	}
}



} } // tungsten::io
