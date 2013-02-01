
#include <boost/test/unit_test.hpp>

#include "builtin/Fixture.hpp"

BOOST_AUTO_TEST_SUITE( HoldAttributesTest )

using namespace tungsten;


BOOST_FIXTURE_TEST_CASE( HoldFirst_holds_only_first_argument, BuiltinFunctionFixture ) {

	addAttribute("f", "HoldFirst");

	boost::optional<ast::Node> result = parseAndEvaluate("f[1+1, 1+1]");

	BOOST_REQUIRE(result);

	ast::Node expected = ast::Node::make<ast::FunctionCall>("f",
			{ast::Node::make<ast::FunctionCall>("Plus", {ast::Node::make<math::Rational>(1), ast::Node::make<math::Rational>(1)}),
					ast::Node::make<math::Rational>(2)});

	BOOST_CHECK_EQUAL( *result, expected );
}

BOOST_FIXTURE_TEST_CASE( HoldRest_doesnt_hold_first_argument, BuiltinFunctionFixture ) {

	addAttribute("f", "HoldRest");

	boost::optional<ast::Node> result = parseAndEvaluate("f[1+1, 1+1]");

	BOOST_REQUIRE(result);

	ast::Node expected = ast::Node::make<ast::FunctionCall>("f",
			{ast::Node::make<math::Rational>(2),
				ast::Node::make<ast::FunctionCall>("Plus", {ast::Node::make<math::Rational>(1), ast::Node::make<math::Rational>(1)})});

	BOOST_CHECK_EQUAL( *result, expected );
}

BOOST_FIXTURE_TEST_CASE( HoldAll_holds_every_argument, BuiltinFunctionFixture ) {

	addAttribute("f", "HoldAll");

	boost::optional<ast::Node> result = parseAndEvaluate("f[1+1, 1+1]");

	BOOST_REQUIRE(result);

	ast::Node expected = ast::Node::make<ast::FunctionCall>("f",
			{ast::Node::make<ast::FunctionCall>("Plus", {ast::Node::make<math::Rational>(1), ast::Node::make<math::Rational>(1)}),
				ast::Node::make<ast::FunctionCall>("Plus", {ast::Node::make<math::Rational>(1), ast::Node::make<math::Rational>(1)})});

	BOOST_CHECK_EQUAL( *result, expected );
}

BOOST_FIXTURE_TEST_CASE( HoldFirst_holds_first_single_argument, BuiltinFunctionFixture ) {

	addAttribute("f", "HoldFirst");

	boost::optional<ast::Node> result = parseAndEvaluate("f[1+1]");

	BOOST_REQUIRE(result);

	ast::Node expected = ast::Node::make<ast::FunctionCall>("f",
			{ast::Node::make<ast::FunctionCall>("Plus", {ast::Node::make<math::Rational>(1), ast::Node::make<math::Rational>(1)})});

	BOOST_CHECK_EQUAL( *result, expected );
}

BOOST_FIXTURE_TEST_CASE( HoldRest_doesnt_hold_first_single_argument, BuiltinFunctionFixture ) {

	addAttribute("f", "HoldRest");

	boost::optional<ast::Node> result = parseAndEvaluate("f[1+1]");

	BOOST_REQUIRE(result);

	ast::Node expected = ast::Node::make<ast::FunctionCall>("f", {ast::Node::make<math::Rational>(2)});

	BOOST_CHECK_EQUAL( *result, expected );
}

BOOST_FIXTURE_TEST_CASE( HoldAll_holds_first_single_argument, BuiltinFunctionFixture ) {

	addAttribute("f", "HoldAll");

	boost::optional<ast::Node> result = parseAndEvaluate("f[1+1]");

	BOOST_REQUIRE(result);

	ast::Node expected = ast::Node::make<ast::FunctionCall>("f",
			{ast::Node::make<ast::FunctionCall>("Plus", {ast::Node::make<math::Rational>(1), ast::Node::make<math::Rational>(1)})});

	BOOST_CHECK_EQUAL( *result, expected );
}

BOOST_FIXTURE_TEST_CASE( HoldFirst_behaves_well_without_arguments, BuiltinFunctionFixture ) {

	addAttribute("f", "HoldFirst");

	boost::optional<ast::Node> result = parseAndEvaluate("f[]");

	BOOST_REQUIRE(result);

	ast::Node expected = evaluate(ast::Node::make<ast::FunctionCall>("f"));

	BOOST_CHECK_EQUAL( *result, expected );
}

BOOST_FIXTURE_TEST_CASE( HoldRest_behaves_well_without_arguments, BuiltinFunctionFixture ) {

	addAttribute("f", "HoldRest");

	boost::optional<ast::Node> result = parseAndEvaluate("f[]");

	BOOST_REQUIRE(result);

	ast::Node expected = evaluate(ast::Node::make<ast::FunctionCall>("f"));

	BOOST_CHECK_EQUAL( *result, expected );
}

BOOST_FIXTURE_TEST_CASE( HoldAll_behaves_well_without_arguments, BuiltinFunctionFixture ) {

	addAttribute("f", "HoldAll");

	boost::optional<ast::Node> result = parseAndEvaluate("f[]");

	BOOST_REQUIRE(result);

	ast::Node expected = evaluate(ast::Node::make<ast::FunctionCall>("f"));

	BOOST_CHECK_EQUAL( *result, expected );
}

BOOST_AUTO_TEST_SUITE_END()


