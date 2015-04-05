#ifndef IO_GRAPHICS_FORMAT_HPP_
#define IO_GRAPHICS_FORMAT_HPP_

#include <string>
#include "../../math/Real.hpp"

namespace tungsten { namespace io { namespace graphics {


class GraphicsDirective {
public:
	virtual ~GraphicsDirective() { }
};

class GrayLevelDirective: public GraphicsDirective {
private:

	math::Real level;
public:
	GrayLevelDirective() = default;
	GrayLevelDirective(math::Real r) : level(std::move(r)) { }
	const math::Real& getLevel() const { return level; }
};

class ColorDirective : public GraphicsDirective {
public:
	typedef unsigned short PixelType;
private:
	PixelType _r, _g, _b;
	bool _fill;
public:
	ColorDirective() = default;
	ColorDirective(const ColorDirective& ) = default;
	ColorDirective& operator=(const ColorDirective& ) = default;
	ColorDirective(const PixelType& r, const PixelType& g, const PixelType& b) : _r(r), _g(g), _b(b) { }
	PixelType r() const;
	PixelType g() const;
	PixelType b() const;
	ColorDirective& fill(const bool b);
	bool isFill() const;
	std::string toSVGString() const ;
	ColorDirective& setRGB(const PixelType& r, const PixelType& g, const PixelType& b){ _r = r; _g = g; _b = b; return *this; }

	ColorDirective& operator*=(const GrayLevelDirective& gld) {
		auto level = gld.getLevel().convert_to<double>();
		_r *= level;
		_g *= level;
		_b *= level;
		return *this;
	}

	static ColorDirective fromHSV(math::Real h, math::Real s, math::Real v);

}; // end ColorDirective



/* format Specifier */

struct FormatSpecifier : public GraphicsDirective {
	virtual std::string toSVGString() const;
	FormatSpecifier() : stroke_width(1.0), stroke_opacity(1.0), fill_opacity(1.0), stroke(0.0, 0.0, 0.0), fill(0.0, 0.0, 0.0) { }
	FormatSpecifier(const FormatSpecifier&) = default;
	virtual ~FormatSpecifier() = default;

/* SVG Vars start here */
	double stroke_width;
	double stroke_opacity;
	double fill_opacity;
	ColorDirective stroke;
	ColorDirective fill;

};

}}} // namspace tungsten::io::graphics;
#endif
