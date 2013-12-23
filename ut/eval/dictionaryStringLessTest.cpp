
#include <boost/test/unit_test.hpp>

#include "eval/orderNode.hpp"

BOOST_AUTO_TEST_SUITE( dictionaryStringLessTest )

using namespace tungsten;

BOOST_AUTO_TEST_CASE( test_dictionaryStringLess_1 ) {
	std::string x = "x";
	std::string y = "y";

	BOOST_CHECK(eval::dictionaryStringLess(x, y));
	BOOST_CHECK(!eval::dictionaryStringLess(y, x));
}

BOOST_AUTO_TEST_CASE( test_dictionaryStringLess_2 ) {
	std::string x = "x";
	std::string y = "x";

	BOOST_CHECK(!eval::dictionaryStringLess(x, y));
	BOOST_CHECK(!eval::dictionaryStringLess(y, x));
}

BOOST_AUTO_TEST_CASE( test_dictionaryStringLess_3 ) {
	std::string x = "x";
	std::string y = "xx";

	BOOST_CHECK(eval::dictionaryStringLess(x, y));
	BOOST_CHECK(!eval::dictionaryStringLess(y, x));
}

BOOST_AUTO_TEST_CASE( test_dictionaryStringLess_4 ) {
	std::string x = "x";
	std::string y = "X";

	BOOST_CHECK(eval::dictionaryStringLess(x, y));
	BOOST_CHECK(!eval::dictionaryStringLess(y, x));
}

BOOST_AUTO_TEST_CASE( test_dictionaryStringLess_5 ) {
	std::string x = "X";
	std::string y = "xx";

	BOOST_CHECK(eval::dictionaryStringLess(x, y));
	BOOST_CHECK(!eval::dictionaryStringLess(y, x));
}

BOOST_AUTO_TEST_CASE( test_dictionaryStringLess_6 ) {
	std::string x = "xx";
	std::string y = "XX";

	BOOST_CHECK(eval::dictionaryStringLess(x, y));
	BOOST_CHECK(!eval::dictionaryStringLess(y, x));
}

BOOST_AUTO_TEST_CASE( test_dictionaryStringLess_7 ) {
	std::string x = "1";
	std::string y = "a";

	BOOST_CHECK(eval::dictionaryStringLess(x, y));
	BOOST_CHECK(!eval::dictionaryStringLess(y, x));
}

BOOST_AUTO_TEST_SUITE_END();

