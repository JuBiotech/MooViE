/*
 * Scene.cc
 *
 *  Created on: 28.08.2017
 *      Author: beyss
 */

#include "Scene.h"
#include "Config.h"
#include <iostream>

Scene::Scene(const Configuration & config)
: _config(config),
  _set(DataSet<double>::parse_from_csv(Util::read_file(config.get_input_file()), config.get_inputs())), _drawer(config),
  _grid(10, 10, angle_helper::deg_to_rad(310), angle_helper::deg_to_rad(50), config.get_output_inner_radius(), config.get_grid_size(), Direction::INCREASING, _set.output_variables()),  // TODO: add output angle calculation
  _split_prop(config.get_prop_thick().line_width, Color::BLACK, Color::GLOW_10)
{
	double angle = 180 / _set.input_variables().size() - config::INPUT_SEPERATION_ANGLE;
	double start = 90, end = start+angle;
	std::size_t i = 0;
	for (DefVar var: _set.input_variables())
	{
		Polar p(config.get_input_inner_radius(), angle_helper::deg_to_rad(end));
		Cartesian c; PolarCartesian pc(800, 800); pc.convert(p, c);
		std::cout << p << " to " << c << std::endl;
		_axis.push_back(
				VarAxis(
						Ticks(10, 10, std::make_pair(var.min, var.max),
								TextProperties("Liberation Serif", 8), "cm"),
						angle_helper::deg_to_rad(start),
						angle_helper::deg_to_rad(end),
						config.get_input_inner_radius(), config.get_input_thickness(),
						var,
						DrawerProperties<>(1, Color::BLACK,
								Color::SET3.at(_set.input_variables().size(), i++)),
						config.get_var_label()));
		start += angle + config::INPUT_SEPERATION_ANGLE;
		end += angle + config::INPUT_SEPERATION_ANGLE;
	}

	for (DefDataRow row: _set)
	{
		std::vector<Polar> in, out;
		for (std::size_t k = 0; k < _axis.size(); ++k)
		{
			in.push_back(_axis[k].get_coord(row[k].value)); // TODO: Throw null value exception
		}
		Polar connector(config.get_output_inner_radius(), _grid.get_coord(row[_axis.size()].value, 0).phi());
		for (std::size_t k = 0; k < _grid.outputs; ++k)
		{
			out.push_back(_grid.get_coord(row[_axis.size() + k].value, k)); // TODO: Throw null value exception
		}
		const Color & c = _grid.get_color(row[_set.input_variables().size()].value);
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
	_drawer.draw_coord_grid(_grid, _config.get_prop_thick(), _config.get_prop_thin());

	for (VarAxis axis: _axis)
		_drawer.draw_var_axis(axis);

	for (DataLink link: _links)
		_drawer.draw_data_link(link);

}
