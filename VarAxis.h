/*
 * VarAxis.h
 *
 *  Created on: 12.12.2017
 *      Author: IBT\stratmann
 */

#ifndef VARAXIS_H_
#define VARAXIS_H_

#include "Ticks.h"
#include "PolarCartesian.h"
#include "DataSet.h"
#include "Mapper.h"
#include "DrawerProperties.h"
#include "Configuration.h"

/** A VarAxis is an axis which displays the possible values
 * of a input variable. It is visualized as a ring segment
 * with a distinct color and has ticks for better readability.
 *
 * @author stratmann
 * @date 12.12.2017
 */
class VarAxis
{
public:
	class Histogram
	{
	public:
	    /** Creates an empty Histogram for this variable with
	     * the specified number of intervals.
	     */
	    Histogram(DefVar var);

	    /** Calculates equidistant data sections and stores
	     * them.
	     * @param data the input values of this variable
	     */
	    void calculate(const std::vector<double> & data);

	    /** Returns the value of the histogram graph in this
	     * section. They are associated with the relative
	     * frequency of the equidistant intervals.
	     * @param i index of the section
	     * @return the height
	     */
	    double get_section_frequency(std::size_t i) const;

	    inline std::size_t get_num_intervals(void) const
	    {
	    	return _num_intervals;
	    }

	    inline void set_num_intervals(std::size_t num_intervals)
	    {
	    	_num_intervals = num_intervals;
	    	_frequencies.clear();
	    	for (std::size_t i = 0; i < _num_intervals; ++i)
	    	    _frequencies.push_back(0);
	    }

	private:
	    DefVar 				_var;
	    std::size_t 		_num_intervals;
	    std::vector<double> _frequencies;
	};

public:
	/**
	 *
	 */
	VarAxis(DefVar var, Ticks ticks,
		const Angle & start, const Angle & end,
		double radius, std::size_t height,
		const DrawerProperties<> & prop, const TextProperties & text_prop);

	const Histogram & get_histogram () const
	{
	      return _histogram;
	}

	Angle get_end () const
	{
	      return _end;
	}

	void set_end (Angle end)
	{
	      this->_end = end;
	}

	std::size_t get_height () const
	{
	      return _height;
	}

	void set_height (std::size_t height)
	{
	      this->_height = height;
	}

	const Label & get_label () const
	{
	      return _label;
	}

	void set_label (const Label& label)
	{
	      this->_label = label;
	}

	const DrawerProperties<> & get_prop () const
	{
	      return _prop;
	}

	void set_prop (const DrawerProperties<> & prop)
	{
	      this->_prop = prop;
	}

	double get_radius () const
	{
	      return _radius;
	}

	void set_radius (double radius)
	{
	      this->_radius = radius;
	}

	Angle get_start () const
	{
	      return _start;
	}

	void set_start (Angle start)
	{
	      this->_start = start;
	}

	const Ticks & get_ticks () const
	{
	      return _ticks;
	}

	void set_ticks (const Ticks & ticks)
	{
	      this->_ticks = ticks;
	}

	const DefVar & get_var () const
	{
	      return _var;
	}

	/**
	 *
	 */
	Polar get_coord(double val) const;

	void calculate_histogram(const std::vector<double> & data);

private:
	/* The Variable this VarAxis represents */
	DefVar 				_var;
	/** The ticks of this variable */
	Ticks 				_ticks;
	/** A mapping from actual values to angles */
	Mapper 				_input_mapper;
	/** The histogram describing the frequencies of the intervals */
	Histogram			_histogram;

	/** Start and end angle for drawing the VarAxis */
	Angle 				_start, _end;
	/** Start radius of the VarAxis */
	double 				_radius;
	/** Height of the VarAxis */
	std::size_t 		_height;

	/** Label showing the variable name */
	Label 				_label;
	/** Style defining how the VarAxis is drawn */
	DrawerProperties<> 	_prop;
};

#endif /* VARAXIS_H_ */
