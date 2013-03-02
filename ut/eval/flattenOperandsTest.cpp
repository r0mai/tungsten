
#include <boost/test/unit_test.hpp>

#include "eval/flattenOperands.hpp"

BOOST_AUTO_TEST_SUITE( flattenOperandsTest )

using namespace tungsten;

BOOST_AUTO_TEST_CASE( empty_Operands_doesnt_change ) {
	ast::Operands operands = {};
	ast::Operands result = eval::flattenOperands( ast::Node::make<ast::Identifier>("f"), operands );

	BOOST_CHECK(result.empty());
}

BOOST_AUTO_TEST_CASE( Operands_with_neutral_operands_doesnt_change ) {
	ast::Operands operands = { ast::Node::make<math::Rational>(-2), ast::Node::make<ast::String>("abc") };
	ast::Operands result = eval::flattenOperands( ast::Node::make<ast::Identifier>("f"), operands );

	BOOST_CHECK(result == operands);
}

BOOST_AUTO_TEST_CASE( Operands_with_nontarget_Head_operand_doesnt_change ) {
	ast::Operands operands = { ast::Node::make<ast::FunctionCall>("g", {ast::Node::make<math::Rational>(-2)}), ast::Node::make<ast::String>("abc") };
	ast::Operands result = eval::flattenOperands( ast::Node::make<ast::Identifier>("f"), operands );

	BOOST_CHECK(result == operands);
}

BOOST_AUTO_TEST_CASE( Operands_with_single_target_Head_flattens ) {
	ast::Operands operands = { ast::Node::make<ast::FunctionCall>("f", {ast::Node::make<math::Rational>(-2)}) };
	ast::Operands result = eval::flattenOperands( ast::Node::make<ast::Identifier>("f"), operands );

	BOOST_CHECK(result == ast::Operands({ast::Node::make<math::Rational>(-2)}));
}

BOOST_AUTO_TEST_CASE( Operands_with_multiple_target_Heads_flattens ) {
	ast::Operands operands = { ast::Node::make<ast::FunctionCall>("f", {ast::Node::make<math::Rational>(-2)}), ast::Node::make<ast::FunctionCall>("f", {ast::Node::make<math::Rational>(-5)}) };
	ast::Operands result = eval::flattenOperands( ast::Node::make<ast::Identifier>("f"), operands );

	BOOST_CHECK(result == ast::Operands({ast::Node::make<math::Rational>(-2), ast::Node::make<math::Rational>(-5)}));
}

BOOST_AUTO_TEST_CASE( Operands_with_mixed_arguments_flattens ) {
	ast::Operands operands = { ast::Node::make<ast::FunctionCall>("f", {ast::Node::make<math::Rational>(-2)}), ast::Node::make<ast::String>("abc"), ast::Node::make<ast::FunctionCall>("f", {ast::Node::make<math::Rational>(-5)}) };
	ast::Operands result = eval::flattenOperands( ast::Node::make<ast::Identifier>("f"), operands );

	BOOST_CHECK(result == ast::Operands({ast::Node::make<math::Rational>(-2), ast::Node::make<ast::String>("abc"), ast::Node::make<math::Rational>(-5)}));
}

BOOST_AUTO_TEST_CASE( Operands_with_2_depth_flattens ) {
	ast::Operands operands = { ast::Node::make<ast::FunctionCall>("f", {ast::Node::make<ast::FunctionCall>("f", {ast::Node::make<math::Rational>(-2)})}), ast::Node::make<ast::String>("abc"), ast::Node::make<ast::FunctionCall>("f", {ast::Node::make<math::Rational>(-5)}) };
	ast::Operands result = eval::flattenOperands( ast::Node::make<ast::Identifier>("f"), operands );

	BOOST_CHECK(result == ast::Operands({ast::Node::make<math::Rational>(-2), ast::Node::make<ast::String>("abc"), ast::Node::make<math::Rational>(-5)}));
}

BOOST_AUTO_TEST_SUITE_END()
