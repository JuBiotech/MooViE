#include <Scene.h>
#include <iostream>

Scene::Scene () :
    m_set (Configuration::get_instance ().get_input_file ()), m_drawer (
	new CairoDrawer (Configuration::get_instance ().get_output_file (),
			 Configuration::get_instance ().get_width (),
			 Configuration::get_instance ().get_height (),
			 m_set.get_num_inputs ())), m_grid (
	m_set.output_variables (),
	angle_helper::deg_to_rad (
	    360 - Configuration::get_instance ().get_output_angle_span () / 2),
	angle_helper::deg_to_rad (
	    Configuration::get_instance ().get_output_angle_span () / 2),
	Configuration::get_instance ().get_output_inner_radius (),
	Configuration::get_instance ().get_grid_size (), Direction::CLOCKWISE)
{
  if (m_set.get_num_inputs () > 12)
    {
      throw std::out_of_range ("cannot have more than 12 inputs");
    }
  if (m_set.get_num_outputs () > 8)
    {
      throw std::out_of_range ("cannot have more than 8 outputs");
    }
  if (m_set.get_num_rows () > 20000)
    {
      throw std::out_of_range ("cannot have more than 20,000 data rows");
    }
  if (m_set.get_num_rows () == 1)
    {
      throw std::out_of_range ("cannot have just one row");
    }

  initialize ();

  draw_components ();
}

std::vector<DefVariable>
Scene::get_input_variables () const
{
  return m_set.input_variables ();
}

std::vector<DefVariable>
Scene::get_output_variables () const
{
  return m_set.output_variables ();
}

void
Scene::toggle_input (std::size_t index, bool mode)
{
  if (index >= m_set.get_num_inputs ())
    {
      throw std::out_of_range (
	  "index " + std::to_string (index) + " exceeds input index range [0, "
	      + std::to_string (m_set.get_num_inputs ()) + ")");
    }

  m_set.toggle_column (index, mode);
}

void
Scene::toggle_output (std::size_t index, bool mode)
{
  if (index >= m_set.get_num_outputs ())
    {
      throw std::out_of_range (
	  "index " + std::to_string (index) + " exceeds output index range [0, "
	      + std::to_string (m_set.get_num_outputs ()) + ")");
    }

  m_set.toggle_column (index + m_set.get_num_inputs (), mode);
}

void
Scene::swap_inputs (std::size_t from_index, std::size_t to_index)
{
  if (from_index >= m_set.get_num_inputs ())
    {
      throw std::out_of_range (
	  "from_index " + std::to_string (from_index)
	      + " exceeds input index range [0, "
	      + std::to_string (m_set.get_num_inputs ()) + ")");
    }
  if (to_index >= m_set.get_num_inputs ())
    {
      throw std::out_of_range (
	  "to_index " + std::to_string (to_index)
	      + " exceeds input index range [0, "
	      + std::to_string (m_set.get_num_inputs ()) + ")");
    }

  m_set.swap_columns (from_index, to_index);
}

void
Scene::swap_outputs (std::size_t from_index, std::size_t to_index)
{
  if (from_index >= m_set.get_num_outputs ())
    {
      throw std::out_of_range (
	  "from_index " + std::to_string (from_index)
	      + " exceeds output index range [0, "
	      + std::to_string (m_set.get_num_outputs ()) + ")");
    }
  if (to_index >= m_set.get_num_outputs ())
    {
      throw std::out_of_range (
	  "to_index " + std::to_string (to_index)
	      + " exceeds input index range [0, "
	      + std::to_string (m_set.get_num_outputs ()) + ")");
    }

  m_set.swap_columns (from_index + m_set.get_num_inputs (),
		      to_index + m_set.get_num_inputs ());
}

