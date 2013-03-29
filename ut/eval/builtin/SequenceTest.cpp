
#include <boost/test/unit_test.hpp>

#include "Fixture.hpp"

BOOST_AUTO_TEST_SUITE( SequenceTest )

using namespace tungsten;


BOOST_FIXTURE_TEST_CASE( test_f_of_Sequence_of_x_and_y , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("f[Sequence[x, y]]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::FunctionCall>("f", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::Identifier>("y")}) );
}


BOOST_FIXTURE_TEST_CASE( test_f_of_Sequence_of_x , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("f[Sequence[x]]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::FunctionCall>("f", {ast::Node::make<ast::Identifier>("x")}) );
}


BOOST_FIXTURE_TEST_CASE( test_f_of_Sequence_of_no_arguments , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("f[Sequence[]]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::FunctionCall>("f", {}) );
}


BOOST_FIXTURE_TEST_CASE( test_f_of_Sequence_of_no_arguments_and_x , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("f[Sequence[], x]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::FunctionCall>("f", {ast::Node::make<ast::Identifier>("x")}) );
}


BOOST_FIXTURE_TEST_CASE( test_f_of_x_and_Sequence_of_no_arguments , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("f[x, Sequence[]]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::FunctionCall>("f", {ast::Node::make<ast::Identifier>("x")}) );
}


BOOST_FIXTURE_TEST_CASE( test_f_of_x__Sequence_of_y_and_z , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("f[x, Sequence[y], z]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::FunctionCall>("f", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::Identifier>("y"), ast::Node::make<ast::Identifier>("z")}) );
}


BOOST_FIXTURE_TEST_CASE( test_f_of_x__Sequence_of_y_and_z_and_w , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("f[x, Sequence[y, z], w]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::FunctionCall>("f", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::Identifier>("y"), ast::Node::make<ast::Identifier>("z"), ast::Node::make<ast::Identifier>("w")}) );
}


BOOST_FIXTURE_TEST_CASE( test_f_of_x_and_Sequence_of_y_and_z , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("f[x, Sequence[y, z]]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::FunctionCall>("f", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::Identifier>("y"), ast::Node::make<ast::Identifier>("z")}) );
}


BOOST_FIXTURE_TEST_CASE( test_f_of_Sequence_of_x_and_y_and_z , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("f[Sequence[x, y], z]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::FunctionCall>("f", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::Identifier>("y"), ast::Node::make<ast::Identifier>("z")}) );
}



BOOST_FIXTURE_TEST_CASE( test_f_of_Sequence_of_x_and_y_with_SequenceHold, BuiltinFunctionFixture ) {

	addAttribute("f", "SequenceHold");

	boost::optional<ast::Node> result = parseAndEvaluate("f[Sequence[x, y]]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::FunctionCall>("f", {ast::Node::make<ast::FunctionCall>("Sequence", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::Identifier>("y")})}) );
}


BOOST_FIXTURE_TEST_CASE( test_f_of_Sequence_of_x_with_SequenceHold, BuiltinFunctionFixture ) {

	addAttribute("f", "SequenceHold");

	boost::optional<ast::Node> result = parseAndEvaluate("f[Sequence[x]]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::FunctionCall>("f", {ast::Node::make<ast::FunctionCall>("Sequence", {ast::Node::make<ast::Identifier>("x")})}) );
}


BOOST_FIXTURE_TEST_CASE( test_f_of_Sequence_of_no_arguments_with_SequenceHold, BuiltinFunctionFixture ) {

	addAttribute("f", "SequenceHold");

	boost::optional<ast::Node> result = parseAndEvaluate("f[Sequence[]]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::FunctionCall>("f", {ast::Node::make<ast::FunctionCall>("Sequence", {})}) );
}


BOOST_FIXTURE_TEST_CASE( test_f_of_Sequence_of_no_arguments_and_x_with_SequenceHold, BuiltinFunctionFixture ) {

	addAttribute("f", "SequenceHold");

	boost::optional<ast::Node> result = parseAndEvaluate("f[Sequence[], x]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::FunctionCall>("f", {ast::Node::make<ast::FunctionCall>("Sequence", {}), ast::Node::make<ast::Identifier>("x")}) );
}


BOOST_FIXTURE_TEST_CASE( test_f_of_x_and_Sequence_of_no_arguments_with_SequenceHold, BuiltinFunctionFixture ) {

	addAttribute("f", "SequenceHold");

	boost::optional<ast::Node> result = parseAndEvaluate("f[x, Sequence[]]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::FunctionCall>("f", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::FunctionCall>("Sequence", {})}) );
}


BOOST_FIXTURE_TEST_CASE( test_f_of_x__Sequence_of_y_and_z_with_SequenceHold, BuiltinFunctionFixture ) {

	addAttribute("f", "SequenceHold");

	boost::optional<ast::Node> result = parseAndEvaluate("f[x, Sequence[y], z]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::FunctionCall>("f", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::FunctionCall>("Sequence", {ast::Node::make<ast::Identifier>("y")}), ast::Node::make<ast::Identifier>("z")}) );
}


BOOST_FIXTURE_TEST_CASE( test_f_of_x__Sequence_of_y_and_z_and_w_with_SequenceHold, BuiltinFunctionFixture ) {

	addAttribute("f", "SequenceHold");

	boost::optional<ast::Node> result = parseAndEvaluate("f[x, Sequence[y, z], w]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::FunctionCall>("f", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::FunctionCall>("Sequence", {ast::Node::make<ast::Identifier>("y"), ast::Node::make<ast::Identifier>("z")}), ast::Node::make<ast::Identifier>("w")}) );
}


BOOST_FIXTURE_TEST_CASE( test_f_of_x_and_Sequence_of_y_and_z_with_SequenceHold, BuiltinFunctionFixture ) {

	addAttribute("f", "SequenceHold");

	boost::optional<ast::Node> result = parseAndEvaluate("f[x, Sequence[y, z]]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::FunctionCall>("f", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::FunctionCall>("Sequence", {ast::Node::make<ast::Identifier>("y"), ast::Node::make<ast::Identifier>("z")})}) );
}


BOOST_FIXTURE_TEST_CASE( test_f_of_Sequence_of_x_and_y_and_z_with_SequenceHold, BuiltinFunctionFixture ) {

	addAttribute("f", "SequenceHold");

	boost::optional<ast::Node> result = parseAndEvaluate("f[Sequence[x, y], z]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::FunctionCall>("f", {ast::Node::make<ast::FunctionCall>("Sequence", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::Identifier>("y")}), ast::Node::make<ast::Identifier>("z")}) );
}

BOOST_AUTO_TEST_SUITE_END()

