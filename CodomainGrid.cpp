/*
 * CoordGrid.cc
 *
 *  Created on: 26.07.2017
 *      Author: beyss
 */

#include "CodomainGrid.h"

CodomainGrid::CodomainGrid(const std::vector<DefVar>& _output_vars,
		const Angle& _start, const Angle& _end,
		double _radius, double _height, Direction _dir)
	: num_outputs(_output_vars.size()),
	  scale(
			  Configuration::get_instance().get_num_major_ticks_cg(),
			  Configuration::get_instance().get_num_minor_ticks_cg(),
			  Configuration::get_instance().get_tick_label()
	  ),
	  start(_start), end(_end), radius(_radius), height(_height), direction(_dir),
	  output_variables(_output_vars)
	{
		for (DefVar var: _output_vars)
		{
			scale.add_scale(create_rounded_interval(var.min, var.max));
		}
	}

const DefVar & CodomainGrid::get_var(std::size_t num_output) const
{
	if (num_output >= num_outputs);
	return output_variables[num_output];
}
