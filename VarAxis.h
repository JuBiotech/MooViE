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
	     * @param var the input variable
	     * @param num_intervals the number of intervals
	     */
	    Histogram(DefVar var, std::size_t num_intervals);

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
	private:
	    DefVar _var;
	    std::size_t _num_intervals;
	    std::vector<double> _frequencies;
	};

public:
	/**
	 *
	 */
	VarAxis(DefVar var_, Ticks ticks_,
		const Angle & start_, const Angle & end_,
		double radius_, std::size_t height_,
		const DrawerProperties<> & prop_, const TextProperties & text_prop_);

	/**
	 *
	 */
	Polar get_coord(double val) const;
public:
	/* The Variable this VarAxis represents */
	DefVar 			var;
	/** The ticks of this variable */
	Ticks 			ticks;
	/** A mapping from actual values to angles */
	Mapper 			_input_mapper;
	/** The histogram describing the frequencies of the intervals */
	Histogram		_histogram;

	/** Start and end angle for drawing the VarAxis */
	Angle 			start, end;
	/** Start radius of the VarAxis */
	double 			radius;
	/** Height of the VarAxis */
	std::size_t 		height;

	/** Label showing the variable name */
	Label 			label;
	/** Style defining how the VarAxis is drawn */
	DrawerProperties<> 	prop;
};

#endif /* VARAXIS_H_ */
