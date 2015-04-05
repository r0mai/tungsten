#include "Format.hpp"
#include <boost/format.hpp>
#include <boost/math/constants/constants.hpp>
#include <cmath>

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

ColorDirective ColorDirective::fromHSV(math::Real h, math::Real s, math::Real v) {
	const auto chroma = v*s;
	const auto pi = math::Real{180};
	const auto piBy3 = 60;
	const auto h_ = math::Real{h / piBy3}.convert_to<float>();
	const auto x = math::Real{chroma*(1-std::abs(std::fmod(h_, 2.f)-1))};

	const auto between = [h_](int lhs, int rhs) { return lhs<=h_ && h_<rhs;};

	math::Real r1, g1, b1;

	if ( between(0, 1) ) {
		r1 = chroma; g1 = x; b1 = 0;
	} else if ( between(1, 2) ) {
		r1=x; g1=chroma; b1=0;
	} else if ( between(2, 3) ) {
		r1=0; g1=chroma; b1=x;
	} else if ( between(3, 4) ) {
		r1=0; g1=x; b1=chroma;
	} else if ( between(4, 5) ) {
		r1=x; g1=0; b1=chroma;
	} else if ( between(5, 6) ) {
		r1=chroma; g1=0; b1=x;
	} else {
		return ColorDirective(0,0,0);
	}

	const auto m = math::Real{v - chroma}.convert_to<float>();
	return ColorDirective{
		ColorDirective::PixelType(math::Real{r1 + m}.convert_to<float>()*255),
		ColorDirective::PixelType(math::Real{g1 + m}.convert_to<float>()*255),
		ColorDirective::PixelType(math::Real{b1 + m}.convert_to<float>()*255)
	};

}

}}} // namespace tungsten::io::graphics;
