

#ifndef EVAL_BUILTIN_FIXTURE_HPP_
#define EVAL_BUILTIN_FIXTURE_HPP_

#include <string>

#include <boost/optional.hpp>

#include "ast/Parser.hpp"
#include "../UnitTestSessionEnvironment.hpp"

class BuiltinFunctionFixture {
public:

	tungsten::ast::Node evaluate(const tungsten::ast::Node& node) {
		return environment.evaluate(node);
	}

	boost::optional<tungsten::ast::Node> parseAndEvaluate(const std::string& string) {
		boost::optional<tungsten::ast::Node> parsed = tungsten::ast::parseInput(string);
		if ( !parsed ) {
			return boost::optional<tungsten::ast::Node>();
		}

		return evaluate(*parsed);
	}

private:
	UnitTestEnvironment environment;
};

#endif /* EVAL_BUILTIN_FIXTURE_HPP_ */
