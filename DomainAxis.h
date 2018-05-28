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
	     *
	     * @brief constructor
	     *
	     * @param _var the variable to present
	     */
	    Histogram(DefVar _var);

	    /** Calculates equidistant data sections and stores
	     * them.
	     *
	     * @param data the input values of this variable
	     */
	    void calculate(const std::vector<double> & data);

	    /** Returns the value of the histogram graph in this
	     * section. They are associated with the relative
	     * frequency of the equidistant intervals.
	     *
	     * @brief frequency of the i-th section
	     *
	     * @param i index of the section
	     *
	     * @return the height
	     */
	    double get_section_frequency(std::size_t i) const;

	    /** Returns the number of equidistant intervals the
	     * domain of this Histogram's Variable is divided in.
	     *
	     * @brief gets number of equidistant intervals
	     *
	     * @return the interval count
	     */
	    inline std::size_t get_num_intervals(void) const
	    {
	    	return num_intervals;
	    }

	    /** Sets the histogram to have a given number of equidistant
	     * intervals. If values for an old number of intervals have
	     * been stored, all data from is deleted and the frequencies
	     * set to 0.
	     *
	     * @brief sets the number of equistant intervals
	     *
	     * @param _num_interval the new interval count
	     */
	    inline void set_num_intervals(std::size_t _num_intervals)
	    {
	    	num_intervals = _num_intervals;
	    	frequencies.clear();
	    	for (std::size_t i = 0; i < num_intervals; ++i)
	    	    frequencies.push_back(0);
	    }

	private:
	    /* The variable whose frequencies to present */
	    DefVar 				var;
	    /* The number of intervals to use */
	    std::size_t 		num_intervals;
	    /* The stored frequencies for the intervals */
	    std::vector<double> frequencies;
	};

public:
	/** Creates a new DomainAxis presenting a given variable
	 * and is drawn between given angles with given radius,
	 * height and properties.
	 *
	 * @brief constructor
	 *
	 * @param _var the variable to present
	 * @param _start the start angle
	 * @param _end the end angle
	 * @param _radius the radius from the center
	 * @param _height the height beginning at the radius
	 * @param _prop the DrawerProperties
	 */
	DomainAxis(DefVar _var,
		const Angle& _start, const Angle& _end,
		double _radius, double _height,
		const DrawerProperties<>& _prop);

	/** Returns a const reference to the variable this
	 * DomainAxis presents.
	 *
	 * @brief gets the Var
	 *
	 * @return the Var
	 */
	const DefVar& get_var () const
	{
		return var;
	}

	/** Returns a reference to its histogram. The
	 * DomainAxis#calculate_histogram function has to called
	 * before drawing the histogram because it is empty by
	 * default.
	 *
	 * @brief gets the Histogram
	 *
	 * @return the Histogram
	 */
	const Histogram& get_histogram () const
	{
	      return histogram;
	}

	/** Returns the start Angle of this DomainAxis'
	 * drawing span.
	 *
	 * @brief gets the start Angle
	 *
	 * @return the start Angle
	 */
	Angle get_start () const
	{
		return start;
	}

	/** Starts the start Angle of this DomainAxis'
	 * drawing span.
	 *
	 * @brief sets the start Angle
	 *
	 * @param the start Angle to set
	 */
	void set_start (const Angle& _start)
	{
		start = _start;
	}

	/** Returns the end Angle of this DomainAxis'
	 * drawing span.
	 *
	 * @brief gets the end Angle
	 *
	 * @return the end Angle
	 */
	Angle get_end () const
	{
		return end;
	}

	/** Sets the end Angle of this DomainAxis'
 	 * drawing span.
 	 *
 	 * @brief gets the end Angle
 	 *
 	 * @param _end the end Angle to set
 	 */
	void set_end (const Angle& _end)
	{
		end = _end;
	}

	/** Returns the height measured from the radius.
	 *
	 * @brief gets the height
	 *
	 * @return the height
	 */
	double get_height () const
	{
		return height;
	}

	/** Sets the height measured from the radius.
	 *
	 * @brief sets the height
	 *
	 * @param the height to set
	 */
	void set_height (double _height)
	{
		height = _height;
	}

	/** Returns the radius measured from the center
	 * of the coordinate system.
	 *
	 * @brief gets the radius
	 *
	 * @return the radius
	 */
	double get_radius () const
	{
		return radius;
	}

	/** Sets the radius measured from the center
	 * of the coordinate system.
	 *
	 * @brief sets the radius
	 *
	 * @param the radius to set
	 */
	void set_radius (double _radius)
	{
		radius = _radius;
	}

	/** Sets the radius measured from the center
	 * of the coordinate system.
	 *
	 * @brief sets the radius
	 *
	 * @param the radius to set
	 */
	const DrawerProperties<>& get_prop () const
	{
		return prop;
	}


	void set_prop (const DrawerProperties<>& _prop)
	{
		prop = _prop;
	}

	const SimpleScale& get_ticks () const
	{
		return scale;
	}

	void set_ticks (const SimpleScale& _scale)
	{
		scale = _scale;
	}

	Label make_label (const TextProperties& _prop) const
	{
		return Label(var.name, _prop);
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
	double		 		height;

	/** Style defining how the VarAxis is drawn */
	DrawerProperties<> 	prop;
};

#endif /* DOMAINAXIS_H_ */
