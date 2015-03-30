
#ifndef EVAL_REALRATIONALNUMBER_HPP_
#define EVAL_REALRATIONALNUMBER_HPP_

#include "ast/Node.hpp"

#include <functional>
#include <type_traits>

#include <boost/variant.hpp>

namespace tungsten { namespace eval {

/**
 * Simplifies operations with numeric operations when Rational is needed
 * by default, but the result should be Real, if there is an operation with
 * a Real
 */

class RealRationalNumber {
public:

	/**
	 * Defaults to Rational(0)
	 */
	RealRationalNumber();
	RealRationalNumber(const math::Real& real);
	RealRationalNumber(const math::Rational& rational);
	RealRationalNumber(const math::ComplexReal& real);
	RealRationalNumber(const math::ComplexRational& rational);

	/**
	 * Node has to be some sort of number
	 */
	RealRationalNumber(const ast::Node& node);

	ast::Node toNode() const;

	template<class T>
	bool is() const;

	static RealRationalNumber doPlus(
			const RealRationalNumber& x,
			const RealRationalNumber& y);

	static RealRationalNumber doTimes(
			const RealRationalNumber& x,
			const RealRationalNumber& y);

private:
	typedef boost::variant<math::Real, math::Rational, math::ComplexReal, math::ComplexRational> Number;
	Number number;
};

template<class T>
bool RealRationalNumber::is() const {
	static_assert( std::is_same<T, math::Real>::value || std::is_same<T, math::Rational>::value ||
			std::is_same<T, math::ComplexReal>::value || std::is_same<T, math::ComplexRational>::value,
			"Only ComplexRational, ComplexReal, Real or Rational allowed as T");

	return boost::get<T>(&number) != nullptr;
}

}} //namespace tungsten::eval

#endif /* EVAL_REALRATIONALNUMBER_HPP_ */
