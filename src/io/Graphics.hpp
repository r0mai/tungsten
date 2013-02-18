#ifndef GRAPHICS_HPP_
#define GRAPHICS_HPP_

#include <string>
#include <vector>
#include "math/Real.hpp"
#include "ast/Node.hpp"
#include "eval/SessionEnvironment.hpp"
#include "eval/getHead.hpp"

namespace tungsten { namespace io {

class GraphicsPrimitive {
protected:
	std::string _formatString;
	std::string _translation;
public:
	
	virtual std::string toSVGString() const = 0;
	
	virtual GraphicsPrimitive& formatString(const std::string& format);
	virtual GraphicsPrimitive& translate(const std::string& trans);
};

class GraphicsObject {
	std::vector<std::unique_ptr<GraphicsPrimitive> > shapes; // polymorphism might not be enough
public:
	std::string toSVGString() const;
	
	GraphicsObject(const GraphicsObject& g) = delete;
	GraphicsObject(GraphicsObject&& g) : shapes(std::move(g.shapes)) { }
	GraphicsObject() = default;
	GraphicsObject& operator=(GraphicsObject&& g) {
		if ( &g != this)
			shapes = std::move(g.shapes);
		return *this;
	}
	
	template<class T, class... Ts>
	void addShape(const T& shape, const Ts& ...shapes){
		addShape(shape);
		addShape(shapes...);
	}
	
	template <class T>
	void addShape(const T& shape) {
		static_assert(std::is_base_of<GraphicsPrimitive, T>::value, "You can only add a GraphicsPrimitive");
		shapes.emplace_back(new T(shape));
	}
};

class Circle : public GraphicsPrimitive {
	math::Real _x, _y, _r;
public:
		
	virtual std::string toSVGString() const override ;
		
	Circle& radius(const math::Real& arg);
	
	Circle& center(const math::Real& arg1, const math::Real& arg2);
};

class Rectangle : public GraphicsPrimitive {
	math::Real _topLeftX, _topLeftY, _bottomRightX, _bottomRightY;
public:
	
	virtual std::string toSVGString() const override ;
	
	Rectangle& topLeft(const math::Real& arg1, const math::Real& arg2);
	
	Rectangle& bottomRight(const math::Real& arg1, const math::Real& arg2);
};

class Ellipse : public GraphicsPrimitive {
	math::Real _x, _y, _xRadius, _yRadius;
public:

	virtual std::string toSVGString() const override;
	
	Ellipse& center(const math::Real& x, const math::Real& y);
	
	Ellipse& radius(const math::Real& x, const math::Real& y);
};

void makeGraphics(const ast::Node& node, eval::SessionEnvironment& e, GraphicsObject& graphics);
void addGraphics(const ast::Node& node, eval::SessionEnvironment& e, GraphicsObject& graphics);

} } // tungsten::io

#endif // GRAPHICS_HPP_
