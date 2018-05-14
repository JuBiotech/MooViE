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
	std::string font_name;
	double font_size;
	Color color;
	double bold;
	double italic;
}

BOOST_AUTO_TEST_SUITE_END()
