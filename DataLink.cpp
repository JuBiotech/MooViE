/*
 * DataLink.cpp
 *
 *  Created on: 12.12.2017
 *      Author: IBT\stratmann
 */

#include "DataLink.h"

DataLinkFactory::DataLinkFactory(
		const CoordGrid & grid,
		const std::vector<VarAxis> & axis)
: _grid(grid), _axis(axis)
{
	std::pair<double, double> out = std::make_pair(
						grid.get_start().get(),
						grid.get_start() > grid.get_end() ?
								grid.get_end().get() + 2 * M_PIl : grid.get_end().get()
					);
	for (DefVar var: grid.get_output_variables())
	{
		_output_mapper.emplace_back(
				std::make_pair(var.min, var.max),
				out
		);
	}

	for (const VarAxis & elem: axis)
	{
		_input_mapper.emplace_back(
				std::make_pair(elem.get_var().min, elem.get_var().max),
				std::make_pair(elem.get_start().get(), elem.get_end().get())
		);
	}
}

DataLink DataLinkFactory::create(const DefDataRow & row) const
{
	DataLink link;
	std::size_t num_inputs = _axis.size(),
			num_cols = row.size();

	for (std::size_t i = 0; i < num_inputs; ++i)
	{
		link.emplace_back(
				Polar(_axis[i].get_radius(), _input_mapper[i].map(row[i].value)),
				_axis[i].get_prop()
		);
	}

	Color line = get_color(row[num_inputs].value);
	Color fill(line.r(), line.g(), line.b(), 0.3);
	DrawerProperties<> prop(0.2, line, fill); // TODO: add config value
	link.emplace_back(
			Polar(
				_grid.get_radius() - Configuration::CONNECTOR_DELTA,
				_output_mapper[0].map(row[num_inputs].value)
			),
			prop
	);

	double height_factor = _grid.get_height() / (_grid.get_num_outputs() - 0.5);
	for (std::size_t i = 0; i < num_cols - num_inputs; ++i)
	{
		link.emplace_back(
				Polar(
					_grid.get_radius()
						+ Configuration::get_instance().get_output_thickness()
						+ i * height_factor,
					_output_mapper[i].map(row[i + num_inputs].value)
				),
				prop
		);
	}

	return link;
}

const Color & DataLinkFactory::get_color(double val) const
{
	double range = angle_helper::rad_dist(
				_grid.get_start().get(),
				_grid.get_end().get()
			);
	double angle = _output_mapper[0].map(val);

	std::size_t i;
	for (i = 0; i < 10; ++i)
	{
		if (angle < _grid.get_start().get() + i * range / 10)
		{
			break;
		}
	}

	return Color::GLOW_10[i - 1];
}
