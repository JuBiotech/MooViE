/*
 * CSVParser.h
 *
 *  Created on: 28.11.2017
 *      Author: IBT\stratmann
 */

#ifndef DATASET_H_
#define DATASET_H_

#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <cfloat>
#include <stdexcept>
#include <memory>

#include <Utils.h>

/** DataSet stores data. It is accessible
 * via iterator, but cannot be modified.
 * @brief the DataSet class
 * @author stratmann
 * @date 28.11.2017
 */
template<typename T>
class DataSet
{
public:
	/** Variable represents an entity attribute and stores its name,
	 * maximal and minimal value.
	 * @brief The Variable struct
	 */
	struct Variable
	{
		/** Minimal value */
		T min;

		/** Maximal value */
		T max;

		/** Variable name */
		std::string name;

		/* Unit of the Variables values */
		std::string unit;

		/** Creates a Variable with the given name, min and max value.
		 *
		 * @brief Variable
		 *
		 * @param min the min value
		 * @param max the max value
		 * @param name the name
		 */
		Variable(T min_, T max_, const std::string & name_, const std::string & unit_ = "") :
				min(min_), max(max_), name(name_), unit(unit_)
		{}
	};

	/** Stores the value of a cell. The value is 0 if
	 * the Cell is a null cell.
	 * @brief the Cell struct
	 */
	struct Cell
	{
		/** Creates a new null Cell. */
		Cell() :
				null(true), value(0)
		{
		}

		/** Creates a new non-null Cell storing the value of T */
		Cell(T value_) :
				null(false), value(value_)
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
	 * @brief a column
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
		 * @param _type the ColumnType
		 * @param _var the Variable
		 */
		DataColumn(ColumnType _type, Variable _var)
		: type(_type), var(_var)
		{}
	};

	/** A mock column that is supposed to hold a pointer to the column
	 * storage. The DataColumns can be swapped between the MockColumn.
	 * MockColumns can be enabled and disabled which alters the number
	 * of cells in the DataRows accordingly.
	 *
	 * @brief a mock column
	 */
	class MockColumn
	{
	public:
		/** Creates a MockColumn from a DataColumn. This MockColumn wraps
		 * and it and provides read-only access to all its components.
		 *
		 * @param _column the DataColumn
		 */
		MockColumn(DataColumn* _column)
		: column(_column), enabled(true)
		{
		}

		/** Accesses the i-th Cell in the stored column.
		 *
		 * @param i the row index
		 * @return the Cell
		 */
		const Cell& operator[](std::size_t i) const
		{
			return column->cells[i];
		}

		/** Sets the enabled flag of this MockColumn to the specified
		 * value.
		 *
		 * @param _enabled set enabled or not
		 */
		void set_enabled(bool _enabled)
		{
			enabled = _enabled;
		}

		/** Returns the ColumnType of this MockColumn. It is either INPUT
		 * or OUTPUT.
		 *
		 * @return the ColumnType
		 */
		ColumnType get_type() const
		{
			return column->type;
		}

		/** Returns the Variable of this MockColumn.
		 *
		 * @return the Variable
		 */
		Variable get_var() const
		{
			return column->var;
		}

		/** Returns the size of this MockColumn.
		 *
		 * @return the size
		 */
		std::size_t size() const
		{
			return column->cells.size();
		}

		/** Returns the value of the enabled flag.
		 *
		 * @return enabled or not
		 */
		bool is_enabled() const
		{
			return enabled;
		}

		/** Class function to swap the columns of two MockColumns.
		 *
		 * @param m0 the first MockColumn
		 * @param m1 the second MockColumn
		 */
		static void swap(MockColumn& m0, MockColumn& m1)
		{
			std::swap(m0.column, m1.column);
		}
	private:
		/** A shared pointer which points to the actual column */
		std::shared_ptr<DataColumn> column;
		/** The enabled flag */
		bool enabled;
	};

