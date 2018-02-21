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
#include "PolarCartesian.h"

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
 * @param fname the path of the file to read
 * @return the files content
 */
std::string read_file(const std::string & fpath);

/** Splits a given string expression using the given delimiter string.
 * @param str the string to divide
 * @param delims the delimiter string
 * @param remove_empty option to remove empty tokens
 * @return the tokens or an empty vector
 */
std::vector<std::string> split(const std::string & str,
		const std::string & delims, bool remove_empty=true);

/** Removes leading and trailing blanks of this string.
 * @param str the string to strip
 * @return the clean string
 */
std::string strip(const std::string & str);

/** Tries to parse an integer from the given string.
 * @param str the string to convert
 * @return the integer value
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
 * @param str the string to convert
 * @return the double value
 * @throws ParseException if string is not an double literal
 */
inline int string_to_double(const std::string & str) throw(ParseException)
{
	try
	{
		return std::stod(str);
	} catch (std::invalid_argument & ia)
	{
		throw ParseException("Invalid integer value.");
	}
}

/** Cairo uses an non-standard way to define angles. The angle of 0 is on
 * the positive X axis, but the angle of pi/2 or 90° is on the negative
 * Y axis (the common model uses the positive Y axis).
 * @param angle
 * @return the cairo angle
 */
inline Angle get_cairo_angle(const Angle & angle)
{
	return Angle(2 * M_PI - angle.get());
}

/** Calculates a Polar coordinate for the beginning of a connector
 * between 'from' and 'to'. If the resulting coordinate is passed to
 * a connector drawing function, the connector does not immediately
 * start at from.
 * @param from the Polar coordinate to start the connector from
 * @param from the Polar coordinate to draw the connector to
 * @return the modified Connector start coordinate
 */
inline Polar get_connector_start(const Polar & from, const Polar to)
{
	return Polar(from.r() + 0.1 * (to.r() - from.r()), from.phi());
}

/** Calculates a Polar coordinate for the end of a connector between
 * 'from' and 'to'. If the resulting coordinate is passed to a connector
 * drawing function, the connector does not immediately end at to.
 * @param from the Polar coordinate to start the connector from
 * @param from the Polar coordinate to draw the connector to
 * @return the modified Connector end coordinate
 */
inline Polar get_connector_end(const Polar & from, const Polar to)
{
	return Polar(to.r() - 0.1 * (to.r() - from.r()), to.phi());
}

}

#endif /* UTILS_H_ */
