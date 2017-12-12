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

/** Representing a coordinate grid by its dimensional constraints.
 * ╟───┼───┼───┼───╫───┼───┼───┼───╢
 * ║   │   │   │   ║   │   │   │   ║
 * ╟───┼───┼───┼───╫───┼───┼───┼───╢
 * ║   │   │   │   ║   │   │   │   ║
 * ╟───┼───┼───┼───╫───┼───┼───┼───╢
 * ║   │   │   │   ║   │   │   │   ║
 * ╟───┼───┼───┼───╫───┼───┼───┼───╢
 * 4 outputs, 2 regions, 4 ticks
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
     * @param num_regions the number of regions
     * @param num_ticks the number of ticks
     * @param start the start angle
     * @param end the end angle
     * @param height the height of the CoordGrid
     * @param output_vars a vector containing the output variables
     */
    CoordGrid(size_t regions, size_t ticks,
              const Angle & start, const Angle & end, std::size_t height,
			  const std::vector<DefVar> output_vars)
		: _outputs(output_vars.size()), _regions(regions), _ticks(ticks),
		  _start(start), _end(end), _height(height)
		{
    		for (DefVar var: output_vars)
    		{
    			_output_mappers.push_back(Mapper(std::make_pair(var.min, var.max), std::make_pair(start.get(), end.get())));
    		}
		}

    virtual ~CoordGrid();

    /** Returns the number of output variables.
     * @brief getnumdatasets
     * @return the number of datasets
     */
    inline size_t & outputs()
    {
        return _outputs;
    }

    /** Returns the number of output variables.
     * @brief getnumdatasets
     * @return the number of datasets
     */
    inline const size_t & outputs() const
    {
    	return _outputs;
    }

    /** Returns the number of regions.
     * @brief getnumregions
     * @return the number of regions
     */
    inline size_t & regions()
    {
        return _regions;
    }

    /** Returns the number of regions.
	 * @brief getnumregions
	 * @return the number of regions
	 */
    inline const size_t & regions() const
	{
		return _regions;
	}

    /** Returns the number of interticks.
     * @brief getinterticks
     * @return the number of interticks
     */
	inline size_t & ticks()
    {
        return _ticks;
    }

    /** Returns the number of interticks.
	 * @brief getinterticks
	 * @return the number of interticks
	 */
	inline const size_t & ticks() const
	{
		return _ticks;
	}

	/** Access function for the start angle of
	 * this CoordGrid.
	 * @brief start
	 * @return a reference to the start angle
	 */
	inline Angle & start()
	{
		return _start;
	}

	/** Access function for the start angle of
	 * this CoordGrid.
	 * @brief start
	 * @return a const reference to the start angle
	 */
	inline const Angle & start() const
	{
		return _start;
	}

	/** Access function for the end angle of
	 * this CoordGrid.
	 * @brief start
	 * @return a reference to the end angle
	 */
	inline Angle & end()
	{
		return _end;
	}

	/** Access function for the end angle of
	 * this CoordGrid.
	 * @brief start
	 * @return a const reference to the end angle
	 */
	inline const Angle & end() const
	{
		return _end;
	}

	/** Access function for the height of
	 * this CoordGrid.
	 * @brief start
	 * @return a reference to the height
	 */
	inline std::size_t & height()
	{
		return _height;
	}

	/** Access function for the height of
	 * this CoordGrid.
	 * @brief start
	 * @return a reference to the height
	 */
	inline const std::size_t & height() const
	{
		return _height;
	}

	Polar get_coord(double val, std::size_t radius, std::size_t num_output) const;

private:
    /** The number of datasets, regions and interticks. */
    size_t _outputs, _regions, _ticks;

    /** Start and end angle for drawing the CoordGrid */
    Angle _start, _end;

    /** Height of the CoordGrid */
    std::size_t _height;

    /** Vector of mappings from actual values to cartesian coordinates */
    std::vector<Mapper> _output_mappers;
};

#endif /* COORDGRID_H_ */
