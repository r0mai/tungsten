
#include "eval/SessionEnvironment.hpp"

#include <chrono>

#include <boost/date_time/posix_time/posix_time_types.hpp>
#include <boost/lexical_cast.hpp>

namespace tungsten { namespace eval { namespace builtin {

OptionalNode AbsoluteTime(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment) {
	using namespace boost::posix_time;
	using namespace boost::gregorian;

	if(!operands.empty()) {
		sessionEnvironment.raiseMessage( Message(ids::AbsoluteTime, ids::argx, {
				ast::Node::make<ast::Identifier>(ids::AbsoluteTime),
				ast::Node::make<math::Rational>(operands.size())
		} ));
		return EvaluationFailure();
	}

	ptime epoch(date(1970, 1, 1));
	ptime pt = second_clock::universal_time();

	time_duration diff = pt - epoch;

	return ast::Node::make<math::Rational>(boost::lexical_cast<int>(diff.total_seconds()));
}

OptionalNode Timing(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment) {
	if(operands.size() != 1) {
		sessionEnvironment.raiseMessage( Message(ids::Timing, ids::argx, {
				ast::Node::make<ast::Identifier>(ids::Timing),
				ast::Node::make<math::Rational>(operands.size())
		} ));
		return EvaluationFailure();
	}

	typedef std::chrono::steady_clock Clock;

	Clock::time_point start = Clock::now();
	ast::Node result = sessionEnvironment.recursiveEvaluate(operands[0]);
	Clock::time_point end = Clock::now();

	std::chrono::duration<double> duration = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);

	return sessionEnvironment.recursiveEvaluate(
				ast::Node::make<ast::FunctionCall>(ids::List, {
					ast::Node::make<math::Real>(duration.count()),
					result
				})
			);
}

}}} // namespace tngsten::eval::builtin

