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
#include <unistd.h>

#define TO_STRING_HELPER(a) #a
#define TO_STRING(a) TO_STRING_HELPER(a)

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

  /** Writes a given string to a given file path.
   *
   * @param fpath the path of the file to write to
   * @param content the content to write
   *
   * @throw invalid_argument if file is not writable
   */
  void
  write_file (const std::string & fpath, const std::string & content);

  /** Splits a given string expression using the given delimiter string.
   *
   * @param str the string to divide
   * @param delims the delimiter string
   * @param remove_empty option to remove empty tokens
   * @param qouted_names option to allow qouted names
   *
   * @return the tokens or an empty vector
   */
  std::vector<std::string>
  split (const std::string & str, const std::string & delims,
	 bool remove_empty = true, bool quoted_names = true);

  /** Removes leading and trailing blanks of this string.
   *
   * @param str the string to strip
   *
   * @return the clean string
   */
  std::string
  strip (const std::string & str);

  /** Returns the current working directory like getcwd.
   *
   * @return the current working directory
   */
  inline std::string
  get_cwd (void)
  {
    char cwd[1000];
    getcwd (cwd, sizeof(cwd));
    return std::string (cwd);
  }

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

  const std::string BLANKS = " \t";

}

#endif /* UTILS_H_ */
