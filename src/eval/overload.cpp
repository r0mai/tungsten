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
	boost::variant<
		std::vector<math::Real>,
		std::vector<math::Rational>,
		std::vector<ast::Identifier>,
		std::vector<ast::String>,
		std::vector<ast::FunctionCall>
	>& storage;

	PushBackVisitor(
		boost::variant<
			std::vector<math::Real>,
			std::vector<math::Rational>,
			std::vector<ast::Identifier>,
			std::vector<ast::String>,
			std::vector<ast::FunctionCall>
		>& storage) : storage(storage) { }

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

boost::variant<
		std::vector<math::Real>,
		std::vector<math::Rational>,
		std::vector<ast::Identifier>,
		std::vector<ast::String>,
		std::vector<ast::FunctionCall>
> castListToCommonType(const ast::Operands& operands) {
	assert(!operands.empty() && "Cannot cast empty vector to common type");

	boost::variant<
			std::vector<math::Real>,
			std::vector<math::Rational>,
			std::vector<ast::Identifier>,
			std::vector<ast::String>,
			std::vector<ast::FunctionCall>
	> returnValue;

	detail::PushBackVisitor visitor(returnValue);
	for(const auto& operand: operands) {
		ast::applyVisitor(operand, visitor);
	}

	return returnValue;
}


}} // namespace tungsten::eval

