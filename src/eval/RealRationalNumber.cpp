
#include "RealRationalNumber.hpp"

#include <cassert>

namespace tungsten { namespace eval {

RealRationalNumber::RealRationalNumber() : number(math::Rational(0)) {}
RealRationalNumber::RealRationalNumber(const math::Real& real) : number(real) {}
RealRationalNumber::RealRationalNumber(const math::Rational& rational) : number(rational) {}

RealRationalNumber::RealRationalNumber(const ast::Node& node) {
	assert(node.isNumeric());
	//TODO we could put this out into a visitor
	if ( node.is<math::Rational>() ) {
		number = node.get<math::Rational>();
	} else {
		number = node.get<math::Real>();
	}
}

struct DoOperationVisitor : boost::static_visitor<RealRationalNumber> {

	DoOperationVisitor(
			RealRationalNumber::RationalOperation rationalOperation,
			RealRationalNumber::RealOperation realOperation) :
				rationalOperation(rationalOperation), realOperation(realOperation) {}

	template<class T, class U>
	RealRationalNumber operator()(const T& x, const U& y) const {
		return realOperation(x, y);
	}

	RealRationalNumber operator()(const math::Rational& x, const math::Rational& y) const {
		return rationalOperation(x, y);
	}

	RealRationalNumber::RationalOperation rationalOperation;
	RealRationalNumber::RealOperation realOperation;
};

RealRationalNumber RealRationalNumber::doOperation(
			const RealRationalNumber& x,
			const RealRationalNumber& y,
			std::function<math::Rational(const math::Rational&, const math::Rational&)> rationalOperation,
			std::function<math::Real(const math::Real&, const math::Real&)> realOperation)
{
	return boost::apply_visitor(DoOperationVisitor{rationalOperation, realOperation}, x.number, y.number);
}

struct ToNodeVisitor : boost::static_visitor<ast::Node> {
	ast::Node operator()(const math::Rational& rational) const {
		return ast::Node::make<math::Rational>(rational);
	}
	ast::Node operator()(const math::Real& real) const {
		return ast::Node::make<math::Real>(real);
	}
};

ast::Node RealRationalNumber::toNode() const {
	return boost::apply_visitor(ToNodeVisitor{}, number);
}

}} //namespace tungsten::eval

