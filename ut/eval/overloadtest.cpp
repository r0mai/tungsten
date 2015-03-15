#include "eval/overload.hpp"
#include "../eval/UnitTestSessionEnvironment.hpp"
#include "../eval/builtin/Fixture.hpp"
#include <boost/test/unit_test.hpp>
#include <boost/mpl/list.hpp>

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

// areAllOfSameType tests here

BOOST_AUTO_TEST_CASE( EmptyRangeShouldBeOfSameType ) {
	BOOST_CHECK_EQUAL( eval::areAllOfSameType({}), true );
}

BOOST_AUTO_TEST_CASE( SingleElementRangeShouldBeOfSameType ) {
	BOOST_CHECK_EQUAL( eval::areAllOfSameType({ast::Node::make<math::Rational>(0)}), true );
}

using NumericTypes =
	boost::mpl::list<math::Real, math::Rational>;

BOOST_AUTO_TEST_CASE_TEMPLATE( TwoCorrespondingNumericsShouldBeOfSameType, TypeParam, NumericTypes ) {
	BOOST_CHECK_EQUAL( eval::areAllOfSameType({
			ast::Node::make<TypeParam>(0),
			ast::Node::make<TypeParam>(1)
	}), true);
}

BOOST_AUTO_TEST_CASE_TEMPLATE( ThreeCorrespondingNumericsShouldBeOfSameType, TypeParam, NumericTypes ) {
	BOOST_CHECK_EQUAL( eval::areAllOfSameType({
			ast::Node::make<TypeParam>(0),
			ast::Node::make<TypeParam>(1),
			ast::Node::make<TypeParam>(2)
	}), true);
}

BOOST_AUTO_TEST_CASE_TEMPLATE( FourCorrespondingNumericsShouldBeOfSameType, TypeParam, NumericTypes ) {
	BOOST_CHECK_EQUAL( eval::areAllOfSameType({
			ast::Node::make<TypeParam>(0),
			ast::Node::make<TypeParam>(1),
			ast::Node::make<TypeParam>(2),
			ast::Node::make<TypeParam>(3)
	}), true);
}

// castToCommonTypeTests
BOOST_AUTO_TEST_CASE_TEMPLATE( OneElementListOfNumericShouldCastToNumeric, TypeParam, NumericTypes ) {
	ast::Operands listOfReals;

	listOfReals.push_back(ast::Node::make<TypeParam>(0));
	auto result = eval::castListToCommonType(listOfReals);
	BOOST_REQUIRE(boost::get<std::vector<TypeParam>>(&result));
	BOOST_CHECK_EQUAL(boost::get<std::vector<TypeParam>>(result)[0], 0);
}

BOOST_AUTO_TEST_CASE_TEMPLATE( TwoElementListOfNumericShouldCastToNumeric, TypeParam, NumericTypes ) {
	ast::Operands listOfReals;

	listOfReals.push_back(ast::Node::make<TypeParam>(0));
	listOfReals.push_back(ast::Node::make<TypeParam>(10));
	auto result = eval::castListToCommonType(listOfReals);
	BOOST_REQUIRE(boost::get<std::vector<TypeParam>>(&result));
	BOOST_CHECK_EQUAL(boost::get<std::vector<TypeParam>>(result)[0], 0);
	BOOST_CHECK_EQUAL(boost::get<std::vector<TypeParam>>(result)[1], 10);
}

BOOST_AUTO_TEST_CASE_TEMPLATE( ThreeElementListOfNumericShouldCastToNumeric, TypeParam, NumericTypes ) {
	ast::Operands listOfReals;

	listOfReals.push_back(ast::Node::make<TypeParam>(0));
	listOfReals.push_back(ast::Node::make<TypeParam>(10));
	listOfReals.push_back(ast::Node::make<TypeParam>(150));
	auto result = eval::castListToCommonType(listOfReals);
	BOOST_REQUIRE(boost::get<std::vector<TypeParam>>(&result));
	BOOST_CHECK_EQUAL(boost::get<std::vector<TypeParam>>(result)[0], 0);
	BOOST_CHECK_EQUAL(boost::get<std::vector<TypeParam>>(result)[1], 10);
	BOOST_CHECK_EQUAL(boost::get<std::vector<TypeParam>>(result)[2], 150);
}


BOOST_AUTO_TEST_SUITE_END()

