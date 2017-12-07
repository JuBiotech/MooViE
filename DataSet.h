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
#include <iterator>
#include <cfloat>
#include <stdexcept>

#include "Utils.h"

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
	/** Var represents an entity attribute and stores its name,
	 * maximal and minimal value.
	 * @brief The Var struct
	 */
	struct Var
	{
		/** Creates a Variable with the given name, min and max value.
		 * @brief Var
		 * @param min the min value
		 * @param max the max value
		 * @param name the name
		 */
		Var(T min_, T max_, const std::string& name_) :
				min(min_), max(max_), name(name_)
		{
		}

		/** Minimal value */
		T min;

		/** Maximal value */
		T max;

		/** Variable name */
		std::string name;
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

	/** Renaming to ease the handling of rows */
	typedef std::vector<Cell> DataRow;

	class iterator: public std::iterator<std::input_iterator_tag, DataRow, long,
			const DataRow *, const DataRow &>
	{
		typename std::vector<DataRow>::const_iterator _it;
	public:
		explicit iterator(
				const typename std::vector<DataRow>::const_iterator & it) :
				_it(it)
		{
		}
		iterator&
		operator++()
		{
			++_it;
			return *this;
		}
		iterator operator++(int)
		{
			iterator retval = *this;
			++(*this);
			return retval;
		}
		bool operator==(const iterator & other) const
		{
			return _it == other.__it;
		}
		bool operator!=(const iterator & other) const
		{
			return _it != other._it;
		}
		const DataRow & operator*() const
		{
			return *_it;
		}
		;
	};

	/** Renaming to ease the iterators */
	typedef const iterator const_iterator;
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
	static DataSet parse_from_csv(const std::string & cont, std::size_t num_ins,
			std::string separator = ",", std::string comment = "#", std::string newline = "\n");

	/** Returns the number of columns in this table.
	 * @return the number of columns
	 */
	inline std::size_t cols() const
	{
		return _number_cols;
	}

	/** Returns the number of rows in this table.
	 * @return the number of rows
	 */
	inline std::size_t rows() const
	{
		return _number_rows;
	}

	/** Returns the row at position i in the table (starting at 0). DataRow can
	 * be used like a vector from the given type.
	 * @return the DataRow object
	 */
	inline const DataRow &
	operator[](std::size_t i) const
	{
		return _rows[i];
	}

	/** Returns a constant vector containing row (referred to
	 * as variables) information like the name and min/max values
	 * of the selected row.
	 * @return the input variables
	 */
	inline const std::vector<Var> & input_variables(void) const
	{
		return _input_vars;
	}

	/** Returns a constant vector containing column (referred to
	 * as variables) information like the name and min/max values
	 * of the selected row.
	 * @return the output variables
	 */
	inline const std::vector<Var> & output_variables(void) const
	{
		return _output_vars;
	}

	/** Returns a constant iterator pointing to the first DataRow.
	 * @return a const_iterator
	 */
	inline const_iterator begin() const
	{
		return iterator(_rows.begin());
	}

	/** Returns a constant iterator pointing to the end element of the
	 * DataRow storage.
	 * @return a const_iterator
	 */
	inline const_iterator end() const
	{
		return iterator(_rows.end());
	}
private:
	/** Creates a DataSet from a vector of DataRows.
	 * @param rows the rows of the table
	 */
	DataSet(const std::vector<Var> input_vars, const std::vector<Var> output_vars,
			const std::vector<DataRow> & rows) :
			_number_rows(rows.size()), _number_cols(input_vars.size()),
			_input_vars(input_vars), _output_vars(output_vars), _rows(rows)
	{
	}

	/** The row and column numbers */
	const std::size_t _number_rows, _number_cols;
	/** The column names and extremes of this table */
	const std::vector<Var> _input_vars;
	/** The input names and extremes of this table */
	const std::vector<Var> _output_vars;
	/** The rows of this data table */
	const std::vector<DataRow> _rows;
};

template<typename T>
DataSet<T> DataSet<T>::parse_from_csv(const std::string & cont, std::size_t num_ins,
		std::string separator, std::string comment, std::string newline)
{
	static_assert(true, "Should not be compiled.");
}

typedef DataSet<double> DefDataSet;
typedef DefDataSet::Var DefVar;
typedef DefDataSet::DataRow DefDataRow;
typedef DefDataSet::Cell DefCell;

#endif /* DATASET_H_ */
