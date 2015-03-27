
#include "RealRationalNumber.hpp"
#include "ast/NodeTypes.hpp"
#include <cassert>

namespace tungsten { namespace eval {

RealRationalNumber::RealRationalNumber() : number(math::Rational(0)) {}
RealRationalNumber::RealRationalNumber(const math::Real& real) : number(real) {}
RealRationalNumber::RealRationalNumber(const math::Rational& rational) : number(rational) {}
RealRationalNumber::RealRationalNumber(const math::ComplexReal& real) : number(real) {}
RealRationalNumber::RealRationalNumber(const math::ComplexRational& rational) : number(rational) {}

RealRationalNumber::RealRationalNumber(const ast::Node& node) {
	assert(node.isNumeric());
	//TODO we could put this out into a visitor
	if ( node.is<math::Rational>() ) {
		number = node.get<math::Rational>();
	} else {
		number = node.get<math::Real>();
	}
}

namespace detail {
template<typename T, typename U>
struct areOperandsComplex {
	static constexpr bool value =
			std::is_same<T, math::ComplexReal>::value ||
			std::is_same<T, math::ComplexRational>::value ||
			std::is_same<U, math::ComplexReal>::value ||
			std::is_same<U, math::ComplexRational>::value;
};

template<typename T, typename U>
struct areOperandsIrrational {
	static constexpr bool value =
			std::is_same<T, math::Real>::value ||
			std::is_same<T, math::ComplexReal>::value ||
			std::is_same<U, math::Real>::value ||
			std::is_same<U, math::ComplexReal>::value;
};

template<typename T>
struct RemoveComplex;

template<typename T>
struct RemoveComplex<std::complex<T>> { using type = T; };

template<typename T>
typename std::enable_if<!areOperandsComplex<T, T>::value, T>::type
getRealPart(const T& t) {
	return t;
}

template<typename T>
typename std::enable_if<areOperandsComplex<T, T>::value, typename RemoveComplex<T>::type>::type
getRealPart(const T& t) {
	return std::real(t);
}

template<typename T>
typename std::enable_if<!areOperandsComplex<T, T>::value, T>::type
getImaginaryPart(const T& t) {
	return T{};
}

template<typename T>
typename std::enable_if<areOperandsComplex<T, T>::value, typename RemoveComplex<T>::type>::type
getImaginaryPart(const T& t) {
	return std::imag(t);
}


} // namespace detail

template<typename Op>
struct DoOperationVisitor : boost::static_visitor<RealRationalNumber> {
	template<class T, class U>
	typename std::enable_if<
			detail::areOperandsComplex<T, U>::value &&
			detail::areOperandsIrrational<T, U>::value
	, RealRationalNumber>::type
	operator()(const T& x, const U& y) const {
		return math::ComplexReal{Op{}(detail::getRealPart(x), detail::getRealPart(y)),
				Op{}(detail::getImaginaryPart(x), detail::getImaginaryPart(y))};
	}

	template<class T, class U>
	typename std::enable_if<
			detail::areOperandsComplex<T, U>::value &&
			!detail::areOperandsIrrational<T, U>::value
	, RealRationalNumber>::type
	operator()(const T& x, const U& y) const {
		return math::ComplexReal{Op{}(detail::getRealPart(x), detail::getRealPart(y)),
				Op{}(detail::getImaginaryPart(x), detail::getImaginaryPart(y))};
	}

	template<class T, class U>
	typename std::enable_if<
			!detail::areOperandsComplex<T, U>::value &&
			detail::areOperandsIrrational<T, U>::value
	, RealRationalNumber>::type
	operator()(const T& x, const U& y) const {
		return math::Real{Op{}(x, y)};
	}

	template<class T, class U>
	typename std::enable_if<
			!detail::areOperandsComplex<T, U>::value &&
			!detail::areOperandsIrrational<T, U>::value
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
		return ast::Node::make<math::ComplexRational>(rational);
	}
	ast::Node operator()(const math::ComplexReal& real) const {
		return ast::Node::make<math::ComplexReal>(real);
	}
};

ast::Node RealRationalNumber::toNode() const {
	return boost::apply_visitor(ToNodeVisitor{}, number);
}

}} //namespace tungsten::eval

