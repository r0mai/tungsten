#include "eval/SessionEnvironment.hpp"
#include "boost/date_time/posix_time/posix_time_types.hpp"
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

}}} // namespace tngsten::eval::builtin

