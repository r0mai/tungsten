
#include <boost/test/unit_test.hpp>

#include "Fixture.hpp"

BOOST_AUTO_TEST_SUITE( SequenceTest )

using namespace tungsten;

BOOST_FIXTURE_TEST_CASE( Sequence_doesnt_get_evaluated_if_its_on_top_with_no_parameters, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Sequence[]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result, ast::Node::make<ast::FunctionCall>("Sequence") );
}


BOOST_FIXTURE_TEST_CASE( Sequence_doesnt_get_evaluated_if_its_on_top_with_parameters, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Sequence[x,y]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result, ast::Node::make<ast::FunctionCall>("Sequence", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::Identifier>("y")} ) );
}


BOOST_FIXTURE_TEST_CASE( Sequence_as_the_only_parameter_to_a_function, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("f[Sequence[x,y]]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result, ast::Node::make<ast::FunctionCall>("f", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::Identifier>("y")} ) );
}


BOOST_FIXTURE_TEST_CASE( Sequence_as_a_prefix_to_function_parameters, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("f[Sequence[x,y], z]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result, ast::Node::make<ast::FunctionCall>("f", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::Identifier>("y"), ast::Node::make<ast::Identifier>("z")} ) );
}


BOOST_FIXTURE_TEST_CASE( Sequence_as_an_infix_to_function_parameters, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("f[a, Sequence[x,y], z]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result, ast::Node::make<ast::FunctionCall>("f", {ast::Node::make<ast::Identifier>("a"), ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::Identifier>("y"), ast::Node::make<ast::Identifier>("z")} ) );
}


BOOST_FIXTURE_TEST_CASE( Sequence_as_a_postfix_to_function_parameters, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("f[x, Sequence[y, z]]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result, ast::Node::make<ast::FunctionCall>("f", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::Identifier>("y"), ast::Node::make<ast::Identifier>("z")} ) );
}


BOOST_FIXTURE_TEST_CASE( empty_Sequence_as_the_only_parameter_to_a_function, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("f[Sequence[]]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result, ast::Node::make<ast::FunctionCall>("f") );
}


BOOST_FIXTURE_TEST_CASE( empty_Sequence_as_a_prefix_to_function_parameters, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("f[Sequence[], z]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result, ast::Node::make<ast::FunctionCall>("f", {ast::Node::make<ast::Identifier>("z")} ) );
}


BOOST_FIXTURE_TEST_CASE( empty_Sequence_as_an_infix_to_function_parameters, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("f[a, Sequence[], z]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result, ast::Node::make<ast::FunctionCall>("f", {ast::Node::make<ast::Identifier>("a"), ast::Node::make<ast::Identifier>("z")} ) );
}


BOOST_FIXTURE_TEST_CASE( empty_Sequence_as_a_postfix_to_function_parameters, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("f[x, Sequence[]]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result, ast::Node::make<ast::FunctionCall>("f", {ast::Node::make<ast::Identifier>("x")} ) );
}



BOOST_AUTO_TEST_SUITE_END()

