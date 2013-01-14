
#include <boost/test/unit_test.hpp>

#include "builtin/Fixture.hpp"

BOOST_AUTO_TEST_SUITE( ListableTest )

using namespace tungsten;


BOOST_FIXTURE_TEST_CASE( test_listable_of_no_arguments , BuiltinFunctionFixture ) {

	addAttribute("listable", "Listable");

	ast::Node result = evaluate(ast::Node::make<ast::FunctionCall>("listable", {}));

	ast::Node expected = evaluate(ast::Node::make<ast::FunctionCall>("listable", {}));

	BOOST_CHECK_EQUAL( result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_listable_of_x , BuiltinFunctionFixture ) {

	addAttribute("listable", "Listable");

	ast::Node result = evaluate(ast::Node::make<ast::FunctionCall>("listable", {ast::Node::make<ast::Identifier>("x")}));

	ast::Node expected = evaluate(ast::Node::make<ast::FunctionCall>("listable", {ast::Node::make<ast::Identifier>("x")}));

	BOOST_CHECK_EQUAL( result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_listable_of_x_and_y , BuiltinFunctionFixture ) {

	addAttribute("listable", "Listable");

	ast::Node result = evaluate(ast::Node::make<ast::FunctionCall>("listable", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::Identifier>("y")}));

	ast::Node expected = evaluate(ast::Node::make<ast::FunctionCall>("listable", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::Identifier>("y")}));

	BOOST_CHECK_EQUAL( result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_listable_of_x__y_and_z , BuiltinFunctionFixture ) {

	addAttribute("listable", "Listable");

	ast::Node result = evaluate(ast::Node::make<ast::FunctionCall>("listable", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::Identifier>("y"), ast::Node::make<ast::Identifier>("z")}));

	ast::Node expected = evaluate(ast::Node::make<ast::FunctionCall>("listable", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::Identifier>("y"), ast::Node::make<ast::Identifier>("z")}));

	BOOST_CHECK_EQUAL( result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_listable_of_an_empty_list , BuiltinFunctionFixture ) {

	addAttribute("listable", "Listable");

	ast::Node result = evaluate(ast::Node::make<ast::FunctionCall>("listable", {ast::Node::make<ast::FunctionCall>("List", {})}));

	ast::Node expected = evaluate(ast::Node::make<ast::FunctionCall>("List", {}));

	BOOST_CHECK_EQUAL( result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_listable_of_the_list_x , BuiltinFunctionFixture ) {

	addAttribute("listable", "Listable");

	ast::Node result = evaluate(ast::Node::make<ast::FunctionCall>("listable", {ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("x")})}));

	ast::Node expected = evaluate(ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::FunctionCall>("listable", {ast::Node::make<ast::Identifier>("x")})}));

	BOOST_CHECK_EQUAL( result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_listable_of_the_list_x__y , BuiltinFunctionFixture ) {

	addAttribute("listable", "Listable");

	ast::Node result = evaluate(ast::Node::make<ast::FunctionCall>("listable", {ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::Identifier>("y")})}));

	ast::Node expected = evaluate(ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::FunctionCall>("listable", {ast::Node::make<ast::Identifier>("x")}), ast::Node::make<ast::FunctionCall>("listable", {ast::Node::make<ast::Identifier>("y")})}));

	BOOST_CHECK_EQUAL( result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_listable_of_the_list_x__y_and_z , BuiltinFunctionFixture ) {

	addAttribute("listable", "Listable");

	ast::Node result = evaluate(ast::Node::make<ast::FunctionCall>("listable", {ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::Identifier>("y")}), ast::Node::make<ast::Identifier>("z")}));

	ast::Node expected = evaluate(ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::FunctionCall>("listable", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::Identifier>("z")}), ast::Node::make<ast::FunctionCall>("listable", {ast::Node::make<ast::Identifier>("y"), ast::Node::make<ast::Identifier>("z")})}));

	BOOST_CHECK_EQUAL( result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_listable_of_x_and_the_list_y__z , BuiltinFunctionFixture ) {

	addAttribute("listable", "Listable");

	ast::Node result = evaluate(ast::Node::make<ast::FunctionCall>("listable", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("y"), ast::Node::make<ast::Identifier>("z")})}));

	ast::Node expected = evaluate(ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::FunctionCall>("listable", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::Identifier>("y")}), ast::Node::make<ast::FunctionCall>("listable", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::Identifier>("z")})}));

	BOOST_CHECK_EQUAL( result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_listable_of_x__the_list_y_and_z , BuiltinFunctionFixture ) {

	addAttribute("listable", "Listable");

	ast::Node result = evaluate(ast::Node::make<ast::FunctionCall>("listable", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("y")}), ast::Node::make<ast::Identifier>("z")}));

	ast::Node expected = evaluate(ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::FunctionCall>("listable", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::Identifier>("y"), ast::Node::make<ast::Identifier>("z")})}));

	BOOST_CHECK_EQUAL( result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_listable_of_the_list_a__b_and_the_list_x__y , BuiltinFunctionFixture ) {

	addAttribute("listable", "Listable");

	ast::Node result = evaluate(ast::Node::make<ast::FunctionCall>("listable", {ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("a"), ast::Node::make<ast::Identifier>("b")}), ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::Identifier>("y")})}));

	ast::Node expected = evaluate(ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::FunctionCall>("listable", {ast::Node::make<ast::Identifier>("a"), ast::Node::make<ast::Identifier>("x")}), ast::Node::make<ast::FunctionCall>("listable", {ast::Node::make<ast::Identifier>("b"), ast::Node::make<ast::Identifier>("y")})}));

	BOOST_CHECK_EQUAL( result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_listable_of_the_list_a__b__g_and_the_list_x__y , BuiltinFunctionFixture ) {

	addAttribute("listable", "Listable");

	ast::Node result = evaluate(ast::Node::make<ast::FunctionCall>("listable", {ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("a"), ast::Node::make<ast::Identifier>("b")}), ast::Node::make<ast::Identifier>("g"), ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::Identifier>("y")})}));

	ast::Node expected = evaluate(ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::FunctionCall>("listable", {ast::Node::make<ast::Identifier>("a"), ast::Node::make<ast::Identifier>("g"), ast::Node::make<ast::Identifier>("x")}), ast::Node::make<ast::FunctionCall>("listable", {ast::Node::make<ast::Identifier>("b"), ast::Node::make<ast::Identifier>("g"), ast::Node::make<ast::Identifier>("y")})}));

	BOOST_CHECK_EQUAL( result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_listable_of_a__the_list_g__f_and_the_list_x__y , BuiltinFunctionFixture ) {

	addAttribute("listable", "Listable");

	ast::Node result = evaluate(ast::Node::make<ast::FunctionCall>("listable", {ast::Node::make<ast::Identifier>("a"), ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("g"), ast::Node::make<ast::Identifier>("f")}), ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::Identifier>("y")})}));

	ast::Node expected = evaluate(ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::FunctionCall>("listable", {ast::Node::make<ast::Identifier>("a"), ast::Node::make<ast::Identifier>("g"), ast::Node::make<ast::Identifier>("x")}), ast::Node::make<ast::FunctionCall>("listable", {ast::Node::make<ast::Identifier>("a"), ast::Node::make<ast::Identifier>("f"), ast::Node::make<ast::Identifier>("y")})}));

	BOOST_CHECK_EQUAL( result, expected );
}


