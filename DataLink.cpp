/*
 * DataLink.cpp
 *
 *  Created on: 12.12.2017
 *      Author: IBT\stratmann
 */

#include "DataLink.h"

std::size_t DataLink::CoordinateStorage::add_unique(Polar && coord)
{
	static auto comparator = [&](const Polar & comp) {
		return (comp.r() - 5 > coord.r() && comp.r() + 5 < coord.r())
				&& (comp.phi() - 0.001 > coord.phi() && comp.phi() + 0.001 < coord.phi());
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

DataLink::DataLink(const std::vector<Polar> & input_coords, const Polar & connector_coord,
		const std::vector<Polar> & output_coords, const DrawerProperties<> & connector_prop)
: _input_coords(input_coords), _connector_coord(connector_coord), _output_coords(output_coords),
  _connector_prop(connector_prop)
{}

DataLinkFactory::DataLinkFactory(const CoordGrid & grid, const std::vector<VarAxis> & axis)
: _grid(grid), _axis(axis)
{
	for (DefVar var: grid.get_output_variables())
	{
		_output_mapper.emplace_back(
				std::make_pair(var.min, var.max),
				std::make_pair(grid.get_start(), grid.get_end())
		);
	}

	for (const VarAxis & elem: axis)
	{
		_input_mapper.emplace_back(
				std::make_pair(elem.get_var().min, elem.get_var().max),
				std::make_pair(elem.get_start(), elem.get_end())
		);
	}
}

DataLink DataLinkFactory::create(const DefDataRow & row) const
{
	DataLink link;
	link.set_connector(DataLink::_coordinate_storage.add_unique(
				Polar(_grid.get_radius() - Configuration::CONNECTOR_DELTA,
					_output_mapper[0].map(row[_axis.size()].value)
				)
			)
	);

	std::size_t add;

	for (std::size_t i = 0; i < _axis.size(); ++i)
	{
		add = DataLink::_coordinate_storage.add_unique(
					Polar(_axis[i].get_radius(), _input_mapper[i].map(row[i].value))
				);
		link.add_input(add, _axis[i].get_prop());
	}

	double height_factor = _grid.get_height() / (_grid.get_num_outputs() - 0.5);
	for (std::size_t i = 0; i < _axis.size(); ++i)
	{
		add = DataLink::_coordinate_storage.add_unique(
					Polar(
							_grid.get_radius()
								+ Configuration::get_instance().get_output_thickness()
								+ i * height_factor,
							_output_mapper[i].map(row[i].value)
					)
				);
		link.add_output(add);
	}

	return link;
}
