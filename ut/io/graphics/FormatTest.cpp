
#include <boost/test/unit_test.hpp>
#include <boost/math/constants/constants.hpp>

#include "../../eval/builtin/Fixture.hpp"

#include <io/graphics/Format.hpp>

BOOST_FIXTURE_TEST_SUITE( FormatTest, BuiltinFunctionFixture )
using namespace tungsten;

const auto PI = math::Real{180};

BOOST_AUTO_TEST_CASE( HueOf0_saturation_of_0_value_of_0_should_be_black ) {
	const auto result = io::graphics::ColorDirective::fromHSV(0,0,0);

	BOOST_CHECK_EQUAL(result.r(), 0);
	BOOST_CHECK_EQUAL(result.g(), 0);
	BOOST_CHECK_EQUAL(result.b(), 0);
}

BOOST_AUTO_TEST_CASE ( HueOf0_saturation_of_0_value_of_1_should_be_white ) {
	const auto result = io::graphics::ColorDirective::fromHSV(0,0,1);

	BOOST_CHECK_EQUAL(result.r(), 255);
	BOOST_CHECK_EQUAL(result.g(), 255);
	BOOST_CHECK_EQUAL(result.b(), 255);
}

BOOST_AUTO_TEST_CASE(HueOf0_saturation_of_0_value_of_05_should_be_gray ) {
	const auto result = io::graphics::ColorDirective::fromHSV(0,0,0.5);

	BOOST_CHECK_EQUAL(result.r(), 127);
	BOOST_CHECK_EQUAL(result.g(), 127);
	BOOST_CHECK_EQUAL(result.b(), 127);
}

BOOST_AUTO_TEST_CASE(HueOf0_saturation_of_0_value_of_066_should_be_light_gray ) {
	const auto result = io::graphics::ColorDirective::fromHSV(0,0,0.66);

	BOOST_CHECK_EQUAL(result.r(), 168);
	BOOST_CHECK_EQUAL(result.g(), 168);
	BOOST_CHECK_EQUAL(result.b(), 168);
}

BOOST_AUTO_TEST_CASE(HueOf0_saturation_of_0_value_of_033_should_be_dark_gray ) {
	const auto result = io::graphics::ColorDirective::fromHSV(0,0,0.33);

	BOOST_CHECK_EQUAL(result.r(), 84);
	BOOST_CHECK_EQUAL(result.g(), 84);
	BOOST_CHECK_EQUAL(result.b(), 84);
}

BOOST_AUTO_TEST_CASE( HueOf0_saturation_of_1_value_of_0_should_be_black ) {
	const auto result = io::graphics::ColorDirective::fromHSV(0,1,0);

	BOOST_CHECK_EQUAL(result.r(), 0);
	BOOST_CHECK_EQUAL(result.g(), 0);
	BOOST_CHECK_EQUAL(result.b(), 0);
}

BOOST_AUTO_TEST_CASE ( HueOf0_saturation_of_1_value_of_1_should_be_red ) {
	const auto result = io::graphics::ColorDirective::fromHSV(0,1,1);

	BOOST_CHECK_EQUAL(result.r(), 255);
	BOOST_CHECK_EQUAL(result.g(), 0);
	BOOST_CHECK_EQUAL(result.b(), 0);
}

BOOST_AUTO_TEST_CASE(HueOf0_saturation_of_1_value_of_05_should_be_maroon ) {
	const auto result = io::graphics::ColorDirective::fromHSV(0,1,0.5);

	BOOST_CHECK_EQUAL(result.r(), 127);
	BOOST_CHECK_EQUAL(result.g(), 0);
	BOOST_CHECK_EQUAL(result.b(), 0);
}

BOOST_AUTO_TEST_CASE(HueOf0_saturation_of_1_value_of_066_should_be_dark_red ) {
	const auto result = io::graphics::ColorDirective::fromHSV(0,1,0.66);

	BOOST_CHECK_EQUAL(result.r(), 168);
	BOOST_CHECK_EQUAL(result.g(), 0);
	BOOST_CHECK_EQUAL(result.b(), 0);
}

BOOST_AUTO_TEST_CASE(HueOf0_saturation_of_1_value_of_033_should_be_maroon ) {
	const auto result = io::graphics::ColorDirective::fromHSV(0,1,0.33);

	BOOST_CHECK_EQUAL(result.r(), 84);
	BOOST_CHECK_EQUAL(result.g(), 0);
	BOOST_CHECK_EQUAL(result.b(), 0);
}

