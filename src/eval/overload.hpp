#ifndef EVAL_OVERLOAD_HPP_
#define EVAL_OVERLOAD_HPP_
#include "ast/Node.hpp"
#include "eval/SessionEnvironment.hpp"

namespace tungsten { namespace eval {

template<typename Implementation>
class Dispatcher {
public:
	Dispatcher() = delete;
	Dispatcher(SessionEnvironment& sessionEnvironment) : sessionEnvironment(sessionEnvironment) { }

	boost::optional<ast::Node> operator()(const ast::Operands& operands) {
		naryVisitor v(sessionEnvironment);
		switch(operands.size()) {
			case 0:
				std::cerr<<"calling nullary"<<std::endl;
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

		SessionEnvironment& sessionEnvironment;
	};

};

}} // namespace tungsten::eval

#endif /* EVAL_OVERLOAD_HPP_ */



