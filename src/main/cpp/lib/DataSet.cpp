#include "DataSet.h"

template<>
  void
  DataSet<double>::parse_from_csv (const std::string& cont,
				   std::string separator, std::string comment,
				   std::string newline)
  {
    std::setlocale(LC_NUMERIC, "en_US.UTF-8");

    std::vector<DataColumn*> columns;
    const std::vector<std::string> & lines = Util::split (cont, newline);

    std::size_t header_pos = 0;
    while (lines[header_pos].find_first_not_of (Util::BLANKS) == std::string::npos
	|| lines[header_pos][lines[header_pos].find_first_not_of (Util::BLANKS)] == '#')
      {
	++header_pos;
      }
    const std::vector<std::string> & header = Util::split (lines[header_pos],
							   separator);

    size_t i = 0;

    // Add input variables from table header
    std::vector<std::pair<double, double>> input_ranges;
    while (i < header.size () && 
			(header[i].find ("i#") != std::string::npos || header[i].find ("I#") != std::string::npos))
      {
          auto entry = extract_header_entry(Util::strip(header[i]));
          std::string name = std::get<0>(entry), unit = std::get<1>(entry),
                  range_min_str = std::get<2>(entry), range_max_str = std::get<3>(entry);

          double range_min = std::numeric_limits<double>::min(), range_max = std::numeric_limits<double>::max();
          if (not range_min_str.empty())
          {
              range_min = std::stod(range_min_str);
          }
          if (not range_max_str.empty())
          {
              range_max = std::stod(range_max_str);
          }
          input_ranges.emplace_back(range_min, range_max);

	    columns.push_back (
		new DataColumn (
		    ColumnType::INPUT,
		    DefVariable (DBL_MAX, DBL_MIN, Util::strip (name),
				 Util::strip (unit))));
	++i;
      }
    std::size_t num_inputs = i;

    // Add output variables from table header
      std::vector<std::pair<double, double>> output_ranges;
    while (i < header.size () && 
			(header[i].find ("o#") != std::string::npos || header[i].find ("O#") != std::string::npos))
      {
  	  auto entry = extract_header_entry(Util::strip(header[i]));
          std::string name = std::get<0>(entry), unit = std::get<1>(entry),
                  range_min_str = std::get<2>(entry), range_max_str = std::get<3>(entry);

          double range_min = std::numeric_limits<double>::min(), range_max = std::numeric_limits<double>::max();
          if (not range_min_str.empty())
          {
              range_min = std::stod(range_min_str);
          }
          if (not range_max_str.empty())
          {
              range_max = std::stod(range_max_str);
          }
          output_ranges.emplace_back(range_min, range_max);

	    columns.push_back (
		new DataColumn (
		    ColumnType::OUTPUT,
		    DefVariable (DBL_MAX, DBL_MIN, Util::strip (name),
				 Util::strip (unit))));
	++i;
      }
    std::size_t num_outputs = i - num_inputs;

    // Add values from table body
    for (std::size_t rowc = header_pos + 1; rowc < lines.size (); ++rowc)
      {
	// Remove empty/comment lines
	if (lines[rowc].find_first_not_of (Util::BLANKS) != std::string::npos
	    && lines[rowc].find_first_of (comment)
		!= lines[rowc].find_first_not_of (Util::BLANKS) + 1)
	  {
	    const std::vector<std::string> & cells = Util::split (lines[rowc], ",",
								  false);

	    if (num_inputs + num_outputs != cells.size ())
	      {
		throw std::length_error (
		    "Row " + std::to_string (rowc)
			+ " has an invalid count of cells" + "(expected: "
			+ std::to_string (num_inputs + num_outputs)
			+ ", given: " + std::to_string (cells.size ()) + ")");
	      }

	    // Add input variable values from this table line
	    for (std::size_t i = 0; i < num_inputs; ++i)
	      {
		try
		  {
		    double val = 0;
		    if (Util::strip (cells[i]).empty() || std::isnan(val))
		      val = std::numeric_limits<double>::quiet_NaN();
		    else
		      val = std::stod (Util::strip (cells[i]));
		    DefCell cell (val);
		    if (cell.value < columns[i]->var.min)
		      columns[i]->var.min = cell.value;
		    if (cell.value > columns[i]->var.max)
		      columns[i]->var.max = cell.value;
		    columns[i]->cells.push_back (cell);
		  }
		catch (std::invalid_argument & e)
		  {
		    columns[i]->cells.emplace_back ();
		  }
	      }

	    // Add output variables values from this table line
	    for (std::size_t i = num_inputs; i < cells.size (); ++i)
	      {
		try
		  {
		    DefCell cell (std::stod (Util::strip (cells[i])));
		    if (cell.value < columns[i]->var.min)
		      columns[i]->var.min = cell.value;
		    if (cell.value > columns[i]->var.max)
		      columns[i]->var.max = cell.value;
		    columns[i]->cells.push_back (cell);
		  }
		catch (std::invalid_argument & e)
		  {
		    columns[i]->cells.emplace_back ();
		  }
	      }
	  }
      }

      // Add spacing to min and max if the variance of a column is 0
      for (std::size_t i = 0; i < columns.size(); ++i)
        {
      if (columns[i]->var.max - columns[i]->var.min <= std::numeric_limits<double>::epsilon())
        {
          columns[i]->var.min -= 1;
          columns[i]->var.max += 1;
        }
      }

    m_num_cols = columns.size ();
    m_num_rows = columns[0]->cells.size ();
    m_cols.reserve (m_num_cols);
    for (std::size_t i = 0; i < columns.size (); ++i)
      {
	m_cols.emplace_back (columns[i]);
      }

    m_num_inputs = m_separator = num_inputs;
    m_num_outputs = m_cols.size () - m_num_inputs;

    m_rows.reserve (m_cols[0].size ());
    for (std::size_t i = 0; i < m_cols[0].size (); ++i)
      {
	m_rows.push_back (DataRow (m_cols, m_num_cols, i));
      }

    for (std::size_t i = 0; i < m_num_inputs; ++i)
    {
        double range_min = m_cols[i].get_var().min, range_max = m_cols[i].get_var().max;
        if (input_ranges[i].first != std::numeric_limits<double>::min())
        {
            range_min = input_ranges[i].first;
        }
        if (input_ranges[i].second != std::numeric_limits<double>::max())
        {
            range_max = input_ranges[i].second;
        }
        this->restrict_column(i, range_min, range_max);
    }

      for (std::size_t i = 0; i < m_num_outputs; ++i)
      {
          double range_min = m_cols[i + m_num_inputs].get_var().min,
          range_max = m_cols[i + m_num_inputs].get_var().max;
          if (output_ranges[i].first  != std::numeric_limits<double>::min())
          {
              range_min = output_ranges[i].first;
          }
          if (output_ranges[i].second != std::numeric_limits<double>::max())
          {
              range_max = output_ranges[i].second;
          }
          this->restrict_column(i + m_num_inputs, range_min, range_max);
      }
  }

template<>
  std::string
  DataSet<double>::write_to_csv (std::string separator, std::string newline)
  {
    std::string content;

      std::setlocale(LC_NUMERIC, "en_US.UTF-8");
      for (DefVariable var : this->input_variables ())
      {
          content += "i#" + var.name;
          if (!var.unit.empty())
          {
              content += "[" + var.unit + "]";
          }
          content += "(" + std::to_string(var.min) + "," + std::to_string(var.max) + ")" + separator + " ";
      }

      for (DefVariable var : this->output_variables ())
      {
          content += "o#" + var.name;
          if (!var.unit.empty())
          {
              content += "[" + var.unit + "]";
          }
          content += "(" + std::to_string(var.min) + "," + std::to_string(var.max) + ")" + separator + " ";
      }

      content += newline;

      for (const DefDataRow & row : *this)
      {
          for (std::size_t i = 0; i < row.size(); ++i)
          {
              if (row[i].null) {
                  content += separator;
              }
              else
              {
                  content += std::to_string(row[i].value) + separator;
              }
          }

          content += newline;
      }

      return content;
  }