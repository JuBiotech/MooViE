/*
 * MooViEUtils.cpp
 *
 *  Created on: 30.11.2017
 *      Author: IBT\stratmann
 */

#include "Utils.h"

namespace Util {

std::string read_file(const std::string & fpath)
{
	std::ifstream in(fpath);
	if (in)
	{
		std::ostringstream content;
		content << in.rdbuf();
		return content.str();
	}
	else
	{
		throw 0;
	}
}

std::vector<std::string> split(const std::string & str,
		const std::string & delims, bool remove_empty)
{
	std::vector<std::string> res;
	std::size_t prev = 0;

	for (std::size_t i = 0; i < str.length(); ++i)
	{
		if (i + delims.length() <= str.length()
				&& str.compare(i, delims.length(), delims) == 0)
		{
			const std::string & part = str.substr(prev, i - prev);
			if (not (remove_empty && part.empty()))
			{
				res.push_back(part);
			}
			prev = i + delims.length();
		}
	}
	if (prev < str.length())
	{
		const std::string & part = str.substr(prev, str.length() - prev);
		if (not (remove_empty && part.empty()))
		{
			res.push_back(part);
		}
	}

	return res;
}

std::string strip(const std::string & str)
{
	std::size_t leading = str.find_first_not_of(' '),
			trailing = str.find_last_not_of(' ');
	return str.substr(leading, trailing - leading + 1);
}

}
