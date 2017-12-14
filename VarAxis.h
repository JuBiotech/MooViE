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

class VarAxis
{
public:
	VarAxis(Ticks ticks_, const Angle & start_, const Angle & end_,
			double radius_, std::size_t height_,
			TextProperties prop_, DefVar var_);

	Polar get_coord(double val) const;
public:
	/** */
	Ticks ticks;
	/** */
	Angle start, end;
	/** */
	double radius;
	/** */
	std::size_t height;

	/** Variable info */
	DefVar var;
	/** */
	Mapper _input_mapper;

	/** */
	Label label;
};

#endif /* VARAXIS_H_ */
