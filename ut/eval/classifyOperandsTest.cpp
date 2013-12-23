
#include <boost/test/unit_test.hpp>

#include "eval/classifyOperands.hpp"
#include "ast/Node.hpp"

BOOST_AUTO_TEST_SUITE( classifyOperandsTest )

using namespace tungsten;

BOOST_AUTO_TEST_CASE( NumericalClassification_empty_operands_returns_ALL_RATIONAL_or_ALL_REAL ) {
	ast::Operands operands;

	eval::NumericalClassification classification = eval::classifyNumerically(operands);

	BOOST_CHECK( classification == eval::NumericalClassification::ALL_RATIONAL ||
			classification == eval::NumericalClassification::ALL_REAL );
}

BOOST_AUTO_TEST_CASE( NumericalClassification_HAS_SYMBOLIC_one_element_operands ) {
	ast::Operands operands = { ast::Node::make<ast::Identifier>("asdf") };

	BOOST_CHECK_EQUAL( eval::classifyNumerically(operands), eval::NumericalClassification::HAS_SYMBOLIC );
}

BOOST_AUTO_TEST_CASE( NumericalClassification_ALL_RATIONAL_one_element_operands ) {
	ast::Operands operands = { ast::Node::make<math::Rational>(1) };

	BOOST_CHECK_EQUAL( eval::classifyNumerically(operands), eval::NumericalClassification::ALL_RATIONAL );
}

BOOST_AUTO_TEST_CASE( NumericalClassification_ALL_REAL_one_element_operands ) {
	ast::Operands operands = { ast::Node::make<math::Real>(1.2) };

	BOOST_CHECK_EQUAL( eval::classifyNumerically(operands), eval::NumericalClassification::ALL_REAL );
}

BOOST_AUTO_TEST_CASE( NumericalClassification_ALL_NUMERICAL_test ) {
	ast::Operands operands = { ast::Node::make<math::Real>(1.2), ast::Node::make<math::Rational>(1) };

	BOOST_CHECK_EQUAL( eval::classifyNumerically(operands), eval::NumericalClassification::ALL_NUMERIC );
}

BOOST_AUTO_TEST_CASE( NumericalClassification_HAS_SYMBOLIC_multiple_operands_1 ) {
	ast::Operands operands = { ast::Node::make<math::Real>(1.2), ast::Node::make<math::Real>(1), ast::Node::make<ast::FunctionCall>("f") };

	BOOST_CHECK_EQUAL( eval::classifyNumerically(operands), eval::NumericalClassification::HAS_SYMBOLIC );
}

BOOST_AUTO_TEST_CASE( NumericalClassification_HAS_SYMBOLIC_multiple_operands_2 ) {
	ast::Operands operands = { ast::Node::make<ast::FunctionCall>("f"), ast::Node::make<math::Real>(1.2), ast::Node::make<math::Real>(1) };

	BOOST_CHECK_EQUAL( eval::classifyNumerically(operands), eval::NumericalClassification::HAS_SYMBOLIC );
}

BOOST_AUTO_TEST_CASE( NumericalClassification_HAS_SYMBOLIC_multiple_operands_3 ) {
	ast::Operands operands = { ast::Node::make<math::Real>(1.2), ast::Node::make<ast::String>("f"), ast::Node::make<math::Real>(1) };

	BOOST_CHECK_EQUAL( eval::classifyNumerically(operands), eval::NumericalClassification::HAS_SYMBOLIC );
}

BOOST_AUTO_TEST_CASE( NumericalClassification_ALL_RATIONAL_multiple_operands ) {
	ast::Operands operands = { ast::Node::make<math::Rational>(1), ast::Node::make<math::Rational>(2), ast::Node::make<math::Rational>(1) };

	BOOST_CHECK_EQUAL( eval::classifyNumerically(operands), eval::NumericalClassification::ALL_RATIONAL );
}

BOOST_AUTO_TEST_CASE( NumericalClassification_ALL_REAL_multiple_operands ) {
	ast::Operands operands = { ast::Node::make<math::Real>(1), ast::Node::make<math::Real>(2), ast::Node::make<math::Real>(1) };

	BOOST_CHECK_EQUAL( eval::classifyNumerically(operands), eval::NumericalClassification::ALL_REAL );
}

BOOST_AUTO_TEST_CASE( NumericalClassification_ALL_NUMERIC_multiple_operands ) {
	ast::Operands operands = { ast::Node::make<math::Real>(1), ast::Node::make<math::Rational>(2), ast::Node::make<math::Real>(1) };

	BOOST_CHECK_EQUAL( eval::classifyNumerically(operands), eval::NumericalClassification::ALL_NUMERIC );
}

BOOST_AUTO_TEST_SUITE_END()

