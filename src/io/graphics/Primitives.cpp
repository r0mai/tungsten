#include "Primitives.hpp"
#include <sstream>
#include <algorithm>

namespace tungsten { namespace io { namespace graphics {

std::string Circle::toSVGString() const {
	return (boost::format(R"ro(<circle %1% cx="%2%" cy="%3%" r="%4%" %5% />)ro") %_translation %_x %(-_y) %_r %(_format.toSVGString())).str();
}

Circle& Circle::radius(const math::Real& arg) {
	_r = arg;
	return *this;
}

Circle& Circle::center(const math::Real& arg1, const math::Real& arg2) {
	_x=arg1;
	_y=arg2;
	return *this;
}

Circle& Circle::fromOperands(const ast::Operands& operands, eval::SessionEnvironment& environment) {
	switch (operands.size()) {
		case 0:
			this->center(0,0).radius(1);
			break;
		case 1:
		{
			ast::Operands center;
			if(eval::getHead(operands[0]) == ast::Node::make<ast::Identifier>(eval::ids::List) &&
			( center = operands[0].get<ast::FunctionCall>().getOperands(), center.size() == 2)) {
				this->center(center[0].getNumeric(), center[1].getNumeric()).radius(1);
			} else {
				raise(environment);
			}
			break;
		}
		case 2:
		{
			ast::Operands center;
			math::Real radius;
			if (eval::getHead(operands[0]) == ast::Node::make<ast::Identifier>(eval::ids::List) &&
			( center = operands[0].get<ast::FunctionCall>().getOperands()/*!!!*/,/*!!!*/ operands[1].isNumeric() ) &&
			( radius = operands[1].getNumeric()/*!!!*/,/*!!!*/center.size() == 2  ) &&
			center[0].isNumeric() && center[1].isNumeric() ) 
			{
				this->center(center[0].getNumeric(), center[1].getNumeric()).radius(radius);

			} else {
				raise(environment);
			}
			break;
		}
		default:
			raise(environment);	
			break;
	}
	return *this;
}

BoundingBox Circle::getBoundingBox() const {
	double minX = math::Real(_x-_r).convert_to<double>();
	double minY = math::Real(_y-_r).convert_to<double>();
	double maxX = math::Real(_x+_r).convert_to<double>();
	double maxY = math::Real(_y+_r).convert_to<double>();
	auto stroke = _format.stroke_width;
	return {minX-stroke, minY-stroke, maxX+stroke, maxY+stroke};
}

std::string Rectangle::toSVGString() const {
	return (boost::format(R"ro(<rect %1% x="%2%" y="%3%" width="%4%" height="%5%" %6% />)ro") 
			% _translation
			% _topLeftX
			% (-_bottomRightY) // flip.
			% (_bottomRightY-_topLeftY)
			% (_bottomRightX-_topLeftX)
			% (_format.toSVGString())
			).str();

}

Rectangle& Rectangle::topLeft(const math::Real& arg1, const math::Real& arg2) {
	_topLeftX = arg1;
	_topLeftY = arg2;
	return *this;
}

Rectangle& Rectangle::bottomRight(const math::Real& arg1, const math::Real& arg2) {
	_bottomRightX = arg1;
	_bottomRightY = arg2;
	return *this;
}

Rectangle& Rectangle::fromOperands(const ast::Operands& operands, eval::SessionEnvironment& environment) {
	switch (operands.size()) {
		case 0:
			this->bottomRight(1,1).topLeft(0,0);
			break;
		case 1:
		{	
			ast::Operands topLeft;
			if(eval::getHead(operands[0]) == ast::Node::make<ast::Identifier>(eval::ids::List) &&
				((topLeft = operands[0].get<ast::FunctionCall>().getOperands())/*!!!*/,/*!!!*/ topLeft.size() == 2 )&&
				topLeft[0].isNumeric() && topLeft[1].isNumeric() )
			{
				this->topLeft(topLeft[0].getNumeric(), topLeft[1].getNumeric())
					.bottomRight(topLeft[0].getNumeric()+1, topLeft[1].getNumeric()+1);
			} else {
				raise(environment);
			}
			break;
		}
		case 2:
		{	
			ast::Operands topLeft, bottomRight;
			if(eval::getHead(operands[0]) == ast::Node::make<ast::Identifier>(eval::ids::List) &&
				eval::getHead(operands[1]) == ast::Node::make<ast::Identifier>(eval::ids::List) &&
				((topLeft = operands[0].get<ast::FunctionCall>().getOperands())/*!!!*/,/*!!!*/ topLeft.size() == 2) &&
				((bottomRight = operands[1].get<ast::FunctionCall>().getOperands())/*!!!*/,/*!!!*/ bottomRight.size() == 2) &&
				topLeft[0].isNumeric() && topLeft[1].isNumeric() &&
				bottomRight[0].isNumeric() && bottomRight[1].isNumeric() )
			{
				this->topLeft(topLeft[0].getNumeric(), topLeft[1].getNumeric())
					.bottomRight(bottomRight[0].getNumeric(), bottomRight[1].getNumeric());
			} else {
				raise(environment);
			}
			break;
		}
		default:
			raise(environment);
			break;
	}
	return *this;
}

BoundingBox Rectangle::getBoundingBox() const {
	double minX = math::Real(_topLeftX).convert_to<double>();
	double minY = math::Real(_topLeftY).convert_to<double>();
	double maxX = math::Real(_bottomRightX).convert_to<double>();
	double maxY = math::Real(_bottomRightY).convert_to<double>();
	auto stroke = _format.stroke_width;
	return {minX-stroke, minY-stroke, maxX+stroke, maxY+stroke};
}

std::string Ellipse::toSVGString() const {
	return (boost::format(R"ro(<ellipse %1% cx="%2%" cy="%3%" rx="%4%" ry="%5%" %6%/ >)ro")
		% _translation
		% _x
		% (-_y)
		% _xRadius
		% _yRadius
		% (_format.toSVGString())
	).str();
}

Ellipse& Ellipse::center(const math::Real& x, const math::Real& y) {
	_x = x;
	_y = y;
	return *this;
}

Ellipse& Ellipse::radius(const math::Real& x, const math::Real& y) {
	_xRadius = x;
	_yRadius = y;
	return *this;
}

Ellipse& Ellipse::fromOperands(const ast::Operands& operands, eval::SessionEnvironment& environment) {
	switch(operands.size()){
		case 0:
			this->center(0.0, 0.0).radius(1.0, 1.0);
			break;
		case 1:
			break;	
		default:
			raise(environment);
			break;
	}
	return *this;
}

BoundingBox Ellipse::getBoundingBox() const {
	double minX = math::Real(_x-_xRadius).convert_to<double>();
	double minY = math::Real(_y-_yRadius).convert_to<double>();
	double maxX = math::Real(_x+_xRadius).convert_to<double>();
	double maxY = math::Real(_y+_yRadius).convert_to<double>();
	auto stroke = _format.stroke_width;
	return {minX-stroke, minY-stroke, maxX+stroke, maxY+stroke};
}

std::string Line::toSVGString() const {
//
// The following commands are available for path data:
// M = moveto
// L = lineto
// H = horizontal lineto
// V = vertical lineto
// C = curveto
// S = smooth curveto
// Q = quadratic Bézier curve
// T = smooth quadratic Bézier curveto
// A = elliptical Arc
// Z = closepath
// Capital letters means absolutely positioned, lower cases means relatively positioned.
//
	if(!points.empty()){
		std::stringstream ss;
		ss<<"<path "<<
		_format.toSVGString()<<
		"d=\"M"<<points.front().first<<" "<<points.front().second;
		std::for_each(points.begin()+1, points.end(), [&ss](const std::pair<math::Real, math::Real>& p){
					ss<<" L"<<p.first.convert_to<double>()<<" "<<-p.second.convert_to<double>();
				});	
		ss<<"\"/>"; // end of path string.
		return ss.str();
	} else {
		return "";
	}
}

Line& Line::fromOperands(const ast::Operands& operands, eval::SessionEnvironment& environment) {
	// check that operands is really just a list.
	// then check that all operands of that list, are points (2-lists)
	// place all of these 2lists as points into this->points.
	// return.
	if(operands.size()==1 && eval::getHead(operands.front()) == ast::Node::make<ast::Identifier>(eval::ids::List)) {
		// we got a list as parameter.
		// get list elements.
		const auto list = operands.front().get<ast::FunctionCall>().getOperands();
		if(std::all_of(list.begin(), list.end(), [](const ast::Node& n) {
					return	eval::getHead(n) == ast::Node::make<ast::Identifier>(eval::ids::List) &&
							n.get<ast::FunctionCall>().getOperands().size() == 2 &&
							n.get<ast::FunctionCall>().getOperands()[0].isNumeric() &&
							n.get<ast::FunctionCall>().getOperands()[1].isNumeric() ;
					})
		){
			// all elements of list are 2-points, proceed to packing into vector.
			for (const auto& p : list) {
				// we know now that p is awesome.
				auto x = p.get<ast::FunctionCall>().getOperands()[0].getNumeric();
				auto y = p.get<ast::FunctionCall>().getOperands()[1].getNumeric();
				points.push_back(std::make_pair(math::Real(x), math::Real(y)));
			}
		} else {
			raise(environment);
		}
	} else {
		raise(environment);
	}
	return *this;
}

BoundingBox Line::getBoundingBox() const {
	BoundingBox out = {0.0, 0.0, 0.0, 0.0};
	if(!points.empty()){
		out = {
			points.front().first.convert_to<double>(), 
			points.front().second.convert_to<double>(), 
			points.front().first.convert_to<double>(),
			points.front().second.convert_to<double>()
		};
	}
	out = std::accumulate(points.begin(), points.end(), out, [](BoundingBox& box, const std::pair<math::Real, math::Real>& p){
		const auto x = p.first.convert_to<double>();
		const auto y = p.first.convert_to<double>();		

			box.minX = std::min(box.minX, x);
			box.minY = std::min(box.minY, y);
			box.maxX = std::max(box.maxX, x);
			box.maxY = std::max(box.maxY, y);
			return box;
			});

//	std::cout<<out.minX <<" "<< out.minY <<" "<< out.maxX <<" "<< out.maxY <<" "<< std::endl;
	return out;
}

std::string BezierCurve::toSVGString() const {
	if(!points.empty()){
		std::stringstream ss;
		ss<<"<path "<<
		_format.toSVGString()<<
		"d=\"M"<<points.front().first<<" "<<points.front().second<<" C";
		std::for_each(points.begin()+1, points.end(), [&ss](const std::pair<math::Real, math::Real>& p){
					ss<<" "<<p.first.convert_to<double>()<<" "<<-p.second.convert_to<double>();
				});	
		ss<<"\"/>"; // end of path string.
		return ss.str();
	} else {
		return "";
	}

}

std::string Arrow::toSVGString() const {
	if(!points.empty()){
		std::stringstream ss;
		ss<"<path "<<
			_format.toSVGString()<<
			"d=\"M"<<points.front().first<<" "<<points.front().second" L";
		std::for_each(points.begin()+1, points.end(), [&ss](const std::pair<math::Real, math::Real>& p){
				ss<<" L"<<p.first.convert_to<double>()<<" "<<-p.second.convert_to<double>();
				});
		ss<<"\" marker-end="url(#arrow)" />";
		return ss.str;
	} else {
		return "";
	}
}

}}} // tungsten::io::graphics;
