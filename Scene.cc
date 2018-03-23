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
				  Util::read_file(Configuration::get_instance().get_input_file())
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
	initialize();

	draw_components();
}

void Scene::update(void)
{
	// Update CoordGrid
	_grid.set_start(angle_helper::deg_to_rad(360 - Configuration::get_instance().get_output_angle_span() / 2));
	_grid.set_end(angle_helper::deg_to_rad(Configuration::get_instance().get_output_angle_span() / 2));
	_grid.set_radius(Configuration::get_instance().get_output_inner_radius());
	_grid.set_height(Configuration::get_instance().get_grid_size());

	// Update VarAxis and DataLinks
	_axis.clear();
	_links.clear();
	initialize();

	// Update Drawer
	_drawer.change_surface(
			Configuration::get_instance().get_output_file(),
			Configuration::get_instance().get_width(),
			Configuration::get_instance().get_height()
	);

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

void Scene::initialize(void)
{
	const Configuration & config = Configuration::get_instance();

	// DataRows of the later histogram
	std::vector<std::vector<double>> histogram_values(_set.input_variables().size());

	// Create VarAxis' from DataSet's input variables
	double angle = 180 / _set.input_variables().size() - config.get_input_separation_angle();
	double start = 90 + config.get_input_separation_angle() / 2, end = start+angle;
	std::size_t axis_color_pos = 0;
	for (DefVar var: _set.input_variables())
	{
		_axis.emplace_back(
				var,
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
	}

	// Create DataLinks from DataSet's input/output values
	DataLinkFactory factory(_set.rows(), _grid, _axis);
	for (const DefDataRow & row: _set)
	{
		_links.push_back(factory.create(row));
		for (std::size_t i = 0; i < histogram_values.size(); ++i)
		{
			histogram_values[i].push_back(row[i].value);
		}
	}

	// Calculate the histograms for the VarAxis'
	for (std::size_t i = 0; i < _axis.size(); ++i)
	{
		_axis[i].calculate_histogram(histogram_values[i]);
	}
}
