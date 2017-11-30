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
		const std::string delims)
{
	std::vector<std::string> res;
	std::size_t prev = 0;

	for (std::size_t i = 0; i < expr.length(); ++i)
	{
		if (i + delims.length() >= expr.length()
				&& expr.substr(i, delims.length()).compare(i, delims.length(),
						delims, 0, delims.length()) == 0)
		{
			res.push_back(expr.substr(i, i - prev));
			prev = i + 1;
		}
	}
	if (prev < expr.length())
	{
		res.push_back(expr.substr(prev, expr.length() - prev));
	}

	return res;
}

std::string strip(const std::string & expr)
{
	std::size_t leading = expr.find_first_not_of(' '),
			trailing = expr.find_last_not_of(' ');
	return expr.substr(leading, trailing-leading);
}
}

