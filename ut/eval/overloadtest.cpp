#include "eval/overload.hpp"
#include "../eval/UnitTestSessionEnvironment.hpp"
#include "../eval/builtin/Fixture.hpp"
#include <boost/test/unit_test.hpp>

BOOST_FIXTURE_TEST_SUITE( OverloadTest, BuiltinFunctionFixture )

using namespace tungsten;

namespace Nullary {
	template<typename... Ts>
	boost::optional<ast::Node> nullary(eval::SessionEnvironment&, const Ts&...) {
		std::cerr<<__PRETTY_FUNCTION__<<std::endl;
		return boost::none;
	}

	template<>
	boost::optional<ast::Node> nullary<>(eval::SessionEnvironment&) {
		return ast::Node::make<math::Rational>(0);
	}
} // namespace Nullary

struct NullaryTester {
	template<typename... Ts>
	auto operator()(eval::SessionEnvironment& sessionEnvironment, const Ts&... ts) {
		return Nullary::nullary<typename std::decay<Ts>::type...>(sessionEnvironment, ts...);
	}
};

BOOST_AUTO_TEST_CASE( nullaryTest ) {

	UnitTestEnvironment environment;
	eval::Dispatcher<NullaryTester> dispatcher(environment);

	BOOST_CHECK(dispatcher({}).is_initialized());
}

namespace Unary {

template<typename... Ts>
boost::optional<ast::Node> unary(eval::SessionEnvironment&, const Ts&...) {
	return boost::none;
}

template<>
boost::optional<ast::Node> unary<math::Real>(eval::SessionEnvironment&, const math::Real&) {
	return ast::Node::make<math::Rational>(0);
}

} // namespace Unary

struct UnaryTester {
	template<typename... Ts>
	boost::optional<ast::Node> operator()(eval::SessionEnvironment& sessionEnvironment, const Ts&... ts) {
		return Unary::unary<typename std::decay<Ts>::type...>(sessionEnvironment, ts...);
	}
};

BOOST_AUTO_TEST_CASE( unaryTest ) {
	UnitTestEnvironment environment;
	eval::Dispatcher<UnaryTester> dispatcher(environment);

	BOOST_REQUIRE(UnaryTester{}(environment, math::Real{0}));
	BOOST_CHECK(dispatcher({ast::Node::make<math::Real>(0)}));
}

BOOST_AUTO_TEST_SUITE_END()

