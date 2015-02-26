
#include <boost/test/unit_test.hpp>

#include "eval/Identifiers.hpp"
#include "eval/threadListableOperands.hpp"

BOOST_AUTO_TEST_SUITE( threadListableOperandsTest )

using namespace tungsten;

BOOST_AUTO_TEST_CASE( threading_not_applicable_on_empty_FunctionCall ) {
//	ThreadListableOperandsReturnType threadListableOperands(const ast::FunctionCall& functionCall,
//			ast::Operands& resultOperands,
//			const ast::Node& head = ast::Node::make<ast::Identifier>(ids::List));

	ast::Operands resultOperands;
	eval::ThreadListableOperandsReturnType returnValue = eval::threadListableOperands(
		ast::FunctionCall("f"),
		resultOperands,
		ast::Node::make<ast::Identifier>("g")
	);

	BOOST_REQUIRE( returnValue == eval::ThreadListableOperandsReturnType::NOT_APPLICABLE );

}

BOOST_AUTO_TEST_CASE( threading_successful_FunctionCall_with_empty_Head_inside ) {
//	ThreadListableOperandsReturnType threadListableOperands(const ast::FunctionCall& functionCall,
//			ast::Operands& resultOperands,
//			const ast::Node& head = ast::Node::make<ast::Identifier>(ids::List));

	ast::Operands resultOperands;
	eval::ThreadListableOperandsReturnType returnValue = eval::threadListableOperands(
		ast::FunctionCall("f", {ast::Node::make<ast::FunctionCall>("g")}),
		resultOperands,
		ast::Node::make<ast::Identifier>("g")
	);

	BOOST_REQUIRE( returnValue == eval::ThreadListableOperandsReturnType::SUCCESSFUL );

	BOOST_CHECK( resultOperands.empty() );
}

//TODO do more

BOOST_AUTO_TEST_CASE( isEvaluationOfNodeThreadSafe_should_be_true_for_reals ) {
	bool returnValue = eval::isEvaluationOfNodeThreadSafe(ast::Node::make<math::Real>(1));
	BOOST_CHECK( returnValue );
}

BOOST_AUTO_TEST_CASE( isEvaluationOfNodeThreadSafe_should_be_true_for_rationals ) {
	bool returnValue = eval::isEvaluationOfNodeThreadSafe(ast::Node::make<math::Rational>(1));
	BOOST_CHECK( returnValue );
}

BOOST_AUTO_TEST_CASE( isEvaluationOfNodeThreadSafe_should_be_true_for_strings ) {
	bool returnValue = eval::isEvaluationOfNodeThreadSafe(ast::Node::make<ast::String>("foobar"));
	BOOST_CHECK( returnValue );
}

BOOST_AUTO_TEST_CASE( isEvaluationOfNodeThreadSafe_should_be_true_for_identifiers ) {
	bool returnValue = eval::isEvaluationOfNodeThreadSafe(ast::Node::make<ast::Identifier>(eval::ids::Plus));
	BOOST_CHECK( returnValue );
}

BOOST_AUTO_TEST_SUITE_END()
