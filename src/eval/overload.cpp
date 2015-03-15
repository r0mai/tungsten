#include "overload.hpp"

namespace tungsten { namespace eval {

namespace detail {

struct AreTypesEqualVisitor: boost::static_visitor<bool> {
	template<typename T, typename U>
	bool operator()(const T&, const U&) { return false; }

	template<typename T>
	bool operator()(const T&, const T&) { return true; }
};

} // namespace detail

bool areAllOfSameType(const ast::Operands& operands) {
	if(operands.size() < 2) { return true; }

	auto equalityVisitor = detail::AreTypesEqualVisitor{};

	for(int i = 1; i<operands.size(); ++i) {
		if (!ast::applyVisitor(operands[i-1], operands[i], equalityVisitor)) {
			return false;
		}
	}
	return true;

}


}} // namespace tungsten::eval