BOOST_AUTO_TEST_CASE( HueOfPi_saturation_of_0_value_of_0_should_be_black ) {
	const auto result = io::graphics::ColorDirective::fromHSV(PI,0,0);

	BOOST_CHECK_EQUAL(result.r(), 0);
	BOOST_CHECK_EQUAL(result.g(), 0);
	BOOST_CHECK_EQUAL(result.b(), 0);
}

BOOST_AUTO_TEST_CASE ( HueOfPi_saturation_of_0_value_of_1_should_be_white ) {
	const auto result = io::graphics::ColorDirective::fromHSV(PI,0,1);

	BOOST_CHECK_EQUAL(result.r(), 255);
	BOOST_CHECK_EQUAL(result.g(), 255);
	BOOST_CHECK_EQUAL(result.b(), 255);
}

BOOST_AUTO_TEST_CASE(HueOfPi_saturation_of_0_value_of_05_should_be_gray ) {
	const auto result = io::graphics::ColorDirective::fromHSV(PI,0,0.5);

	BOOST_CHECK_EQUAL(result.r(), 127);
	BOOST_CHECK_EQUAL(result.g(), 127);
	BOOST_CHECK_EQUAL(result.b(), 127);
}

BOOST_AUTO_TEST_CASE(HueOfPi_saturation_of_0_value_of_066_should_be_light_gray ) {
	const auto result = io::graphics::ColorDirective::fromHSV(PI,0,0.66);

	BOOST_CHECK_EQUAL(result.r(), 168);
	BOOST_CHECK_EQUAL(result.g(), 168);
	BOOST_CHECK_EQUAL(result.b(), 168);
}

BOOST_AUTO_TEST_CASE(HueOfPi_saturation_of_0_value_of_033_should_be_dark_gray ) {
	const auto result = io::graphics::ColorDirective::fromHSV(PI,0,0.33);

	BOOST_CHECK_EQUAL(result.r(), 84);
	BOOST_CHECK_EQUAL(result.g(), 84);
	BOOST_CHECK_EQUAL(result.b(), 84);
}

BOOST_AUTO_TEST_CASE( HueOfPi_saturation_of_1_value_of_0_should_be_black ) {
	const auto result = io::graphics::ColorDirective::fromHSV(PI,1,0);

	BOOST_CHECK_EQUAL(result.r(), 0);
	BOOST_CHECK_EQUAL(result.g(), 0);
	BOOST_CHECK_EQUAL(result.b(), 0);
}

BOOST_AUTO_TEST_CASE ( HueOfPi_saturation_of_1_value_of_1_should_be_aqua ) {
	const auto result = io::graphics::ColorDirective::fromHSV(PI,1,1);

	BOOST_CHECK_EQUAL(result.r(), 0);
	BOOST_CHECK_EQUAL(result.g(), 255);
	BOOST_CHECK_EQUAL(result.b(), 255);
}

BOOST_AUTO_TEST_CASE(HueOfPi_saturation_of_1_value_of_05_should_be_teal ) {
	const auto result = io::graphics::ColorDirective::fromHSV(PI,1,0.5);

	BOOST_CHECK_EQUAL(result.r(), 0);
	BOOST_CHECK_EQUAL(result.g(), 127);
	BOOST_CHECK_EQUAL(result.b(), 127);
}

BOOST_AUTO_TEST_CASE(HueOfPi_saturation_of_1_value_of_066_should_be_light_sea_green ) {
	const auto result = io::graphics::ColorDirective::fromHSV(PI,1,0.66);

	BOOST_CHECK_EQUAL(result.r(), 0);
	BOOST_CHECK_EQUAL(result.g(), 168);
	BOOST_CHECK_EQUAL(result.b(), 168);
}

BOOST_AUTO_TEST_CASE(HueOfPi_saturation_of_1_value_of_033_should_be_dark_slate_gray ) {
	const auto result = io::graphics::ColorDirective::fromHSV(PI,1,0.33);

	BOOST_CHECK_EQUAL(result.r(), 0);
	BOOST_CHECK_EQUAL(result.g(), 84);
	BOOST_CHECK_EQUAL(result.b(), 84);
}

BOOST_AUTO_TEST_SUITE_END();
