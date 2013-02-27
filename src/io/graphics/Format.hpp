#ifndef FORMAT_HPP_
#define FORMAT_HPP_
#include "Graphics.hpp"


namespace tungsten { namespace io {


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

/* format Specifier */

struct FormatSpecifier {
	virtual std::string toSVGString() const;
	FormatSpecifier() : stroke_width(1.0), stroke_opacity(1.0), fill_opacity(1.0), stroke(0.0, 0.0, 0.0), fill(0.0, 0.0, 0.0) { }
	FormatSpecifier(FormatSpecifier&& f) = default;	

	virtual ~FormatSpecifier() = default;

/* SVG Vars start here */
	double stroke_width;
	double stroke_opacity;
	double fill_opacity;
	ColorDirective stroke;
	ColorDirective fill;

};


}} // namspace tungsten::io;
#endif
