#include "eval/overload.hpp"
#include "../eval/UnitTestSessionEnvironment.hpp"
#include "../eval/builtin/Fixture.hpp"
#include <boost/test/unit_test.hpp>

BOOST_FIXTURE_TEST_SUITE( OverloadTest, BuiltinFunctionFixture )

using namespace tungsten;

struct NullaryTester {
	template<typename... Ts>
	bool operator()(eval::SessionEnvironment&, Ts&&...) { return false; }

	bool operator()(eval::SessionEnvironment&) { return true; }
};

BOOST_AUTO_TEST_CASE( nullaryTest ) {

	UnitTestEnvironment environment;
	eval::Dispatcher<NullaryTester> dispatcher(environment);

	BOOST_CHECK_EQUAL(dispatcher({}), true);
}

BOOST_AUTO_TEST_SUITE_END()

