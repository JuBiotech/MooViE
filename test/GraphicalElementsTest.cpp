#include "../DomainAxis.h"
#include "../CodomainGrid.h"
#include "../RelationElement.h"
#include "../CairoDrawer.h"
#include "../Scene.h"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE "Graphical elements test"
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(domainaxis_test)

BOOST_AUTO_TEST_CASE(constructor_getters)
{
	std::string var_name = "var", unit = "mT", font_name = "Liberation Sans";
	DefVar var(0, 10, var_name, unit);
	Angle start = M_PI, end = M_PI + M_PI_2;
	double radius = 10.0, height = 20.0, line_width = 1.0, font_size = 40;
	Color line_color(.123, .8, .1, .071), fill_color(.94, .81, .7316, .5);
	DrawerProperties<> prop(line_width, line_color, fill_color);
	bool bold = true, italic = true;
	TextProperties text_prop(font_name, font_size, line_color, bold, italic);

	DomainAxis axis(var, start, end, radius, height, prop);

}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(codomaingrid_test)
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(relationelement_test)
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(cairodrawer_test)
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(scene_test)
BOOST_AUTO_TEST_SUITE_END()
