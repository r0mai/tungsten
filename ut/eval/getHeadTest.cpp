
#include <boost/test/unit_test.hpp>

#include "eval/getHead.hpp"

BOOST_AUTO_TEST_SUITE( getHeadTest )

using namespace tungsten;

BOOST_AUTO_TEST_CASE( getHead_on_Integer ) {
	BOOST_CHECK_EQUAL(
			eval::getHead( ast::Node::make<math::Rational>(5) ),
			ast::Node::make<ast::Identifier>("Integer") );
}

BOOST_AUTO_TEST_CASE( getHead_on_Rational ) {
	BOOST_CHECK_EQUAL(
			eval::getHead( ast::Node::make<math::Rational>(5, 3) ),
			ast::Node::make<ast::Identifier>("Rational") );
}

BOOST_AUTO_TEST_CASE( getHead_on_Real ) {
	BOOST_CHECK_EQUAL(
			eval::getHead( ast::Node::make<math::Real>(1.2) ),
			ast::Node::make<ast::Identifier>("Real") );
}

BOOST_AUTO_TEST_CASE( getHead_on_Symbol ) {
	BOOST_CHECK_EQUAL(
			eval::getHead( ast::Node::make<ast::Identifier>("x") ),
			ast::Node::make<ast::Identifier>("Symbol") );
}

BOOST_AUTO_TEST_CASE( getHead_on_String ) {
	BOOST_CHECK_EQUAL(
			eval::getHead( ast::Node::make<ast::String>("x") ),
			ast::Node::make<ast::Identifier>("String") );
}

BOOST_AUTO_TEST_CASE( getHead_on_FunctionCall_with_Identifier_function ) {
	BOOST_CHECK_EQUAL(
			eval::getHead( ast::Node::make<ast::FunctionCall>("f", {}) ),
			ast::Node::make<ast::Identifier>("f") );
}

BOOST_AUTO_TEST_CASE( getHead_on_FunctionCall_with_non_Identifier_function ) {
	BOOST_CHECK_EQUAL( //f[][]
			eval::getHead( ast::Node::make<ast::FunctionCall>(ast::Node::make<ast::FunctionCall>("f")) ),
			ast::Node::make<ast::FunctionCall>("f", {}) );
}

BOOST_AUTO_TEST_SUITE_END()






