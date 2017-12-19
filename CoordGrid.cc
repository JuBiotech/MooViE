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
	: outputs(output_vars.size()), major_ticks(major_ticks_), minor_ticks(minor_ticks_),
	  start(start_), end(end_), radius(radius_), height(height_), dir(dir_)
	{
		for (DefVar var: output_vars)
		{
			_output_mappers.push_back(Mapper(std::make_pair(var.min, var.max),
					std::make_pair(start.get(), start > end ? end.get() + 2 * M_PIl : end.get())));
		}
	}

Polar CoordGrid::get_coord(double val, std::size_t num_output) const
{
	if (num_output >= outputs); // TODO: Write exception
	return Polar(radius + num_output * (height / outputs), _output_mappers[num_output].map(val));
}
