#include <Scene.h>
#include <iostream>

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
	if (set->get_num_inputs() > 12)
	{
		throw std::out_of_range("cannot have more than 12 inputs");
	}
	if (set->get_num_outputs() > 8)
	{
		throw std::out_of_range("cannot have more than 8 outputs");
	}
	if (set->get_num_rows() > 20000)
	{
		throw std::out_of_range("cannot have more than 20,000 data rows");
	}

	initialize();

	draw_components();
}


void Scene::toggle_input(std::size_t index, bool mode)
{
	if (index >= set->input_variables().size())
	{
		throw std::out_of_range("index " + std::to_string(index)
				+ " exceeds input index range 0 to"
				+ std::to_string(set->input_variables().size()));
	}

	set->toggle_column(index, mode);
}

void Scene::toggle_output(std::size_t index, bool mode)
{
	if (index >= set->output_variables().size())
	{
		throw std::out_of_range("index " + std::to_string(index)
				+ " exceeds output index range 0 to"
				+ std::to_string(set->output_variables().size()));
	}

	set->toggle_column(index, mode);
}

void Scene::swap_inputs(std::size_t from_index, std::size_t to_index)
{
	if (from_index >= set->input_variables().size())
	{
		throw std::out_of_range("from_index " + std::to_string(from_index)
				+ " exceeds input index range 0 to"
				+ std::to_string(set->input_variables().size()));
	}
	if (to_index >= set->input_variables().size())
	{
		throw std::out_of_range("to_index " + std::to_string(to_index)
				+ " exceeds input index range 0 to"
				+ std::to_string(set->input_variables().size()));
	}

	set->swap_columns(set->get_num_inputs() + from_index,
			set->get_num_inputs() + to_index);
}

void Scene::swap_outputs(std::size_t from_index, std::size_t to_index)
{
	if (from_index >= set->output_variables().size())
	{
		throw std::out_of_range("from_index " + std::to_string(from_index)
				+ " exceeds output index range 0 to"
				+ std::to_string(set->output_variables().size()));
	}
	if (to_index >= set->output_variables().size())
	{
		throw std::out_of_range("to_index " + std::to_string(to_index)
				+ " exceeds input index range 0 to"
				+ std::to_string(set->output_variables().size()));
	}

	set->swap_columns(set->get_num_outputs() + from_index,
			set->get_num_outputs() + to_index);
}

void Scene::restrict_input(std::size_t index, double lower_restr, double upper_restr)
{
	if (index >= set->output_variables().size())
	{
		throw std::out_of_range("index " + std::to_string(index)
				+ " exceeds input index range 0 to"
				+ std::to_string(set->output_variables().size()));
	}
	if (upper_restr < lower_restr)
	{
		throw std::invalid_argument("lower bound is bigger than upper bound");
	}

	set->restrict_column(index, lower_restr, upper_restr);
}

void Scene::restrict_output(std::size_t index, double lower_restr, double upper_restr)
{
	if (index >= set->output_variables().size())
	{
		throw std::out_of_range("index " + std::to_string(index)
				+ " exceeds output index range 0 to"
				+ std::to_string(set->output_variables().size()));
	}
	if (upper_restr < lower_restr)
	{
		throw std::invalid_argument("lower bound is bigger than upper bound");
	}

	set->restrict_column(index, lower_restr, upper_restr);
}

void Scene::update(void)
{
	// Update CodomainGrid
	grid = CodomainGrid(
			  set->output_variables(),
			  angle_helper::deg_to_rad(360 - Configuration::get_instance().get_output_angle_span() / 2),
			  angle_helper::deg_to_rad(Configuration::get_instance().get_output_angle_span() / 2),
			  Configuration::get_instance().get_output_inner_radius(), Configuration::get_instance().get_grid_size(),
			  Direction::COUNTER_CLOCKWISE
	);

	// Update DomainAxis and RelationElements
	axis.clear();
	links.clear();
	initialize();

	// Update Drawer
	drawer->change_surface(
			Configuration::get_instance().get_output_file(),
			Configuration::get_instance().get_width(),
			Configuration::get_instance().get_height(),
			set->get_num_inputs()
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

	// RelationElements of the later histogram
	std::vector<std::vector<double>> histogram_values(set->get_num_inputs());

	// Create DomainAxis' from DataSet's input variables
	double angle = 180 / set->get_num_inputs() - config.get_input_separation_angle();
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
					Color::BLACK, Configuration::SET3.at(set->get_num_inputs() - 1, axis_color_pos++)
				)
		);
		start += angle + config.get_input_separation_angle();
		end += angle + config.get_input_separation_angle();
	}

	// Create RelationElements from DataSet's input/output values
	RelationElementFactory factory(set->get_num_rows(), grid, axis);
	for (const DefDataRow & row: *set)
	{
		std::cout << row[0].value << " " << row[1].value << " " << row[2].value << " " << row[3].value
				<< " " << row[4].value << " " << row[5].value /*<< " " << row[6].value*/ << std::endl;
		links.push_back(factory.create(row));
		for (std::size_t i = 0; i < histogram_values.size(); ++i)
		{
			histogram_values[i].push_back(row[i].value);
		}
	}

	// Calculate the histograms for the DomainAxis'
	if (config.is_histograms_enabled())
	{
		for (std::size_t i = 0; i < axis.size(); ++i)
		{
			axis[i].calculate_histogram(histogram_values[i]);
		}
	}
}
