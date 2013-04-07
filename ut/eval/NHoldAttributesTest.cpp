
#include <boost/test/unit_test.hpp>

#include "builtin/Fixture.hpp"

BOOST_AUTO_TEST_SUITE( NHoldAttributesTest )

using namespace tungsten;

BOOST_FIXTURE_TEST_CASE( NHoldFirst_NHolds_first_argument, BuiltinFunctionFixture ) {

	addAttribute("f", "NHoldFirst");

	boost::optional<ast::Node> result = parseAndEvaluate("N[f[1, 1]]");

	BOOST_REQUIRE(result);

	ast::Node expected = evaluate(ast::Node::make<ast::FunctionCall>("f", { ast::Node::make<math::Rational>(1), ast::Node::make<math::Real>(1) }));

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( NHoldRest_NHolds_rest_of_the_arguments, BuiltinFunctionFixture ) {

	addAttribute("f", "NHoldRest");

	boost::optional<ast::Node> result = parseAndEvaluate("N[f[1, 1]]");

	BOOST_REQUIRE(result);

	ast::Node expected = evaluate(ast::Node::make<ast::FunctionCall>("f", { ast::Node::make<math::Real>(1), ast::Node::make<math::Rational>(1) }));

	BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( NHoldAll_NHolds_all_of_the_arguments, BuiltinFunctionFixture ) {

	addAttribute("f", "NHoldAll");

	boost::optional<ast::Node> result = parseAndEvaluate("N[f[1, 1]]");

	BOOST_REQUIRE(result);

	ast::Node expected = evaluate(ast::Node::make<ast::FunctionCall>("f", { ast::Node::make<math::Rational>(1), ast::Node::make<math::Rational>(1) }));

	BOOST_CHECK_EQUAL( *result, expected );
}

BOOST_AUTO_TEST_SUITE_END()


