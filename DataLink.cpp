/*
 * DataLink.cpp
 *
 *  Created on: 12.12.2017
 *      Author: IBT\stratmann
 */

#include "DataLink.h"

const Polar & DataPoint::coord() const
{
	return DataLinkFactory::_coordinate_storage.get(_coord);
}

DataLinkFactory::CoordinateStorage DataLinkFactory::_coordinate_storage;

std::size_t DataLinkFactory::CoordinateStorage::add_unique(Polar && coord)
{
	static auto comparator = [&](const Polar & comp) {
		return (comp.r() - 5 < coord.r() && comp.r() + 5 > coord.r())
				&& (comp.phi() - 0.001 < coord.phi() && comp.phi() + 0.001 > coord.phi());
	};

	std::vector<Polar>::iterator found;

	if ((found = std::find_if(_coordinates.begin(), _coordinates.end(), comparator))
			!= _coordinates.end())
	{
		return found - _coordinates.begin();
	}
	else
	{
		_coordinates.push_back(std::move(coord));
		return _coordinates.size() - 1;
	}
}

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
				_coordinate_storage.add_unique(
						Polar(_axis[i].get_radius(), _input_mapper[i].map(row[i].value))
				),
				_axis[i].get_prop()
		);
	}

	DrawerProperties<> prop(1.0, Color::BLACK, _grid.get_color(row[num_inputs].value)); // TODO: add config value
	link.emplace_back(
			_coordinate_storage.add_unique(
					Polar(_grid.get_radius() - Configuration::CONNECTOR_DELTA,
						_output_mapper[0].map(row[num_inputs].value)
					)
			),
			prop
	);

	double height_factor = _grid.get_height() / (_grid.get_num_outputs() - 0.5);
	for (std::size_t i = 0; i < num_cols - num_inputs; ++i)
	{
		link.emplace_back(
				_coordinate_storage.add_unique(
						Polar(
								_grid.get_radius()
									+ Configuration::get_instance().get_output_thickness()
									+ i * height_factor,
								_output_mapper[i].map(row[i + num_inputs].value)
						)
				),
				prop
		);
	}

	return link;
}
