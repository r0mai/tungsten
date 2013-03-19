#include <string>
#include <iostream>
#include <boost/format.hpp>
#include "Graphics.hpp"
#include <algorithm>
#include <cmath>
namespace tungsten { namespace io { namespace graphics {


GraphicsPrimitive& GraphicsPrimitive::formatString(const std::string& format) {
	_formatString = format;
	return *this;
}

GraphicsPrimitive& GraphicsPrimitive::translate(const std::string& trans) {
	_translation = trans;
	return *this;
}

GraphicsPrimitive& GraphicsPrimitive::translate(const Translation& trans) {
	return this->translate(trans.toSVGString());
}

void GraphicsPrimitive::raise(eval::SessionEnvironment& environment) const {
	environment.raiseMessage(eval::Message(eval::ids::General, eval::ids::Graphics, {} ));
}

void GraphicsPrimitive::modify(const GraphicsDirective& directive) {

	auto colorDirective = dynamic_cast<const ColorDirective*>(&directive);
	if(colorDirective){
		this->_format.stroke=std::move(*colorDirective);
		this->_format.stroke.fill(true);
	}
}

std::string GraphicsObject::toSVGString() const {
	std::stringstream _output;

		// calulate scale for ACS
	const auto box = getBoundingBox();
	const auto diffX = box.maxX - box.minX;
	const auto diffY = box.maxY - box.minY;
	_output<<
	"<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" width=\"70%\" height=\"70%\" viewbox=\""
	<<box.minX<<" "<<-box.maxY<<" "<<diffX<<" "<<diffY<<"\" preserveAspectRatio=\"xMidYMid meet\" overflow=\"visible\" >"<<std::endl; // svg header in.

	// assume graph is 500px wide.

	for(const auto& shape : shapes){
		_output<<shape->toSVGString()<<std::endl;
	}
	_output<<"</svg>";
	return _output.str();
}

BoundingBox GraphicsObject::getBoundingBox() const {
	std::cout<<"Global getBoundingBox()"<<std::endl;
	if(!shapes.empty()){
		return std::accumulate(shapes.begin(), shapes.end(), shapes.front()->getBoundingBox(), 
		[](BoundingBox& out, const std::unique_ptr<GraphicsPrimitive>& ptr) {
			BoundingBox box = ptr->getBoundingBox();
			out.minX = std::min(out.minX, box.minX);
			out.minY = std::min(out.minY, box.minY);
			out.maxX = std::max(out.maxX, box.maxX);
			out.maxY = std::max(out.maxY, box.maxY);
			return out;
		});
	} else {

	return { 0.0, 0.0, 500.0, 500.0 };
}
}


void makeGraphics(const ast::Node& node, eval::SessionEnvironment& e, GraphicsObject& graphics) {
	if(eval::getHead(node) == ast::Node::make<ast::Identifier>(eval::ids::Graphics)) {
	// Graphics[] should have exactly 1 parameter.
		if(node.get<ast::FunctionCall>().getOperands().size()!=1){
			e.raiseMessage(eval::Message(eval::ids::General, eval::ids::argx, {}));
			std::cout<<"Invalid number of operands in Graphics"<<std::endl;
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
		graphics.addShape(Circle().fromOperands(primitive.get<ast::FunctionCall>().getOperands(), e));
	}
	else if(getHead(primitive) == ast::Node::make<ast::Identifier>(eval::ids::Disk)) {
		auto d = Circle().fromOperands(primitive.get<ast::FunctionCall>().getOperands(), e);
		d.getFormat().fill.fill(true);
		graphics.addShape(d);
	}
	else if(getHead(primitive) == ast::Node::make<ast::Identifier>(eval::ids::Rectangle)) {
		graphics.addShape(Rectangle().fromOperands(primitive.get<ast::FunctionCall>().getOperands(), e));
	}
	else if(getHead(primitive) == ast::Node::make<ast::Identifier>(eval::ids::Ellipse)) {
		graphics.addShape(Ellipse().center(0,0).radius(1,1));
	}
	else if(getHead(primitive) == ast::Node::make<ast::Identifier>(eval::ids::Line)) {
		graphics.addShape(Line().fromOperands(primitive.get<ast::FunctionCall>().getOperands(), e));
	}
	else if(getHead(primitive) == ast::Node::make<ast::Identifier>(eval::ids::BezierCurve)) {
		graphics.addShape(BezierCurve().fromOperands(primitive.get<ast::FunctionCall>().getOperands(), e));
	}

	else if(getHead(primitive) == ast::Node::make<ast::Identifier>(eval::ids::List)) {
		graphics.pushModifierVector();
		for(const auto& p : primitive.get<ast::FunctionCall>().getOperands() )
			addGraphics(p, e, graphics);
		graphics.popModifierVector();
	}
	// Color types here.
	else if(primitive == ast::Node::make<ast::Identifier>(eval::ids::Red)) {
		graphics.addModifier(ColorDirective(255,0,0));
	} else if(primitive == ast::Node::make<ast::Identifier>(eval::ids::Blue)) {
		graphics.addModifier(ColorDirective(0,0,255));
	} else if(primitive == ast::Node::make<ast::Identifier>(eval::ids::Green)) {
		graphics.addModifier(ColorDirective(0,255,0));
	} else if(primitive == ast::Node::make<ast::Identifier>(eval::ids::White)) {
		graphics.addModifier(ColorDirective(255,255,255));
	} else if(primitive == ast::Node::make<ast::Identifier>(eval::ids::Black)) {
		graphics.addModifier(ColorDirective(0,0,0));
	} else if(primitive == ast::Node::make<ast::Identifier>(eval::ids::None)) {
		// do something smart here.
	}

	else if(primitive.isFunctionCall(eval::ids::RGBColor) ) {
		if(primitive.get<ast::FunctionCall>().getOperands().size()==3){
			const auto& ops = primitive.get<ast::FunctionCall>().getOperands();
			typedef ColorDirective::PixelType PT;
			if(ops[0].isNumeric() && ops[1].isNumeric() && ops[2].isNumeric())
				graphics.addModifier(ColorDirective(math::Real(ops[0].getNumeric()*256).convert_to<PT>(), math::Real(ops[1].getNumeric()*256).convert_to<PT>(), math::Real(ops[2].getNumeric()*256).convert_to<PT>()));
		}
		
	}
	else {
		e.raiseMessage(eval::Message(eval::ids::General, eval::ids::argx, {} ));
		std::cout<<"Invalid graphics primitive occured!"<<std::endl;
	}
}

}}} // tungsten::io::graphics;
