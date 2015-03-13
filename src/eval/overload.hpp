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

	auto operator()(const ast::Operands& operands) {
		naryVisitor v(sessionEnvironment);
		switch(operands.size()) {
			case 0:
				return v();
			case 1:
				return v(operands[0]);
			case 2:
				return v(operands[0], operands[1]);
			case 3:
				return v(operands[0], operands[1], operands[2]);
			default:
				return v(operands);
		}
	}

private:

	SessionEnvironment& sessionEnvironment;

	struct naryVisitor : boost::static_visitor<ast::Node> {
		naryVisitor(SessionEnvironment& sessionEnvironment): sessionEnvironment(sessionEnvironment) { }
		template<typename... Ts>
		auto operator()(Ts&&...ts) {
			return Implementation{}(sessionEnvironment, std::forward<Ts>(ts)...);
		}

		SessionEnvironment& sessionEnvironment;
	};

};

}} // namespace tungsten::eval

#endif /* EVAL_OVERLOAD_HPP_ */



