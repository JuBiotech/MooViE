/*
 * VarAxis.h
 *
 *  Created on: 12.12.2017
 *      Author: IBT\stratmann
 */

#ifndef VARAXIS_H_
#define VARAXIS_H_

#include "Ticks.h"
#include "PolarCartesian.h"
#include "DataSet.h"
#include "Mapper.h"
#include "DrawerProperties.h"

/** A VarAxis is an axis which displays the possible values
 * of a input variable. It is visualized as a ring segment
 * with a distinct color and has ticks for better readability.
 *
 * @author stratmann
 * @date 12.12.2017
 */
class VarAxis
{
public:
	/**
	 *
	 */
	VarAxis(Ticks ticks_, const Angle & start_, const Angle & end_,
			double radius_, std::size_t height_, DefVar var_,
			const DrawerProperties<> & prop_, const TextProperties & text_prop_);

	/**
	 *
	 */
	Polar get_coord(double val) const;
public:
	/* The Variable this VarAxis represents */
	DefVar 			var;
	/** The ticks of this variable */
	Ticks 			ticks;
	/** A mapping from actual values to angles */
	Mapper 			_input_mapper;

	/** Start and end angle for drawing the VarAxis */
	Angle 			start, end;
	/** Start radius of the VarAxis */
	double 			radius;
	/** Height of the VarAxis */
	std::size_t 		height;

	/** Label showing the variable name */
	Label 			label;
	/** Style defining how the VarAxis is drawn */
	DrawerProperties<> 	prop;
};

#endif /* VARAXIS_H_ */
