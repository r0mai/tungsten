
#include <boost/test/unit_test.hpp>

#include "UnitTestSessionEnvironment.hpp"

BOOST_AUTO_TEST_SUITE( OrderlessTest )

using namespace tungsten;

BOOST_AUTO_TEST_CASE( Orderless_sorts_argument_list ) {
	UnitTestEnvironment environment;
	environment.addAttribute("f", "Orderless");

	ast::Node result = environment.evaluate(
			ast::Node::make<ast::FunctionCall>( "f", {ast::Node::make<math::Rational>(4), ast::Node::make<math::Rational>(3)} )
	);

	BOOST_CHECK_EQUAL(result,
			ast::Node::make<ast::FunctionCall>( "f", {ast::Node::make<math::Rational>(3), ast::Node::make<math::Rational>(4)} ));

}

BOOST_AUTO_TEST_CASE( non_Orderless_doesnt_sort_argument_list ) {
	UnitTestEnvironment environment;

	ast::Node result = environment.evaluate(
			ast::Node::make<ast::FunctionCall>( "f", {ast::Node::make<math::Rational>(4), ast::Node::make<math::Rational>(3)} )
	);

	BOOST_CHECK_EQUAL(result,
			ast::Node::make<ast::FunctionCall>( "f", {ast::Node::make<math::Rational>(4), ast::Node::make<math::Rational>(3)} ));

}

BOOST_AUTO_TEST_CASE( Orderless_doesnt_break_on_empty_argument_list ) {
	UnitTestEnvironment environment;
	environment.addAttribute("f", "Orderless");

	ast::Node result = environment.evaluate(
			ast::Node::make<ast::FunctionCall>( "f" )
	);

	BOOST_CHECK_EQUAL(result,
			ast::Node::make<ast::FunctionCall>( "f" ));

}

BOOST_AUTO_TEST_CASE( Orderless_doesnt_break_on_single_element_argument_list ) {
	UnitTestEnvironment environment;
	environment.addAttribute("f", "Orderless");

	ast::Node result = environment.evaluate(
			ast::Node::make<ast::FunctionCall>( "f", {ast::Node::make<math::Rational>(4)} )
	);

	BOOST_CHECK_EQUAL(result,
			ast::Node::make<ast::FunctionCall>( "f", {ast::Node::make<math::Rational>(4)} ));

}

BOOST_AUTO_TEST_SUITE_END()
