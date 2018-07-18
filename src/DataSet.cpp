#include <DataSet.h>
#include <iostream>

template<>
DataSet<double>* DataSet<double>::parse_from_csv(const std::string& cont,
		std::string separator, std::string comment, std::string newline)
{
	std::vector<DataColumn*> columns;
	const std::vector<std::string> & lines = Util::split(cont, newline);

	std::size_t header_pos = 0;
	while (lines[header_pos].find_first_not_of(' ') == std::string::npos ||
			lines[header_pos][lines[header_pos].find_first_not_of(' ')] == '#')
	{
		++header_pos;
	}
	const std::vector<std::string> & header = Util::split(lines[header_pos], separator);

	size_t i = 0;

	// Add input variables from table header
	while (i < header.size() && header[i].find_first_of("i#") == 0)
	{
		std::size_t open_bracket = header[i].find_first_of('['),
				close_bracket = header[i].find_first_of(']');
		if (open_bracket != std::string::npos
				&& close_bracket != std::string::npos)
		{
			std::string name = header[i].substr(2, open_bracket - 2),
					unit = header[i].substr(open_bracket + 1, close_bracket - open_bracket - 1);
			columns.push_back(
					new DataColumn(
							ColumnType::INPUT,
							DefVariable(DBL_MAX, DBL_MIN, Util::strip(name), Util::strip(unit))
					)
			);
		}
		else
		{
			std::string name = header[i].substr(2, header[i].length() - 2);
			columns.push_back(
					new DataColumn(
							ColumnType::INPUT,
							DefVariable(DBL_MAX, DBL_MIN, Util::strip(name))
					)
			);
		}
		++i;
	}
	std::size_t num_inputs = i;

	// Add output variables from table header
	while (i < header.size() && header[i].find_first_of("o#") == 0)
	{
		std::size_t open_bracket = header[i].find_first_of('['),
				close_bracket = header[i].find_first_of(']');
		if (open_bracket != std::string::npos
				&& close_bracket != std::string::npos)
		{
			std::string name = header[i].substr(2, open_bracket - 2),
					unit = header[i].substr(open_bracket + 1, close_bracket - open_bracket - 2);
			columns.push_back(
					new DataColumn(
							ColumnType::OUTPUT,
							DefVariable(DBL_MAX, DBL_MIN, Util::strip(name), Util::strip(unit))
					)
			);
		}
		else
		{
			std::string name = header[i].substr(2, header[i].length() - 2);
			columns.push_back(
					new DataColumn(
							ColumnType::OUTPUT,
							DefVariable(DBL_MAX, DBL_MIN, Util::strip(name))
					)
			);
		}
		++i;
	}
	std::size_t num_outputs = i - num_inputs;

	// Add values from table body
	for (std::size_t i = header_pos + 1; i < lines.size(); ++i)
	{
		// Remove empty/comment lines
		if (lines[i].find_first_not_of(' ') != std::string::npos
				|| lines[i].find_first_of(comment) != lines[i].find_first_not_of(' ') + 1)
		{
			const std::vector<std::string> & cells = Util::split(lines[i], ",", false);

			if (num_inputs + num_outputs != cells.size())
			{
				throw std::length_error(
						"Row " + std::to_string(i) + " has an invalid count of cells"
						+ "(expected: " + std::to_string(num_inputs + num_outputs)
						+ ", given: " + std::to_string(cells.size()) + ")"
				);
			}

			// Add input variable values from this table line
			for (std::size_t i = 0; i < num_inputs; ++i)
			{
				try
				{
					DefCell cell(std::stod(Util::strip(cells[i])));
					if (cell.value < columns[i]->var.min)
						columns[i]->var.min = cell.value;
					if (cell.value > columns[i]->var.max)
						columns[i]->var.max = cell.value;
					columns[i]->cells.push_back(cell);
				} catch (std::invalid_argument & e)
				{
					columns[i]->cells.emplace_back();
				}
			}

			// Add output variables values from this table line
			for (std::size_t i = num_inputs; i < cells.size(); ++i)
			{
				try
				{
					DefCell cell(std::stod(Util::strip(cells[i])));
					if (cell.value < columns[i]->var.min)
						columns[i]->var.min = cell.value;
					if (cell.value > columns[i]->var.max)
						columns[i]->var.max = cell.value;
					columns[i]->cells.push_back(cell);
				} catch (std::invalid_argument & e)
				{
					columns[i]->cells.emplace_back();
				}
			}
		}
	}

	std::vector<MockColumn> mock_columns;
	mock_columns.reserve(columns.size());
	for (std::size_t i = 0; i < columns.size(); ++i)
	{
		mock_columns.emplace_back(columns[i]);
	}
	return new DataSet(mock_columns);
}

