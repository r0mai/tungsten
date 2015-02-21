

#include <boost/test/unit_test.hpp>

#include "Fixture.hpp"
#include "ast/Identifier.hpp"

BOOST_AUTO_TEST_SUITE( FindDivisionsTest )

using namespace tungsten;
using namespace eval;

// FindDivisions ----

BOOST_FIXTURE_TEST_CASE( test_0_1_5_finddivisions, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("FindDivisions[{0,1},5]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result, ast::Node::make<ast::FunctionCall>(ids::List, {
			ast::Node::make<math::Rational>(0),
			ast::Node::make<math::Rational>(1, 5),
			ast::Node::make<math::Rational>(2, 5),
			ast::Node::make<math::Rational>(3, 5),
			ast::Node::make<math::Rational>(4, 5),
			ast::Node::make<math::Rational>(1) }));
}

BOOST_AUTO_TEST_SUITE_END()
