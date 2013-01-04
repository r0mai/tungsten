
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

	/**
	 * node.isNumeric() must be true (<=> node.isReal() || node.isRational())
	 */
	RealRationalNumber(const ast::Node& node);

	ast::Node toNode() const;

	template<class T>
	bool is() const;

	typedef std::function<math::Rational(const math::Rational&, const math::Rational&)> RationalOperation;
	typedef std::function<math::Real(const math::Real&, const math::Real&)> RealOperation;

	static RealRationalNumber doOperation(
			const RealRationalNumber& x,
			const RealRationalNumber& y,
			RationalOperation rationalOperation,
			RealOperation realOperation);
private:
	typedef boost::variant<math::Real, math::Rational> Number;
	Number number;
};

template<class T>
bool RealRationalNumber::is() const {
	static_assert( std::is_same<T, math::Real>::value || std::is_same<T, math::Rational>::value,
			"Only Reals or Rational allowed as T");

	return boost::get<T>(&number) != nullptr;
}

}} //namespace tungsten::eval

#endif /* EVAL_REALRATIONALNUMBER_HPP_ */
