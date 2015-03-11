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
	math::Real _xMultiplier, _yMultiplier;
public:

	GraphicsPrimitive() = default;
	virtual std::string toSVGString() const = 0;
	virtual std::string toBoundedSVGString(const BoundingBox& /*b*/ ) const { return toSVGString(); }
	virtual BoundingBox getBoundingBox() const = 0;

	virtual GraphicsPrimitive& formatString(const std::string& format);
	virtual GraphicsPrimitive& translate(const std::string& trans);
	virtual GraphicsPrimitive& fromOperands(const ast::Operands& operands, eval::SessionEnvironment& environment) = 0;
	virtual void raise(eval::SessionEnvironment& environment) const;
	virtual void modify(const GraphicsDirective&);
	virtual GraphicsPrimitive& translate(const Translation&);
	FormatSpecifier& getFormat() { return _format; }
	const FormatSpecifier& getFormat() const { return _format; }
	virtual ~GraphicsPrimitive() { }
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
	math::Real radius() const { return _r; }

	Circle& center(const math::Real& arg1, const math::Real& arg2);
	std::pair<math::Real, math::Real> center() const { return std::make_pair(_x, _y); }

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

class Line : public virtual GraphicsPrimitive {
	// this is a 2d line, Line3D is the 3 dimensional one.
protected:
	std::vector<std::pair<math::Real, math::Real> > points;
public:
	Line() : GraphicsPrimitive(), points() {
		_format.stroke.fill(true);
		_format.fill.fill(false);
	}
	virtual std::string toSVGString() const override;
	virtual std::string toBoundedSVGString(const BoundingBox&) const override {return toSVGString(); }
	virtual Line& fromOperands(const ast::Operands& operands, eval::SessionEnvironment& environment);
	virtual BoundingBox getBoundingBox() const override;
};

class BezierCurve : public Line {
public:
	BezierCurve() : Line() { }
	virtual std::string toSVGString() const override;
	virtual BezierCurve& fromOperands(const ast::Operands& operands, eval::SessionEnvironment& environment) {
		this->Line::fromOperands(operands, environment);
		return *this;
	}
	virtual BoundingBox getBoundingBox() const override {
		return Line::getBoundingBox();
	}
};

class Arrow : public Line {
public:
	Arrow() : Line() { _format.fill.fill(true); }
	virtual std::string toSVGString() const override { return toBoundedSVGString(this->Line::getBoundingBox()); }
	virtual std::string toBoundedSVGString(const BoundingBox& ) const override;
	virtual Arrow& fromOperands(const ast::Operands& operands, eval::SessionEnvironment& environment) {
		this->Line::fromOperands(operands, environment);
		return *this;
	}
	virtual BoundingBox getBoundingBox() const override {
		return Line::getBoundingBox();
	}
};

class Polygon : public Line {
public:
	Polygon() : Line() { _format.fill.fill(true); }
	virtual std::string toSVGString() const override;
	virtual Polygon& fromOperands(const ast::Operands& operands, eval::SessionEnvironment& environment) {
		this->Line::fromOperands(operands, environment);
		return *this;
	}
	virtual BoundingBox getBoundingBox() const override {
		return Line::getBoundingBox();
	}
};

class Text : public GraphicsPrimitive {
	std::string _text;
	double _x, _y;
public:
	Text() : _text(), _x(), _y() { }
	virtual std::string toBoundedSVGString(const BoundingBox& box) const override;
	virtual std::string toSVGString() const override { return this->toBoundedSVGString(this->getBoundingBox()); }
	virtual Text& fromOperands(const ast::Operands& operands, eval::SessionEnvironment& environment);
	virtual BoundingBox getBoundingBox() const override;

};

}}} // tungsten::io::graphics

#endif