BOOST_FIXTURE_TEST_CASE( test_listable_of_the_list_a__b__c__the_list_f__g__h_and_the_list_x__y__z , BuiltinFunctionFixture ) {

	addAttribute("listable", "Listable");

	ast::Node result = evaluate(ast::Node::make<ast::FunctionCall>("listable", {ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("a"), ast::Node::make<ast::Identifier>("b"), ast::Node::make<ast::Identifier>("c")}), ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("f"), ast::Node::make<ast::Identifier>("g"), ast::Node::make<ast::Identifier>("h")}), ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::Identifier>("x"), ast::Node::make<ast::Identifier>("y"), ast::Node::make<ast::Identifier>("z")})}));

	ast::Node expected = evaluate(ast::Node::make<ast::FunctionCall>("List", {ast::Node::make<ast::FunctionCall>("listable", {ast::Node::make<ast::Identifier>("a"), ast::Node::make<ast::Identifier>("f"), ast::Node::make<ast::Identifier>("x")}), ast::Node::make<ast::FunctionCall>("listable", {ast::Node::make<ast::Identifier>("b"), ast::Node::make<ast::Identifier>("g"), ast::Node::make<ast::Identifier>("y")}), ast::Node::make<ast::FunctionCall>("listable", {ast::Node::make<ast::Identifier>("c"), ast::Node::make<ast::Identifier>("h"), ast::Node::make<ast::Identifier>("z")})}));

	BOOST_CHECK_EQUAL( result, expected );
}




BOOST_AUTO_TEST_SUITE_END()
