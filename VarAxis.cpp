/*
 * VarAxis.cpp
 *
 *  Created on: 12.12.2017
 *      Author: IBT\stratmann
 */

#include "VarAxis.h"
#include <iostream>

VarAxis::VarAxis(Ticks ticks_, const Angle & start_, const Angle & end_,
		double radius_, std::size_t height_, DefVar var_,
		const DrawerProperties<> & prop_, const TextProperties & text_prop_)
: ticks(ticks_), start(start_), end(end_),radius(radius_),  height(height_), var(var_),
  _input_mapper(std::make_pair(var.min, var.max), std::make_pair(start.get(), end.get())), label(var.name, text_prop_), prop(prop_)
{
	std::cout << "mapped " << var.min << ", " << var.max << " to " << start.get() << ", " << end.get() << std::endl;
}

Polar VarAxis::get_coord(double val) const
{
	return Polar(radius, _input_mapper.map(val));
}
