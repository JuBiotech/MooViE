#include "../DataSet.h"
#include "../Utils.h"
#include <limits>

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE "DataSet test"
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(dataset_test)

BOOST_AUTO_TEST_CASE(csv_parsing_constructor_iterator_getter)
{
	DefDataSet set = DefDataSet::parse_from_csv(Util::read_file("../testfiles/input.csv"));

	double eps = std::numeric_limits<double>::epsilon();

	BOOST_CHECK((set.rows() == 7) && (set.cols() == 5));

	const std::vector<DefVar> & inputs = set.input_variables();
	BOOST_CHECK_EQUAL(inputs[0].name, "Input1");
	BOOST_CHECK_EQUAL(inputs[1].name, "Input2");
	BOOST_CHECK_EQUAL(inputs[2].name, "Input3");
	BOOST_CHECK_EQUAL(inputs[3].name, "Input4");

	const std::vector<DefVar> & outputs = set.output_variables();
	BOOST_CHECK_EQUAL(outputs[0].name, "Output1");
	BOOST_CHECK_EQUAL(outputs[1].name, "Output2");
	BOOST_CHECK_EQUAL(outputs[2].name, "Output3");

	BOOST_CHECK_CLOSE(set[0][0], 0.111, eps);
	BOOST_CHECK_CLOSE(set[0][1], 0.112, eps);
	BOOST_CHECK_CLOSE(set[0][2], 10, eps);
	BOOST_CHECK_CLOSE(set[0][3], 0.113, eps);
	BOOST_CHECK_CLOSE(set[0][4], 0.121, eps);
	BOOST_CHECK_CLOSE(set[0][5], 0.322, eps);
	BOOST_CHECK_CLOSE(set[0][6], 0.123, eps);
	BOOST_CHECK_CLOSE(set[1][0], 0.211, eps);
	BOOST_CHECK_CLOSE(set[1][1], 0.212, eps);
	BOOST_CHECK_CLOSE(set[1][2], 20, eps);
	BOOST_CHECK_CLOSE(set[1][3], 0.213, eps);
	BOOST_CHECK_CLOSE(set[1][4], 0.221, eps);
	BOOST_CHECK_CLOSE(set[1][5], 0.222, eps);
	BOOST_CHECK_CLOSE(set[1][6], 0.723, eps);
	BOOST_CHECK_CLOSE(set[2][0], 0.311, eps);
	BOOST_CHECK_CLOSE(set[2][1], 0.312, eps);
	BOOST_CHECK_CLOSE(set[2][2], 0.2, eps);
	BOOST_CHECK_CLOSE(set[2][3], 0.313, eps);
	BOOST_CHECK_CLOSE(set[2][4], 0.321, eps);
	BOOST_CHECK_CLOSE(set[2][5], 0.422, eps);
	BOOST_CHECK_CLOSE(set[2][6], 0.323, eps);
	BOOST_CHECK_CLOSE(set[3][0], 0.411, eps);
	BOOST_CHECK_CLOSE(set[3][1], 0.412, eps);
	BOOST_CHECK_CLOSE(set[3][2], 31, eps);
	BOOST_CHECK_CLOSE(set[3][3], 0.413, eps);
	BOOST_CHECK_CLOSE(set[3][4], 0.421, eps);
	BOOST_CHECK_CLOSE(set[3][5], 0.122, eps);
	BOOST_CHECK_CLOSE(set[3][6], 0.023, eps);
	BOOST_CHECK_CLOSE(set[4][0], 0.511, eps);
	BOOST_CHECK_CLOSE(set[4][1], 0.512, eps);
	BOOST_CHECK_CLOSE(set[4][2], 13, eps);
	BOOST_CHECK_CLOSE(set[4][3], 0.513, eps);
	BOOST_CHECK_CLOSE(set[4][4], 0.521, eps);
	BOOST_CHECK_CLOSE(set[4][5], 0.522, eps);
	BOOST_CHECK_CLOSE(set[4][6], 0.623, eps);


	for (DefDataRow row: set)
	{

	}
}

BOOST_AUTO_TEST_CASE

BOOST_AUTO_TEST_SUITE_END()