void
Scene::restrict_input (std::size_t index, double lower_restr,
		       double upper_restr)
{
  if (index >= m_set.get_num_active_inputs ())
    {
      throw std::out_of_range (
	  "index " + std::to_string (index) + " exceeds input index range [0, "
	      + std::to_string (m_set.get_num_active_outputs ()) + ")");
    }
  if (upper_restr < lower_restr)
    {
      throw std::invalid_argument ("lower bound is bigger than upper bound");
    }

  m_set.restrict_column (index, lower_restr, upper_restr);
}

void
Scene::restrict_output (std::size_t index, double lower_restr,
			double upper_restr)
{
  if (index >= m_set.get_num_active_outputs ())
    {
      throw std::out_of_range (
	  "index " + std::to_string (index) + " exceeds output index range [0, "
	      + std::to_string (m_set.get_num_active_outputs ()) + ")");
    }
  if (upper_restr < lower_restr)
    {
      throw std::invalid_argument ("lower bound is bigger than upper bound");
    }

  m_set.restrict_column (index + m_set.get_num_active_inputs (), lower_restr,
			 upper_restr);
}

void
Scene::update (void)
{
  // Update CoinputGrid
  m_grid = OutputGrid (
      m_set.output_variables (),
      angle_helper::deg_to_rad (
	  360 - Configuration::get_instance ().get_output_angle_span () / 2),
      angle_helper::deg_to_rad (
	  Configuration::get_instance ().get_output_angle_span () / 2),
      Configuration::get_instance ().get_output_inner_radius (),
      Configuration::get_instance ().get_grid_size (),
      Direction::CLOCKWISE);

  // Update DomainAxis and IOVectors
  m_axis.clear ();
  m_iov.clear ();
  initialize ();

  // Update Drawer
  m_drawer->change_surface (Configuration::get_instance ().get_output_file (),
			    Configuration::get_instance ().get_width (),
			    Configuration::get_instance ().get_height (),
			    m_set.get_num_active_inputs ());

  draw_components ();
}

void
Scene::draw_components (void)
{
  for (IOVector link : m_iov)
    {
      m_drawer->draw_io_vector (link);
    }

  m_drawer->draw_output_grid (m_grid);

  for (InputAxis axis0 : m_axis)
    {
      m_drawer->draw_input_axis (axis0);
    }

  m_drawer->finish ();
}

void
Scene::initialize (void)
{
  const Configuration & config = Configuration::get_instance ();

  // IOVectors of the later histogram
  std::vector<std::vector<double>> histogram_values (m_set.get_num_active_inputs());

  // Create DomainAxis' from DataSet's input variables
  double angle = 180 / m_set.get_num_active_inputs ()
      - config.get_input_separation_angle ();
  double start = 90 + config.get_input_separation_angle () / 2, end = start
      + angle;
  std::size_t axis_color_pos = 0;
  for (DefVariable var : m_set.input_variables ())
    {
      m_axis.emplace_back (
	  var,
	  angle_helper::deg_to_rad (start),
	  angle_helper::deg_to_rad (end),
	  config.get_input_inner_radius (),
	  config.get_input_thickness (),
	  DrawerProperties<> (
	      config.get_prop_thick ().line_width,
	      Color::BLACK,
	      Configuration::SET3.at (m_set.get_num_active_inputs() - 1,
				      axis_color_pos++)));
      start += angle + config.get_input_separation_angle ();
      end += angle + config.get_input_separation_angle ();
    }

  // Create IOVectors from DataSet's input/output values
  IOVectorFactory factory (m_set.get_num_rows (), m_grid, m_axis);
  for (const DefDataRow & row : m_set)
    {
      m_iov.push_back (factory.create (row));
      for (std::size_t i = 0; i < histogram_values.size (); ++i)
	{
	  histogram_values[i].push_back (row[i].value);
	}
    }

  // Calculate the histograms for the DomainAxis'
  if (config.is_histograms_enabled ())
    {
      for (std::size_t i = 0; i < m_axis.size (); ++i)
	{
	  m_axis[i].calculate_histogram (histogram_values[i]);
	}
    }
}
