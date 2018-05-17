/*
 * Utils.h
 *
 *  Created on: 30.11.2017
 *      Author: IBT\stratmann
 */

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

class ParseException : public std::exception
{
public:
	ParseException(const std::string & msg) : _msg(msg) {}
	virtual char const * what() { return _msg.c_str(); }
private:
	const std::string _msg;
};

namespace Util {

/** Reads the content of a file with the given path.
 *
 * @param fname the path of the file to read
 *
 * @return the files content
 */
std::string read_file(const std::string & fpath);

/** Splits a given string expression using the given delimiter string.
 *
 * @param str the string to divide
 * @param delims the delimiter string
 * @param remove_empty option to remove empty tokens
 *
 * @return the tokens or an empty vector
 */
std::vector<std::string> split(const std::string & str,
		const std::string & delims, bool remove_empty=true);

/** Removes leading and trailing blanks of this string.
 *
 * @param str the string to strip
 *
 * @return the clean string
 */
std::string strip(const std::string & str);

/** Tries to parse an integer from the given string.
 *
 * @param str the string to convert
 *
 * @return the integer value
 *
 * @throws ParseException if string is not an integer literal
 */
inline int string_to_int(const std::string & str) throw(ParseException)
{
	try
	{
		return std::stoi(str);
	} catch (std::invalid_argument & ia)
	{
		throw ParseException("Invalid integer value.");
	}
}

/** Tries to parse an double from the given string.
 *
 * @param str the string to convert
 *
 * @return the double value
 *
 * @throws ParseException if string is not an double literal
 */
inline double string_to_double(const std::string & str) throw(ParseException)
{
	try
	{
		return std::stod(str);
	} catch (std::invalid_argument & ia)
	{
		throw ParseException("Invalid integer value.");
	}
}

/** Compares to doubles for approximate equality
 * using |a - b| < machine_epsilon.
 *
 * @param a first double
 * @param b second double
 *
 * @return approximately equal or not
 */
inline bool double_equal(double a, double b)
{
	double eps = std::numeric_limits<double>().epsilon();
	return std::fabs(a - b) < eps;
}

}

#endif /* UTILS_H_ */
