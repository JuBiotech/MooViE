/*
 * VarAxis.cpp
 *
 *  Created on: 12.12.2017
 *      Author: IBT\stratmann
 */

#include "VarAxis.h"
#include <iostream>

VarAxis::Histogram::Histogram(DefVar var)
: _var(var), _num_intervals(0)
{
}

void VarAxis::Histogram::calculate(const std::vector<double> & data)
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

double VarAxis::Histogram::get_section_frequency(std::size_t i) const
{
    if (i >= _num_intervals); // TODO: exception handling
    return _frequencies[i];
}

VarAxis::VarAxis(DefVar var,
		 const Angle & start, const Angle & end,
		 double radius, std::size_t height,
		 const DrawerProperties<> & prop,
		 const TextProperties & text_prop)
: _var(var),
  _ticks(
		  Configuration::get_instance().get_num_major_ticks_va(),
		  Configuration::get_instance().get_num_minor_ticks_va(),
		  create_axis(var.min, var.max),
		  Configuration::get_instance().get_tick_label(), var.unit
  ),
  _histogram(var),
  _start(start), _end(end),_radius(radius),  _height(height),
  _label(_var.name, text_prop), _prop(prop)
{}

void VarAxis::calculate_histogram(const std::vector<double> & data)
{
	_histogram.set_num_intervals(Configuration::get_instance().get_num_histogram_classes());
    _histogram.calculate(data);
}