	/** DataRow represents a row in this DataSet. A DataRow does not become invalid when
	 * column order is changed or a column is disabled. It might get invalid when restricting
	 * columns to a certain interval.
	 *
	 * @brief DataRow class
	 */
	class DataRow
	{
	public:
		class const_iterator: public std::iterator<std::input_iterator_tag, const Cell>
		{
				typename std::vector<MockColumn>::const_iterator it;
				typename std::vector<MockColumn>::const_iterator end;
				const std::size_t offset;
			public:
				explicit const_iterator(
						const typename std::vector<MockColumn>::const_iterator& _it,
						const typename std::vector<MockColumn>::const_iterator& _end,
						std::size_t _offset) :
						it(_it), end(_end), offset(_offset)
				{
				}

				const_iterator& operator++()
				{
					do
					{
						++it;
					} while (not it->is_enabled() and it != end);
					return *this;
				}
				const_iterator operator++(int)
				{
					const_iterator retval = *this;
					++(*this);
					return retval;
				}
				bool operator==(const const_iterator & other) const
				{
					return it == other.it;
				}
				bool operator!=(const const_iterator & other) const
				{
					return it != other.it;
				}
				const Cell& operator*() const
				{
					return (*it)[offset];
				}
				;
			};
	public:
		/** Creates a DataRow from given reference to the columns and to the number of enabled columns
		 * (needed for update) and the row number (aka column offset).
		 *
		 * @param _columns a reference to the column array
		 * @param _enabled_columns a reference to the number of enabled columns
		 * @param _offset the row offset
		 */
		DataRow (const std::vector<MockColumn>& _columns, const std::size_t& _enabled_columns, std::size_t _offset)
		: columns(_columns), enabled_columns(_enabled_columns), offset(_offset), enabled(true)
		{
		}

		/** Accesses the i-th Cell of this DataRow.
		 *
		 * @param i the index
		 * @return the Cell
		 */
		const Cell& operator[](std::size_t i) const
		{
			if (i >= enabled_columns)
			{
				throw std::out_of_range("index exceeds range 0-" + std::to_string(enabled_columns - 1)
											+ ", (" + std::to_string(i) + " given)");
			}

			for (std::size_t j = 0; j <= i; ++j)
			{
				if (not columns[j].is_enabled()) ++i;
			}

			return columns[i][offset];
		}

		/** Sets the enabled flag of this MockColumn to the specified
		 * value.
		 *
		 * @param _enabled set enabled or not
		 */
		void set_enabled(bool _enabled)
		{
			enabled = _enabled;
		}

		/** Returns the size of this MockColumn.
		 *
		 * @return the size
		 */
		std::size_t size() const
		{
			return enabled_columns;
		}

		/** Returns the value of the enabled flag.
		 *
		 * @return enabled or not
		 */
		bool is_enabled() const
		{
			return enabled;
		}

		/** Returns a const_iterator pointing to the first cell in
		 * this DataRow.
		 *
		 * @return the iterator
		 */
		const_iterator begin() const
		{
			return const_iterator(columns.begin(), columns.end());
		}

		/** Returns a const_iterator pointing to the end of this
		 * DataRow
		 *
		 * @return the iterator
		 */
		const_iterator end() const
		{
			return const_iterator(columns.end(), columns.end());
		}
	private:
		/** The array of MockColumns */
		const std::vector<MockColumn>& columns;
		/** The number of enabled columns */
		const std::size_t& enabled_columns;
		/** The number of this DataRow */
		const std::size_t offset;
		/** The enabled flag */
		bool enabled;
	};

