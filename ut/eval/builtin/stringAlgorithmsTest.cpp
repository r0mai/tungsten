
#include <boost/test/unit_test.hpp>

#include "Fixture.hpp"

BOOST_AUTO_TEST_SUITE( stringAlgorithmTest )

using namespace tungsten;

BOOST_FIXTURE_TEST_CASE( test_StringLength_of_quote_quote, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("StringLength[\"\"]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<math::Rational>(0) );
}


BOOST_FIXTURE_TEST_CASE( test_StringLength_of_quote_a_quote, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("StringLength[\"a\"]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<math::Rational>(1) );
}


BOOST_FIXTURE_TEST_CASE( test_StringLength_of_quote_space_quote, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("StringLength[\" \"]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<math::Rational>(1) );
}


BOOST_FIXTURE_TEST_CASE( test_StringLength_of_quote_tab_quote, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("StringLength[\"\\t\"]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<math::Rational>(1) );
}


BOOST_FIXTURE_TEST_CASE( test_StringLength_of_quote_abc_quote, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("StringLength[\"abc\"]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<math::Rational>(3) );
}



BOOST_AUTO_TEST_SUITE_END()

