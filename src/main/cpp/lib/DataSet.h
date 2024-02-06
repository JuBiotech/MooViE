#ifndef DATASET_H_
#define DATASET_H_

#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <cfloat>
#include <stdexcept>
#include <memory>
#include <clocale>

#include "Utils.h"

/** A class for storing data of some type. It is accessible row-wise
 * and not directly changeble, but columns can be swapped, toggled and restricted.
 * Rows are divided in INPUTs and OUTPUTs, so they can be used in MooViE terms.
 * It can also be parsed from a CSV file.
 *
 * @brief Table of data
 *
 * @author stratmann
 * @date 28.11.2017
 */
template<typename T>
  class DataSet
  {
  public:
    /** Variable represents an entity attribute and stores its name,
     * maximal and minimal value.
     *
     * @brief Header description
     */
    struct Variable
    {
      /** Minimal value */
      T min;
      /** Maximal value */
      T max;
      /** Variable name */
      std::string name;
      /** Unit of the Variables values */
      std::string unit;

      /** Creates a Variable with the given name, min and max value.
       *
       * @param min the min value
       * @param max the max value
       * @param name the name
       */
      Variable (T min_, T max_, const std::string & name_,
		const std::string & unit_ = "") :
	  min (min_), max (max_), name (name_), unit (unit_)
      {
      }
    };

    /** Stores the value of a cell. The value is 0 if
     * the Cell is a null cell.
     *
     * @brief Cell of a data table
     */
    struct Cell
    {
      /** Creates a new null Cell. */
      Cell () :
	  null (true), value (0)
      {
      }

      /** Creates a new non-null Cell storing the value of T */
      Cell (T value_) :
	  null (false), value (value_)
      {
      }

      /** Null or not */
      const bool null;

      /** The value of the cell */
      const T value;
    };

    /** MooViE columns can either represent outputs or inputs. This
     * is indicated by a member of the type ColumnType.
     */
    enum ColumnType
    {
      INPUT, OUTPUT
    };

    /** DataColumn represents a column of a data set. It has a type (INPUT,
     * OUTPUT), a Variable and a set of cells
     *
     * @brief Column of a data table
     */
    struct DataColumn
    {
      /** The ColumnType */
      const ColumnType type;
      /** The header information about this column (name, unit, range) */
      Variable var;
      /** An array of the cells of this column */
      std::vector<Cell> cells;

      /** Creates a new column with given ColumnType and Variable.
       *
       * @param type_ the ColumnType
       * @param var_ the Variable
       */
      DataColumn (ColumnType type_, Variable var_) :
	  type (type_), var (var_)
      {
      }
    };

    /** A mock column that is supposed to hold a pointer to the column
     * storage. The DataColumns can be swapped between the MockColumn.
     * MockColumns can be enabled and disabled which alters the number
     * of cells in the DataRows accordingly.
     *
     * @brief Technical column for internal use
     */
    class MockColumn
    {
    public:
      /** Creates a MockColumn from a DataColumn. This MockColumn wraps
       * and it and provides read-only access to all its components.
       *
       * @param _column the DataColumn
       */
      MockColumn (DataColumn* column) :
	  m_column (column), m_var (column->var), m_enabled (true)
      {
      }

      /** Accesses the i-th Cell in the stored column.
       *
       * @param i the row index
       *
       * @return the Cell
       */
      const Cell&
      operator[] (std::size_t i) const
      {
	return m_column->cells[i];
      }

      void
	  set_range (double l_restr, double u_restr)
      {
    m_var.min = l_restr;
    m_var.max = u_restr;
      }

      /** Sets the enabled flag of this MockColumn to the specified
       * value.
       *
       * @param enabled set enabled or not
       */
      void
      set_enabled (bool enabled)
      {
	m_enabled = enabled;
      }

      /** Returns the ColumnType of this MockColumn. It is either INPUT
       * or OUTPUT.
       *
       * @return the ColumnType
       */
      ColumnType
      get_type () const
      {
	return m_column->type;
      }

      /** Returns the Variable of this MockColumn.
       *
       * @return the Variable
       */
      Variable
      get_var () const
      {
	return m_var;
      }

      /** Returns the size of this MockColumn.
       *
       * @return the size
       */
      std::size_t
      size () const
      {
	return m_column->cells.size ();
      }

      /** Returns the value of the enabled flag.
       *
       * @return enabled or not
       */
      bool
      is_enabled () const
      {
	return m_enabled;
      }

      /** Class function to swap the columns of two MockColumns.
       *
       * @param m0 the first MockColumn
       * @param m1 the second MockColumn
       */
      static void
      swap (MockColumn& m0, MockColumn& m1)
      {
	std::swap (m0.m_column, m1.m_column);
	std::swap (m0.m_var, m1.m_var);
	std::swap (m0.m_enabled, m1.m_enabled);
      }
    private:
      /** A shared pointer which points to the actual m_column */
      std::shared_ptr<DataColumn> m_column;
      /** Variable range header information */
      Variable m_var;
      /** The enabled flag */
      bool m_enabled;
    };

    /** DataRow represents a row in this DataSet. A DataRow does not become invalid when
     * column order is changed or a column is disabled. It might get invalid when restricting
     * columns to a certain interval.
     *
     * @brief Row of a data table
     */
    class DataRow
    {
    public:
      class const_iterator : public std::iterator<std::input_iterator_tag,
	  const Cell>
      {
	typename std::vector<MockColumn>::const_iterator it;
	typename std::vector<MockColumn>::const_iterator end;
	const std::size_t offset;
      public:
	explicit
	const_iterator (
	    const typename std::vector<MockColumn>::const_iterator& _it,
	    const typename std::vector<MockColumn>::const_iterator& _end,
	    std::size_t _offset) :
	    it (_it), end (_end), offset (_offset)
	{
	}

	const_iterator&
	operator++ ()
	{
	  do
	    {
	      ++it;
	    }
	  while (not it->is_enabled () and it != end);
	  return *this;
	}
	const_iterator
	operator++ (int)
	{
	  const_iterator retval = *this;
	  ++(*this);
	  return retval;
	}
	bool
	operator== (const const_iterator & other) const
	{
	  return it == other.it;
	}
	bool
	operator!= (const const_iterator & other) const
	{
	  return it != other.it;
	}
	const Cell&
	operator* () const
	{
	  return (*it)[offset];
	}
	;
      };

    private:
      /** The array of MockColumns */
      const std::vector<MockColumn>& m_columns;
      /** The number of enabled columns */
      const std::size_t& m_enabled_columns;
      /** The number of this DataRow */
      const std::size_t m_offset;
      /** The enabled flag */
      bool m_enabled;

    public:
      /** Creates a DataRow from given reference to the columns and to the number of enabled columns
       * (needed for update) and the row number (aka column offset).
       *
       * @param columns a reference to the column array
       * @param enabled_columns a reference to the number of enabled columns
       * @param offset the row offset
       */
      DataRow (const std::vector<MockColumn>& columns,
	       const std::size_t& enabled_columns, std::size_t offset) :
	  m_columns (columns), m_enabled_columns (enabled_columns), m_offset (
	      offset), m_enabled (true)
      {
      }

      /** Accesses the i-th Cell of this DataRow.
       *
       * @param i the index
       * @return the Cell
       */
      const Cell&
      operator[] (std::size_t i) const
      {
	if (i >= m_enabled_columns)
	  {
	    throw std::out_of_range (
		"index exceeds range [0,"
		    + std::to_string (m_enabled_columns) + "), given: "
		    + std::to_string (i));
	  }

	for (std::size_t j = 0; j <= i; ++j)
	  {
	    if (not m_columns[j].is_enabled ())
	      ++i;
	  }

	return m_columns[i][m_offset];
      }

      /** Sets the enabled flag of this MockColumn to the specified
       * value.
       *
       * @param enabled set enabled or not
       */
      void
      set_enabled (bool enabled)
      {
	m_enabled = enabled;
      }

      /** Returns the size of this MockColumn.
       *
       * @return the size
       */
      std::size_t
      size () const
      {
	return m_enabled_columns;
      }

      /** Returns the value of the enabled flag.
       *
       * @return enabled or not
       */
      bool
      is_enabled () const
      {
	return m_enabled;
      }

      /** Returns a const_iterator pointing to the first cell in
       * this DataRow.
       *
       * @return the iterator
       */
      const_iterator
      begin () const
      {
	return const_iterator (m_columns.begin (), m_columns.end (), m_offset);
      }

      /** Returns a const_iterator pointing to the end of this
       * DataRow
       *
       * @return the iterator
       */
      const_iterator
      end () const
      {
	return const_iterator (m_columns.end (), m_columns.end (), m_offset);
      }
    };

    class const_iterator : public std::iterator<std::input_iterator_tag,
	const DataRow>
    {
      typename std::vector<DataRow>::const_iterator m_it;
      typename std::vector<DataRow>::const_iterator m_end;
    public:
      explicit
      const_iterator (const typename std::vector<DataRow>::const_iterator & it,
		      const typename std::vector<DataRow>::const_iterator & end) :
	  m_it (it), m_end (end)
      {
	while (m_it != m_end and not m_it->is_enabled ())
	  {
	    ++m_it;
	  }
      }
      const_iterator&
      operator++ ()
      {
	do
	  {
	    ++m_it;
	  }
	while (m_it != m_end and not m_it->is_enabled ());
	return *this;
      }
      const_iterator
      operator++ (int)
      {
	const_iterator retval = *this;
	++(*this);
	return retval;
      }
      bool
      operator== (const const_iterator & other) const
      {
	return m_it == other.m_it;
      }
      bool
      operator!= (const const_iterator & other) const
      {
	return m_it != other.m_it;
      }
      const DataRow &
      operator* () const
      {
	return *m_it;
      }
      ;
    };

  private:
    /** The row and m_column numbers */
    std::size_t m_num_rows, m_num_cols;
    /** The number of inputs and outputs */
    std::size_t m_num_inputs, m_num_outputs;
    /** A technical constant for dividing the cols vector into inputs and outputs */
    std::size_t m_separator;
    /** The columns of this data table */
    std::vector<MockColumn> m_cols;
    /** The rows of this data table */
    std::vector<DataRow> m_rows;

  public:
    /** Creates an empty DataSet.
     */
    DataSet () :
	m_num_rows (0), m_num_cols (0), m_num_inputs (0), m_num_outputs (0), m_separator (
	    0)
    {
    }

    /** Parses a DataSet from a given CSV file. The table must have the form:
     * <input1>[<uniti1>], ... , <inputN>[<unitiN>], <output1>[<unito1>], ... , <outputM>[<unitoM>]
     * <datai1>, ... , <dataiN>, <datao1>, ... , <dataoM>
     *
     * @param fpath the CSV file path
     */
    DataSet (const std::string& fpath):
	m_num_rows (0), m_num_cols (0), m_num_inputs (0), m_num_outputs (0), m_separator (
	    0)
    {
      parse_from_csv(Util::read_file(fpath));
    }


    /** Returns a data table parsed from a csv encoded string
     * and encapsulated in a DataSet object. The table must have the
     * form:
     * <input1>[<uniti1>], ... , <inputN>[<unitiN>], <output1>[<unito1>], ... , <outputM>[<unitoM>]
     * <datai1>, ... , <dataiN>, <datao1>, ... , <dataoM>
     *
     * @param cont the csv encoded string
     * @param num_ins the number of input variables
     * @param separator the column seperator used in this csv string
     * @param comment the comment indicator used in this csv string
     * @param newline the newline indicator used in this csv string
     */
    void
    parse_from_csv (const std::string & cont, std::string separator = ",",
		    std::string comment = "#", std::string newline = "\n");

    /** Enables/disables a column. The DataRows now do not contain the affected Cell anymore.
     *
     * @param c the column index
     * @param mode set enabled or disabled
     *
     * @throw out_of_range id c is incorrect
     */
    void
    toggle_column (std::size_t c, bool mode)
    {
      if (c >= m_cols.size ())
	{
	  throw std::out_of_range (
	      "index exceeds range [0, " + std::to_string (m_num_cols)
		  + "), given: " + std::to_string (c));
	}

      if (not mode and m_cols[c].is_enabled ())
	{
	  --m_num_cols;

	  if (m_cols[c].get_type () == ColumnType::INPUT)
	    {
	      --m_num_inputs;
	    }
	  else
	    {
	      --m_num_outputs;
	    }
	}
      else if (mode and not m_cols[c].is_enabled ())
	{
	  ++m_num_cols;

	  if (m_cols[c].get_type () == ColumnType::INPUT)
	    {
	      ++m_num_inputs;
	    }
	  else
	    {
	      ++m_num_outputs;
	    }
	}

      m_cols[c].set_enabled (mode);
    }

    /** Swaps the two columns with the given index. The DataRows are changed accordingly.
     *
     * @param c0 the index of the first column
     * @param c1 the index of the second column
     *
     * @throw out_of_bounds if indices are incorrect
     */
    void
    swap_columns (std::size_t c0, std::size_t c1)
    {
      if (c0 >= m_cols.size())
	{
	  throw std::out_of_range (
	      "index exceeds range [0, " + std::to_string (m_cols.size())
		  + "), given: " + std::to_string (c0));
	}
      if (c1 >= m_cols.size())
	{
	  throw std::out_of_range (
	      "index exceeds range [0, " + std::to_string (m_cols.size())
		  + "), given: " + std::to_string (c1));
	}

      MockColumn::swap (m_cols[c0], m_cols[c1]);
    }

    /** Restricts a column to values in the given interval. The DataRows that contain a Cell
     * not fitting in this interval will be disabled.
     *
     * @param c the column index
     * @param l_restr lower restriction value
     * @param u_restr upper restriction value
     *
     * @throw out_of range if c is incorrect
     */
    void
    restrict_column (std::size_t c, T l_restr, T u_restr)
    {
      if (c >= m_cols.size())
	{
	  throw std::out_of_range (
	      "index exceeds range [0, " + std::to_string (m_cols.size())
		  + "), given: " + std::to_string (c));
	}

      m_cols[c].set_range (l_restr, u_restr);
      std::size_t num_disabled = std::count_if(m_cols.begin(), m_cols.begin() + c,
                                               [](const MockColumn& c) -> std::size_t { return not c.is_enabled(); });
      for (DataRow& r : m_rows)
	{
	  if (r.is_enabled())
	    {
	      if (r[c - num_disabled].value < l_restr || r[c - num_disabled].value > u_restr)
	        {
	          r.set_enabled (false);
	          --m_num_rows;
	        }
	    }
	  else
	    {
          bool is_active = true;
          std::size_t data_row_index = 0;
          for (std::size_t i = 0; i < m_cols.size(); ++i)
            {
              if (m_cols[i].is_enabled()) {
                  Variable variable = m_cols[i].get_var();
                  if (r[data_row_index].value < variable.min || r[data_row_index].value > variable.max) {
                      is_active = false;
                      break;
                  }
                  ++data_row_index;
              }
            }
          if (is_active)
            {
              r.set_enabled (true);
              ++m_num_rows;
            }
	    }
	}
    }

    /** Returns the number of active columns in this table. For every
     * toggled-off column this size decreases by 1.
     *
     * @return the number of active columns
     */
    inline std::size_t
    get_num_active_cols () const
    {
      return m_num_cols;
    }

    /** Returns the total number of columns in this table. This includes
     * toggled-off columns.
     *
     * @return the number of total columns
     */
    inline std::size_t
    get_num_cols () const
    {
      return m_cols.size();
    }

    /** Returns the number of rows in this table.
     *
     * @return the number of rows
     */
    inline std::size_t
    get_num_rows () const
    {
      return m_num_rows;
    }

    /** Returns the number of active inputs in this table.
     * For every toggled-off column this size decreases by 1.
     *
     * @return the number of active inputs
     */
    inline std::size_t
    get_num_active_inputs () const
    {
      return m_num_inputs;
    }

    /** Returns the total number of inputs in this table. This includes
     * toggled-off columns.
     *
     * @return the total number of inputs
     */
    inline std::size_t
    get_num_inputs () const
    {
      return m_separator;
    }

    /** Returns the number of outputs in this table. For every
     * toggled-off column this size decreases by 1.
     *
     * @return the number of active outputs
     */
    inline std::size_t
    get_num_active_outputs () const
    {
      return m_num_outputs;
    }

    /** Returns the total number of outputs in this table. This includes
     * toggled-off columns.
     *
     * @return the total number of outputs
     */
    inline std::size_t
    get_num_outputs () const
    {
      return m_cols.size() - m_separator;
    }

    /** Returns the row at position i in the table (starting at 0). DataRow can
     * be used like a vector from the given type.
     *
     * @return the DataRow object
     */
    inline const DataRow &
    operator[] (std::size_t i) const
    {
      return m_rows[i];
    }

    /** Returns a constant vector containing row (referred to
     * as variables) information like the name and min/max values
     * of the selected row.
     *
     * @return the input variables
     */
    inline std::vector<Variable>
    input_variables (void) const
    {
      std::vector<Variable> input_vars;

      for (std::size_t i = 0; i < m_separator; ++i)
	{
	  if (m_cols[i].is_enabled ())
	    {
	      input_vars.push_back (m_cols[i].get_var ());
	    }
	}

      return input_vars;
    }

    /** Returns a constant vector containing column (referred to
     * as variables) information like the name and min/max values
     * of the selected row.
     *
     * @return the output variables
     */
    inline std::vector<Variable>
    output_variables (void) const
    {
      std::vector<Variable> output_vars;

      for (std::size_t i = m_separator; i < m_cols.size (); ++i)
	{
	  if (m_cols[i].is_enabled ())
	    {
	      output_vars.push_back (m_cols[i].get_var ());
	    }
	}

      return output_vars;
    }

    /** Returns a constant iterator pointing to the first DataRow.
     *
     * @return a const_iterator
     */
    inline const_iterator
    begin () const
    {
      return const_iterator (m_rows.begin (), m_rows.end ());
    }

    /** Returns a constant iterator pointing to the end element of the
     * DataRow storage.
     *
     * @return a const_iterator
     */
    inline const_iterator
    end () const
    {
      return const_iterator (m_rows.end (), m_rows.end ());
    }

    /** Extracts the variable name and unit from a header entry
     *
     * @return a pair of strings, the first one is the name, the second one the unit
     */
    std::pair<std::string, std::string>
    extract_header_entry(const std::string & header) const
    {
    	// the unit is encapsulated by brackets. we use the last pair of brackets
    	std::size_t open_bracket = header.find_last_of ("["),
    			close_bracket = header.find_first_of ("]", open_bracket + 1);
    	// the name can be enclosed in quotes
    	std::size_t open_quote = header.find_first_of("\""),
    			close_quote = header.find_last_of("\"");

    	//the unit should not be part of the name
    	//if no unit is present, open_bracket is npos, aka -1 i.e. very large
    	close_quote = std::min(close_quote, open_bracket);

    	std::string name = "", unit = "";

    	// get unit only if it was specified
    	if (open_bracket != std::string::npos
    			&& close_bracket != std::string::npos)
    	{
    		unit = header.substr (
    				open_bracket + 1, close_bracket - open_bracket - 1);
    	}

    	// if there are no quotes, we start after i# or o#
    	if (open_quote == std::string::npos)
    	{
    		open_quote = 1;
    	}

    	//get the name
    	name = header.substr (open_quote + 1,
    			close_quote - open_quote - 1);

    	return std::make_pair(name, unit);

    }
  };

template<typename T>
  void
  DataSet<T>::parse_from_csv (const std::string & cont, std::string separator,
			      std::string comment, std::string newline)
  {
    static_assert(std::is_same<T, double>::value, "Should not be compiled.");
  }

template<>
  void
  DataSet<double>::parse_from_csv (const std::string & cont,
				   std::string separator, std::string comment,
				   std::string newline);

typedef DataSet<double> DefDataSet;
typedef DefDataSet::Variable DefVariable;
typedef DefDataSet::DataRow DefDataRow;
typedef DefDataSet::Cell DefCell;

#endif /* DATASET_H_ */
