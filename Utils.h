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
#include "PolarCartesian.h"

namespace Util {

/** Reads the content of a file with the given path.
 * @param fname the path of the file to read
 * @return the files content
 */
std::string read_file(const std::string & fpath);

/** Splits a given string expression using the given delimiter string.
 * @param str the string to divide
 * @param delims the delimiter string
 * @param remove_empty option to remove empty tokens
 */
std::vector<std::string> split(const std::string & str,
		const std::string & delims, bool remove_empty=true);

/** Removes leading and trailing blanks of this string.
 * @param str the string to strip
 */
std::string strip(const std::string & str);

/** Calculates a Polar coordinate for the beginning of a connector
 * between 'from' and 'to'. If the resulting coordinate is passed to
 * a connector drawing function, the connector does not immediately
 * start at from.
 * @param from the Polar coord to start the connector from
 * @param from the Polar coord to draw the connector to
 */
inline Polar get_connector_start(const Polar & from, const Polar to)
{
	return Polar(from.r() + 0.1 * (to.r() - from.r()), from.phi());
}

/** Calculates a Polar coordinate for the end of a connector between
 * 'from' and 'to'. If the resulting coordinate is passed to a connector
 * drawing function, the connector does not immediately end at to.
 * @param from the Polar coord to start the connector from
 * @param from the Polar coord to draw the connector to
 */
inline Polar get_connector_end(const Polar & from, const Polar to)
{
	return Polar(to.r() - 0.1 * (to.r() - from.r()), to.phi());
}

}

#endif /* UTILS_H_ */
