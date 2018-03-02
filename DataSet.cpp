/*
 * CSVParser.cpp
 *
 *  Created on: 28.11.2017
 *      Author: IBT\stratmann
 */

#include "DataSet.h"

template<>
DataSet<double> DataSet<double>::parse_from_csv(const std::string & cont, std::size_t num_ins,
		std::string separator, std::string comment, std::string newline)
{
	std::vector<DefVar> input_vars, output_vars;
	std::vector<DefDataRow> rows;
	const std::vector<std::string> & lines = Util::split(cont, newline);

	std::size_t header_pos = 0;
	while (lines[header_pos].find_first_not_of(' ') == std::string::npos ||
			lines[header_pos][lines[header_pos].find_first_not_of(' ')] == '#')
		++header_pos;
	const std::vector<std::string> & header = Util::split(lines[header_pos], separator);

	// Add input variables from table header
	for (std::size_t i = 0; i < num_ins; ++i)
	{
		std::size_t open_bracket = header[i].find_first_of('['),
				close_bracket = header[i].find_first_of(']');
		if (open_bracket != std::string::npos
				&& close_bracket != std::string::npos)
		{
			std::string name = header[i].substr(0, open_bracket),
					unit = header[i].substr(open_bracket + 1, close_bracket - open_bracket - 2);
			input_vars.push_back(DefVar(DBL_MAX, DBL_MIN, Util::strip(name), Util::strip(unit)));
		}
		else
		{
			input_vars.push_back(DefVar(DBL_MAX, DBL_MIN, Util::strip(header[i])));
		}
	}

	// Add output variables from table header
	for (std::size_t i = num_ins; i < header.size(); ++i)
	{
		std::size_t open_bracket = header[i].find_first_of('['),
				close_bracket = header[i].find_first_of(']');
		if (open_bracket != std::string::npos
				&& close_bracket != std::string::npos)
		{
			std::string name = header[i].substr(0, open_bracket),
					unit = header[i].substr(open_bracket + 1, close_bracket - open_bracket - 2);
			output_vars.push_back(DefVar(DBL_MAX, DBL_MIN, Util::strip(name), Util::strip(unit)));
		}
		else
		{
			output_vars.push_back(DefVar(DBL_MAX, DBL_MIN, Util::strip(header[i])));
		}
	}

	// Add values from table body
	for (std::size_t i = header_pos + 1; i < lines.size(); ++i)
	{
		// Remove empty/comment lines
		if (lines[i].find_first_not_of(' ') != std::string::npos
				|| lines[i].find_first_of(comment) == lines[i].find_first_not_of(' ') + 1)
		{
			DefDataRow row;
			const std::vector<std::string> & cells = Util::split(lines[i], ",");

			// Add input variable values from this table line
			for (std::size_t i = 0; i < num_ins; ++i)
			{
				try
				{
					DefCell cell(std::stod(Util::strip(cells[i])));
					if (cell.value < input_vars[i].min)
						input_vars[i].min = cell.value;
					if (cell.value > input_vars[i].max)
						input_vars[i].max = cell.value;
					row.push_back(cell);
				} catch (std::invalid_argument & e)
				{
					row.push_back(DefCell());
				}
			}

			// Add output variables values from this table line
			for (std::size_t i = num_ins; i < cells.size(); ++i)
			{
				try
				{
					DefCell cell(std::stod(Util::strip(cells[i])));
					if (cell.value < output_vars[i - num_ins].min)
						output_vars[i - num_ins].min = cell.value;
					if (cell.value > output_vars[i - num_ins].max)
						output_vars[i - num_ins].max = cell.value;
					row.push_back(cell);
				} catch (std::invalid_argument & e)
				{
					row.push_back(DefCell());
				}
			}
			rows.push_back(row);
		}
	}

	return DataSet(input_vars, output_vars, rows);
}