	class const_iterator: public std::iterator<std::input_iterator_tag, const DataRow>
	{
		typename std::vector<DataRow>::const_iterator _it;
		typename std::vector<DataRow>::const_iterator _end;
	public:
		explicit const_iterator(
				const typename std::vector<DataRow>::const_iterator & it,
				const typename std::vector<DataRow>::const_iterator & end) :
				_it(it), _end(end)
		{
			while (not _it->is_enabled() and _it != _end)
			{
				++_it;
			}
		}
		const_iterator&
		operator++()
		{
			do
			{
				++_it;
			} while (not _it->is_enabled() and _it != _end);
			return *this;
		}
		const_iterator operator++(int)
		{
			const_iterator retval = *this;
			++(*this);
			return retval;
		}
		bool operator==(const const_iterator & other) const
		{
			return _it == other.__it;
		}
		bool operator!=(const const_iterator & other) const
		{
			return _it != other._it;
		}
		const DataRow & operator*() const
		{
			return *_it;
		}
		;
	};
public:
	/** Returns a data table parsed from a csv encoded string
	 * and encapsulated in a DataSet object. The table must have the
	 * form:
	 *  ║ input1 │ ... │ inputN ║ output1 │ ... │ outputM ║
	 *  ╟────────┼─────┼────────╫─────────┼─────┼─────────╢
	 *  ║  ...	 │     │  ...   ║   ...   │     │  	...   ║
	 *  ╟────────┼─────┼────────╫─────────┼─────┼─────────╢
	 *  ║  ...	 │     │  ...   ║   ...	  │   	│   ...	  ║
	 *  ╟────────┼─────┼────────╫─────────┼─────┼─────────╢
	 * @param cont the csv encoded string
	 * @param num_ins the number of input variables
	 * @param separator the column seperator used in this csv string
	 * @param comment the comment indicator used in this csv string
	 * @param newline the newline indicator used in this csv string
	 * @return the DataSet object
	 */
	static DataSet* parse_from_csv(const std::string & cont,
			std::string separator = ",", std::string comment = "#", std::string newline = "\n");

	/** Enables/disables a column. The DataRows now do not contain the affected Cell anymore.
	 *
	 * @param c the column index
	 * @param mode set enabled or disabled
	 */
	void toggle_column(std::size_t c, bool mode)
	{
		if (c >= num_cols)
		{
			throw std::out_of_range("index exceeds range 0-" + std::to_string(num_cols - 1)
										+ " (" + std::to_string(c) + " given)");
		}

		if (not mode and cols[c].is_enabled())
		{
			--num_cols;

			if (cols[c].get_type() == ColumnType::INPUT)
			{
				--num_inputs;
			}
			else
			{
				--num_outputs;
			}
		}

		cols[c].set_enabled(mode);
	}

	/** Swaps the two columns with the given index. The DataRows are changed accordingly.
	 *
	 * @param c0 the index of the first column
	 * @param c1 the index of the second column
	 *
	 * @throw out_of_bounds if indices are incorrect
	 */
	void swap_columns(std::size_t c0, std::size_t c1)
	{
		if (c0 >= num_cols)
		{
			throw std::out_of_range("index exceeds range 0-" + std::to_string(num_cols - 1)
										+ " (" + std::to_string(c0) + " given)");
		}
		if (c1 >= num_cols)
		{
			throw std::out_of_range("index exceeds range 0-" + std::to_string(num_cols - 1)
										+ " (" + std::to_string(c1) + " given)");
		}

		MockColumn::swap(cols[c0], cols[c1]);
	}

	/** Restricts a column to values in the given interval. The DataRows that contain a Cell
	 * not fitting in this interval will be disabled.
	 *
	 * @param c the column index
	 * @param l_restr lower restriction value
	 * @param u_restr upper restriction value
	 */
	void restrict_column(std::size_t c, T l_restr, T u_restr)
	{
		if (c >= num_cols)
		{
			throw std::out_of_range("index exceeds range 0-" + std::to_string(num_cols - 1)
									+ " (" + std::to_string(c) + " given)");
		}

		for (DataRow& r: rows)
		{
			if (r[c].value < l_restr || r[c].value > u_restr)
			{
				r.set_enabled(false);
				--num_rows;
			}
			else if (not r.is_enabled())
			{
				r.set_enabled(true);
				++num_rows;
			}
		}
	}

