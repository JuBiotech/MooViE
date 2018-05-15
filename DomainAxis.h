/*
 * DomainAxis.h
 *
 *  Created on: 12.12.2017
 *      Author: IBT\stratmann
 */

#ifndef DOMAINAXIS_H_
#define DOMAINAXIS_H_

#include "Scale.h"
#include "DataSet.h"
#include "Configuration.h"
#include "Coordinates.h"

/** A DomainAxis is an axis which displays the possible values
 * of a input variable. It is visualized as a ring segment
 * with a distinct color and has ticks for better readability.
 *
 * @author stratmann
 * @date 12.12.2017
 */
class DomainAxis
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
	DomainAxis(DefVar var,
		const Angle& start, const Angle& end,
		double radius, std::size_t height,
		const DrawerProperties<>& prop,
		const TextProperties& text_prop);

	const Histogram& get_histogram () const
	{
	      return histogram;
	}

	Angle get_end () const
	{
	      return end;
	}

	void set_end (const Angle& end)
	{
	      this->end = end;
	}

	std::size_t get_height () const
	{
	      return height;
	}

	void set_height (std::size_t height)
	{
	      this->height = height;
	}

	const Label& get_label () const
	{
	      return label;
	}

	void set_label (const Label& label)
	{
	      this->label = label;
	}

	const DrawerProperties<>& get_prop () const
	{
	      return prop;
	}

	void set_prop (const DrawerProperties<>& prop)
	{
	      this->prop = prop;
	}

	double get_radius () const
	{
	      return radius;
	}

	void set_radius (double radius)
	{
	      this->radius = radius;
	}

	Angle get_start () const
	{
	      return start;
	}

	void set_start (const Angle& start)
	{
	      this->start = start;
	}

	const SimpleScale& get_ticks () const
	{
	      return scale;
	}

	void set_ticks (const SimpleScale& ticks)
	{
	      this->scale = ticks;
	}

	const DefVar & get_var () const
	{
	      return var;
	}

	void calculate_histogram(const std::vector<double>& data);

private:
	/* The Variable this VarAxis represents */
	DefVar 				var;
	/** The ticks of this variable */
	SimpleScale 		scale;
	/** The histogram describing the frequencies of the intervals */
	Histogram			histogram;

	/** Start and end angle for drawing the VarAxis */
	Angle 				start, end;
	/** Start radius of the VarAxis */
	double 				radius;
	/** Height of the VarAxis */
	std::size_t 		height;

	/** Label showing the variable name */
	Label 				label;
	/** Style defining how the VarAxis is drawn */
	DrawerProperties<> 	prop;
};

#endif /* DOMAINAXIS_H_ */
