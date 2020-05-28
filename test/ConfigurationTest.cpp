#include <Configuration.h>
#include <iostream>

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE "Configuration test"
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(configuration_test)

  BOOST_AUTO_TEST_CASE(check_get_instance)
  {
    BOOST_CHECK_THROW(Configuration::get_instance (), std::bad_function_call);
  }

  BOOST_AUTO_TEST_CASE(standard_values)
  {
    std::string cwd = Util::get_cwd ();

    Configuration::initialize (cwd + "/input.csv");
    Configuration& c = Configuration::get_instance ();

    BOOST_CHECK_EQUAL(c.get_input_file (),
		      std::string (cwd + "/input.csv"));
    BOOST_CHECK_EQUAL(c.get_output_file (), std::string ("image.svg"));
    double width_height_adjustment = 2
	* (c.get_output_inner_radius () + c.get_output_thickness ()
	    + c.get_grid_size ()) + 100;
    BOOST_CHECK_EQUAL(c.get_width (), width_height_adjustment);
    BOOST_CHECK_EQUAL(c.get_height (), width_height_adjustment);

    BOOST_CHECK_EQUAL(c.get_output_angle_span (), 160);
    BOOST_CHECK_EQUAL(c.get_output_inner_radius (), 160);
    BOOST_CHECK_EQUAL(c.get_output_thickness (), 5);
    BOOST_CHECK_EQUAL(c.get_grid_size (), 150);
    BOOST_CHECK_EQUAL(c.get_num_major_sections_grid (), 10);
    BOOST_CHECK_EQUAL(c.get_num_minor_sections_grid (), 10);
    BOOST_CHECK_EQUAL(c.get_min_grid_fill_ratio(), 0.9);

    BOOST_CHECK_EQUAL(c.get_input_inner_radius (), 180);
    BOOST_CHECK_EQUAL(c.get_input_thickness (), 5);
    BOOST_CHECK_EQUAL(c.get_input_separation_angle (), 5);
    BOOST_CHECK_EQUAL(c.get_num_major_sections_axis (), 10);
    BOOST_CHECK_EQUAL(c.get_num_minor_sections_axis (), 10);

    BOOST_CHECK_EQUAL(c.get_num_histogram_classes (), 10);
    BOOST_CHECK_EQUAL(c.get_histogram_height (), 20);
    BOOST_CHECK_EQUAL(c.get_histogram_background (), Color (0, 0, 0, .1));
    BOOST_CHECK_EQUAL(c.get_histogram_fill (), Color (0.5, 0.5, 0.5));

    BOOST_CHECK_EQUAL(c.get_prop_thick ().line_width, 0.5);
    BOOST_CHECK_EQUAL(c.get_prop_thin ().line_width, 0.1);

    BOOST_CHECK_EQUAL(c.get_prop_scale_label ().font_name, "Liberation Serif");
    BOOST_CHECK_EQUAL(c.get_prop_scale_label ().font_size, 5);
    BOOST_CHECK_EQUAL(c.get_prop_axis_label ().font_name, "Liberation Serif");
    BOOST_CHECK_EQUAL(c.get_prop_axis_label ().font_size, 10);
  }

  BOOST_AUTO_TEST_CASE(file_values)
  {
    std::string cwd = Util::get_cwd ();

    Configuration::initialize (cwd + "/input.csv",
			       cwd + "/moovie.conf");
    Configuration& c = Configuration::get_instance ();

    BOOST_CHECK_EQUAL(c.get_input_file (),
		      std::string (cwd + "/input.csv"));
    BOOST_CHECK_EQUAL(c.get_output_file (), std::string ("image.svg"));
    BOOST_CHECK_EQUAL(c.get_width (), 750);
    BOOST_CHECK_EQUAL(c.get_height (), 750);

    BOOST_CHECK_EQUAL(c.get_output_angle_span (), 160);
    BOOST_CHECK_EQUAL(c.get_output_inner_radius (), 160);
    BOOST_CHECK_EQUAL(c.get_output_thickness (), 5);
    BOOST_CHECK_EQUAL(c.get_grid_size (), 150);
    BOOST_CHECK_EQUAL(c.get_num_major_sections_grid (), 10);
    BOOST_CHECK_EQUAL(c.get_num_minor_sections_grid (), 10);

    BOOST_CHECK_EQUAL(c.get_input_inner_radius (), 180);
    BOOST_CHECK_EQUAL(c.get_input_thickness (), 5);
    BOOST_CHECK_EQUAL(c.get_input_separation_angle (), 5);
    BOOST_CHECK_EQUAL(c.get_num_major_sections_axis (), 10);
    BOOST_CHECK_EQUAL(c.get_num_minor_sections_axis (), 10);

    BOOST_CHECK_EQUAL(c.get_num_histogram_classes (), 10);
    BOOST_CHECK_EQUAL(c.get_histogram_height (), 20);
    BOOST_CHECK_EQUAL(c.get_histogram_background (), Color (0, 0, 0, .1));
    BOOST_CHECK_EQUAL(c.get_histogram_fill (), Color (0.5, 0.5, 0.5));

    BOOST_CHECK_EQUAL(c.get_prop_thick ().line_width, 0.5);
    BOOST_CHECK_EQUAL(c.get_prop_thin ().line_width, 0.1);

    BOOST_CHECK_EQUAL(c.get_prop_scale_label ().font_name, "Liberation Serif");
    BOOST_CHECK_EQUAL(c.get_prop_scale_label ().font_size, 5);
    BOOST_CHECK_EQUAL(c.get_prop_axis_label ().font_name, "Liberation Serif");
    BOOST_CHECK_EQUAL(c.get_prop_axis_label ().font_size, 10);
  }

  BOOST_AUTO_TEST_CASE(invalid_file)
  {
    BOOST_CHECK_THROW(Configuration::initialize ("image.svg", "failure"),
		      std::invalid_argument);
  }

  BOOST_AUTO_TEST_SUITE_END()
