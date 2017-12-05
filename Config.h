/*
 * Config.h
 *
 *  Created on: 23.08.2017
 *      Author: beyss
 */

#ifndef CONFIG_H_
#define CONFIG_H_

#include "Color.h"
#include "DrawerProperties.h"

/** Style configurations for MooViE.
 * Definition namespace for constants like radii,
 * stroke withs, thicknesses and TextProperties.
 */
namespace config
{
	static const double STROKE_WIDTH = 1;
	static const double THIN_STROKE_WIDTH = 0.5;
	static const double THICK_STROKE_WIDTH = 1;
	static const double OUTPUT_BEGIN_ANGLE = 85;
	static const double OUTPUT_END_ANGLE = - OUTPUT_BEGIN_ANGLE;
	static const double INPUT_SEPERATION_ANGLE = 5;

	static const double INPUT_INNER_RADIUS = 180;
	static const double INPUT_THICKNESS = 20;

	static const double OUTPUT_INNER_RADIUS = INPUT_INNER_RADIUS + INPUT_THICKNESS;
	static const double OUTPUT_THICKNESS = INPUT_THICKNESS;

	static const double GRID_SIZE = 150;

	static const TextProperties TICK_LABEL = {"Liberation Serif", 8};
	static const TextProperties VAR_LABEL = {"Liberation Serif", 20};
}




#endif /* CONFIG_H_ */

