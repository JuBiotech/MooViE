/*
 * VarAxis.cpp
 *
 *  Created on: 12.12.2017
 *      Author: IBT\stratmann
 */

#include "VarAxis.h"
#include <iostream>

VarAxis::Histogram::Histogram(DefVar var, std::size_t num_intervals)
: _var(var), _num_intervals(num_intervals)
{
    for (std::size_t i = 0; i < _num_intervals; ++i)
	_frequencies.push_back(0);
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

VarAxis::VarAxis(DefVar var_, Ticks ticks_,
		 const Angle & start_, const Angle & end_,
		 double radius_, std::size_t height_,
		 const DrawerProperties<> & prop_, const TextProperties & text_prop_)
: _var(var_), _ticks(ticks_), _input_mapper(std::make_pair(_var.min, _var.max), std::make_pair(start_.get(), end_.get())),
  _histogram(var_, Configuration::get_instance().get_num_histogram_classes()),
  _start(start_), _end(end_),_radius(radius_),  _height(height_),
  _label(_var.name, text_prop_), _prop(prop_)
{}

Polar VarAxis::get_coord(double val) const
{
    return Polar(_radius, _input_mapper.map(val));
}

void VarAxis::calculate_histogram(const std::vector<double> & data)
{
    _histogram.calculate(data);
}
