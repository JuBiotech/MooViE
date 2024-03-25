#include "OutputGrid.h"

OutputGrid::OutputGrid (const std::vector<DefVariable>& output_vars,
			const Angle& start, const Angle& end, double radius,
			double height, Direction dir) :
    output_variables (output_vars), m_num_outputs (output_vars.size ()), m_scale (
	Configuration::get_instance ().get_num_major_sections_grid (),
	Configuration::get_instance ().get_num_minor_sections_grid (),
	Configuration::get_instance ().get_prop_scale_label ()), m_start (
	start), m_end (end), m_radius (radius), m_height (height), m_direction (
	dir)
{
  for (DefVariable var : output_vars)
    {
      m_scale.add_scale (std::make_pair (var.min, var.max), var.unit);
    }
}

const DefVariable &
OutputGrid::get_var (std::size_t num_output) const
{
  if (num_output >= m_num_outputs)
    {
      throw std::out_of_range (
	  "Variable index (" + std::to_string (num_output)
	      + ") is out of range " + std::to_string (m_num_outputs - 1));
    }

  return output_variables[num_output];
}
