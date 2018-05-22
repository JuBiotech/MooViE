#include "../Utils.h"
#include "../Mapper.h"
#include <limits>

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE "Utilities test"
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(util)

BOOST_AUTO_TEST_CASE(read_file_existing)
{
	std::string content = Util::read_file("files/input6_nouse.csv");
	BOOST_CHECK_EQUAL(content,
			"Invalid comment csv\n\n"
			"i#Input1 o#Output1\n"
			"1,2\n");
}

BOOST_AUTO_TEST_CASE(read_file_not_existing)
{
	BOOST_CHECK_THROW(Util::read_file("files/not_existing"), std::exception);
}

BOOST_AUTO_TEST_CASE(split)
{
	std::string regular = "M,o,o,V,I,E",
			one_element = "MooViE",
			empty = "",
			with_empties = "Multi,objective,,optimization,,visualization,,engine";

	BOOST_CHECK_EQUAL(Util::split(regular, ","), std::vector<std::string>({"M", "o", "o", "V", "i", "E"}));
	BOOST_CHECK_EQUAL(Util::split(one_element, ","), std::vector<std::string>({"MooViE"}));
	BOOST_CHECK_EQUAL(Util::split(empty, ","), std::vector<std::string>());
	BOOST_CHECK_EQUAL(Util::split(empty, ",", false),
			std::vector<std::string>({"Multi","objective","","optimization","","visualization","","engine"}));
}

BOOST_AUTO_TEST_CASE(strip)
{
	std::string both = "  Multi-objective optimization visualization engine     ",
			left = "  Multi-objective optimization visualization engine",
			right = "Multi-objective optimization visualization engine ",
			none = "Multi-objective optimization visualization engine",
			empty = "";

	BOOST_CHECK_EQUAL(Util::strip(both), both.substr(2));
	BOOST_CHECK_EQUAL(Util::strip(left), left.substr(2, none.length()));
	BOOST_CHECK_EQUAL(Util::strip(right), right.substr(0, none.length()));
	BOOST_CHECK_EQUAL(Util::strip(none), none);
	BOOST_CHECK_EQUAL(Util::strip(empty), empty);
}

BOOST_AUTO_TEST_CASE(string_to_int)
{
	std::string regular = "3",
			negative = "-3",
			null = "0",
			wrong = "213-3",
			too_large = "10000000000",
			too_small = "-10000000000";

	double eps = std::numeric_limits<double>::epsilon();

	BOOST_CHECK_EQUAL(Util::string_to_int(regular), 3);
	BOOST_CHECK_EQUAL(Util::string_to_int(negative), -3);
	BOOST_CHECK_EQUAL(Util::string_to_int(null), 0);
	BOOST_CHECK_THROW(Util::string_to_double(wrong), ParseException);
	BOOST_CHECK_THROW(Util::string_to_double(too_large), ParseException);
	BOOST_CHECK_THROW(Util::string_to_double(too_small), ParseException);
}

BOOST_AUTO_TEST_CASE(string_to_double)
{
	std::string regular = "3.1415",
			negative = "-3.1415",
			integer = "0",
			e_value = "-0.31415e-1",
			wrong = "213,3",
			too_large = "10e-1000",
			too_small = "-10e-1000";

	double eps = std::numeric_limits<double>::epsilon();

	BOOST_CHECK_CLOSE(Util::string_to_double(regular), 3.1415, eps);
	BOOST_CHECK_CLOSE(Util::string_to_double(negative), -3.1415, eps);
	BOOST_CHECK_CLOSE(Util::string_to_double(integer), 0, eps);
	BOOST_CHECK_CLOSE(Util::string_to_double(e_value), -0.31415e-1, eps);
	BOOST_CHECK_THROW(Util::string_to_double(wrong), ParseException);
	BOOST_CHECK_THROW(Util::string_to_double(too_large), ParseException);
	BOOST_CHECK_THROW(Util::string_to_double(too_small), ParseException);
}

BOOST_AUTO_TEST_CASE(double_equal)
{
	double a = 31415, b = 271828,
			not_existing = NAN;

	double eps = std::numeric_limits<double>::epsilon();

	BOOST_CHECK(Util::double_equal(a,a));
	BOOST_CHECK(not Util::double_equal(a,a + eps));
	BOOST_CHECK(not Util::double_equal(a,b));
	BOOST_CHECK(not Util::double_equal(a,not_existing));
	BOOST_CHECK(not Util::double_equal(not_existing,a));
	BOOST_CHECK(not Util::double_equal(not_existing,not_existing));
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(mapper)

BOOST_AUTO_TEST_CASE(constructor_map_inverse)
{
	std::pair<double,double> in(2.71828, 3.14159),
			out(3.14159, 2.71828);
	Mapper mapper(in, out);

	double eps = std::numeric_limits<double>::epsilon();

	BOOST_CHECK_CLOSE(mapper.map(3.5),
			(out.second - out.first) / (in.second - in.first)
			* (3.5 - in.first) + out.first,
			eps);
	BOOST_CHECK_CLOSE(mapper.inverse(3.5),
			(in.second - in.first) / (out.second - out.first)
			* (3.5 - out.first) + in.first,
			eps);
}

BOOST_AUTO_TEST_CASE(constructor_nan)
{
	BOOST_CHECK_THROW(
			Mapper(std::pair<double, double>(NAN, 1), std::pair<double, double>(1,1)),
			std::exception);
	BOOST_CHECK_THROW(
				Mapper(std::pair<double, double>(1, NAN), std::pair<double, double>(1,1)),
				std::exception);
	BOOST_CHECK_THROW(
				Mapper(std::pair<double, double>(1, 1), std::pair<double, double>(NAN,1)),
				std::exception);
	BOOST_CHECK_THROW(
				Mapper(std::pair<double, double>(1, 1), std::pair<double, double>(1,NAN)),
				std::exception);
}

BOOST_AUTO_TEST_SUITE_END()
