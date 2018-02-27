/*
 * Scene.cc
 *
 *  Created on: 28.08.2017
 *      Author: beyss
 */

#include "Scene.h"
#include <iostream>

Scene::Scene()
: _set(
		  DefDataSet::parse_from_csv(
				  Util::read_file(Configuration::get_instance().get_input_file()),
				  Configuration::get_instance().get_num_inputs()
		  )
  ),
  _drawer (
		  Configuration::get_instance().get_output_file(),
		  Configuration::get_instance().get_width(),
		  Configuration::get_instance().get_height()
  ),
  _grid(
		  10, 10,
		  angle_helper::deg_to_rad(360 - Configuration::get_instance().get_output_angle_span() / 2),
		  angle_helper::deg_to_rad(Configuration::get_instance().get_output_angle_span() / 2),
		  Configuration::get_instance().get_output_inner_radius(), Configuration::get_instance().get_grid_size(),
		  Direction::INCREASING, _set.output_variables()
  ),
  _split_prop(
		  Configuration::get_instance().get_prop_thick().line_width,
		  Color::BLACK, Color::GLOW_10
  )
{
	const Configuration & config = Configuration::get_instance();

	// DataRows of the later histogram
	std::vector<std::vector<double>> histogram_values;

	// Create VarAxis' from DataSet's input variables
	double angle = 180 / _set.input_variables().size() - config.get_input_separation_angle();
	double start = 90 + config.get_input_separation_angle() / 2, end = start+angle;
	std::size_t axis_color_pos = 0;
	for (DefVar var: _set.input_variables())
	{
		_axis.emplace_back(
				var,
				Ticks(10, 10, std::make_pair(var.min, var.max), config.get_tick_label(), "cm"),
				angle_helper::deg_to_rad(start),
				angle_helper::deg_to_rad(end),
				config.get_input_inner_radius(), config.get_input_thickness(),
				DrawerProperties<>(
					config.get_prop_thick().line_width,
					Color::BLACK, Color::SET3.at(_set.input_variables().size(), axis_color_pos++)
				),
				config.get_var_label()
		);
		start += angle + config.get_input_separation_angle();
		end += angle + config.get_input_separation_angle();

		histogram_values.push_back(std::vector<double>());
	}

	// Create DataLinks from DataSet's input/output values
	for (DefDataRow row: _set)
	{
		std::vector<Polar> in, out;

		for (std::size_t k = 0; k < _axis.size(); ++k)
		{
			in.push_back(_axis[k].get_coord(row[k].value)); // TODO: Throw null value exception
			histogram_values[k].push_back(row[k].value);
		}

		Polar connector(config.get_output_inner_radius() - Configuration::CONNECTOR_DELTA, _grid.get_coord(row[_axis.size()].value, 0).phi());

		for (std::size_t k = 0; k < _grid.get_num_outputs(); ++k)
		{
			out.push_back(_grid.get_coord(row[_axis.size() + k].value, k)); // TODO: Throw null value exception
		}

		const Color & c = _grid.get_color(row[_set.input_variables().size()].value);
		DataLink link(in, connector, out, DrawerProperties<>(0.4, c, Color(c.r(), c.g(), c.b(), 0.5)));

		for(const VarAxis & va: _axis)
		{
			link.add_link_prop(va.get_prop());
		}

		_links.push_back(link);
	}

	// Calculate the histograms for the VarAxis'
	for (std::size_t k = 0; k < _axis.size(); ++k)
	{
		_axis[k].calculate_histogram(histogram_values[k]);
	}

	draw_components();
}

void Scene::draw_components(void)
{
	for (DataLink link: _links)
	{
		_drawer.draw_data_link(link);
	}

	_drawer.draw_coord_grid(_grid);

	for (VarAxis axis: _axis)
	{
		_drawer.draw_var_axis(axis);
	}

}
