/*
 * Scene.cc
 *
 *  Created on: 28.08.2017
 *      Author: beyss
 */

#include "Scene.h"
#include "Config.h"
#include <iostream>

Scene::Scene(const std::string & fname, size_t width, size_t height, const DefDataSet & set)
: _grid(10, 10, angle_helper::deg_to_rad(310), angle_helper::deg_to_rad(50), config::OUTPUT_INNER_RADIUS, config::GRID_SIZE, Direction::INCREASING, set.output_variables()),  // TODO: replace with configuration values
  _set(set),
  _drawer(fname, width, height), _prop(config::THIN_STROKE_WIDTH, Color::BLACK, Color::BLACK),
  _split_prop(1, Color::BLACK, Color::GLOW_10)
{
	double angle = 180 / set.input_variables().size() - config::INPUT_SEPERATION_ANGLE;
	double start = 90, end = start+angle;
	std::size_t i = 0;
	for (DefVar var: set.input_variables())
	{
		Polar p(config::INPUT_INNER_RADIUS, angle_helper::deg_to_rad(end));
		Cartesian c; PolarCartesian pc(800, 800); pc.convert(p, c);
		std::cout << p << " to " << c << std::endl;
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
		start += angle + config::INPUT_SEPERATION_ANGLE;
		end += angle + config::INPUT_SEPERATION_ANGLE;
	}

	for (DefDataRow row: set)
	{
		std::vector<Polar> in, out;
		for (std::size_t k = 0; k < _axis.size(); ++k)
		{
			in.push_back(_axis[k].get_coord(row[k].value)); // TODO: Throw null value exception
		}
		Polar connector(config::OUTPUT_INNER_RADIUS + config::INPUT_THICKNESS, _grid.get_coord(row[_axis.size()].value, 0).phi());
		for (std::size_t k = 0; k < _grid.outputs; ++k)
		{
			out.push_back(_grid.get_coord(row[_axis.size() + k].value, k)); // TODO: Throw null value exception
		}
		const Color & c = _grid.get_color(row[set.input_variables().size()].value);
		DataLink link(in, connector, out, DrawerProperties<>(0.4, c, Color(c.r(), c.g(), c.b(), 0.5)));
		for(const VarAxis & va: _axis)
		{
			link.add_link_prop(va.prop);
		}
		_links.push_back(link);
	}

	draw_scene();
}

void Scene::draw_scene(void)
{
	_drawer.draw_coord_grid(_grid, _prop, _prop); // TODO: Replace properties with configuration properties

	for (VarAxis axis: _axis)
		_drawer.draw_var_axis(axis); // TODO: Replace properties with configuration properties

	for (DataLink link: _links)
		_drawer.draw_data_link(link); // TODO:: Replace properties with configuration properties

}
