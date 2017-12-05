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

namespace Util {

/** Reads the content of a file with the given path.
 * @param fname the path of the file to read
 * @return the files content
 */
std::string read_file(const std::string & fpath);

/** Splits a given string expression using the given delimiter string.
 * @param expr the string to divide
 * @param delims the delimiter string
 */
std::vector<std::string> split(const std::string & expr,
		const std::string & delims, bool remove_empty=true);

/** Removes leading and trailing blanks of this string.
 * @param the string to strip
 */
std::string strip(const std::string & expr);
}

#endif /* UTILS_H_ */
