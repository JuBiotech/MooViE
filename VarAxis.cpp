/*
 * VarAxis.cpp
 *
 *  Created on: 12.12.2017
 *      Author: IBT\stratmann
 */

#include "VarAxis.h"

VarAxis::VarAxis(Ticks ticks_, std::size_t height_, const Angle & start_, const Angle & end_,
		TextProperties prop_, DefVar var_)
: ticks(ticks_), start(start_), end(end_), height(height_), var(var_),
  _input_mapper(create_axis(var.min, var.max), std::make_pair(start.get(), end.get())), label(var.name, prop_) {}

Polar VarAxis::get_coord(double val, double radius) const
{
	return Polar(radius, _input_mapper.map(val));
}
