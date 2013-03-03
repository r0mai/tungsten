
#include <boost/test/unit_test.hpp>

#include "Fixture.hpp"

BOOST_AUTO_TEST_SUITE( HeadTest )

using namespace tungsten;

BOOST_FIXTURE_TEST_CASE( test_Flatten_of_the_list_x , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Flatten[{x}]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("x")}) );
}


BOOST_FIXTURE_TEST_CASE( test_Flatten_of_the_list_x__the_list_y , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Flatten[{x, {y}}]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::Identifier>("y")}) );
}


BOOST_FIXTURE_TEST_CASE( test_Flatten_of_the_list_the_list_x , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Flatten[{{x}}]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("x")}) );
}


BOOST_FIXTURE_TEST_CASE( test_Flatten_of_the_list_the_list_a__b__the_list_c__the_list_d__e__the_list_f__the_list_g__h , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Flatten[{{a, b}, {c, {d}, e}, {f, {g, h}}}]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("a"), ast::Node::make<ast::Identifier>("b"), ast::Node::make<ast::Identifier>("c"), ast::Node::make<ast::Identifier>("d"), ast::Node::make<ast::Identifier>("e"), ast::Node::make<ast::Identifier>("f"), ast::Node::make<ast::Identifier>("g"), ast::Node::make<ast::Identifier>("h")}) );
}


BOOST_FIXTURE_TEST_CASE( test_Flatten_of_the_list_the_list_a__b__the_list_c__the_list_d__e__the_list_f__the_list_g__h_and_1 , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Flatten[{{a, b}, {c, {d}, e}, {f, {g, h}}}, 1]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("a"), ast::Node::make<ast::Identifier>("b"), ast::Node::make<ast::Identifier>("c"), ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("d")}), ast::Node::make<ast::Identifier>("e"), ast::Node::make<ast::Identifier>("f"), ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("g"), ast::Node::make<ast::Identifier>("h")})}) );
}


BOOST_FIXTURE_TEST_CASE( test_Flatten_of_the_list_0__the_list_1__the_list_the_list_2__minus_2__the_list_the_list_the_list_3__the_list_minus_3__the_list_the_list_the_list_the_list_4_and_0 , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Flatten[{0, {1}, {{2, -2}}, {{{3}, {-3}}}, {{{{4}}}}}, 0]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<math::Rational>(0), ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<math::Rational>(1)}), ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<math::Rational>(2), ast::Node::make<math::Rational>(-2)})}), ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<math::Rational>(3)}), ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<math::Rational>(-3)})})}), ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<math::Rational>(4)})})})})}) );
}


BOOST_FIXTURE_TEST_CASE( test_Flatten_of_the_list_0__the_list_1__the_list_the_list_2__minus_2__the_list_the_list_the_list_3__the_list_minus_3__the_list_the_list_the_list_the_list_4_and_1 , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Flatten[{0, {1}, {{2, -2}}, {{{3}, {-3}}}, {{{{4}}}}}, 1]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<math::Rational>(0), ast::Node::make<math::Rational>(1), ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<math::Rational>(2), ast::Node::make<math::Rational>(-2)}), ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<math::Rational>(3)}), ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<math::Rational>(-3)})}), ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<math::Rational>(4)})})})}) );
}


BOOST_FIXTURE_TEST_CASE( test_Flatten_of_the_list_0__the_list_1__the_list_the_list_2__minus_2__the_list_the_list_the_list_3__the_list_minus_3__the_list_the_list_the_list_the_list_4_and_2 , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Flatten[{0, {1}, {{2, -2}}, {{{3}, {-3}}}, {{{{4}}}}}, 2]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<math::Rational>(0), ast::Node::make<math::Rational>(1), ast::Node::make<math::Rational>(2), ast::Node::make<math::Rational>(-2), ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<math::Rational>(3)}), ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<math::Rational>(-3)}), ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<math::Rational>(4)})})}) );
}


BOOST_FIXTURE_TEST_CASE( test_Flatten_of_the_list_0__the_list_1__the_list_the_list_2__minus_2__the_list_the_list_the_list_3__the_list_minus_3__the_list_the_list_the_list_the_list_4_and_3 , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Flatten[{0, {1}, {{2, -2}}, {{{3}, {-3}}}, {{{{4}}}}}, 3]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<math::Rational>(0), ast::Node::make<math::Rational>(1), ast::Node::make<math::Rational>(2), ast::Node::make<math::Rational>(-2), ast::Node::make<math::Rational>(3), ast::Node::make<math::Rational>(-3), ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<math::Rational>(4)})}) );
}


BOOST_FIXTURE_TEST_CASE( test_Flatten_of_the_list_0__the_list_1__the_list_the_list_2__minus_2__the_list_the_list_the_list_3__the_list_minus_3__the_list_the_list_the_list_the_list_4_and_4 , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Flatten[{0, {1}, {{2, -2}}, {{{3}, {-3}}}, {{{{4}}}}}, 4]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<math::Rational>(0), ast::Node::make<math::Rational>(1), ast::Node::make<math::Rational>(2), ast::Node::make<math::Rational>(-2), ast::Node::make<math::Rational>(3), ast::Node::make<math::Rational>(-3), ast::Node::make<math::Rational>(4)}) );
}


BOOST_FIXTURE_TEST_CASE( test_Flatten_of_f_of_f_of_x_and_y_and_z , BuiltinFunctionFixture ) {
	boost::optional<ast::Node> result = parseAndEvaluate("Flatten[f[f[x, y], z]]");

	BOOST_REQUIRE( result );

	BOOST_CHECK_EQUAL( *result,ast::Node::make<ast::FunctionCall>("f", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::Identifier>("y"), ast::Node::make<ast::Identifier>("z")}) );
}

BOOST_AUTO_TEST_SUITE_END()
