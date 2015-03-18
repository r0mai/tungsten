#include "overload.hpp"

namespace tungsten { namespace eval {

namespace detail {

struct AreTypesEqualVisitor: boost::static_visitor<bool> {
	template<typename T, typename U>
	bool operator()(const T&, const U&) { return false; }

	template<typename T>
	bool operator()(const T&, const T&) { return true; }
};

struct PushBackVisitor: boost::static_visitor<void> {
	SameTypeOperands& storage;

	PushBackVisitor(
		SameTypeOperands& storage) : storage(storage) { }

	template<typename T>
	void operator()(const T& t) {
		if ( !boost::get<std::vector<T>>(&storage) ) {
			storage = std::vector<T>();
		}
		boost::get<std::vector<T>>(storage).push_back(t);
	}

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

bool areAllListsOfSameType(const std::vector<SameTypeOperands>& operandLists) {
	if(operandLists.size() < 2) { return true; }

	auto equalityVisitor = detail::AreTypesEqualVisitor{};

	for(int i = 1; i<operandLists.size(); ++i) {
		if (!boost::apply_visitor(equalityVisitor, operandLists[i-1], operandLists[i])) {
			return false;
		}
	}
	return true;

}

SameTypeOperands castListToCommonType(const ast::Operands& operands) {
	assert(!operands.empty() && "Cannot cast empty vector to common type");

	SameTypeOperands returnValue;

	detail::PushBackVisitor visitor(returnValue);
	for(const auto& operand: operands) {
		ast::applyVisitor(operand, visitor);
	}

	return returnValue;
}


}} // namespace tungsten::eval

