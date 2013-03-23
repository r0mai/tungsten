
#include <boost/test/unit_test.hpp>

#include "Fixture.hpp"

BOOST_AUTO_TEST_SUITE( MinusTest )

using namespace tungsten;

BOOST_FIXTURE_TEST_CASE( test_Minus_of_x , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("-x");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<math::Rational>(-1), ast::Node::make<ast::Identifier>("x")}) );
}


BOOST_FIXTURE_TEST_CASE( test_Minus_of_the_list_x__y , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("-{x, y}");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<math::Rational>(-1), ast::Node::make<ast::Identifier>("x")}), ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<math::Rational>(-1), ast::Node::make<ast::Identifier>("y")})}) );
}


BOOST_FIXTURE_TEST_CASE( test_Minus_of_1 , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("-1");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<math::Rational>(-1) );
}


BOOST_FIXTURE_TEST_CASE( test_Minus_of_minus_1 , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("-(-1)");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<math::Rational>(1) );
}


BOOST_FIXTURE_TEST_CASE( test_Minus_of_1_0 , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("-1.");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<math::Real>(-1.) );
}


BOOST_FIXTURE_TEST_CASE( test_Minus_of_minus_1_0 , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("-(-1.)");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<math::Real>(1.) );
}


//---Same as above, but with explicit Minus[]

BOOST_FIXTURE_TEST_CASE( test_Minus_of_x_explicit, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Minus[x]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<math::Rational>(-1), ast::Node::make<ast::Identifier>("x")}) );
}


BOOST_FIXTURE_TEST_CASE( test_Minus_of_the_list_x__y_explicit, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Minus[{x, y}]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<math::Rational>(-1), ast::Node::make<ast::Identifier>("x")}), ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<math::Rational>(-1), ast::Node::make<ast::Identifier>("y")})}) );
}


BOOST_FIXTURE_TEST_CASE( test_Minus_of_1_explicit , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Minus[1]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<math::Rational>(-1) );
}


BOOST_FIXTURE_TEST_CASE( test_Minus_of_minus_1_explicit, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Minus[-1]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<math::Rational>(1) );
}


BOOST_FIXTURE_TEST_CASE( test_Minus_of_1_0_explicit, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Minus[1.]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<math::Real>(-1.) );
}


BOOST_FIXTURE_TEST_CASE( test_Minus_of_minus_1_0_explicit, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Minus[-1.]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<math::Real>(1.) );
}



BOOST_AUTO_TEST_SUITE_END()
