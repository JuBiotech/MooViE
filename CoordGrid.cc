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
	{
		for (DefVar var: _output_variables)
		{
			_output_mappers.push_back(Mapper(std::make_pair(var.min, var.max),
					std::make_pair(_start.get(), _start > _end ? _end.get() + 2 * M_PIl : _end.get())));
		}
	}

const DefVar & CoordGrid::get_var(std::size_t num_output) const
{
	if (num_output >= _num_outputs);
	return _output_variables[num_output];
}

Polar CoordGrid::get_coord(double val, std::size_t num_output) const
{
	if (num_output >= _num_outputs); // TODO: throw exception
	return Polar(_radius + Configuration::get_instance().get_output_thickness() + num_output * (_height / (_num_outputs - 0.5)),
			_output_mappers[num_output].map(val));
}

Color CoordGrid::get_color(double val) const
{
	double range = angle_helper::rad_dist(_start.get(), _end.get());
	double angle = _output_mappers[0].map(val);

	std::size_t i;
	for (i = 0; i < 10; ++i)
	{
		if (angle < _start.get() + i * range / 10)
		{
			break;
		}
	}

	return Color::GLOW_10[i - 1];
}
