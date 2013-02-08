#ifndef GRAPHICS_HPP_
#define GRAPHICS_HPP_

#include <string>
#include <sstream>
#include <vector>
#include <memory>
#include <iostream>


namespace tungsten { namespace io {

class GraphicsPrimitive {
protected:
	std::string _formatString;
	std::string _translation;
public:
	GraphicsPrimitive() : _formatString() { };
	
	GraphicsPrimitive(const GraphicsPrimitive& shape) = default;
	
	virtual std::string toSVGString() const {
		return "don't see this please.";
	}
	
	virtual GraphicsPrimitive& formatString(const std::string& format) {
		_formatString = format;
		return *this;
	}
	
	virtual GraphicsPrimitive& translate(const std::string& trans) {
		_translation = trans;
		return *this;
	}
	
	virtual ~GraphicsPrimitive() { };	
};

class Graphics {
	std::vector<std::unique_ptr<GraphicsPrimitive> > shapes; // polymorphism might not be enough
public:
	std::string toSVGString() const {
		std::stringstream _output;
		_output<<
		"<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\">"; // svg header in.
		for(const auto& shape : shapes){
			_output<<shape->toSVGString()<<std::endl;
		}		
		_output<<"</svg>";
		return _output.str();
	};
	
	template <class T>
	void addShape(const T& shape) {
		static_assert(std::is_base_of<GraphicsPrimitive, T>::value, "You can only add a GraphicsPrimitive");
		shapes.emplace_back(new T(shape));
	}
	
	template<typename T, typename... Ts>
	void addShape(const T& shape, const Ts&... shapes) {
		addShape(shape);
		addShape(shapes...);
	}
};

class Circle : public GraphicsPrimitive {
	math::Real _x, _y, _r;
public:
	Circle() : _x(0), _y(0), _r(0) { };
	
	virtual ~Circle() { };
	
	virtual std::string toSVGString() const override {
		std::stringstream _output;
		_output<<"<circle "<<_translation<<" cx=\""<<_x<<"\" cy=\""<<_y<<"\" r=\""<<_r<<"\" "<<_formatString<<"  />"; 
		// <Circle cx="x" cy="y" r="r" />
		return _output.str();
	}
		
	Circle& radius(const math::Real arg) {
		_r = arg;
		return *this;
	}
	
	Circle& center(const math::Real arg1, const math::Real arg2) {
		_x=arg1;
		_y=arg2;
		return *this;
	}
};

class Rectangle : public GraphicsPrimitive {
	math::Real _topLeftX, _topLeftY, _bottomRightX, _bottomRightY;
public:
	
	Rectangle() : _topLeftX(0), _topLeftY(0), _bottomRightX(0), _bottomRightY(0) { };
	
	virtual ~Rectangle() { };
	
	virtual std::string toSVGString() const override {
		std::stringstream _output;
		_output<< "<rect "<<_translation<<" x=\""<<_topLeftX<<"\" y=\""<<_topLeftY<<"\" width=\""<<
			_bottomRightY-_topLeftY<<"\" height=\""<<_bottomRightX-_topLeftX<<"\" "<<_formatString<<" />";
		return _output.str();
	}
	
	Rectangle& topLeft(const math::Real arg1, const math::Real arg2) {
		_topLeftX = arg1;
		_topLeftY = arg2;
		return *this;
	}
	
	Rectangle& bottomRight(const math::Real arg1, const math::Real arg2) {
		_bottomRightX = arg1;
		_bottomRightY = arg2;
		return *this;
	}
};

class Ellipse : public GraphicsPrimitive {
	math::Real _x, _y, _xRadius, _yRadius;
public:

	Ellipse() : _x(0), _y(0), _xRadius(0), _yRadius(0) { };
	
	virtual ~Ellipse() { };
	
	virtual std::string toSVGString() const override {
		std::stringstream _output;
		_output<<"<ellipse "<<_translation<<" cx=\""<<_x<<"\" cy=\""<<_y<<
			"\" rx=\""<<_xRadius<<"\" ry=\""<<_yRadius<<"\" "<<_formatString<<" />";
		return _output.str();
	}
	
	Ellipse& center(const math::Real& x, const math::Real& y) {
		_x = x;
		_y = y;
		return *this;
	}
	
	Ellipse& radius(const math::Real& x, const math::Real& y) {
		_xRadius = x;
		_yRadius = y;
		return *this;
	}
};

} } // tungsten::io

#endif // GRAPHICS_HPP_
