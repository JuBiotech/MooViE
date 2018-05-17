/*
 * VarAxis.cpp
 *
 *  Created on: 12.12.2017
 *      Author: IBT\stratmann
 */

#include "DomainAxis.h"
#include <iostream>

DomainAxis::Histogram::Histogram(DefVar _var)
: _var(_var), _num_intervals(0)
{
}

void DomainAxis::Histogram::calculate(const std::vector<double> & data)
{
    double span = std::abs(_var.max - _var.min);
    double section_width = span / _num_intervals;

    for (double value: data)
    {
    	std::size_t pos = std::floor((value - _var.min) / section_width);
		++_frequencies.at(pos < _num_intervals ? pos : _num_intervals - 1);
    }
    for (std::size_t i = 0; i < _frequencies.size(); ++i)
    	_frequencies[i] /= data.size();
}

double DomainAxis::Histogram::get_section_frequency(std::size_t i) const
{
    if (i >= _num_intervals); // TODO: exception handling
    return _frequencies[i];
}

DomainAxis::DomainAxis(DefVar _var,
		 const Angle & start, const Angle & end,
		 double radius, std::size_t height,
		 const DrawerProperties<> & prop,
		 const TextProperties & text_prop)
: var(_var),
  scale(
		  Configuration::get_instance().get_num_major_ticks_va(),
		  Configuration::get_instance().get_num_minor_ticks_va(),
		  create_rounded_interval(_var.min, _var.max),
		  Configuration::get_instance().get_tick_label(), _var.unit
  ),
  histogram(_var),
  start(start), end(end),radius(radius),  height(height),
  label(_var.name, text_prop), prop(prop)
{}

void DomainAxis::calculate_histogram(const std::vector<double> & data)
{
	histogram.set_num_intervals(Configuration::get_instance().get_num_histogram_classes());
    histogram.calculate(data);
}
