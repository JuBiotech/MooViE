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
			return _it != other.__it;
		}
		const T &
		operator*() const
		{
			return *_it;
		}
		;
	};

	/** Renaming to ease the iterators */
	typedef const iterator const_iterator;
public:
	/** Returns a data table parsed from a csv encoded string
	 * and encapsulated in a DataSet object.
	 * @param cont the csv encoded string
	 * @return the DataSet object
	 */
	static DataSet
	parse_from_csv(const std::string & cont);

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

	inline const std::vector<Var> &
	variables(void) const
	{
		return _variables;
	}

	/** Returns a constant iterator pointing to the first DataRow.
	 * @return a const_iterator
	 */
	const_iterator begin()
	{
		return iterator(_rows.begin());
	}

	/** Returns a constant iterator pointing to the end element of the
	 * DataRow storage.
	 * @return a const_iterator
	 */
	const_iterator end()
	{
		return iterator(_rows.end());
	}
private:
	/** Creates a DataSet from a vector of DataRows.
	 * @param rows the rows of the table
	 */
	DataSet(const std::vector<Var> variables, const std::vector<DataRow> & rows) :
			_number_rows(rows.size()), _number_cols(variables.size()),
			_variables(variables), _rows(rows)
	{
	}

	/** Splits a given string expression using the given delimiter string.
	 * @param expr the string to divide
	 * @param delims the delimiter string
	 */
	static std::vector<std::string> split(const std::string & expr,
			const std::string delims)
	{
		std::vector<std::string> res;
		std::size_t prev = 0;

		for (std::size_t i = 0; i < expr.length(); ++i)
		{
			if (i + delims.length() >= expr.length() &&
					expr.substr(i, delims.length()).compare(i,
							delims.length(), delims, 0,
							delims.length()) == 0)
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
private:
	/** The row and column numbers */
	const std::size_t _number_rows, _number_cols;
	/** The column names and extremes of this table */
	const std::vector<Var> _variables;
	/** The rows of this data table */
	const std::vector<DataRow> _rows;
};

template<typename T>
DataSet<T> DataSet<T>::parse_from_csv(const std::string & cont)
{
	static_assert(true, "Should not be compiled.");
}

typedef DataSet<double> DefDataSet;
typedef DefDataSet::Var DefVar;
typedef DefDataSet::DataRow DefDataRow;
typedef DefDataSet::Cell DefCell;

#endif /* DATASET_H_ */
