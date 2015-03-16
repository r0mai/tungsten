

#include <boost/test/unit_test.hpp>

#include "Fixture.hpp"
#include "ast/Identifier.hpp"

using namespace tungsten;
using namespace eval;

BOOST_AUTO_TEST_SUITE( FindDivisionsTest )

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

BOOST_FIXTURE_TEST_SUITE( ContinuedFractionTest, BuiltinFunctionFixture )

BOOST_AUTO_TEST_CASE( test_continuedfraction_of_3_4 ) {
	boost::optional<ast::Node> result = parseAndEvaluate("ContinuedFraction[3.4]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result, ast::Node::make<ast::FunctionCall>(ids::List, {
			ast::Node::make<math::Rational>(3),
			ast::Node::make<math::Rational>(2),
			ast::Node::make<math::Rational>(2) }));
}

BOOST_AUTO_TEST_CASE( test_continuedfraction_of_pi_with_20_elements ) {
	boost::optional<ast::Node> result = parseAndEvaluate("ContinuedFraction[N[Pi], 20]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result, ast::Node::make<ast::FunctionCall>(ids::List, {
			ast::Node::make<math::Rational>(3),
			ast::Node::make<math::Rational>(7),
			ast::Node::make<math::Rational>(15),
			ast::Node::make<math::Rational>(1),
			ast::Node::make<math::Rational>(292),
			ast::Node::make<math::Rational>(1),
			ast::Node::make<math::Rational>(1),
			ast::Node::make<math::Rational>(1),
			ast::Node::make<math::Rational>(2),
			ast::Node::make<math::Rational>(1),
			ast::Node::make<math::Rational>(3),
			ast::Node::make<math::Rational>(1),
			ast::Node::make<math::Rational>(14),
			ast::Node::make<math::Rational>(2),
			ast::Node::make<math::Rational>(1),
			ast::Node::make<math::Rational>(1),
			ast::Node::make<math::Rational>(2),
			ast::Node::make<math::Rational>(2),
			ast::Node::make<math::Rational>(2),
			ast::Node::make<math::Rational>(2) }));
}

BOOST_AUTO_TEST_SUITE_END()
