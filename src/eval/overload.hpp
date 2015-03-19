#ifndef EVAL_OVERLOAD_HPP_
#define EVAL_OVERLOAD_HPP_
#include "ast/Node.hpp"
#include "eval/SessionEnvironment.hpp"
#include <map>
#include <string>
#include <iostream>
#include <vector>
#include <boost/type_index.hpp>

namespace tungsten { namespace eval {


using SameTypeOperands =
boost::variant<
		std::vector<math::Real>,
		std::vector<math::Rational>,
		std::vector<ast::Identifier>,
		std::vector<ast::String>,
		std::vector<ast::FunctionCall>
>;

bool areAllOfSameType(const ast::Operands& operands);
bool areAllListsOfSameType(const std::vector<SameTypeOperands>& operandLists);

SameTypeOperands castListToCommonType(const ast::Operands& operands);

namespace detail {

template<typename... Ts>
std::vector<std::string> getTypeNames() {
	return { std::string(boost::typeindex::type_id<Ts>().pretty_name())... };
}

template<typename... Ts>
struct AllEqual : std::false_type { };

template<typename Head1, typename Head2, typename... Tail>
struct AllEqual<Head1, Head2, Tail...> {
	static constexpr bool value = std::is_same<Head1, Head2>::value &&
			AllEqual<Head2, Tail...>::value;
};

template<typename Head>
struct AllEqual<Head> : std::true_type { };

template<typename... Ts>
struct AllEqualTo : std::false_type { };

template<typename T, typename Head, typename... Tail>
struct AllEqualTo<T, Head, Tail...> {
	static constexpr bool value = std::is_same<T, typename std::decay<Head>::type>::value &&
			AllEqual<T, Tail...>::value;
};

template<typename... Ts>
std::string getTypePackString() {
	const auto typeStringPack = getTypeNames<Ts...>();
	if(typeStringPack.empty()) { return ""; }
	if(typeStringPack.size() == 0) { return typeStringPack.front(); }

	std::string result = typeStringPack.front();

	for(int i=1; i<typeStringPack.size(); ++i) {
		result += ", " + typeStringPack[i];
	}

	return result;

}

template<typename T>
const T& addConst(const T& t) { return t; }

} // namespace detail

template<typename Implementation>
class Dispatcher {
public:
	Dispatcher() = delete;
	Dispatcher(SessionEnvironment& sessionEnvironment) : sessionEnvironment(sessionEnvironment) { }

	boost::optional<ast::Node> operator()(const ast::Operands& operands) {
		naryVisitor v(sessionEnvironment);
		switch(operands.size()) {
			case 0:
				return v();
			case 1:
				return ast::applyVisitor(operands[0], v);
			case 2:
				return ast::applyVisitor(operands[0], operands[1], v);
			default:
				return v(operands);
		}
	}

private:

	SessionEnvironment& sessionEnvironment;

	struct naryVisitor : boost::static_visitor<boost::optional<ast::Node>> {
		naryVisitor(SessionEnvironment& sessionEnvironment): sessionEnvironment(sessionEnvironment) { }
		template<typename... Ts>
		typename std::enable_if<!detail::AllEqualTo<ast::FunctionCall, Ts...>::value, boost::optional<ast::Node>>::type
		operator()(const Ts&...ts) {
			return Implementation{}.template operator()<typename std::decay<Ts>::type...>(sessionEnvironment, ts...);
		}

		template<typename T, typename... Ts>
		typename std::enable_if<detail::AllEqualTo<ast::FunctionCall, T, Ts...>::value, boost::optional<ast::Node>>::type
		operator()(const T& t, const Ts&... ts) {
			std::vector<bool> areLists = {
					t.getFunction() == ast::Node::make<ast::Identifier>(ids::List),
					ts.getFunction() == ast::Node::make<ast::Identifier>(ids::List)...
			};
			if ( std::all_of(areLists.begin(), areLists.end(), [](bool b) { return b; }) ) {
				std::vector<bool> areOfSameTypes = {
						areAllOfSameType(t.getOperands()),
						areAllOfSameType(ts.getOperands())...
				};
				if ( std::all_of(areOfSameTypes.begin(), areOfSameTypes.end(), [](bool b) { return b;}) ) {
					return boost::apply_visitor(*this,
							detail::addConst(castListToCommonType(t.getOperands())),
							detail::addConst(castListToCommonType(ts.getOperands()))...
					);
				}
			}
			return Implementation{}.template operator()<ast::FunctionCall>(sessionEnvironment, t, ts...);
		}

		SessionEnvironment& sessionEnvironment;
	};

};

}} // namespace tungsten::eval

#endif /* EVAL_OVERLOAD_HPP_ */



