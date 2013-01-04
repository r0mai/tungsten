
#include <boost/test/unit_test.hpp>

#include "eval/flattenOperands.hpp"

BOOST_AUTO_TEST_SUITE( flattenOperandsTest )

using namespace tungsten;

BOOST_AUTO_TEST_CASE( empty_Operands_doesnt_change ) {
	ast::Operands operands = {};
	ast::Operands result = eval::flattenOperands( "f", operands );

	BOOST_CHECK(result.empty());
}

BOOST_AUTO_TEST_CASE( Operands_with_neutral_operands_doesnt_change ) {
	ast::Operands operands = { ast::Node::makeRational(-2), ast::Node::makeString("abc") };
	ast::Operands result = eval::flattenOperands( "f", operands );

	BOOST_CHECK(result == operands);
}

BOOST_AUTO_TEST_CASE( Operands_with_nontarget_Head_operand_doesnt_change ) {
	ast::Operands operands = { ast::Node::makeFunctionCall("g", {ast::Node::makeRational(-2)}), ast::Node::makeString("abc") };
	ast::Operands result = eval::flattenOperands( "f", operands );

	BOOST_CHECK(result == operands);
}

BOOST_AUTO_TEST_CASE( Operands_with_single_target_Head_flattens ) {
	ast::Operands operands = { ast::Node::makeFunctionCall("f", {ast::Node::makeRational(-2)}) };
	ast::Operands result = eval::flattenOperands( "f", operands );

	BOOST_CHECK(result == ast::Operands({ast::Node::makeRational(-2)}));
}

BOOST_AUTO_TEST_CASE( Operands_with_multiple_target_Heads_flattens ) {
	ast::Operands operands = { ast::Node::makeFunctionCall("f", {ast::Node::makeRational(-2)}), ast::Node::makeFunctionCall("f", {ast::Node::makeRational(-5)}) };
	ast::Operands result = eval::flattenOperands( "f", operands );

	BOOST_CHECK(result == ast::Operands({ast::Node::makeRational(-2), ast::Node::makeRational(-5)}));
}

BOOST_AUTO_TEST_CASE( Operands_with_mixed_arguments_flattens ) {
	ast::Operands operands = { ast::Node::makeFunctionCall("f", {ast::Node::makeRational(-2)}), ast::Node::makeString("abc"), ast::Node::makeFunctionCall("f", {ast::Node::makeRational(-5)}) };
	ast::Operands result = eval::flattenOperands( "f", operands );

	BOOST_CHECK(result == ast::Operands({ast::Node::makeRational(-2), ast::Node::makeString("abc"), ast::Node::makeRational(-5)}));
}

BOOST_AUTO_TEST_CASE( Operands_with_2_depth_flattens ) {
	ast::Operands operands = { ast::Node::makeFunctionCall("f", {ast::Node::makeFunctionCall("f", {ast::Node::makeRational(-2)})}), ast::Node::makeString("abc"), ast::Node::makeFunctionCall("f", {ast::Node::makeRational(-5)}) };
	ast::Operands result = eval::flattenOperands( "f", operands );

	BOOST_CHECK(result == ast::Operands({ast::Node::makeRational(-2), ast::Node::makeString("abc"), ast::Node::makeRational(-5)}));
}

BOOST_AUTO_TEST_SUITE_END()
