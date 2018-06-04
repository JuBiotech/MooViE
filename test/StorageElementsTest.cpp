#include "../include/DrawerProperties.h"
#include "../include/TextProperties.h"
#include <iostream>

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE "Coordinates test"
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(color)

BOOST_AUTO_TEST_CASE(constructor_access)
{
	Color test(0.1, 0.4, 0.6, 0.2);

	double eps = 0.0001;
	BOOST_CHECK_CLOSE(test.r(), 0.1, eps);
	BOOST_CHECK_CLOSE(test.g(), 0.4, eps);
	BOOST_CHECK_CLOSE(test.b(), 0.6, eps);
	BOOST_CHECK_CLOSE(test.a(), 0.2, eps);
}

BOOST_AUTO_TEST_CASE(comparison)
{
	Color test(.5, .5, .5, .5),
			cmp0(.5, .5, .5, .5),
			cmp1(.4, .5, .5, .5),
			cmp2(.5, .6, .5, .5),
			cmp3(.5, .5, .3, .5),
			cmp4(.5, .5, .5, .7);

	BOOST_CHECK_EQUAL(test, cmp0);
	BOOST_CHECK(!(test == cmp1) && !(test == cmp2)
			&& !(test == cmp3) && !(test == cmp4));

	BOOST_CHECK_NE(test, cmp1);
	BOOST_CHECK_NE(test, cmp2);
	BOOST_CHECK_NE(test, cmp3);
	BOOST_CHECK_NE(test, cmp4);
}

BOOST_AUTO_TEST_CASE(setters)
{
	const Color start(1., 1., 1.);
	Color test0 = start,
			test1 = start,
			test2 = start,
			test3 = start;

	test0.set_red(0.5);
	test1.set_green(0.5);
	test2.set_blue(0.5);
	test3.set_alpha(0.5);

	double eps = 0.0001;

	BOOST_CHECK_CLOSE(test0.r(), 0.5, eps);
	BOOST_CHECK_CLOSE(test1.g(), 0.5, eps);
	BOOST_CHECK_CLOSE(test2.b(), 0.5, eps);
	BOOST_CHECK_CLOSE(test3.a(), 0.5, eps);
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(drawer_properties)

BOOST_AUTO_TEST_CASE(constructor_access)
{
	double width = 1.;
	const Color line(1., 1., 1.);
	const Color fill(0., 0., 0.);

	DrawerProperties<> prop0(width, line, fill);
	BOOST_CHECK_EQUAL(prop0.line_width, width);
	BOOST_CHECK_EQUAL(prop0.line_color, line);
	BOOST_CHECK_EQUAL(prop0.fill_color, fill);
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(text_properties)

BOOST_AUTO_TEST_CASE(constructor_access)
{
	std::string font_name = "Sans serif";
	double font_size = 20;
	Color color(.4, .3, .2, .1);
	bool bold = true;
	bool italic = false;

	TextProperties prop(font_name, font_size, color, bold, italic);
	BOOST_CHECK_EQUAL(prop.font_name, font_name);
	BOOST_CHECK_EQUAL(prop.font_size, font_size);
	BOOST_CHECK_EQUAL(prop.color, color);
	BOOST_CHECK_EQUAL(prop.bold, bold);
	BOOST_CHECK_EQUAL(prop.italic, italic);
}

BOOST_AUTO_TEST_SUITE_END()
