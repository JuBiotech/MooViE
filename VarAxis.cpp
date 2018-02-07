/*
 * VarAxis.cpp
 *
 *  Created on: 12.12.2017
 *      Author: IBT\stratmann
 */

#include "VarAxis.h"
#include <iostream>

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
