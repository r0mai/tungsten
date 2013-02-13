#include <string>
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
	"<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\">"; // svg header in.
	for(const auto& shape : shapes){
		_output<<shape->toSVGString()<<std::endl;
	}		
	_output<<"</svg>";
	return _output.str();
}

	
std::string Circle::toSVGString() const {	
	return (boost::format(R"ro(<circle %1% cx="%2%" cy="%3%" r="%4%" %5% />)ro") %_translation %_x %_y %_r %_formatString).str();
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
	return (boost::format(R"ro(<rect %1% x="%2%" y="%3%" width="%4%" height="%5" %6%/>)ro") 
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
	return (boost::format(R"ro(<ellipse %1% cx="%2%" cy="%3%" rx="%4%" ry="%5%" %6%/>)ro")
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

} } // tungsten::io