	/** Returns the number of columns in this table.
	 * @return the number of columns
	 */
	inline std::size_t get_num_cols() const
	{
		return num_cols;
	}

	/** Returns the number of rows in this table.
	 * @return the number of rows
	 */
	inline std::size_t get_num_rows() const
	{
		return num_rows;
	}

	/** Returns the number of inputs in this table.
	 * @return the number of inputs
	 */
	inline std::size_t get_num_inputs() const
	{
		return num_inputs;
	}

	/** Returns the number of outputs in this table.
	 * @return the number of outputs
	 */
	inline std::size_t get_num_outputs() const
	{
		return num_outputs;
	}

	/** Returns the row at position i in the table (starting at 0). DataRow can
	 * be used like a vector from the given type.
	 * @return the DataRow object
	 */
	inline const DataRow & operator[](std::size_t i) const
	{
		return rows[i];
	}

	/** Returns a constant vector containing row (referred to
	 * as variables) information like the name and min/max values
	 * of the selected row.
	 * @return the input variables
	 */
	inline std::vector<Variable> input_variables(void) const
	{
		std::vector<Variable> input_vars;

		for (std::size_t i = 0; i < separator; ++i)
		{
			if (cols[i].is_enabled())
			{
				input_vars.push_back(cols[i].get_var());
			}
		}

		return input_vars;
	}

	/** Returns a constant vector containing column (referred to
	 * as variables) information like the name and min/max values
	 * of the selected row.
	 * @return the output variables
	 */
	inline std::vector<Variable> output_variables(void) const
	{
		std::vector<Variable> output_vars;

		for (std::size_t i = separator; i < cols.size(); ++i)
		{
			if (cols[i].is_enabled())
			{
				output_vars.push_back(cols[i].get_var());
			}
		}

		return output_vars;
	}

	/** Returns a constant iterator pointing to the first DataRow.
	 * @return a const_iterator
	 */
	inline const_iterator begin() const
	{
		return const_iterator(rows.begin(), rows.end());
	}

	/** Returns a constant iterator pointing to the end element of the
	 * DataRow storage.
	 * @return a const_iterator
	 */
	inline const_iterator end() const
	{
		return const_iterator(rows.end(), rows.end());
	}
private:
	/** Creates a DataSet from a vector of DataRows.
	 * @param rows the rows of the table
	 */
	DataSet(const std::vector<MockColumn>& _cols) :
			num_rows(_cols[0].size()), num_cols(_cols.size()),
			cols(_cols)
	{
		std::size_t i = 0;
		while (cols[i].get_type() == ColumnType::INPUT) ++i;
		num_inputs = separator = i;
		num_outputs = cols.size() - num_inputs;

		rows.reserve(cols[0].size());
		for (std::size_t i = 0; i < cols[0].size(); ++i)
		{
			rows.push_back(DataRow(cols, num_cols, i));
		}
	}

	/** The row and column numbers */
	std::size_t num_rows, num_cols;
	/** The number of inputs and outputs */
	std::size_t num_inputs, num_outputs;
	/** A technical constant for dividing the cols vector into inputs and outputs */
	std::size_t separator;
	/** The columns of this data table */
	std::vector<MockColumn> cols;
	/** The rows of this data table */
	std::vector<DataRow> rows;
};

template<typename T>
DataSet<T>* DataSet<T>::parse_from_csv(const std::string & cont,
		std::string separator, std::string comment, std::string newline)
{
	static_assert(std::is_same<T, double>::value, "Should not be compiled.");
	return nullptr;
}

typedef DataSet<double> DefDataSet;
typedef DefDataSet::Variable DefVariable;
typedef DefDataSet::DataRow DefDataRow;
typedef DefDataSet::Cell DefCell;

#endif /* DATASET_H_ */
