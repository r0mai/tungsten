
#include <boost/test/unit_test.hpp>

#include "util/SharedPointer.hpp"

BOOST_AUTO_TEST_SUITE( SharedPointerTest )

struct DestructorTest {
	DestructorTest(bool *isDestructed) : isDestructed(isDestructed) { *isDestructed = false; }
	~DestructorTest() { *isDestructed = true; }

	bool *isDestructed;
};

using namespace tungsten;

BOOST_AUTO_TEST_CASE( SharedPointer_Test_1 ) {
	bool b = true;
	{
		util::SharedPointer<DestructorTest> ptr(&b);
		BOOST_REQUIRE(!b);
		BOOST_REQUIRE_EQUAL(ptr.useCount(), 1);
	}
	BOOST_REQUIRE(b);
}

BOOST_AUTO_TEST_SUITE_END()


