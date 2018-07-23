#include <InputAxis.h>

InputAxis::Histogram::Histogram (DefVariable variable) :
    m_variable (variable), m_num_intervals (0)
{
}

void
InputAxis::Histogram::calculate (const std::vector<double> & data)
{
  double span = std::abs (m_variable.max - m_variable.min);
  double section_width = span / m_num_intervals;

  for (double value : data)
    {
      std::size_t pos = std::floor ((value - m_variable.min) / section_width);
      ++m_frequencies.at (pos < m_num_intervals ? pos : m_num_intervals - 1);
    }

  if (data.size () > 0)
    {
      for (std::size_t i = 0; i < m_frequencies.size (); ++i)
	{
	  m_frequencies[i] /= data.size ();
	}
    }
}

double
InputAxis::Histogram::get_section_frequency (std::size_t i) const
{
  if (i >= m_num_intervals)
    {
      throw std::out_of_range (
	  "Histogram section index is out of range (value: "
	      + std::to_string (i) + ", range: 0-"
	      + std::to_string (m_num_intervals - 1) + ")");
    }

  return m_frequencies[i];
}

InputAxis::InputAxis (DefVariable variable, const Angle& start,
		      const Angle& end, double radius, double height,
		      const DrawerProperties<> & prop) :
    m_variable (variable), m_scale (
	Configuration::get_instance ().get_num_major_sections_axis (),
	Configuration::get_instance ().get_num_minor_sections_axis (),
	create_rounded_interval (variable.min, variable.max),
	Configuration::get_instance ().get_prop_scale_label (), variable.unit), m_start (
	start), m_end (end), m_radius (radius), m_height (height), m_prop (
	prop), m_histogram (variable)
{
}

void
InputAxis::calculate_histogram (const std::vector<double> & data)
{
  m_histogram.set_num_intervals (
      Configuration::get_instance ().get_num_histogram_classes ());
  m_histogram.calculate (data);
}
