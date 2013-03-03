#ifndef IO_GRAPHICS_PRIMITIVES_
#define IO_GRAPHICS_PRIMITIVES_
#include "Format.hpp"
#include "ast/Node.hpp"
#include "eval/getHead.hpp"
#include "eval/SessionEnvironment.hpp"
#include "math/Real.hpp"


namespace tungsten { namespace io { namespace graphics {

struct BoundingBox{
	double minX, minY;
	double maxX, maxY;
};

class Translation;

class GraphicsPrimitive {
protected:
	std::string _formatString;
	std::string _translation;
	FormatSpecifier _format;
public:

	GraphicsPrimitive() = default;
	virtual std::string toSVGString() const = 0;
	virtual BoundingBox getBoundingBox() const = 0;

	virtual GraphicsPrimitive& formatString(const std::string& format);
	virtual GraphicsPrimitive& translate(const std::string& trans);
	virtual GraphicsPrimitive& fromOperands(const ast::Operands& operands, eval::SessionEnvironment& environment) = 0;
	virtual void raise(eval::SessionEnvironment& environment) const;
	virtual void modify(const GraphicsDirective&);
	virtual GraphicsPrimitive& translate(const Translation&);
	FormatSpecifier& getFormat() { return _format; }
	const FormatSpecifier& getFormat() const { return _format; }
};


class Circle : public GraphicsPrimitive {
	math::Real _x, _y, _r;
public:

	Circle() : GraphicsPrimitive() , _x(), _y(), _r(){
		// set overriding formatting options here.
		_format.fill.fill(false);
		_format.stroke.fill(true);	
	}
		
	virtual std::string toSVGString() const override ;
		
	Circle& radius(const math::Real& arg);
	
	Circle& center(const math::Real& arg1, const math::Real& arg2);
	
	virtual Circle& fromOperands(const ast::Operands& operands, eval::SessionEnvironment& environment);

	virtual BoundingBox getBoundingBox() const override;
};

class Rectangle : public GraphicsPrimitive {
	math::Real _topLeftX, _topLeftY, _bottomRightX, _bottomRightY;
public:

	Rectangle() : GraphicsPrimitive() , _topLeftX(), _topLeftY(), _bottomRightX(), _bottomRightY() {
		_format.fill.fill(true);
		_format.stroke.fill(false);
	}	
	virtual std::string toSVGString() const override ;
	
	Rectangle& topLeft(const math::Real& arg1, const math::Real& arg2);
	
	Rectangle& bottomRight(const math::Real& arg1, const math::Real& arg2);
	
	virtual Rectangle& fromOperands(const ast::Operands& operands, eval::SessionEnvironment& environment);
	virtual BoundingBox getBoundingBox() const override;
};

class Ellipse : public GraphicsPrimitive {
	math::Real _x, _y, _xRadius, _yRadius;
public:

	virtual std::string toSVGString() const override;
	
	Ellipse& center(const math::Real& x, const math::Real& y);
	
	Ellipse& radius(const math::Real& x, const math::Real& y);
	
	virtual Ellipse& fromOperands(const ast::Operands& operands, eval::SessionEnvironment& environment);
	virtual BoundingBox getBoundingBox() const override;

};

class Line : public GraphicsPrimitive {
	// this is a 2d line, Line3D is the 3 dimensional one.
	std::vector<std::pair<math::Real, math::Real> > points;
public:
	Line() : GraphicsPrimitive(), points() {
		_format.stroke.fill(true);
		_format.fill.fill(false);
	}

	virtual std::string toSVGString() const override;
	virtual Line& fromOperands(const ast::Operands& operands, eval::SessionEnvironment& environment);
	virtual BoundingBox getBoundingBox() const override;
};



}}} // tungsten::io::graphics

#endif