#ifndef GRAPHICS_HPP_
#define GRAPHICS_HPP_

#include <string>
#include <vector>
#include "math/Real.hpp"
#include "ast/Node.hpp"
#include "eval/SessionEnvironment.hpp"
#include "eval/getHead.hpp"
#include "Format.hpp"

namespace tungsten { namespace io {



class GraphicsDirective;
class Translation;
struct BoundingBox{
	double minX, minY;
	double maxX, maxY;
};

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
};

class Translation {
	std::string _translation;
public:
	Translation() : _translation("transform= \"") { }

	std::string toSVGString() const { return _translation+"\""; }

	Translation& translate(double x, double y=0.0) {
		_translation += 
		(boost::format("translate(%1%, %2%)")  %x %y).str();
		return *this;
	}

	Translation& scale(double sx) { 
		_translation += 
		(boost::format("scale(%1%)")%sx).str();
		return *this;
	}

	Translation& scale(double sx, double sy) {
		_translation +=
		(boost::format("scale(%1%, %2%) ") %sx %sy).str();
		return *this;
	}

	Translation& rotate(double angle, double cx=0.0, double cy=0.0 ) {
		_translation += 
		(boost::format("rotate(%1%, %2%, %3%)") %angle %cx % cy).str();
		return *this;
	}

	Translation& skewX(double angle) {
		_translation +=
		(boost::format("skewX(%1%) ")%angle ).str();
		return *this;
	}

	Translation& skewY(double angle) {
		_translation +=
		(boost::format("skewY(%1%) ")%angle).str();
		return *this;
	}	
};


class GraphicsObject {
	std::vector<std::unique_ptr<GraphicsPrimitive> > shapes; // polymorphism might not be enough
	std::vector<std::unique_ptr<GraphicsDirective> > modifiers;
public:
	std::string toSVGString() const;
	
	GraphicsObject(const GraphicsObject& g) = delete;
	GraphicsObject(GraphicsObject&& g) : shapes(std::move(g.shapes)), modifiers(std::move(g.modifiers)) { }
	GraphicsObject() = default;
	GraphicsObject& operator=(GraphicsObject&& g) {
		if ( &g != this)
			shapes = std::move(g.shapes);
			modifiers = std::move(g.modifiers);
		return *this;
	}
	
	template<class T, class... Ts>
	void addShape(const T& shape, const Ts& ...shapes){
		addShape(shape);
		addShape(shapes...);
	}
	
	template <class T>
	void addShape(T shape) {
		static_assert(std::is_base_of<GraphicsPrimitive, T>::value, "You can only add a GraphicsPrimitive");
		for(const auto& modifier : modifiers)
			shape.modify(*modifier);
		shapes.emplace_back(new T(shape));
	}

	template<class T, class... Ts>
	void addModifier(const T& modifier, const Ts& ...modifiers){
		addModifier(modifier);
		addModifier(modifiers...);
	}
	
	template<class T>
	void addModifier(const T& modifier){
		static_assert(std::is_base_of<GraphicsDirective, T>::value, "You can only add a GraphicsDirective");
		modifiers.emplace_back(new T(modifier));
	}

	BoundingBox getBoundingBox() const;
};

class Circle : public GraphicsPrimitive {
	math::Real _x, _y, _r;
public:

	Circle() : GraphicsPrimitive() {
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

void makeGraphics(const ast::Node& node, eval::SessionEnvironment& e, GraphicsObject& graphics);
void addGraphics(const ast::Node& node, eval::SessionEnvironment& e, GraphicsObject& graphics);

} } // tungsten::io

#endif // GRAPHICS_HPP_
