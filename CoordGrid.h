 /*
 * CoordGrid.h
 *
 *  Created on: 26.07.2017
 *      Author: beyss
 */

#ifndef COORDGRID_H_
#define COORDGRID_H_

#include <cstddef>
#include <vector>
#include "Mapper.h"
#include "PolarCartesian.h"
#include "DataSet.h"
#include "Ticks.h"
#include "Config.h"

/** A enum for drawer direction */
enum Direction
{
	INCREASING, DECREASING
};

/** Representing a coordinate grid by its dimensional constraints.
 * ╟───┼───┼───┼───╫───┼───┼───┼───╢
 * ║   │   │   │   ║   │   │   │   ║
 * ╟───┼───┼───┼───╫───┼───┼───┼───╢
 * ║   │   │   │   ║   │   │   │   ║
 * ╟───┼───┼───┼───╫───┼───┼───┼───╢
 * ║   │   │   │   ║   │   │   │   ║
 * ╟───┼───┼───┼───╫───┼───┼───┼───╢
 * 4 outputs, 4 ticks
 * @brief The CoordGrid class
 * @author beyss
 * @date 26.07.2017
 */
class CoordGrid
{
public:
    /** Creates a CoordGrid which can be drawn between two angles in a
     * polar coordinate system.
     * @brief CoordGrid
     * @param num_ticks the number of ticks
     * @param start the start angle
     * @param end the end angle
     * @param height the height of the CoordGrid
     * @param output_vars a vector containing the output variables
     */
    CoordGrid(std::size_t major_ticks_, std::size_t minor_ticks_,
    		const Angle & start_, const Angle & end_,
			double radius_, double height_, Direction dir_,
			const std::vector<DefVar> output_vars);

    virtual ~CoordGrid() {};

	Polar get_coord(double val, std::size_t num_output) const;

	Color get_color(double val) const;

public:
    /** The number of outputs. */
    std::size_t outputs;

    /** The major and minor sections */
    std::size_t major_ticks, minor_ticks;

    /** Start and end angle for drawing the CoordGrid */
    Angle start, end;
    /** Radius of the CoordGrid */
    double radius;
    /** Height of the CoordGrid */
    double height;
    /** Direction of the CoordGrid's values */
    Direction dir;

private:
    /** Vector of mappings from actual values to cartesian coordinates */
    std::vector<Mapper> _output_mappers;
};

#endif /* COORDGRID_H_ */
