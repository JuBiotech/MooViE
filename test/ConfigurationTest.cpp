#include <Configuration.h>
#include <iostream>

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE "Configuration test"
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(configuration_test)

// TODO: Implement so that a more specific exception is caught
BOOST_AUTO_TEST_CASE(check_get_instance)
{
	//BOOST_CHECK_THROW(Configuration::get_instance(), std::exception);
}

BOOST_AUTO_TEST_CASE(standard_values)
{

    Configuration::initialize("/home/IBT/stratmann/MooViE/test/files/input.csv");
    Configuration& c = Configuration::get_instance();

	BOOST_CHECK_EQUAL(c.get_input_file(), std::string("/home/IBT/stratmann/MooViE/test/files/input.csv"));
	BOOST_CHECK_EQUAL(c.get_output_file(), std::string("image.svg"));
	BOOST_CHECK_EQUAL(c.get_width(), 320);
	BOOST_CHECK_EQUAL(c.get_height(), 320);

	BOOST_CHECK_EQUAL(c.get_output_angle_span(), 100);
	BOOST_CHECK_EQUAL(c.get_output_inner_radius(), 160);
	BOOST_CHECK_EQUAL(c.get_output_thickness(), 10);
	BOOST_CHECK_EQUAL(c.get_grid_size(), 150);
	BOOST_CHECK_EQUAL(c.get_num_major_ticks_cg(), 10);
	BOOST_CHECK_EQUAL(c.get_num_minor_ticks_cg(), 10);
	BOOST_CHECK_EQUAL(c.get_num_segments(), 10);

	BOOST_CHECK_EQUAL(c.get_input_inner_radius(), 150);
	BOOST_CHECK_EQUAL(c.get_input_thickness(), 10);
	BOOST_CHECK_EQUAL(c.get_input_separation_angle(), 5);
	BOOST_CHECK_EQUAL(c.get_num_major_ticks_va(), 10);
	BOOST_CHECK_EQUAL(c.get_num_minor_ticks_va(), 10);

	BOOST_CHECK_EQUAL(c.get_num_histogram_classes(), 10);
	BOOST_CHECK_EQUAL(c.get_histogram_height(), 20);
	BOOST_CHECK_EQUAL(c.get_histogram_background(), Color(0, 0, 0, .1));
	BOOST_CHECK_EQUAL(c.get_histogram_fill(), Color(0.5, 0.5, 0.5));

	BOOST_CHECK_EQUAL(c.get_line_with_dl(), 0.1);
	BOOST_CHECK_EQUAL(c.get_ratio_connector_arc(), 0.6);

	BOOST_CHECK_EQUAL(c.get_prop_thick().line_width, 0.5);
	BOOST_CHECK_EQUAL(c.get_prop_thin().line_width, 0.2);

	BOOST_CHECK_EQUAL(c.get_tick_label().font_name, "Sans Serif");
	BOOST_CHECK_EQUAL(c.get_tick_label().font_size, 8);
	BOOST_CHECK_EQUAL(c.get_var_label().font_name, "Sans Serif");
	BOOST_CHECK_EQUAL(c.get_var_label().font_size, 20);
}

BOOST_AUTO_TEST_CASE(file_values)
{
	Configuration::initialize("/home/IBT/stratmann/MooViE/test/files/input.csv", "/home/IBT/stratmann/MooViE/test/files/moovie.conf");
    Configuration& c = Configuration::get_instance();

    BOOST_CHECK_EQUAL(c.get_input_file(), std::string("/home/IBT/stratmann/MooViE/test/files/input.csv"));
    BOOST_CHECK_EQUAL(c.get_output_file(), std::string("image.svg"));
    BOOST_CHECK_EQUAL(c.get_width(), 750);
    BOOST_CHECK_EQUAL(c.get_height(), 750);

    BOOST_CHECK_EQUAL(c.get_output_angle_span(), 160);
    BOOST_CHECK_EQUAL(c.get_output_inner_radius(), 160);
    BOOST_CHECK_EQUAL(c.get_output_thickness(), 5);
    BOOST_CHECK_EQUAL(c.get_grid_size(), 150);
    BOOST_CHECK_EQUAL(c.get_num_major_ticks_cg(), 10);
    BOOST_CHECK_EQUAL(c.get_num_minor_ticks_cg(), 10);
    BOOST_CHECK_EQUAL(c.get_num_segments(), 10);

    BOOST_CHECK_EQUAL(c.get_input_inner_radius(), 180);
    BOOST_CHECK_EQUAL(c.get_input_thickness(), 5);
    BOOST_CHECK_EQUAL(c.get_input_separation_angle(), 5);
    BOOST_CHECK_EQUAL(c.get_num_major_ticks_va(), 10);
    BOOST_CHECK_EQUAL(c.get_num_minor_ticks_va(), 10);

    BOOST_CHECK_EQUAL(c.get_num_histogram_classes(), 10);
    BOOST_CHECK_EQUAL(c.get_histogram_height(), 20);
    BOOST_CHECK_EQUAL(c.get_histogram_background(), Color(0,0,0,.1));
    BOOST_CHECK_EQUAL(c.get_histogram_fill(), Color(0.5,0.5,0.5));

    BOOST_CHECK_EQUAL(c.get_line_with_dl(), 0.1);
    BOOST_CHECK_EQUAL(c.get_ratio_connector_arc(), 0.6);

    BOOST_CHECK_EQUAL(c.get_prop_thick().line_width, 0.5);
    BOOST_CHECK_EQUAL(c.get_prop_thin().line_width, 0.2);

    BOOST_CHECK_EQUAL(c.get_tick_label().font_name, "Liberation Serif");
    BOOST_CHECK_EQUAL(c.get_tick_label().font_size, 5);
    BOOST_CHECK_EQUAL(c.get_var_label().font_name, "Liberation Serif");
    BOOST_CHECK_EQUAL(c.get_var_label().font_size, 10);
}

// TODO: Implement so that a more specific exception is caught
BOOST_AUTO_TEST_CASE(invalid_file)
{
	//BOOST_CHECK_THROW(Configuration::initialize("."), std::exception);
}

BOOST_AUTO_TEST_SUITE_END()
