#include <InputAxis.h>
#include <IOVector.h>
#include <OutputGrid.h>
#include <limits>

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE "Graphical elements test"
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(graphical_elements_test)

  BOOST_AUTO_TEST_CASE(domainaxis)
  {
    std::string cwd = Util::get_cwd ();

    // Construction

    Configuration::initialize (cwd + "/test/files/input.csv");
    const Configuration& conf = Configuration::get_instance ();

    std::string var_name = "var", unit = "mT", font_name = "Liberation Sans";
    double min = 1, max = 10;
    DefVariable var (min, max, var_name, unit);
    Angle start = M_PI, end = M_PI + M_PI_2;
    double radius = 10.0, height = 20.0, line_width = 1.0, font_size = 40;
    Color line_color (.123, .8, .1, .071), fill_color (.94, .81, .7316, .5);
    DrawerProperties<> prop (line_width, line_color, fill_color);

    InputAxis axis (var, start, end, radius, height, prop);

    // Test Constructor/Getters

    double eps = std::numeric_limits<double>::epsilon ();

    BOOST_CHECK_EQUAL(axis.get_var ().name, var_name);
    BOOST_CHECK_CLOSE(axis.get_var ().min, min, eps);
    BOOST_CHECK_CLOSE(axis.get_var ().max, max, eps);
    BOOST_CHECK_EQUAL(axis.get_var ().unit, unit);
    BOOST_CHECK_CLOSE(axis.get_start ().value (), start.value (), eps);
    BOOST_CHECK_CLOSE(axis.get_end ().value (), end.value (), eps);
    BOOST_CHECK_CLOSE(axis.get_start ().value (), start.value (), eps);
    BOOST_CHECK_CLOSE(axis.get_radius (), radius, eps);
    BOOST_CHECK_CLOSE(axis.get_height (), height, eps);
    BOOST_CHECK_CLOSE(axis.get_prop ().line_width, line_width, eps);
    BOOST_CHECK_EQUAL(axis.get_prop ().line_color, line_color);
    BOOST_CHECK_EQUAL(axis.get_prop ().fill_color, fill_color);

    std::pair<double, double> extremes = create_rounded_interval (var.min,
								  var.max);
    BOOST_CHECK_EQUAL(axis.get_scale ().get_major_intersections (),
		      conf.get_num_major_sections_axis ());
    BOOST_CHECK_EQUAL(axis.get_scale ().get_major_intersections (),
		      conf.get_num_major_sections_axis ());
    BOOST_CHECK_CLOSE(axis.get_scale ().get_extremes ().first, extremes.first,
		      eps);
    BOOST_CHECK_CLOSE(axis.get_scale ().get_extremes ().second, extremes.second,
		      eps);

    bool bold = true, italic = true;
    TextProperties text_prop (font_name, font_size, line_color, bold, italic);
    Label label = axis.make_label (text_prop);

    BOOST_CHECK_EQUAL(label.get_text (), axis.get_var ().name);
    BOOST_CHECK_EQUAL(label.get_properties ().font_name, font_name);
    BOOST_CHECK_CLOSE(label.get_properties ().font_size, font_size, eps);
    BOOST_CHECK_EQUAL(label.get_properties ().color, line_color);
    BOOST_CHECK_EQUAL(label.get_properties ().bold, bold);
    BOOST_CHECK_EQUAL(label.get_properties ().italic, italic);

    std::vector<double> data =
      { 1, 1, 1, 2, 5, 9, 9, 10, 10, 10, 10 };
    axis.calculate_histogram (data);
    BOOST_CHECK_EQUAL(axis.get_histogram ().get_num_intervals (),
		      conf.get_num_histogram_classes ());
    BOOST_CHECK_CLOSE(axis.get_histogram ().get_section_frequency (0),
		      3. / data.size (), eps);
    BOOST_CHECK_CLOSE(axis.get_histogram ().get_section_frequency (1),
		      1. / data.size (), eps);
    BOOST_CHECK_CLOSE(axis.get_histogram ().get_section_frequency (4),
		      1. / data.size (), eps);
    BOOST_CHECK_CLOSE(axis.get_histogram ().get_section_frequency (8),
		      2. / data.size (), eps);
    BOOST_CHECK_CLOSE(axis.get_histogram ().get_section_frequency (9),
		      4. / data.size (), eps);

    // Test Setters

    start = M_PI, end = M_PI + M_PI_2;
    radius = 10.0, height = 20.0, line_width = 1.0, font_size = 40;
    line_color = Color (.123, .8, .1, .071), fill_color = Color (.94, .81,
								 .7316, .5);
    prop = DrawerProperties<> (line_width, line_color, fill_color);

    axis.set_start (start);
    axis.set_end (end);
    axis.set_radius (radius);
    axis.set_height (height);
    axis.set_prop (prop);

    BOOST_CHECK_EQUAL(axis.get_var ().name, var_name);
    BOOST_CHECK_CLOSE(axis.get_var ().min, min, eps);
    BOOST_CHECK_CLOSE(axis.get_var ().max, max, eps);
    BOOST_CHECK_EQUAL(axis.get_var ().unit, unit);
    BOOST_CHECK_CLOSE(axis.get_start ().value (), start.value (), eps);
    BOOST_CHECK_CLOSE(axis.get_end ().value (), end.value (), eps);
    BOOST_CHECK_CLOSE(axis.get_start ().value (), start.value (), eps);
    BOOST_CHECK_CLOSE(axis.get_radius (), radius, eps);
    BOOST_CHECK_CLOSE(axis.get_height (), height, eps);
    BOOST_CHECK_CLOSE(axis.get_prop ().line_width, line_width, eps);
    BOOST_CHECK_EQUAL(axis.get_prop ().line_color, line_color);
    BOOST_CHECK_EQUAL(axis.get_prop ().fill_color, fill_color);
  }

  BOOST_AUTO_TEST_CASE(codomaingrid)
  {
    std::string cwd = Util::get_cwd ();

    // Construction

    Configuration::initialize (cwd + "/test/files/input.csv");
    const Configuration& conf = Configuration::get_instance ();

    std::vector<DefVariable> output_vars;

    std::string var_name0 = "var0", unit0 = "mT";
    double min0 = 0, max0 = 10;
    output_vars.emplace_back (min0, max0, var_name0, unit0);

    std::string var_name1 = "var1", unit1 = "V";
    double min1 = -27, max1 = -9;
    output_vars.emplace_back (min1, max1, var_name1, unit1);

    Angle start = M_PI_2, end = M_PI;
    double radius = 1.0, height = 0.5;
    Direction dir = Direction::COUNTER_CLOCKWISE;

    OutputGrid grid (output_vars, start, end, radius, height, dir);

    // Test Costructor/Getters

    double eps = std::numeric_limits<double>::epsilon ();

    BOOST_CHECK_EQUAL(grid.get_var (0).name, var_name0);
    BOOST_CHECK_EQUAL(grid.get_var (1).name, var_name1);
    BOOST_CHECK_CLOSE(grid.get_var (0).min, min0, eps);
    BOOST_CHECK_CLOSE(grid.get_var (1).min, min1, eps);
    BOOST_CHECK_CLOSE(grid.get_var (0).max, max0, eps);
    BOOST_CHECK_CLOSE(grid.get_var (1).max, max1, eps);
    BOOST_CHECK_EQUAL(grid.get_var (0).unit, unit0);
    BOOST_CHECK_EQUAL(grid.get_var (1).unit, unit1);
    BOOST_CHECK_THROW(grid.get_var (2), std::out_of_range)
    BOOST_CHECK_EQUAL(grid.get_num_outputs (), output_vars.size ());
    BOOST_CHECK_CLOSE(grid.get_start ().value (), start.value (), eps);
    BOOST_CHECK_CLOSE(grid.get_end ().value (), end.value (), eps);
    BOOST_CHECK_CLOSE(grid.get_start ().value (), start.value (), eps);
    BOOST_CHECK_CLOSE(grid.get_radius (), radius, eps);
    BOOST_CHECK_CLOSE(grid.get_height (), height, eps);
    BOOST_CHECK_EQUAL(grid.get_direction (), dir);

    std::pair<double, double> extremes0 = create_rounded_interval (min0, max0),
	extremes1 = create_rounded_interval (min1, max1);
    BOOST_CHECK_EQUAL(grid.get_scale ().get_major_intersections (),
		      conf.get_num_major_sections_grid ());
    BOOST_CHECK_EQUAL(grid.get_scale ().get_minor_intersections (),
		      conf.get_num_minor_sections_grid ());
    BOOST_CHECK_EQUAL(grid.get_scale ().get_scale_number (),
		      output_vars.size ());
    BOOST_CHECK_CLOSE(grid.get_scale ().get_extremes (0).first, extremes0.first,
		      eps);
    BOOST_CHECK_CLOSE(grid.get_scale ().get_extremes (0).second,
		      extremes0.second, eps);
    BOOST_CHECK_CLOSE(grid.get_scale ().get_extremes (1).first, extremes1.first,
		      eps);
    BOOST_CHECK_CLOSE(grid.get_scale ().get_extremes (1).second,
		      extremes1.second, eps);

    // Test Setters

    start = M_PI_4, end = M_PI_2;
    radius = 30, height = 9.;
    dir = Direction::CLOCKWISE;

    grid.set_start (start);
    grid.set_end (end);
    grid.set_radius (radius);
    grid.set_height (height);
    grid.set_direction (dir);

    BOOST_CHECK_CLOSE(grid.get_start ().value (), start.value (), eps);
    BOOST_CHECK_CLOSE(grid.get_end ().value (), end.value (), eps);
    BOOST_CHECK_CLOSE(grid.get_start ().value (), start.value (), eps);
    BOOST_CHECK_CLOSE(grid.get_radius (), radius, eps);
    BOOST_CHECK_CLOSE(grid.get_height (), height, eps);
    BOOST_CHECK_EQUAL(grid.get_direction (), dir);
  }

  BOOST_AUTO_TEST_CASE(relationelement)
  {
    std::string cwd = Util::get_cwd ();

    Configuration::initialize (cwd + "/test/files/input.csv");

    std::string var_name = "var", unit = "mT", font_name = "Liberation Sans";
    double min = 0, max = 10;
    DefVariable var (min, max, var_name, unit);
    Angle start = M_PI, end = M_PI + M_PI_2;
    double radius = 10.0, height = 20.0, line_width = 1.0;
    Color line_color (.123, .8, .1, .071), fill_color (.94, .81, .7316, .5);
    DrawerProperties<> prop (line_width, line_color, fill_color);

    std::vector<InputAxis> axis
      {
	{ var, start, end, radius, height, prop } };

    std::vector<DefVariable> output_vars;

    std::string var_name1 = "var1", unit1 = "V";
    double min1 = -27, max1 = -9;
    output_vars.emplace_back (min1, max1, var_name1, unit1);

    start = M_PI_2, end = M_PI;
    radius = 30, height = 0.5;
    Direction dir = Direction::COUNTER_CLOCKWISE;

    OutputGrid grid (output_vars, start, end, radius, height, dir);

    DefDataSet set (cwd + "/test/files/input.csv");
    const DefDataRow& row = set[0];

    IOVectorFactory factory (1, grid, axis);
    IOVector elem = factory.create (row);

    double eps = std::numeric_limits<double>::epsilon ();

    Mapper m0 (
	axis[0].get_scale ().get_extremes (),
	std::make_pair (axis[0].get_start ().value (),
			axis[0].get_end ().value ())), m1 (
	grid.get_scale ().get_extremes (0),
	std::make_pair (grid.get_start ().value (), grid.get_end ().value ()));

    BOOST_CHECK_CLOSE(elem[0].coord.angle ().value (), m0.map (row[0].value),
		      eps);
    BOOST_CHECK_CLOSE(elem[0].coord.radius (), axis[0].get_radius (), eps);
    BOOST_CHECK_CLOSE(elem[1].coord.angle ().value (), m1.map (row[1].value),
		      eps);
    BOOST_CHECK_CLOSE(elem[1].coord.radius (), grid.get_radius () - 10, eps);
  }

  BOOST_AUTO_TEST_SUITE_END()
