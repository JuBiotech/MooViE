/*
 * CoordGrid.cc
 *
 *  Created on: 26.07.2017
 *      Author: beyss
 */

#include <CodomainGrid.h>

CodomainGrid::CodomainGrid(const std::vector<DefVariable>& _output_vars,
		const Angle& _start, const Angle& _end,
		double _radius, double _height, Direction _dir)
	: output_variables(_output_vars), num_outputs(_output_vars.size()),
	  scale(
			  Configuration::get_instance().get_num_major_sections_grid(),
			  Configuration::get_instance().get_num_minor_sections_grid(),
			  Configuration::get_instance().get_prop_scale_label()
	  ),
	  start(_start), end(_end), radius(_radius), height(_height), direction(_dir)
	{
		for (DefVariable var: _output_vars)
		{
			scale.add_scale(create_rounded_interval(var.min, var.max));
		}
	}

const DefVariable & CodomainGrid::get_var(std::size_t num_output) const
{
	if (num_output >= num_outputs)
	{
		throw std::out_of_range(
				"Variable index (" + std::to_string(num_output) +
				") is out of range " + std::to_string(num_outputs - 1)
		);
	}

	return output_variables[num_output];
}
