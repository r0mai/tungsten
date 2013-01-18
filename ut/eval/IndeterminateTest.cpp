
#include <boost/test/unit_test.hpp>

#include "builtin/Fixture.hpp"

BOOST_AUTO_TEST_SUITE( IndeterminateTest )

using namespace tungsten;


BOOST_FIXTURE_TEST_CASE( NumericFunction_with_Indeterminate_parameter_results_in_Indeterminate, BuiltinFunctionFixture ) {

	addAttribute("f", "NumericFunction");

	ast::Node result = evaluate(ast::Node::make<ast::FunctionCall>("f", {ast::Node::make<ast::Identifier>("Indeterminate")}));

	ast::Node expected = ast::Node::make<ast::Identifier>("Indeterminate");

	BOOST_CHECK_EQUAL( result, expected );
}

BOOST_FIXTURE_TEST_CASE( non_NumericFunction_with_Indeterminate_parameter_results_in_non_Indeterminate, BuiltinFunctionFixture ) {

	ast::Node result = evaluate(ast::Node::make<ast::FunctionCall>("f", {ast::Node::make<ast::Identifier>("Indeterminate")}));

	ast::Node expected = ast::Node::make<ast::FunctionCall>("f", {ast::Node::make<ast::Identifier>("Indeterminate")});

	BOOST_CHECK_EQUAL( result, expected );
}

BOOST_FIXTURE_TEST_CASE( NumericFunction_with_multiple_Indeterminate_parameters_results_in_Indeterminate, BuiltinFunctionFixture ) {

	addAttribute("f", "NumericFunction");

	ast::Node result = evaluate(ast::Node::make<ast::FunctionCall>("f", {ast::Node::make<ast::Identifier>("Indeterminate"), ast::Node::make<ast::Identifier>("Indeterminate")}));

	ast::Node expected = ast::Node::make<ast::Identifier>("Indeterminate");

	BOOST_CHECK_EQUAL( result, expected );
}

BOOST_FIXTURE_TEST_CASE( NumericFunction_with_multiple_paramters_including_Indeterminate_results_in_Indeterminate, BuiltinFunctionFixture ) {

	addAttribute("f", "NumericFunction");

	ast::Node result = evaluate(ast::Node::make<ast::FunctionCall>("f", {ast::Node::make<math::Rational>(12), ast::Node::make<ast::Identifier>("Indeterminate")}));

	ast::Node expected = ast::Node::make<ast::Identifier>("Indeterminate");

	BOOST_CHECK_EQUAL( result, expected );
}

BOOST_FIXTURE_TEST_CASE( nested_NumericFunctions_with_Indeterminate_parameter_results_in_Indeterminate, BuiltinFunctionFixture ) {

	addAttribute("f", "NumericFunction");
	addAttribute("g", "NumericFunction");

	ast::Node result = evaluate(ast::Node::make<ast::FunctionCall>("f", {ast::Node::make<ast::FunctionCall>("g", {ast::Node::make<ast::Identifier>("Indeterminate")})}));

	ast::Node expected = ast::Node::make<ast::Identifier>("Indeterminate");

	BOOST_CHECK_EQUAL( result, expected );
}

BOOST_AUTO_TEST_SUITE_END()
