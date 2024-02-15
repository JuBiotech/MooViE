#include "lib/DataSet.h"
#include "lib/Utils.h"
#include <limits>
#include <memory>

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE "DataSet test"
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(dataset_test)

  BOOST_AUTO_TEST_CASE(csv_parsing_iterator_getter)
  {
    std::string cwd = Util::get_cwd ();

    DefDataSet set (cwd + "/input.csv");

    double eps = std::numeric_limits<double>::epsilon ();

    BOOST_CHECK_EQUAL(set.get_num_rows (), 5);
    BOOST_CHECK_EQUAL(set.get_num_cols (), 7);

    const std::vector<DefVariable>& inputs = set.input_variables ();
    BOOST_CHECK_EQUAL(inputs[0].name, std::string ("Input1"));
    BOOST_CHECK_CLOSE(inputs[0].min, 0.111, eps);
    BOOST_CHECK_CLOSE(inputs[0].max, 0.511, eps);
    BOOST_CHECK_EQUAL(inputs[1].name, std::string ("Input2"));
    BOOST_CHECK_CLOSE(inputs[1].min, 0.112, eps);
    BOOST_CHECK_CLOSE(inputs[1].max, 0.512, eps);
    BOOST_CHECK_EQUAL(inputs[2].name, std::string ("Input3"));
    BOOST_CHECK_CLOSE(inputs[2].min, 2, eps);
    BOOST_CHECK_CLOSE(inputs[2].max, 31, eps);
    BOOST_CHECK_EQUAL(inputs[3].name, std::string ("Input4"));
    BOOST_CHECK_CLOSE(inputs[3].min, 0.113, eps);
    BOOST_CHECK_CLOSE(inputs[3].max, 0.513, eps);

    const std::vector<DefVariable> & outputs = set.output_variables ();
    BOOST_CHECK_EQUAL(outputs[0].name, std::string ("Output1"));
    BOOST_CHECK_CLOSE(outputs[0].min, 0.121, eps);
    BOOST_CHECK_CLOSE(outputs[0].max, 0.521, eps);
    BOOST_CHECK_EQUAL(outputs[1].name, std::string ("Output2"));
    BOOST_CHECK_CLOSE(outputs[1].min, 0.122, eps);
    BOOST_CHECK_CLOSE(outputs[1].max, 0.522, eps);
    BOOST_CHECK_EQUAL(outputs[2].name, std::string ("Output3"));
    BOOST_CHECK_CLOSE(outputs[2].min, 0.023, eps);
    BOOST_CHECK_CLOSE(outputs[2].max, 0.723, eps);

    BOOST_CHECK_CLOSE(set[0][0].value, 0.111, eps);
    BOOST_CHECK_CLOSE(set[0][1].value, 0.112, eps);
    BOOST_CHECK_CLOSE(set[0][2].value, 10, eps);
    BOOST_CHECK_CLOSE(set[0][3].value, 0.113, eps);
    BOOST_CHECK_CLOSE(set[0][4].value, 0.121, eps);
    BOOST_CHECK_CLOSE(set[0][5].value, 0.322, eps);
    BOOST_CHECK_CLOSE(set[0][6].value, 0.123, eps);
    BOOST_CHECK_CLOSE(set[1][0].value, 0.211, eps);
    BOOST_CHECK_CLOSE(set[1][1].value, 0.212, eps);
    BOOST_CHECK_CLOSE(set[1][2].value, 20, eps);
    BOOST_CHECK_CLOSE(set[1][3].value, 0.213, eps);
    BOOST_CHECK_CLOSE(set[1][4].value, 0.221, eps);
    BOOST_CHECK_CLOSE(set[1][5].value, 0.222, eps);
    BOOST_CHECK_CLOSE(set[1][6].value, 0.723, eps);
    BOOST_CHECK_CLOSE(set[2][0].value, 0.311, eps);
    BOOST_CHECK_CLOSE(set[2][1].value, 0.312, eps);
    BOOST_CHECK_CLOSE(set[2][2].value, 2, eps);
    BOOST_CHECK_CLOSE(set[2][3].value, 0.313, eps);
    BOOST_CHECK_CLOSE(set[2][4].value, 0.321, eps);
    BOOST_CHECK_CLOSE(set[2][5].value, 0.422, eps);
    BOOST_CHECK_CLOSE(set[2][6].value, 0.323, eps);
    BOOST_CHECK_CLOSE(set[3][0].value, 0.411, eps);
    BOOST_CHECK_CLOSE(set[3][1].value, 0.412, eps);
    BOOST_CHECK_CLOSE(set[3][2].value, 31, eps);
    BOOST_CHECK_CLOSE(set[3][3].value, 0.413, eps);
    BOOST_CHECK_CLOSE(set[3][4].value, 0.421, eps);
    BOOST_CHECK_CLOSE(set[3][5].value, 0.122, eps);
    BOOST_CHECK_CLOSE(set[3][6].value, 0.023, eps);
    BOOST_CHECK_CLOSE(set[4][0].value, 0.511, eps);
    BOOST_CHECK_CLOSE(set[4][1].value, 0.512, eps);
    BOOST_CHECK_CLOSE(set[4][2].value, 13, eps);
    BOOST_CHECK_CLOSE(set[4][3].value, 0.513, eps);
    BOOST_CHECK_CLOSE(set[4][4].value, 0.521, eps);
    BOOST_CHECK_CLOSE(set[4][5].value, 0.522, eps);
    BOOST_CHECK_CLOSE(set[4][6].value, 0.623, eps);

    for (const DefDataRow& row : set)
      {
	for (DefCell cell : row)
	  {
	    BOOST_CHECK(not cell.null);
	  }
      }
  }

  BOOST_AUTO_TEST_CASE(null_cells)
  {
    std::string cwd = Util::get_cwd ();

    DefDataSet set (cwd + "/input4_nouse.csv");

    double eps = std::numeric_limits<double>::epsilon ();

    BOOST_CHECK_EQUAL(set.get_num_rows (), 2);
    BOOST_CHECK_EQUAL(set.get_num_cols (), 3);

    const std::vector<DefVariable>& inputs = set.input_variables ();
    BOOST_CHECK_EQUAL(inputs[0].name, std::string ("Input1"));
    BOOST_CHECK_CLOSE(inputs[0].min, 1, eps);
    BOOST_CHECK_CLOSE(inputs[0].max, 7, eps);
    BOOST_CHECK_EQUAL(inputs[1].name, std::string ("Input2"));
    BOOST_CHECK_CLOSE(inputs[1].min, 7, eps);
    BOOST_CHECK_CLOSE(inputs[1].max, 9, eps);

    const std::vector<DefVariable> & outputs = set.output_variables ();
    BOOST_CHECK_EQUAL(outputs[0].name, std::string ("Output1"));
    BOOST_CHECK_CLOSE(outputs[0].min, 2, eps);
    BOOST_CHECK_CLOSE(outputs[0].max, 9, eps);

    BOOST_CHECK_CLOSE(set[0][0].value, 1, eps);
    BOOST_CHECK(not set[0][0].null);
    BOOST_CHECK(set[0][1].null);
    BOOST_CHECK_CLOSE(set[0][2].value, 2, eps);
    BOOST_CHECK(not set[0][2].null);
    BOOST_CHECK_CLOSE(set[1][0].value, 7, eps);
    BOOST_CHECK(not set[1][0].null);
    BOOST_CHECK_CLOSE(set[1][1].value, 8, eps);
    BOOST_CHECK(not set[1][1].null);
    BOOST_CHECK_CLOSE(set[1][2].value, 9, eps);BOOST_CHECK(not set[1][2].null);
  }

  BOOST_AUTO_TEST_CASE(invalid_column_count)
  {
    std::string cwd = Util::get_cwd ();

    BOOST_CHECK_THROW(DefDataSet (cwd + "/input5_nouse.csv"),
		      std::length_error);
  }

  BOOST_AUTO_TEST_CASE(invalid_comment)
  {
    std::string cwd = Util::get_cwd ();

    BOOST_CHECK_THROW(DefDataSet (cwd + "/input6_nouse.csv"),
		      std::length_error);
  }

  BOOST_AUTO_TEST_CASE(blanks)
  {
	  std::string cwd = Util::get_cwd ();

	  DefDataSet set (cwd + "/input2.csv");
	  DefDataSet set_blank (cwd + "/input2_blank.csv");

	  double eps = std::numeric_limits<double>::epsilon ();

	  BOOST_CHECK_EQUAL(set.get_num_rows (), set_blank.get_num_rows ());
	  BOOST_CHECK_EQUAL(set.get_num_cols (), set_blank.get_num_cols ());

	    for (size_t row_idx = 0; row_idx < set.get_num_rows (); ++row_idx)
	      {
		for (size_t col_idx = 0; col_idx < set.get_num_cols (); ++col_idx)
		  {
		    BOOST_CHECK_CLOSE(set[row_idx][col_idx].value, set_blank[row_idx][col_idx].value, eps);
		  }
	      }
  }

  BOOST_AUTO_TEST_CASE(nans)
  {
	  std::string cwd = Util::get_cwd ();

	  DefDataSet set (cwd + "/input8.csv");

	  double eps = std::numeric_limits<double>::epsilon ();

	  BOOST_CHECK(std::isnan(set[0][0].value));
	  BOOST_CHECK(std::isnan(set[0][1].value));
	  BOOST_CHECK(std::isnan(set[0][2].value));
	  BOOST_CHECK_CLOSE(set[0][3].value, 0, eps);
	  BOOST_CHECK_CLOSE(set[0][4].value, 1, eps);

	  BOOST_CHECK(std::isnan(set[1][0].value));
	  BOOST_CHECK(std::isnan(set[1][1].value));
	  BOOST_CHECK(std::isnan(set[1][2].value));
	  BOOST_CHECK_CLOSE(set[1][3].value, 2, eps);
	  BOOST_CHECK_CLOSE(set[1][4].value, 3, eps);

	  BOOST_CHECK(std::isnan(set[2][0].value));
	  BOOST_CHECK(std::isnan(set[2][1].value));
	  BOOST_CHECK(std::isnan(set[2][2].value));
	  BOOST_CHECK_CLOSE(set[2][3].value, 4, eps);
	  BOOST_CHECK_CLOSE(set[2][4].value, 5, eps);

  }

  BOOST_AUTO_TEST_CASE(extract_header)
  {
	  DefDataSet set;

	  auto out = set.extract_header_entry("i#varname");
	  BOOST_CHECK(std::get<0>(out) == "varname");
	  BOOST_CHECK(std::get<1>(out).empty());
	  BOOST_CHECK(std::get<2>(out).empty());
	  BOOST_CHECK(std::get<3>(out).empty());

	  out = set.extract_header_entry("i#varname [unit]");
	  BOOST_CHECK(std::get<0>(out) == "varname");
	  BOOST_CHECK(std::get<1>(out) == "unit");
	  BOOST_CHECK(std::get<2>(out).empty());
	  BOOST_CHECK(std::get<3>(out).empty());

	  out = set.extract_header_entry("i#varname (-0.1, 13)");
	  BOOST_CHECK(std::get<0>(out) == "varname");
	  BOOST_CHECK(std::get<1>(out).empty());
	  BOOST_CHECK(std::get<2>(out) == "-0.1");
	  BOOST_CHECK(std::get<3>(out) == "13");


	  out = set.extract_header_entry("i#varname [ unit] (0,7)");
	  BOOST_CHECK(std::get<0>(out) == "varname");
	  BOOST_CHECK(std::get<1>(out) == "unit");
	  BOOST_CHECK(std::get<2>(out) == "0");
	  BOOST_CHECK(std::get<3>(out) == "7");

	  out = set.extract_header_entry("\"i#varname [ unit] (0,7)\"");
	  BOOST_CHECK(std::get<0>(out) == "varname");
	  BOOST_CHECK(std::get<1>(out) == "unit");
	  BOOST_CHECK(std::get<2>(out) == "0");
	  BOOST_CHECK(std::get<3>(out) == "7");

	  out = set.extract_header_entry("i#var,name [ unit/other unit] (-0.45,3e9)");
	  BOOST_CHECK(std::get<0>(out) == "var,name");
	  BOOST_CHECK(std::get<1>(out) == "unit/other unit");
	  BOOST_CHECK(std::get<2>(out) == "-0.45");
	  BOOST_CHECK(std::get<3>(out) == "3e9");
  }

  BOOST_AUTO_TEST_SUITE_END()
