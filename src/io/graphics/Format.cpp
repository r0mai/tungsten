#include "Format.hpp"
#include <boost/format.hpp>


namespace tungsten { namespace io { namespace graphics {

std::string FormatSpecifier::toSVGString() const {
	return (boost::format(R"phi(stroke-width="%1%" stroke-opacity="%2%" fill-opacity="%3%" fill="%4%" stroke="%5%" vector-effect="non-scaling-stroke" )phi")
		%stroke_width
		%stroke_opacity
		%fill_opacity
		%fill.toSVGString()
		%stroke.toSVGString()
	).str();
}

ColorDirective::PixelType ColorDirective::r() const {
	return _r;
}

ColorDirective::PixelType ColorDirective::g() const {
	return _g;
}

ColorDirective::PixelType ColorDirective::b() const {
	return _b;
}

ColorDirective& ColorDirective::fill(const bool b) {
	_fill = b;
	return *this;
}

bool ColorDirective::isFill() const {
	return this->_fill;
}

std::string ColorDirective::toSVGString() const {
	if(!isFill())
		return "none";
	else
	return (boost::format(R"phi(rgb(%1%, %2%, %3%))phi")
		%_r
		%_g
		%_b
	).str();
}

}}} // namespace tungsten::io::graphics;
