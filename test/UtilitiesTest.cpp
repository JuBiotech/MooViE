#include <Utils.h>
#include <Mapper.h>
#include <limits>

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE "Utilities test"
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(util)

  BOOST_AUTO_TEST_CASE(read_file_existing)
  {
    std::string cwd = Util::get_cwd ();

    std::string content = Util::read_file (
	cwd + "/input6_nouse.csv");
    BOOST_CHECK_EQUAL(content, "Invalid comment csv\n\n"
		      "i#Input1 o#Output1\n"
		      "1,2\n");
  }

  BOOST_AUTO_TEST_CASE(read_file_not_existing)
  {
    BOOST_CHECK_THROW(Util::read_file ("files/not_existing"),
		      std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(split)
  {
    std::string regular = "M,o,o,V,i,E", one_element = "MooViE", empty = "",
	with_empties = "Multi,objective,,optimization,,visualization,,engine";

    auto check_vectors =
	[](const std::vector<std::string>& cmp0, const std::vector<std::string>& cmp1)
	  {
	    BOOST_CHECK_EQUAL(cmp0.size(), cmp1.size());
	    if (cmp0.size() != cmp1.size())
	      {
		return;
	      }

	    for (std::size_t i = 0; i < cmp0.size(); ++i)
	      {
		BOOST_CHECK_EQUAL(cmp0[i], cmp1[i]);
	      }
	  };

    check_vectors (Util::split (regular, ","), std::vector<std::string> (
      { "M", "o", "o", "V", "i", "E" }));
    check_vectors (Util::split (one_element, ","), std::vector<std::string> (
      { "MooViE" }));
    check_vectors (Util::split (empty, ","), std::vector<std::string> ());
    check_vectors (Util::split (with_empties, ",", false),
		   std::vector<std::string> (
		     { "Multi", "objective", "", "optimization", "",
			 "visualization", "", "engine" }));
  }

  BOOST_AUTO_TEST_CASE(strip)
  {
    std::string both =
	"  Multi-objective optimization visualization engine     ", left =
	"  Multi-objective optimization visualization engine", right =
	"Multi-objective optimization visualization engine ", none =
	"Multi-objective optimization visualization engine", empty = "";

    BOOST_CHECK_EQUAL(Util::strip (both), none);
    BOOST_CHECK_EQUAL(Util::strip (left), none);
    BOOST_CHECK_EQUAL(Util::strip (right), none);
    BOOST_CHECK_EQUAL(Util::strip (none), none);
    BOOST_CHECK_EQUAL(Util::strip (empty), empty);
  }

  BOOST_AUTO_TEST_CASE(double_equal)
  {
    double a = 31415, b = 271828, not_existing = NAN;

    double eps = std::numeric_limits<float>::epsilon ();

    BOOST_CHECK(Util::double_equal (a, a));
    BOOST_CHECK(not Util::double_equal (a, a + eps));
    BOOST_CHECK(not Util::double_equal (a, b));
    BOOST_CHECK(not Util::double_equal (a, not_existing));
    BOOST_CHECK(not Util::double_equal (not_existing, a));
    BOOST_CHECK(not Util::double_equal (not_existing, not_existing));
  }

  BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(mapper)

  BOOST_AUTO_TEST_CASE(constructor_map_inverse)
  {
    std::pair<double, double> in (2.71828, 3.14159), out (3.14159, 2.71828);
    Mapper mapper (in, out);

    double eps = std::numeric_limits<double>::epsilon ();

    BOOST_CHECK_CLOSE(
	mapper.map (3.5),
	(out.second - out.first) / (in.second - in.first) * (3.5 - in.first)
	    + out.first,
	eps);
    BOOST_CHECK_CLOSE(
	mapper.inverse (3.5),
	(in.second - in.first) / (out.second - out.first) * (3.5 - out.first)
	    + in.first,
	eps);
  }

// TODO: Implement so that a more specific exception is caught
  BOOST_AUTO_TEST_CASE(constructor_nan)
  {
//	BOOST_CHECK_THROW(
//			Mapper(std::pair<double, double>(NAN, 1), std::pair<double, double>(1,1)),
//			std::exception);
//	BOOST_CHECK_THROW(
//				Mapper(std::pair<double, double>(1, NAN), std::pair<double, double>(1,1)),
//				std::exception);
//	BOOST_CHECK_THROW(
//				Mapper(std::pair<double, double>(1, 1), std::pair<double, double>(NAN,1)),
//				std::exception);
//	BOOST_CHECK_THROW(
//				Mapper(std::pair<double, double>(1, 1), std::pair<double, double>(1,NAN)),
//				std::exception);
  }

  BOOST_AUTO_TEST_SUITE_END()
