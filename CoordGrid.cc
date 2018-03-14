/*
 * CoordGrid.cc
 *
 *  Created on: 26.07.2017
 *      Author: beyss
 */

#include "CoordGrid.h"

CoordGrid::CoordGrid(std::size_t major_ticks_, std::size_t minor_ticks_,
		const Angle & start_, const Angle & end_,
		double radius_, double height_, Direction dir_,
		const std::vector<DefVar> output_vars)
	: _num_outputs(output_vars.size()), _major_ticks(major_ticks_), _minor_ticks(minor_ticks_),
	  _start(start_), _end(end_), _radius(radius_), _height(height_), _direction(dir_),
	  _output_variables(output_vars)
	{}

const DefVar & CoordGrid::get_var(std::size_t num_output) const
{
	if (num_output >= _num_outputs);
	return _output_variables[num_output];
}
