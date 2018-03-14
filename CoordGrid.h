 /*
 * CoordGrid.h
 *
 *  Created on: 26.07.2017
 *      Author: beyss
 */

#ifndef COORDGRID_H_
#define COORDGRID_H_

#include <cstddef>
#include <vector>
#include "Mapper.h"
#include "PolarCartesian.h"
#include "DataSet.h"
#include "Ticks.h"
#include "Configuration.h"

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
class CoordGrid
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
    CoordGrid(std::size_t major_ticks_, std::size_t minor_ticks_,
    		const Angle & start_, const Angle & end_,
			double radius_, double height_, Direction dir_,
			const std::vector<DefVar> output_vars);

	const std::vector<DefVar>& get_output_variables() const
	{
		return _output_variables;
	}

	Direction get_direction() const
	{
		return _direction;
	}

	void set_direction(Direction direction)
	{
		this->_direction = direction;
	}

	Angle get_end() const
	{
		return _end;
	}

	void set_end(Angle end)
	{
		this->_end = end;
	}

	double get_height() const
	{
		return _height;
	}

	void set_height(double height)
	{
		this->_height = height;
	}

	std::size_t get_major_ticks() const
	{
		return _major_ticks;
	}

	void set_major_ticks(std::size_t major_ticks)
	{
		this->_major_ticks = major_ticks;
	}

	std::size_t get_minor_ticks() const
	{
		return _minor_ticks;
	}

	void set_minor_ticks(std::size_t minor_ticks)
	{
		this->_minor_ticks = minor_ticks;
	}

	std::size_t get_num_outputs() const
	{
		return _num_outputs;
	}

	double get_radius() const
	{
		return _radius;
	}

	void set_radius(double radius)
	{
		this->_radius = radius;
	}

	Angle get_start() const
	{
		return _start;
	}

	void set_start(Angle start)
	{
		this->_start = start;
	}

	const DefVar & get_var(std::size_t num_output) const;

private:
    /** The number of outputs. */
    std::size_t 		_num_outputs;

    /** The major and minor sections */
    std::size_t 		_major_ticks, _minor_ticks;

    /** Start and end angle for drawing the CoordGrid */
    Angle 				_start, _end;
    /** Radius of the CoordGrid */
    double 				_radius;
    /** Height of the CoordGrid */
    double 				_height;
    /** Direction of the CoordGrid's values */
    Direction 			_direction;

    /* The output variables */
    std::vector<DefVar> _output_variables;
};

#endif /* COORDGRID_H_ */
