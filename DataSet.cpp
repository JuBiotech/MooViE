/*
 * CSVParser.cpp
 *
 *  Created on: 28.11.2017
 *      Author: IBT\stratmann
 */

#include "DataSet.h"

template<>
DataSet<double> DataSet<double>::parse_from_csv(const std::string & cont)
{
	std::vector<DefVar> variables;
	std::vector<DefDataRow> rows;
	const std::vector<std::string> & lines = DataSet::split(cont, "\n");

	for (std::string varname : DataSet::split(lines[0], ","))
	{
		variables.push_back(Var(DBL_MAX, DBL_MIN, varname));
	}
	for (std::size_t i = 1; i < lines.size(); ++i)
	{
		if (lines[i].find_first_not_of(' ', 0) != std::string::npos
				|| lines[i][lines[i].find_first_not_of(' ', 0)] == '#')
		{
			DefDataRow row;
			const std::vector<std::string> & cells = DataSet::split(lines[0], ",");
			for (std::size_t i = 0; i < cells.size(); ++i)
			{
				try
				{
					DefCell cell(std::stod(cells[i]));
					if (cell.value < variables[i].min)
						variables[i].min = cell.value;
					if (cell.value > variables[i].max)
						variables[i].max = cell.value;
					row.push_back(cell);
				} catch (std::invalid_argument & e)
				{
					row.push_back(DefCell());
				}
			}
			rows.push_back(row);
		}
	}

	return DataSet(variables, rows);
}

