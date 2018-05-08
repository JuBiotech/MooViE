#include "../Configuration.h"
#include <iostream>

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE "Configuration test"
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(values)

BOOST_AUTO_TEST_CASE(config_vals_0)
{
    Configuration c("/home/IBT/stratmann/MooViE/testfiles/input.csv", 3);

    BOOST_CHECK_EQUAL(c.get_input_file(), std::string("/home/IBT/stratmann/MooViE/testfiles/input.csv"));
    BOOST_CHECK_EQUAL(c.get_output_file(), std::string("image.svg"));
    BOOST_CHECK_EQUAL(c.get_width(), 500);
    BOOST_CHECK_EQUAL(c.get_height(), 500);
    BOOST_CHECK_EQUAL(c.get_input_inner_radius(), 150);
    BOOST_CHECK_EQUAL(c.get_input_thickness(), 10);
    BOOST_CHECK_EQUAL(c.get_input_separation_angle(), 5);
    BOOST_CHECK_EQUAL(c.get_output_inner_radius(), 160);
    BOOST_CHECK_EQUAL(c.get_output_thickness(), 10);
    BOOST_CHECK_EQUAL(c.get_grid_size(), 150);
}

BOOST_AUTO_TEST_CASE(config_vals_1)
{
    Configuration c("/home/IBT/stratmann/MooViE/testfiles/input.csv", "/home/IBT/stratmann/MooViE/testfiles/moovie.conf");

    BOOST_CHECK_EQUAL(c.get_input_file(), std::string("/home/IBT/stratmann/MooViE/testfiles/input.csv"));
    BOOST_CHECK_EQUAL(c.get_output_file(), std::string("image.svg"));
    BOOST_CHECK_EQUAL(c.get_width(), 750);
    BOOST_CHECK_EQUAL(c.get_height(), 750);
    BOOST_CHECK_EQUAL(c.get_input_inner_radius(), 150);
    BOOST_CHECK_EQUAL(c.get_input_thickness(), 10);
    BOOST_CHECK_EQUAL(c.get_input_separation_angle(), 5);
    BOOST_CHECK_EQUAL(c.get_output_inner_radius(), 160);
    BOOST_CHECK_EQUAL(c.get_output_thickness(), 10);
    BOOST_CHECK_EQUAL(c.get_grid_size(), 150);
}

BOOST_AUTO_TEST_SUITE_END()
