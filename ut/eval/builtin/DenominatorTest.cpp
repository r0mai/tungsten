
#include <boost/test/unit_test.hpp>

#include "Fixture.hpp"

BOOST_AUTO_TEST_SUITE( DenominatorTest )

using namespace tungsten;

BOOST_FIXTURE_TEST_CASE( test_Denominator_of_x , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Denominator[x]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<math::Rational>(1) );
}


BOOST_FIXTURE_TEST_CASE( test_Denominator_of_quote_abc_quote , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Denominator[\"abc\"]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<math::Rational>(1) );
}


BOOST_FIXTURE_TEST_CASE( test_Denominator_of_4 , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Denominator[4]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<math::Rational>(1) );
}


BOOST_FIXTURE_TEST_CASE( test_Denominator_of_1_5 , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Denominator[1.5]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<math::Rational>(1) );
}


BOOST_FIXTURE_TEST_CASE( test_Denominator_of_the_quantity_2_over_3 , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Denominator[2/3]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<math::Rational>(3) );
}


BOOST_FIXTURE_TEST_CASE( test_Denominator_of_the_quantity_x_over_y , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Denominator[x/y]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::Identifier>("y") );
}


BOOST_FIXTURE_TEST_CASE( test_Denominator_of_the_quantity_x_over_y_squared , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Denominator[x/y^2]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("y"), ast::Node::make<math::Rational>(2)}) );
}

BOOST_FIXTURE_TEST_CASE( test_Denominator_of_the_quantity_1_over_x , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Denominator[1/x]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::Identifier>("x") );
}


BOOST_FIXTURE_TEST_CASE( test_Denominator_of_the_quantity_1_over_x_squared , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Denominator[1/x^2]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::FunctionCall>("Power", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<math::Rational>(2)}) );
}

BOOST_AUTO_TEST_SUITE_END()
