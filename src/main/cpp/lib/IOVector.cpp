#include "IOVector.h"
#include "CairoDrawer.h"

IOVectorFactory::IOVectorFactory (std::size_t num_data_rows,
				  const OutputGrid& grid,
				  const std::vector<InputAxis>& axis) :
    m_grid (grid), m_axis (axis)
{
  m_line_width = 0.1 * (1 + 4 * std::exp (-(num_data_rows * 0.006)));
  m_line_alpha = 3 * m_line_width;
  m_fill_alpha = 2.5 * m_line_width;
  m_round_factor = std::pow (
      10, Configuration::get_instance ().get_relevant_places ());

  std::pair<double, double> out = std::make_pair (
      m_grid.get_start ().value (),
      m_grid.get_start () > m_grid.get_end () ?
	  m_grid.get_end ().value () + 2 * M_PI : m_grid.get_end ().value ());

  const MultiScale& scale = m_grid.get_scale ();
  if (grid.get_direction () == Direction::COUNTER_CLOCKWISE)
    {
      for (size_t i = 0; i < scale.get_scale_number (); ++i)
	{
	  m_output_mapper.emplace_back (scale.get_extremes (i), out);
	}
    }
  else
    {
      for (size_t i = 0; i < scale.get_scale_number (); ++i)
	{
	  m_output_mapper.emplace_back (
	      std::make_pair (scale.get_extremes (i).second,
			      scale.get_extremes (i).first),
	      out);
	}

    }

  for (const InputAxis& elem : m_axis)
    {
      m_input_mapper.emplace_back (
	  elem.get_scale ().get_extremes (),
	  std::make_pair (elem.get_start ().value (),
			  elem.get_end ().value ()));
    }
}

IOVector
IOVectorFactory::create (const DefDataRow & row) const
{
  IOVector elem;
  std::size_t num_inputs = m_axis.size (), num_outputs = m_grid.get_num_outputs();

  for (std::size_t i = 0; i < num_inputs; ++i)
    {
      elem.emplace_back (
	  Polar (m_axis[i].get_radius (),
		 m_input_mapper[i].map (this->round (false, i, row[i].value))),
	  DrawerProperties<> (
	      m_line_width,
	      Color (m_axis[i].get_prop ().fill_color, m_line_alpha),
	      Color (m_axis[i].get_prop ().fill_color, m_fill_alpha)));
    }

  Color line (get_color (this->round (true, 0, row[num_inputs].value)),
	      m_line_alpha);
  Color fill (line.r (), line.g (), line.b (), m_fill_alpha);
  DrawerProperties<> prop (m_line_width, line, fill);
  elem.emplace_back (
      Polar (
	  m_grid.get_radius () - CairoDrawer::CONNECTOR_DELTA,
	  m_output_mapper[0].map (
	      this->round (true, 0, row[num_inputs].value))),
      prop);

  double height_factor = m_grid.get_height ()
      / (m_grid.get_num_outputs () - 0.5);
  for (std::size_t i = 0; i < num_outputs; ++i)
    {
      elem.emplace_back (
	  Polar (
	      m_grid.get_radius ()
		  + Configuration::get_instance ().get_output_thickness ()
		  + i * height_factor,
	      m_output_mapper[i].map (this->round (true, i, row[i + num_inputs].value))),
	  prop);
    }

  return elem;
}

double
IOVectorFactory::round (bool grid, std::size_t i, double val) const
{
  val = std::round (val * m_round_factor) / m_round_factor;

  if (grid)
    {
      double min = m_grid.get_var (i).min, max = m_grid.get_var (i).max;

      if (min > val)
	{
	  val = min;
	}
      if (max < val)
	{
	  val = max;
	}
    }
  else
    {
      double min = m_axis[i].get_var ().min, max = m_axis[i].get_var ().max;

      if (min > val)
	{
	  val = min;
	}
      if (max < val)
	{
	  val = max;
	}
    }

  return val;
}

const Color&
IOVectorFactory::get_color (double val) const
{
  double range = angle_helper::rad_dist (m_grid.get_start ().value (),
					 m_grid.get_end ().value ());
  double angle = m_output_mapper[0].map (val);

  std::size_t i = std::ceil (
      10 * (angle - m_grid.get_start ().value ()) / range);

  return Configuration::GLOW_10[i - 1];
}
