#include <IOVector.h>
#include "CairoDrawer.h"

IOVectorFactory::IOVectorFactory (std::size_t num_data_rows,
				  const OutputGrid& grid,
				  const std::vector<InputAxis>& axis) :
    m_grid (grid), m_axis (axis)
{
  m_line_width = 0.1 * (1 + std::exp (-(num_data_rows * 0.0006)));
  m_line_alpha = 0.3 * (1 + 3 * std::exp (-(num_data_rows * 0.04)));
  m_fill_alpha = 0.25 * (1 + 3 * std::exp (-(num_data_rows * 0.04)));

  std::pair<double, double> out = std::make_pair (
      m_grid.get_start ().value (),
      m_grid.get_start () > m_grid.get_end () ?
	  m_grid.get_end ().value () + 2 * M_PIl : m_grid.get_end ().value ());

  const MultiScale& scale = m_grid.get_scale ();
  for (size_t i = 0; i < scale.get_scale_number (); ++i)
    {
      m_output_mapper.emplace_back (scale.get_extremes (i), out);
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
  std::size_t num_inputs = m_axis.size (), num_cols = row.size ();

  for (std::size_t i = 0; i < num_inputs; ++i)
    {
      elem.emplace_back (
	  Polar (m_axis[i].get_radius (), m_input_mapper[i].map (row[i].value)),
	  DrawerProperties<> (
	      m_line_width,
	      Color (m_axis[i].get_prop ().fill_color, m_line_alpha),
	      Color (m_axis[i].get_prop ().fill_color, m_fill_alpha)));
    }

  Color line (get_color (row[num_inputs].value), m_line_alpha);
  Color fill (line.r (), line.g (), line.b (), m_fill_alpha);
  DrawerProperties<> prop (m_line_width, line, fill);
  elem.emplace_back (
      Polar (m_grid.get_radius () - CairoDrawer::CONNECTOR_DELTA,
	     m_output_mapper[0].map (row[num_inputs].value)),
      prop);

  double height_factor = m_grid.get_height ()
      / (m_grid.get_num_outputs () - 0.5);
  for (std::size_t i = 0; i < num_cols - num_inputs; ++i)
    {
      elem.emplace_back (
	  Polar (
	      m_grid.get_radius ()
		  + Configuration::get_instance ().get_output_thickness ()
		  + i * height_factor,
	      m_output_mapper[i].map (row[i + num_inputs].value)),
	  prop);
    }

  return elem;
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
