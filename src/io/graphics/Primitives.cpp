#include "Primitives.hpp"

namespace tungsten { namespace io { namespace graphics {

std::string Circle::toSVGString() const {
	return (boost::format(R"ro(<circle %1% cx="%2%" cy="%3%" r="%4%" %5% />)ro") %_translation %_x %_y %_r %(_format.toSVGString())).str();
}

Circle& Circle::radius(const math::Real& arg) {
	_r = arg;
	_format.stroke_width = arg.convert_to<double>() * 0.05;	

	return *this;
}

Circle& Circle::center(const math::Real& arg1, const math::Real& arg2) {
	_x=arg1;
	_y=arg2;
	return *this;
}

Circle& Circle::fromOperands(const ast::Operands& operands, eval::SessionEnvironment& environment) {
	switch (operands.size()) {
		case 0:
			this->center(0,0).radius(1);
			break;
		case 1:
		{
			ast::Operands center;
			if(eval::getHead(operands[0]) == ast::Node::make<ast::Identifier>(eval::ids::List) &&
			( center = operands[0].get<ast::FunctionCall>().getOperands(), center.size() == 2)) {
				this->center(center[0].getNumeric(), center[1].getNumeric()).radius(1);
			} else {
				raise(environment);
			}
			break;
		}
		case 2:
		{
			ast::Operands center;
			math::Real radius;
			if (eval::getHead(operands[0]) == ast::Node::make<ast::Identifier>(eval::ids::List) &&
			( center = operands[0].get<ast::FunctionCall>().getOperands()/*!!!*/,/*!!!*/ operands[1].isNumeric() ) &&
			( radius = operands[1].getNumeric()/*!!!*/,/*!!!*/center.size() == 2  ) &&
			center[0].isNumeric() && center[1].isNumeric() ) 
			{
				this->center(center[0].getNumeric(), center[1].getNumeric()).radius(radius);

			} else {
				raise(environment);
			}
			break;
		}
		default:
			raise(environment);	
			break;
	}
	return *this;
}

BoundingBox Circle::getBoundingBox() const {
	double minX = math::Real(_x-_r).convert_to<double>();
	double minY = math::Real(_y-_r).convert_to<double>();
	double maxX = math::Real(_x+_r).convert_to<double>();
	double maxY = math::Real(_y+_r).convert_to<double>();
	auto stroke = _format.stroke_width;
	return {minX-stroke, minY-stroke, maxX+stroke, maxY+stroke};
}

std::string Rectangle::toSVGString() const {
	return (boost::format(R"ro(<rect %1% x="%2%" y="%3%" width="%4%" height="%5%" %6% />)ro") 
			% _translation
			% _topLeftX
			% _topLeftY
			% (_bottomRightY-_topLeftY)
			% (_bottomRightX-_topLeftX)
			% (_format.toSVGString())
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

Rectangle& Rectangle::fromOperands(const ast::Operands& operands, eval::SessionEnvironment& environment) {
	switch (operands.size()) {
		case 0:
			this->bottomRight(1,1).topLeft(0,0);
			break;
		case 1:
		{	
			ast::Operands topLeft;
			if(eval::getHead(operands[0]) == ast::Node::make<ast::Identifier>(eval::ids::List) &&
				((topLeft = operands[0].get<ast::FunctionCall>().getOperands())/*!!!*/,/*!!!*/ topLeft.size() == 2 )&&
				topLeft[0].isNumeric() && topLeft[1].isNumeric() )
			{
				this->topLeft(topLeft[0].getNumeric(), topLeft[1].getNumeric())
					.bottomRight(topLeft[0].getNumeric()+1, topLeft[1].getNumeric()+1);
			} else {
				raise(environment);
			}
			break;
		}
		case 2:
		{	
			ast::Operands topLeft, bottomRight;
			if(eval::getHead(operands[0]) == ast::Node::make<ast::Identifier>(eval::ids::List) &&
				eval::getHead(operands[1]) == ast::Node::make<ast::Identifier>(eval::ids::List) &&
				((topLeft = operands[0].get<ast::FunctionCall>().getOperands())/*!!!*/,/*!!!*/ topLeft.size() == 2) &&
				((bottomRight = operands[1].get<ast::FunctionCall>().getOperands())/*!!!*/,/*!!!*/ bottomRight.size() == 2) &&
				topLeft[0].isNumeric() && topLeft[1].isNumeric() &&
				bottomRight[0].isNumeric() && bottomRight[1].isNumeric() )
			{
				this->topLeft(topLeft[0].getNumeric(), topLeft[1].getNumeric())
					.bottomRight(bottomRight[0].getNumeric(), bottomRight[1].getNumeric());
			} else {
				raise(environment);
			}
			break;
		}
		default:
			raise(environment);
			break;
	}
	return *this;
}

BoundingBox Rectangle::getBoundingBox() const {
	double minX = math::Real(_topLeftX).convert_to<double>();
	double minY = math::Real(_topLeftY).convert_to<double>();
	double maxX = math::Real(_bottomRightX).convert_to<double>();
	double maxY = math::Real(_bottomRightY).convert_to<double>();
	auto stroke = _format.stroke_width;
	return {minX-stroke, minY-stroke, maxX+stroke, maxY+stroke};
}

std::string Ellipse::toSVGString() const {
	return (boost::format(R"ro(<ellipse %1% cx="%2%" cy="%3%" rx="%4%" ry="%5%" %6%/ >)ro")
		% _translation
		% _x
		% _y
		% _xRadius
		% _yRadius
		% (_format.toSVGString())
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

Ellipse& Ellipse::fromOperands(const ast::Operands& operands, eval::SessionEnvironment& environment) {
	switch(operands.size()){
		case 0:
			this->center(0.0, 0.0).radius(1.0, 1.0);
			break;
		case 1:
			break;	
		default:
			raise(environment);
			break;
	}
	return *this;
}

BoundingBox Ellipse::getBoundingBox() const {
	double minX = math::Real(_x-_xRadius).convert_to<double>();
	double minY = math::Real(_y-_yRadius).convert_to<double>();
	double maxX = math::Real(_x+_xRadius).convert_to<double>();
	double maxY = math::Real(_y+_yRadius).convert_to<double>();
	auto stroke = _format.stroke_width;
	return {minX-stroke, minY-stroke, maxX+stroke, maxY+stroke};
}

}}} // tungsten::io::graphics;
