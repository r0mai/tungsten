
#include "RealRationalNumber.hpp"
#include "ast/NodeTypes.hpp"
#include "ast/Node.hpp"

#include <cassert>

namespace tungsten { namespace eval {

RealRationalNumber::RealRationalNumber() : number(math::Rational(0)) {}
RealRationalNumber::RealRationalNumber(const math::Real& real) : number(real) {}
RealRationalNumber::RealRationalNumber(const math::Rational& rational) : number(rational) {}
RealRationalNumber::RealRationalNumber(const math::ComplexReal& real) : number(real) {}
RealRationalNumber::RealRationalNumber(const math::ComplexRational& rational) : number(rational) {}

RealRationalNumber::RealRationalNumber(const ast::Node& node) :
		number(node.get<math::Real, math::Rational, math::ComplexReal, math::ComplexRational>()) { }

template<typename Op>
struct DoOperationVisitor : boost::static_visitor<RealRationalNumber> {
	template<class T, class U>
	typename std::enable_if<
			math::detail::areOperandsComplex<T, U>::value &&
			math::detail::areOperandsIrrational<T, U>::value
	, RealRationalNumber>::type
	operator()(const T& x, const U& y) const {
		const auto left = math::ComplexReal{math::detail::getRealPart(x), math::detail::getImaginaryPart(x)};
		const auto right = math::ComplexReal{math::detail::getRealPart(y), math::detail::getImaginaryPart(y)};
		return math::ComplexReal{Op{}(left, right)};
	}

	template<class T, class U>
	typename std::enable_if<
			math::detail::areOperandsComplex<T, U>::value &&
			!math::detail::areOperandsIrrational<T, U>::value
	, RealRationalNumber>::type
	operator()(const T& x, const U& y) const {
		const auto left = math::ComplexRational{math::detail::getRealPart(x), math::detail::getImaginaryPart(x)};
		const auto right = math::ComplexRational{math::detail::getRealPart(y), math::detail::getImaginaryPart(y)};
		return math::ComplexRational{Op{}(left, right)};
	}

	template<class T, class U>
	typename std::enable_if<
			!math::detail::areOperandsComplex<T, U>::value &&
			math::detail::areOperandsIrrational<T, U>::value
	, RealRationalNumber>::type
	operator()(const T& x, const U& y) const {
		return math::Real{Op{}(x, y)};
	}

	template<class T, class U>
	typename std::enable_if<
			!math::detail::areOperandsComplex<T, U>::value &&
			!math::detail::areOperandsIrrational<T, U>::value
	, RealRationalNumber>::type
	operator()(const T& x, const U& y) const {
		return math::Rational{Op{}(x, y)};
	}

};

struct Plus {
	template<typename T, typename U>
	auto operator()(const T& x, const U& y) {
		return x+y;
	}
};

struct Times {
	template<typename T, typename U>
	auto operator()(const T& x, const U& y) {
		return x*y;
	}
};

RealRationalNumber RealRationalNumber::doPlus(
			const RealRationalNumber& x,
			const RealRationalNumber& y)
{
	return boost::apply_visitor(DoOperationVisitor<Plus>{}, x.number, y.number);
}

RealRationalNumber RealRationalNumber::doTimes(
			const RealRationalNumber& x,
			const RealRationalNumber& y)
{
	return boost::apply_visitor(DoOperationVisitor<Times>{}, x.number, y.number);
}
struct ToNodeVisitor : boost::static_visitor<ast::Node> {
	ast::Node operator()(const math::Rational& rational) const {
		return ast::Node::make<math::Rational>(rational);
	}
	ast::Node operator()(const math::Real& real) const {
		return ast::Node::make<math::Real>(real);
	}
	ast::Node operator()(const math::ComplexRational& rational) const {
		if(rational.imag()) {
			return ast::Node::make<math::ComplexRational>(rational);
		} else {
			return ast::Node::make<math::Rational>(rational.real());
		}
	}
	ast::Node operator()(const math::ComplexReal& real) const {
		if(real.imag()) {
			return ast::Node::make<math::ComplexReal>(real);
		} else {
			return ast::Node::make<math::Real>(real.real());
		}
	}
};

ast::Node RealRationalNumber::toNode() const {
	return boost::apply_visitor(ToNodeVisitor{}, number);
}

}} //namespace tungsten::eval

