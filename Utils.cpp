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

std::vector<std::string> split(const std::string & expr,
		const std::string & delims, bool remove_empty)
{
	std::vector<std::string> res;
	std::size_t prev = 0;

	for (std::size_t i = 0; i < expr.length(); ++i)
	{
		if (i + delims.length() <= expr.length()
				&& expr.compare(i, delims.length(), delims) == 0)
		{
			const std::string & part = expr.substr(prev, i - prev);
			if (not (remove_empty && part.empty()))
			{
				res.push_back(part);
			}
			prev = i + delims.length();
		}
	}
	if (prev < expr.length())
	{
		const std::string & part = expr.substr(prev, expr.length() - prev);
		if (not (remove_empty && part.empty()))
		{
			res.push_back(part);
		}
	}

	return res;
}

std::string strip(const std::string & expr)
{
	std::size_t leading = expr.find_first_not_of(' '),
			trailing = expr.find_last_not_of(' ');
	return expr.substr(leading, trailing - leading + 1);
}
}

