/*
 * CoordGrid.cc
 *
 *  Created on: 26.07.2017
 *      Author: beyss
 */

#include "CodomainGrid.h"

CodomainGrid::CodomainGrid(std::size_t major_ticks_, std::size_t minor_ticks_,
		const Angle & start_, const Angle & end_,
		double radius_, double height_, Direction dir_,
		const std::vector<DefVar> output_vars)
	: num_outputs(output_vars.size()),
	  scale(major_ticks_, minor_ticks_, Configuration::get_instance().get_tick_label()),
	  start(start_), end(end_), radius(radius_), height(height_), direction(dir_),
	  output_variables(output_vars)
	{
		for (DefVar var: output_vars)
		{
			scale.add_scale(create_rounded_interval(var.min, var.max));
		}
	}

const DefVar & CodomainGrid::get_var(std::size_t num_output) const
{
	if (num_output >= num_outputs);
	return output_variables[num_output];
}
