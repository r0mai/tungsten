#ifndef IO_GRAPHICS_GRAPHICS_HPP_
#define IO_GRAPHICS_GRAPHICS_HPP_

#include <string>
#include <vector>
#include "math/Real.hpp"
#include "ast/Node.hpp"
#include "eval/SessionEnvironment.hpp"
#include "eval/getHead.hpp"
#include "Primitives.hpp"

namespace tungsten { namespace io { namespace graphics {



class GraphicsDirective;



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

void makeGraphics(const ast::Node& node, eval::SessionEnvironment& e, GraphicsObject& graphics);
void addGraphics(const ast::Node& node, eval::SessionEnvironment& e, GraphicsObject& graphics);

}}} // tungsten::io::graphics;

#endif // GRAPHICS_HPP_
