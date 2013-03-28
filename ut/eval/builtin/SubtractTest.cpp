
#include <boost/test/unit_test.hpp>

#include "Fixture.hpp"

BOOST_AUTO_TEST_SUITE( SubtractTest )

using namespace tungsten;

BOOST_FIXTURE_TEST_CASE( test_Subtract_of_x_and_y , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("x - y");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::FunctionCall>("Plus", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<math::Rational>(-1), ast::Node::make<ast::Identifier>("y")})}) );
}


BOOST_FIXTURE_TEST_CASE( test_Subtract_of_3_and_2 , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("3 - 2");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<math::Rational>(1) );
}


BOOST_FIXTURE_TEST_CASE( test_Subtract_of_3_0_and_2 , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("3. - 2");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<math::Real>(1.) );
}


BOOST_FIXTURE_TEST_CASE( test_Subtract_of_3_and_2_0 , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("3 - 2.");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<math::Real>(1.) );
}


BOOST_FIXTURE_TEST_CASE( test_Subtract_of_3_0_and_2_0 , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("3. - 2.");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<math::Real>(1.) );
}


BOOST_FIXTURE_TEST_CASE( test_Subtract_of_x_and_x , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("x - x");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<math::Rational>(0) );
}


BOOST_FIXTURE_TEST_CASE( test_Subtract_of_the_list_a__b_and_the_list_c__d , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("{a, b} - {c, d}");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result, ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::FunctionCall>("Plus", {ast::Node::make<ast::Identifier>("a"), ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<math::Rational>(-1), ast::Node::make<ast::Identifier>("c")})}), ast::Node::make<ast::FunctionCall>("Plus", {ast::Node::make<ast::Identifier>("b"), ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<math::Rational>(-1), ast::Node::make<ast::Identifier>("d")})})}) );
}

//---- Same as above, but with explicit Subtract


BOOST_FIXTURE_TEST_CASE( test_Subtract_of_x_and_y_explicit , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Subtract[x, y]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::FunctionCall>("Plus", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<math::Rational>(-1), ast::Node::make<ast::Identifier>("y")})}) );
}


BOOST_FIXTURE_TEST_CASE( test_Subtract_of_3_and_2_explicit, BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Subtract[3, 2]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<math::Rational>(1) );
}


BOOST_FIXTURE_TEST_CASE( test_Subtract_of_3_0_and_2_explicit , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Subtract[3., 2]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<math::Real>(1.) );
}


BOOST_FIXTURE_TEST_CASE( test_Subtract_of_3_and_2_0_explicit , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Subtract[3, 2.]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<math::Real>(1.) );
}


BOOST_FIXTURE_TEST_CASE( test_Subtract_of_3_0_and_2_0_explicit , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Subtract[3., 2.]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<math::Real>(1.) );
}


BOOST_FIXTURE_TEST_CASE( test_Subtract_of_x_and_x_explicit , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Subtract[x, x]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<math::Rational>(0) );
}


BOOST_FIXTURE_TEST_CASE( test_Subtract_of_the_list_a__b_and_the_list_c__d_explicit , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Subtract[{a, b}, {c, d}]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result, ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::FunctionCall>("Plus", {ast::Node::make<ast::Identifier>("a"), ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<math::Rational>(-1), ast::Node::make<ast::Identifier>("c")})}), ast::Node::make<ast::FunctionCall>("Plus", {ast::Node::make<ast::Identifier>("b"), ast::Node::make<ast::FunctionCall>("Times", {ast::Node::make<math::Rational>(-1), ast::Node::make<ast::Identifier>("d")})})}) );
}

BOOST_AUTO_TEST_SUITE_END()



