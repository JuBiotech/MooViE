/*
 * VarAxis.cpp
 *
 *  Created on: 12.12.2017
 *      Author: IBT\stratmann
 */

#include "VarAxis.h"
#include <iostream>

VarAxis::Histogram::Histogram(DefVar var, std::size_t num_intervals)
: _var(var), _num_intervals(num_intervals), _max_frequency(0)
{
    for (double & height: _frequencies)
      height = 0;
}

void VarAxis::Histogram::calculate(const std::vector<double> & data)
{
    double span = std::abs(_var.max - var.min);
    double section_width = span / _num_intervals;

    for (double value: data)
    {
	std::size_t pos = std::floor((value - _var.min) / section_width);
	++_frequencies[pos];
	if (_frequencies[pos] > _max_frequency)
	{
	    _max_frequency = _frequencies[pos];
	}
    }
}

std::size_t VarAxis::Histogram::get_max_frequency(void) const
{
    return _max_frequency;
}

std::size_t VarAxis::Histogram::get_section_frequency(std::size_t i) const
{
    if (i >= _num_intervals); // TODO: exception handling
    return _frequencies[i];
}

VarAxis::VarAxis(DefVar var_, Ticks ticks_,
		 const Angle & start_, const Angle & end_,
		 double radius_, std::size_t height_,
		 const DrawerProperties<> & prop_, const TextProperties & text_prop_)
: var(var_), ticks(ticks_), _input_mapper(std::make_pair(var.min, var.max), std::make_pair(start_.get(), end_.get())),
  start(start_), end(end_),radius(radius_),  height(height_),
  label(var.name, text_prop_), prop(prop_)
{}

Polar VarAxis::get_coord(double val) const
{
    return Polar(radius, _input_mapper.map(val));
}
