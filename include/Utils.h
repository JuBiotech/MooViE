#ifndef UTILS_H_
#define UTILS_H_

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include <climits>
#include <cstdlib>
#include <limits>
#include <cmath>

namespace Util
{

  /** Reads the content of a file with the given path.
   *
   * @param fname the path of the file to read
   *
   * @return the files content
   *
   * @throw invalid_argument if file is not readable
   */
  std::string
  read_file (const std::string & fpath);

  /** Splits a given string expression using the given delimiter string.
   *
   * @param str the string to divide
   * @param delims the delimiter string
   * @param remove_empty option to remove empty tokens
   *
   * @return the tokens or an empty vector
   */
  std::vector<std::string>
  split (const std::string & str, const std::string & delims,
	 bool remove_empty = true);

  /** Removes leading and trailing blanks of this string.
   *
   * @param str the string to strip
   *
   * @return the clean string
   */
  std::string
  strip (const std::string & str);

  /** Compares to doubles for approximate equality
   * using |a - b| < machine_epsilon.
   *
   * @param a first double
   * @param b second double
   *
   * @return approximately equal or not
   */
  inline bool
  double_equal (double a, double b, int ulp = 15)
  {
    double eps = std::numeric_limits<double>::epsilon (), min =
	std::numeric_limits<double>::min ();
    return std::abs (a - b) <= eps * std::abs (a + b) * ulp
	|| std::abs (a - b) < min;
  }

}

#endif /* UTILS_H_ */
