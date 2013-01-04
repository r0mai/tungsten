
#include <boost/test/unit_test.hpp>

#include "eval/Attribute.hpp"

BOOST_AUTO_TEST_SUITE( AttributeTest )

using namespace tungsten;

BOOST_AUTO_TEST_CASE( addAttribute_works ) {
	eval::AttributeMap attributeMap;

	BOOST_CHECK( !attributeMap.hasAttribute("f", "Flat") );

	attributeMap.addAttribute( "f", "Flat" );

	BOOST_CHECK( attributeMap.hasAttribute("f", "Flat") );
}

BOOST_AUTO_TEST_SUITE_END()

