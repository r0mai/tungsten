#ifndef EVAL_OVERLOAD_HPP_
#define EVAL_OVERLOAD_HPP_
#include "ast/Node.hpp"
#include "eval/SessionEnvironment.hpp"
#include <map>
#include <string>
#include <vector>
#include <boost/type_index.hpp>

namespace tungsten { namespace eval {

bool areAllOfSameType(const ast::Operands& operands);
boost::variant<
		std::vector<math::Real>,
		std::vector<math::Rational>,
		std::vector<ast::Identifier>,
		std::vector<ast::String>,
		std::vector<ast::FunctionCall>
> castListToCommonType(const ast::Operands& operands);

namespace detail {

template<typename... Ts>
std::vector<std::string> getTypeNames() {
	return { std::string(boost::typeindex::type_id<Ts>().pretty_name())... };
}

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
		boost::optional<ast::Node> operator()(const Ts&...ts) {
			return Implementation{}.template operator()<typename std::decay<Ts>::type...>(sessionEnvironment, ts...);
		}

		boost::optional<ast::Node> operator()(const ast::FunctionCall& f) {
			if ( f.getFunction() == ast::Node::make<ast::Identifier>(ids::List) ) {
				if ( areAllOfSameType(f.getOperands()) ) {
					const auto commonTyped = castListToCommonType(f.getOperands());
					return boost::apply_visitor(*this, commonTyped);
				}
			}
			return Implementation{}.template operator()<ast::FunctionCall>(sessionEnvironment, f);
		}

		template<typename T>
		boost::optional<ast::Node> operator()(const T& list) {
			return Implementation{}.template operator()<T>(sessionEnvironment, list);
		}

		SessionEnvironment& sessionEnvironment;
	};

};

}} // namespace tungsten::eval

#endif /* EVAL_OVERLOAD_HPP_ */



