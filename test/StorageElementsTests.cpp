#include "../DrawerProperties.h"
#include "../TextProperties.h"
#include <iostream>

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE "Coordinates test"
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(color)

BOOST_AUTO_TEST_CASE(constructor_access)
{

}

BOOST_AUTO_TEST_CASE(setters)
{

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
