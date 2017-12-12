/*
 * CoordGrid.cc
 *
 *  Created on: 26.07.2017
 *      Author: beyss
 */

#include "CoordGrid.h"

CoordGrid::CoordGrid(size_t regions, size_t ticks,
		const Angle & start, const Angle & end, std::size_t height,
		const std::vector<DefVar> output_vars)
		: _outputs(output_vars.size()), _regions(regions), _ticks(ticks),
		  _start(start), _end(end), _height(height)
		{
    		for (DefVar var: output_vars)
    		{
    			_output_mappers.push_back(Mapper(std::make_pair(var.min, var.max), std::make_pair(start.get(), end.get())));
    		}
		}

Polar CoordGrid::get_coord(double val, std::size_t radius, std::size_t num_output) const
{
	if (num_output >= _outputs); // TODO: Write exception
	return Polar(radius + num_output * (_height / (double) _outputs), _output_mappers[num_output].map(val));
}
