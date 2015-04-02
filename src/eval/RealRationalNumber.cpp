
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
struct RemoveComplex { using type = T; };

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
	return T{0};
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
		const auto left = math::ComplexReal{detail::getRealPart(x), detail::getImaginaryPart(x)};
		const auto right = math::ComplexReal{detail::getRealPart(y), detail::getImaginaryPart(y)};
		return math::ComplexReal{Op{}(left, right)};
	}

	template<class T, class U>
	typename std::enable_if<
			detail::areOperandsComplex<T, U>::value &&
			!detail::areOperandsIrrational<T, U>::value
	, RealRationalNumber>::type
	operator()(const T& x, const U& y) const {
		const auto left = math::ComplexRational{detail::getRealPart(x), detail::getImaginaryPart(x)};
		const auto right = math::ComplexRational{detail::getRealPart(y), detail::getImaginaryPart(y)};
		return math::ComplexRational{Op{}(left, right)};
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

