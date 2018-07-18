#include <DomainAxis.h>

DomainAxis::Histogram::Histogram(DefVariable _var)
: var(_var), num_intervals(0)
{
}

void DomainAxis::Histogram::calculate(const std::vector<double> & data)
{
    double span = std::abs(var.max - var.min);
    double section_width = span / num_intervals;

    for (double value: data)
    {
    	std::size_t pos = std::floor((value - var.min) / section_width);
		++frequencies.at(pos < num_intervals ? pos : num_intervals - 1);
    }

    if (data.size() > 0)
    {
    	for (std::size_t i = 0; i < frequencies.size(); ++i)
    	{
    		frequencies[i] /= data.size();
    	}
    }
}

double DomainAxis::Histogram::get_section_frequency(std::size_t i) const
{
	if (i >= num_intervals)
	{
		throw std::out_of_range(
				"Histogram section index is out of range (value: "
				+ std::to_string(i) + ", range: 0-"
				+ std::to_string(num_intervals - 1) + ")"
		);
	}

    return frequencies[i];
}

DomainAxis::DomainAxis(DefVariable _var,
		 const Angle& _start, const Angle& _end,
		 double _radius, double _height,
		 const DrawerProperties<> & _prop)
: var(_var),
  scale(
		  Configuration::get_instance().get_num_major_sections_axis(),
		  Configuration::get_instance().get_num_minor_sections_axis(),
		  create_rounded_interval(_var.min, _var.max),
		  Configuration::get_instance().get_prop_scale_label(), _var.unit
  ),
  start(_start), end(_end),radius(_radius),  height(_height),
  prop(_prop),
  histogram(_var)
{}

void DomainAxis::calculate_histogram(const std::vector<double> & data)
{
	histogram.set_num_intervals(Configuration::get_instance().get_num_histogram_classes());
    histogram.calculate(data);
}
