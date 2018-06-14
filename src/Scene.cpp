/*
 * Scene.cc
 *
 *  Created on: 28.08.2017
 *      Author: beyss
 */

#include <Scene.h>

Scene::Scene()
: set(
		  DefDataSet::parse_from_csv(
				  Util::read_file(Configuration::get_instance().get_input_file())
		  )
  ),
  drawer (
		  new CairoDrawer(
				  Configuration::get_instance().get_output_file(),
				  Configuration::get_instance().get_width(),
				  Configuration::get_instance().get_height(),
				  set->input_variables().size()
				  )
  ),
  grid(
		  set->output_variables(),
		  angle_helper::deg_to_rad(360 - Configuration::get_instance().get_output_angle_span() / 2),
		  angle_helper::deg_to_rad(Configuration::get_instance().get_output_angle_span() / 2),
		  Configuration::get_instance().get_output_inner_radius(), Configuration::get_instance().get_grid_size(),
		  Direction::COUNTER_CLOCKWISE
  )
{
	initialize();

	draw_components();
}

void Scene::update(void)
{
	// Update CoordGrid
	grid.set_start(angle_helper::deg_to_rad(360 - Configuration::get_instance().get_output_angle_span() / 2));
	grid.set_end(angle_helper::deg_to_rad(Configuration::get_instance().get_output_angle_span() / 2));
	grid.set_radius(Configuration::get_instance().get_output_inner_radius());
	grid.set_height(Configuration::get_instance().get_grid_size());

	// Update VarAxis and DataLinks
	axis.clear();
	links.clear();
	initialize();

	// Update Drawer
	drawer->change_surface(
			Configuration::get_instance().get_output_file(),
			Configuration::get_instance().get_width(),
			Configuration::get_instance().get_height()
	);

	draw_components();
}

void Scene::draw_components(void)
{
	for (RelationElement link: links)
	{
		drawer->draw_relation_element(link);
	}

	drawer->draw_codomain_grid(grid);

	for (DomainAxis axis0: axis)
	{
		drawer->draw_domain_axis(axis0);
	}

}

void Scene::initialize(void)
{
	const Configuration & config = Configuration::get_instance();

	// DataRows of the later histogram
	std::vector<std::vector<double>> histogram_values(set->input_variables().size());

	// Create VarAxis' from DataSet's input variables
	double angle = 180 / set->input_variables().size() - config.get_input_separation_angle();
	double start = 90 + config.get_input_separation_angle() / 2, end = start+angle;
	std::size_t axis_color_pos = 0;
	for (DefVariable var: set->input_variables())
	{
		axis.emplace_back(
				var,
				angle_helper::deg_to_rad(start),
				angle_helper::deg_to_rad(end),
				config.get_input_inner_radius(), config.get_input_thickness(),
				DrawerProperties<>(
					config.get_prop_thick().line_width,
					Color::BLACK, Configuration::SET3.at(set->input_variables().size(), axis_color_pos++)
				)
		);
		start += angle + config.get_input_separation_angle();
		end += angle + config.get_input_separation_angle();
	}

	// Create DataLinks from DataSet's input/output values
	RelationElementFactory factory(set->rows(), grid, axis);
	for (const DefDataRow & row: *set)
	{
		links.push_back(factory.create(row));
		for (std::size_t i = 0; i < histogram_values.size(); ++i)
		{
			histogram_values[i].push_back(row[i].value);
		}
	}

	// Calculate the histograms for the VarAxis'
	if (config.is_histograms_enabled())
	{
		for (std::size_t i = 0; i < axis.size(); ++i)
		{
			axis[i].calculate_histogram(histogram_values[i]);
		}
	}
}
