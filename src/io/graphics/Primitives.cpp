#include "Primitives.hpp"
#include "math/Real.hpp"
#include "eval/numericNodeEvaluation.hpp"
#include <sstream>
#include <iostream>
#include <algorithm>
#include <boost/math/constants/constants.hpp>

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
				//raise(environment);
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

namespace detail {

using Point = std::pair<math::Real, math::Real>;
using Line = std::pair<Point, Point>;

bool isPointOnLine(Point p, Line l) {
	const auto lineDy = l.second.second - l.first.second;
	const auto lineDx = l.second.first - l.first.first;

	const auto pointDy = p.second - l.first.second;
	const auto pointDx = p.first - l.first.first;

	if(lineDx == 0 || pointDx == 0) return false;

	return (lineDy/lineDx) == (pointDy/pointDx);
}

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
	if(points.size() > 1){
		std::stringstream ss;
		ss<<"<path "<<
		_format.toSVGString()<<
		"d=\"M"<<points.front().first<<" "<<-points.front().second;

		for(auto it = points.begin() + 1; it != points.end() -1; ++it) {
			if( not detail::isPointOnLine(*it, {it[-1], it[1]})) {
				ss << " L" << it->first.convert_to<double>()
					<< " " << -it->second.convert_to<double>();
			}
		}
		ss << " L" << points.back().first
			<< " " << -points.back().second;
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
		const auto y = p.second.convert_to<double>();

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
		"d=\"M"<<points.front().first<<" "<<-points.front().second<<" C";
		std::for_each(points.begin()+1, points.end(), [&ss](const std::pair<math::Real, math::Real>& p){
					ss<<" "<<p.first.convert_to<double>()<<" "<<-p.second.convert_to<double>();
				});
		ss<<"\"/>"; // end of path string.
		return ss.str();
	} else {
		return "";
	}

}

std::string Arrow::toBoundedSVGString( const BoundingBox& box) const {
	Arrow arrowHead;
	if(points.size()>=2){
		// figure out points for triangle path here.
		const auto last = points.back();
		auto it = std::find_if_not(points.rbegin(), points.rend(), [&last](const std::pair<math::Real, math::Real>& p){
					return p.first == last.first && p.second == last.second;
				});
		// rationale: atan2 has issues when diffX and diffY are both 0 (ie.: prev == last),
		// so we find the last point that isn't last.
		if(it != points.rend()){
		//	std::cout<<"Arrow made sense"<<std::endl;
			// arrow still makes sense.
			const auto previous = *it;
			const auto diffX = last.first.convert_to<double>() - previous.first.convert_to<double>();
			const auto diffY = last.second.convert_to<double>() - previous.second.convert_to<double>();
			assert(diffX != 0 || diffY != 0);
			const auto radians = std::atan2(diffY, diffX);

			const auto diameter = std::sqrt((box.maxX - box.minX)*(box.maxX - box.minX) + (box.maxY - box.minY)*(box.maxY - box.minY));

			const auto distance = diameter * 0.01; // const for triangle size.
//			const auto pi = boost::math::constants::pi<double>();

			const auto x = math::Real(last.first - std::cos(radians)*distance ).convert_to<double>();
			const auto y = math::Real(last.second - std::sin(radians)*distance ).convert_to<double>();
			std::pair<double, double> p1;
				p1.first = x - std::sin(radians) * distance;
				p1.second = y + std::cos(radians) * distance;

			std::pair<double, double> p2;
				p2.first = last.first.convert_to<double>();
				p2.second = last.second.convert_to<double>();

			std::pair<double, double> p3;
				p3.first = x + std::sin(radians) * distance;
				p3.second = y - std::cos(radians) * distance;

			arrowHead.points = { p2, p1, p3, p2 };
			arrowHead._format = this->_format;

		} else {
			std::cout<<"Arrow had to raise."<<std::endl;
		}
	}

	return this->Line::toSVGString()+arrowHead.Line::toSVGString(); // No more slicing.
}

std::string Polygon::toSVGString() const {
	if(!points.empty()){
		std::stringstream ss;
		ss<<"<path "<<
		_format.toSVGString()<<
		"d=\"M"<<points.front().first<<" "<<-points.front().second;
		std::for_each(points.begin()+1, points.end(), [&ss](const std::pair<math::Real, math::Real>& p){
					ss<<" L"<<p.first.convert_to<double>()<<" "<<-p.second.convert_to<double>();
				});
		ss<<"\" Z/>"; // end of path string.
		return ss.str();
	} else {
		return "";
	}
}

std::string Text::toBoundedSVGString(const BoundingBox& box) const {
	std::stringstream ss;
	const auto permissibleHeight = box.maxY - box.minY;
	const auto permissibleWidth = box.maxX - box.minX;
	const auto charSizeRatio = 7./13.;
	const auto heightBasedOnWidth = permissibleWidth / _text.size() * charSizeRatio;
	const auto size = std::min(permissibleHeight, heightBasedOnWidth);
	if(!_text.empty()){
		ss<<"<text x=\""<<_x<<"\" y=\""<<-(_y)<<"\" "<</*_format.toSVGString()<<*/" font-family=\"Verdana\" font-size=\""<<size<<"\" dominant-baseline=\"middle\" alignment-baseline=\"central\" text-anchor=\"middle\">"<<
				_text<<"</text>";
	}
	return ss.str();
}

Text& Text::fromOperands(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment) {
	if(operands.size()==2 && eval::getHead(operands.back()) == ast::Node::make<ast::Identifier>(eval::ids::List)){
		const auto& listRef = operands.back().get<ast::FunctionCall>().getOperands();
		if(listRef.size()==2){
			const auto xNode = listRef[0];
			const auto yNode = listRef[1];
			const auto xReal = numericNodeEvaluation(xNode, sessionEnvironment);
			const auto yReal = numericNodeEvaluation(yNode, sessionEnvironment);
			if(xReal.is<math::Real>() && yReal.is<math::Real>()){
				// all okay, lets get to work.
				_text = operands[0].toString();
				_x = xReal.get<math::Real>().convert_to<double>();
				_y = yReal.get<math::Real>().convert_to<double>();
			} else {
				raise(sessionEnvironment);
			}
		} else {
			raise(sessionEnvironment);
		}
	} else if(operands.size()==1) {
		_text = operands[0].toString();
		_x = 0.0;
		_y = 0.0;
	} else {
		raise(sessionEnvironment);
	}
	return *this;
}

BoundingBox Text::getBoundingBox() const {
	const auto halfHeight = 0.5;
	const auto halfWidth = _text.size() * 2 * halfHeight /2;
	return {_x - halfWidth, _y - halfHeight, _x + halfWidth, _y + halfHeight };
}


}}} // tungsten::io::graphics;
