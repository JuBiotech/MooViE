/*
 * Scene.cc
 *
 *  Created on: 28.08.2017
 *      Author: beyss
 */

#include "Scene.h"
#include "Config.h"

Scene::Scene(Drawer & drawer,
		const DefDataSet & set)
: _grid(10, 10, angle_helper::deg_to_rad(-50), angle_helper::deg_to_rad(50), config::OUTPUT_INNER_RADIUS, config::GRID_SIZE, Direction::DECREASING, set.output_variables()),  // TODO: replace with configuration values
  _set(set),
  _drawer(drawer), _prop(config::THIN_STROKE_WIDTH, Color::BLACK, Color::BLACK),
  _split_prop(1, Color::BLACK, Color::GLOW_10)
{
	double angle = 180 / set.input_variables().size() - config::INPUT_SEPERATION_ANGLE;
	double start = -90, end = start-angle;
	std::size_t i = 0;
	for (DefVar var: set.input_variables())
	{
		_axis.push_back(
				VarAxis(
						Ticks(10, 10, std::make_pair(var.min, var.max),
								TextProperties("Liberation Serif", 8), "cm"),
						angle_helper::deg_to_rad(start),
						angle_helper::deg_to_rad(end),
						config::INPUT_INNER_RADIUS, config::INPUT_THICKNESS,
						var,
						DrawerProperties<>(1, Color::BLACK,
								Color::SET3.at(set.input_variables().size(), i++)),
						config::VAR_LABEL));
		start -= angle + config::INPUT_SEPERATION_ANGLE;
		end -= angle + config::INPUT_SEPERATION_ANGLE;
	}

	for (DefDataRow row: set)
	{
		std::vector<Polar> in, out;
		for (std::size_t i = 0; i < _axis.size(); ++i)
			in.push_back(_axis[i].get_coord(row[i].value)); // TODO: Throw null value exception
		Polar connector(_grid.get_coord(row[_axis.size()].value, 0));
		for (std::size_t i = 0; i < _grid.outputs; ++i)
			out.push_back(_grid.get_coord(row[_axis.size() + i].value, i)); // TODO: Throw null value exception
		DataLink link(in, connector, out, _prop);
		for(const VarAxis & va: _axis)
		{
			link.add_link_prop(va.prop);
		}
		_links.push_back(link);
	}

	draw_scene();
}

void Scene::draw_scene(void) const
{
	_drawer.draw_coord_grid(_grid, _prop, _prop); // TODO: Replace properties with configuration properties

	for (VarAxis axis: _axis)
		_drawer.draw_var_axis(axis); // TODO: Replace properties with configuration properties

	//_drawer.draw_data_link(_links[0]);
	for (DataLink link: _links)
		_drawer.draw_data_link(link); // TODO:: Replace properties with configuration properties
}
