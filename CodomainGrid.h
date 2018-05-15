 /*
 * CodomainGrid.h
 *
 *  Created on: 26.07.2017
 *      Author: beyss
 */

#ifndef CODOMAINGRID_H_
#define CODOMAINGRID_H_

#include <cstddef>
#include <vector>

#include "Scale.h"
#include "DataSet.h"
#include "Configuration.h"
#include "Coordinates.h"

/** A enum for drawer direction */
enum Direction
{
	INCREASING, DECREASING
};

/** Representing a coordinate grid by its dimensional constraints.
 * ╟───┼───┼───┼───╫───┼───┼───┼───╢
 * ║   │   │   │   ║   │   │   │   ║
 * ╟───┼───┼───┼───╫───┼───┼───┼───╢
 * ║   │   │   │   ║   │   │   │   ║
 * ╟───┼───┼───┼───╫───┼───┼───┼───╢
 * ║   │   │   │   ║   │   │   │   ║
 * ╟───┼───┼───┼───╫───┼───┼───┼───╢
 * 4 outputs, 4 ticks
 * @brief The CoordGrid class
 * @author beyss
 * @date 26.07.2017
 */
class CodomainGrid
{
public:
    /** Creates a CoordGrid which can be drawn between two angles in a
     * polar coordinate system.
     * @brief CoordGrid
     * @param num_ticks the number of ticks
     * @param start the start angle
     * @param end the end angle
     * @param height the height of the CoordGrid
     * @param output_vars a vector containing the output variables
     */
    CodomainGrid(std::size_t major_ticks_, std::size_t minor_ticks_,
    		const Angle & start_, const Angle & end_,
			double radius_, double height_, Direction dir_,
			const std::vector<DefVar> output_vars);

	Direction get_direction() const
	{
		return direction;
	}

	void set_direction(Direction direction)
	{
		this->direction = direction;
	}

	Angle get_end() const
	{
		return end;
	}

	void set_end(const Angle& end)
	{
		this->end = end;
	}

	double get_height() const
	{
		return height;
	}

	void set_height(double height)
	{
		this->height = height;
	}

	const MultiScale& get_scale() const
	{
		return scale;
	}

	std::size_t get_num_outputs() const
	{
		return num_outputs;
	}

	double get_radius() const
	{
		return radius;
	}

	void set_radius(double radius)
	{
		this->radius = radius;
	}

	Angle get_start() const
	{
		return start;
	}

	void set_start(const Angle& start)
	{
		this->start = start;
	}

	const DefVar& get_var(std::size_t num_output) const;

private:
    /** The number of outputs. */
    std::size_t 		num_outputs;

    /** The Scale information */
    MultiScale			scale;

    /** Start and end angle for drawing the CoordGrid */
    Angle 				start, end;
    /** Radius of the CoordGrid */
    double 				radius;
    /** Height of the CoordGrid */
    double 				height;
    /** Direction of the CoordGrid's values */
    Direction 			direction;

    /* The output variables */
    std::vector<DefVar> output_variables;
};

#endif /* CODOMAINGRID_H_ */
