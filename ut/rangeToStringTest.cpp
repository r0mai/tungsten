
#include <boost/test/unit_test.hpp>

#include "../src/rangeToString.hpp"

BOOST_AUTO_TEST_SUITE( rangeToStringTest )

using namespace tungsten;

BOOST_AUTO_TEST_CASE( empty_range_prints_nothing ) {
	BOOST_CHECK_EQUAL( "", rangeToString(std::vector<int>(), ", ") );
}

BOOST_AUTO_TEST_CASE( single_element_range_prints_no_separator ) {
	BOOST_CHECK_EQUAL( "1", rangeToString(std::vector<int>{{1}}, ", ") );
}

BOOST_AUTO_TEST_CASE( multiple_element_range_test_1 ) {
	BOOST_CHECK_EQUAL( "1, 2", rangeToString(std::vector<int>{{1, 2}}, ", ") );
}

BOOST_AUTO_TEST_CASE( multiple_element_range_test_2 ) {
	BOOST_CHECK_EQUAL( "1, 2, 3, 4", rangeToString(std::vector<int>{{1, 2, 3, 4}}, ", ") );
}

BOOST_AUTO_TEST_CASE( printfunction_argument_works ) {
	BOOST_CHECK_EQUAL( "b, c, d, e", rangeToString(std::vector<int>{{1, 2, 3, 4}},
			[](int x) { return std::string(1, 'a' + x); },
			", ") );
}

BOOST_AUTO_TEST_SUITE_END()
