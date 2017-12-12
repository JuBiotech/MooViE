/*
 * Scene.cc
 *
 *  Created on: 28.08.2017
 *      Author: beyss
 */

#include "Scene.h"
#include "Config.h"

Scene::Scene(Drawer & drawer,
		double radius,
		const DefDataSet & set)
: _radius(radius),
  _grid(10, 10, angle_helper::deg_to_rad(-50), angle_helper::deg_to_rad(50), config::GRID_SIZE, Direction::DECREASING, set.output_variables()),  // TODO: replace with configuration values
  _set(set),
  _drawer(drawer), _prop(config::THIN_STROKE_WIDTH, Color::BLACK, Color::BLACK),
  _split_prop(1, Color::BLACK, Color::GLOW_10)
{
	double angle = 180 / set.input_variables().size() - config::INPUT_SEPERATION_ANGLE;
	double start = -90, end = start-angle;
	for (DefVar var: set.input_variables())
	{
		_axis.push_back(VarAxis(Ticks(10,10,std::make_pair(var.min, var.max), TextProperties("Liberation Serif", 8), "cm"),
				config::INPUT_THICKNESS, angle_helper::deg_to_rad(start), angle_helper::deg_to_rad(end), config::VAR_LABEL, var));
		start -= angle + config::INPUT_SEPERATION_ANGLE;
		end -= angle + config::INPUT_SEPERATION_ANGLE;
	}

	for (DefDataRow row: set)
	{
		std::vector<Polar> in, out;
		for (std::size_t i = 0; i < _axis.size(); ++i)
			in.push_back(_axis[i].get_coord(row[i].value, _radius)); // TODO: Throw null value exception
		Polar connector(_radius, _grid.get_coord(row[0].value, _radius, 0).phi());
		for (std::size_t i = 0; i < _grid.outputs; ++i)
			out.push_back(_grid.get_coord(row[i].value, _radius, i)); // TODO: Throw null value exception
		_links.push_back(DataLink(in, connector, out));
	}

	draw_scene();
}

void Scene::draw_scene(void) const
{
	_drawer.draw_coord_grid(_grid, _radius, _prop, _prop); // TODO: Replace properties with configuration properties

	for (VarAxis axis: _axis)
		_drawer.draw_var_axis(axis, _radius, _prop); // TODO: Replace properties with configuration properties

	/*
	for (DataLink link: _links)
		_drawer.draw_data_link(link, _grid, _radius, _prop); // TODO:: Replace properties with configuration properties
		*/
}
