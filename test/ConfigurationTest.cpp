#include "../Args.h"
#include "../Configuration.h"
#include <iostream>

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE "CL arguments and Configuration test"
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(clarguments_and_configuration)

BOOST_AUTO_TEST_CASE(parse_0)
{
    int argc = 13;
    const char * argv[argc] = {
	"moovie",
	"--width", "800", "--height", "800",
	"--output-file", "/home/IBT/stratmann/MooViE/image.svg",
	"--file-type", "csv",
	"--configuration-file", "/home/IBT/stratmann/MooViE/testfiles/moovie.conf",
	"/home/IBT/stratmann/MooViE/testfiles/input.csv",
	"3"
    };

    const Args & args = Args::parse(argc, argv);

    BOOST_CHECK_EQUAL(args.width(), 800);
    BOOST_CHECK_EQUAL(args.height(), 800);
    BOOST_CHECK_EQUAL(args.output_file(), std::string("/home/IBT/stratmann/MooViE/image.svg"));
    BOOST_CHECK_EQUAL(args.input_file(), std::string("/home/IBT/stratmann/MooViE/testfiles/input.csv"));
    BOOST_CHECK_EQUAL(args.config_file(), std::string("/home/IBT/stratmann/MooViE/testfiles/moovie.conf"));
    BOOST_CHECK_EQUAL(args.file_type(), Args::File_t::CSV);
}

BOOST_AUTO_TEST_CASE(parse_1)
{
    int argc = 13;
    const char * argv[argc] = {
	"moovie",
	"-w", "800", "-h", "800",
	"-o", "/home/IBT/stratmann/MooViE/image.svg",
	"-f", "csv",
	"-c", "/home/IBT/stratmann/MooViE/testfiles/moovie.conf",
	"/home/IBT/stratmann/MooViE/testfiles/input.csv",
	"3"
    };

    const Args & args = Args::parse(argc, argv);

    BOOST_CHECK_EQUAL(args.width(), 800);
    BOOST_CHECK_EQUAL(args.height(), 800);
    BOOST_CHECK_EQUAL(args.output_file(), std::string("/home/IBT/stratmann/MooViE/image.svg"));
    BOOST_CHECK_EQUAL(args.input_file(), std::string("/home/IBT/stratmann/MooViE/testfiles/input.csv"));
    BOOST_CHECK_EQUAL(args.config_file(), std::string("/home/IBT/stratmann/MooViE/testfiles/moovie.conf"));
    BOOST_CHECK_EQUAL(args.file_type(), Args::File_t::CSV);
}

BOOST_AUTO_TEST_CASE(parse_3)
{
    int argc = 9;
    const char * argv[argc] = {
	"moovie",
	"--width", "230",
	"--file-type", "csv",
	"--configuration-file", "/home/IBT/stratmann/MooViE/testfiles/moovie.conf",
	"/home/IBT/stratmann/MooViE/testfiles/input.csv",
	"3"
    };

    const Args & args = Args::parse(argc, argv);

    BOOST_CHECK_EQUAL(args.width(), 230);
    BOOST_CHECK_EQUAL(args.has_height(), false);
    BOOST_CHECK_EQUAL(args.has_output_file(), false);
    BOOST_CHECK_EQUAL(args.input_file(), std::string("/home/IBT/stratmann/MooViE/testfiles/input.csv"));
    BOOST_CHECK_EQUAL(args.config_file(), std::string("/home/IBT/stratmann/MooViE/testfiles/moovie.conf"));
    BOOST_CHECK_EQUAL(args.file_type(), Args::File_t::CSV);
}

BOOST_AUTO_TEST_CASE(exception_0)
{
    int argc = 9;
    const char * argv[argc] = {
	"moovie",
  	"--width", "230",
  	"--file-type", "s",
  	"--configuration-file", "/home/IBT/stratmann/MooViE/testfiles/moovie.conf",
  	"/home/IBT/stratmann/MooViE/testfiles/input.csv",
  	"3"
    };

    try
    {
	const Args & args = Args::parse(argc, argv);
    }
    catch (ParseException & e)
    {
	BOOST_CHECK_EQUAL(std::string(e.what()), std::string("Given file type is not supported."));
    }
}

BOOST_AUTO_TEST_CASE(exception_1)
{
    int argc = 8;
    const char * argv[argc] = {
	"moovie",
  	"--width",
  	"--file-type", "s",
  	"--configuration-file", "/home/IBT/stratmann/MooViE/testfiles/moovie.conf",
  	"/home/IBT/stratmann/MooViE/testfiles/input.csv",
  	"3"
    };

    try
    {
	const Args & args = Args::parse(argc, argv);
    }
    catch (ParseException & e)
    {
	BOOST_CHECK_EQUAL(std::string(e.what()), std::string("width option expected an positional parameter, but found option."));
    }
}

BOOST_AUTO_TEST_CASE(exception_3)
{
    int argc = 9;
    const char * argv[argc] = {
	"moovie",
  	"--width", "as",
  	"--file-type", "s",
  	"--configuration-file", "/home/IBT/stratmann/MooViE/testfiles/moovie.conf",
  	"/home/IBT/stratmann/MooViE/testfiles/input.csv",
  	"3"
    };

    try
    {
	const Args & args = Args::parse(argc, argv);
    }
    catch (ParseException & e)
    {
	BOOST_CHECK_EQUAL(e.what(), std::string("Invalid integer value."));
    }
}

BOOST_AUTO_TEST_CASE(config_vals_0)
{
    Configuration c("/home/IBT/stratmann/MooViE/testfiles/input.csv", 3);

    BOOST_CHECK_EQUAL(c.get_input_file(), std::string("/home/IBT/stratmann/MooViE/testfiles/input.csv"));
    BOOST_CHECK_EQUAL(c.get_output_file(), std::string("image.svg"));
    BOOST_CHECK_EQUAL(c.get_inputs(), 3);
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
    Configuration c("/home/IBT/stratmann/MooViE/testfiles/input.csv", 3, "/home/IBT/stratmann/MooViE/testfiles/moovie.conf");

    BOOST_CHECK_EQUAL(c.get_input_file(), std::string("/home/IBT/stratmann/MooViE/testfiles/input.csv"));
    BOOST_CHECK_EQUAL(c.get_output_file(), std::string("image.svg"));
    BOOST_CHECK_EQUAL(c.get_inputs(), 3);
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
