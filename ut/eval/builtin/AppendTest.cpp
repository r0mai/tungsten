
#include <boost/test/unit_test.hpp>

#include "Fixture.hpp"

BOOST_AUTO_TEST_SUITE( AppendTest )

using namespace tungsten;

BOOST_FIXTURE_TEST_CASE( test_Append_of_an_empty_list_and_x, BuiltinFunctionFixture ) {
		boost::optional<ast::Node> result = parseAndEvaluate("Append[{}, x]");

			BOOST_REQUIRE( result );

				ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("x")});

					BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Prepend_of_an_empty_list_and_x, BuiltinFunctionFixture ) {
		boost::optional<ast::Node> result = parseAndEvaluate("Prepend[{}, x]");

			BOOST_REQUIRE( result );

				ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("x")});

					BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Append_of_the_list_a_and_x, BuiltinFunctionFixture ) {
		boost::optional<ast::Node> result = parseAndEvaluate("Append[{a}, x]");

			BOOST_REQUIRE( result );

				ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("a"), ast::Node::make<ast::Identifier>("x")});

					BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Prepend_of_the_list_a_and_x, BuiltinFunctionFixture ) {
		boost::optional<ast::Node> result = parseAndEvaluate("Prepend[{a}, x]");

			BOOST_REQUIRE( result );

				ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::Identifier>("a")});

					BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Append_of_the_list_a__b_and_x, BuiltinFunctionFixture ) {
		boost::optional<ast::Node> result = parseAndEvaluate("Append[{a, b}, x]");

			BOOST_REQUIRE( result );

				ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("a"), ast::Node::make<ast::Identifier>("b"), ast::Node::make<ast::Identifier>("x")});

					BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_Prepend_of_the_list_a__b_and_x, BuiltinFunctionFixture ) {
		boost::optional<ast::Node> result = parseAndEvaluate("Prepend[{a, b}, x]");

			BOOST_REQUIRE( result );

				ast::Node expected = ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::Identifier>("a"), ast::Node::make<ast::Identifier>("b")});

					BOOST_CHECK_EQUAL( *result, expected );
}


BOOST_AUTO_TEST_SUITE_END()

