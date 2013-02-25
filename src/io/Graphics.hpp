#ifndef GRAPHICS_HPP_
#define GRAPHICS_HPP_

#include <string>
#include <vector>
#include "math/Real.hpp"
#include "ast/Node.hpp"
#include "eval/SessionEnvironment.hpp"
#include "eval/getHead.hpp"

namespace tungsten { namespace io {

class GraphicsDirective;

class GraphicsPrimitive {
protected:
	std::string _formatString;
	std::string _translation;
public:
	
	virtual std::string toSVGString() const = 0;
	
	virtual GraphicsPrimitive& formatString(const std::string& format);
	virtual GraphicsPrimitive& translate(const std::string& trans);
	virtual GraphicsPrimitive& fromOperands(const ast::Operands& operands, eval::SessionEnvironment& environment) = 0;
	virtual void raise(eval::SessionEnvironment& environment) const;
	virtual void modify(const GraphicsDirective&);
};

class GraphicsDirective {
public:
	virtual ~GraphicsDirective() { }	
};

class ColorDirective : public GraphicsDirective {
public:
	typedef unsigned short PixelType;
private:
	PixelType _r, _g, _b;
public:
	ColorDirective() = default;
	ColorDirective(const ColorDirective& ) = default;
	ColorDirective(ColorDirective&& c) : _r(std::move(c._r)), _g(std::move(_g)), _b(std::move(_b)) { }
	ColorDirective& operator=(ColorDirective&& c) {
		if(&c != this){
			_r = std::move(c._r);
			_g = std::move(c._g);
			_b = std::move(c._b);
		}
		return *this;
	}
	ColorDirective(const PixelType& r, const PixelType& g, const PixelType& b) : _r(r), _g(g), _b(b) { }
	PixelType r() const;
	PixelType g() const;
	PixelType b() const;
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
};

class Circle : public GraphicsPrimitive {
	math::Real _x, _y, _r;
public:
		
	virtual std::string toSVGString() const override ;
		
	Circle& radius(const math::Real& arg);
	
	Circle& center(const math::Real& arg1, const math::Real& arg2);
	
	virtual Circle& fromOperands(const ast::Operands& operands, eval::SessionEnvironment& environment);
};

class Rectangle : public GraphicsPrimitive {
	math::Real _topLeftX, _topLeftY, _bottomRightX, _bottomRightY;
public:
	
	virtual std::string toSVGString() const override ;
	
	Rectangle& topLeft(const math::Real& arg1, const math::Real& arg2);
	
	Rectangle& bottomRight(const math::Real& arg1, const math::Real& arg2);
	
	virtual Rectangle& fromOperands(const ast::Operands& operands, eval::SessionEnvironment& environment);
};

class Ellipse : public GraphicsPrimitive {
	math::Real _x, _y, _xRadius, _yRadius;
public:

	virtual std::string toSVGString() const override;
	
	Ellipse& center(const math::Real& x, const math::Real& y);
	
	Ellipse& radius(const math::Real& x, const math::Real& y);
	
	virtual Ellipse& fromOperands(const ast::Operands& operands, eval::SessionEnvironment& environment);
};

void makeGraphics(const ast::Node& node, eval::SessionEnvironment& e, GraphicsObject& graphics);
void addGraphics(const ast::Node& node, eval::SessionEnvironment& e, GraphicsObject& graphics);

} } // tungsten::io

#endif // GRAPHICS_HPP_
