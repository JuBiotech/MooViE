/*
 * CoordGrid.h
 *
 *  Created on: 26.07.2017
 *      Author: beyss
 *
 *  ╟───┼───┼───┼────╫───┼───┼───┼────╢
 *  ║   │   │   │    ║   │   │   │    ║
 *  ╟───┼───┼───┼────╫───┼───┼───┼────╢
 *  ║   │   │   │    ║   │   │   │    ║
 *  ╟───┼───┼───┼────╫───┼───┼───┼────╢
 *  ║   │   │   │    ║   │   │   │    ║
 *  ╟───┼───┼───┼────╫───┼───┼───┼────╢
 *  4 datasets, 2 regions, 4 inter_ticks
 */

#ifndef COORDGRID_H_
#define COORDGRID_H_

#include <cstddef>
#include <vector>

/** Representing a coordinate grid by its dimensional constraints.
 * ╟───┼───┼───┼───╫───┼───┼───┼───╢
 * ║   │   │   │   ║   │   │   │   ║
 * ╟───┼───┼───┼───╫───┼───┼───┼───╢
 * ║   │   │   │   ║   │   │   │   ║
 * ╟───┼───┼───┼───╫───┼───┼───┼───╢
 * ║   │   │   │   ║   │   │   │   ║
 * ╟───┼───┼───┼───╫───┼───┼───┼───╢
 * 4 datasets, 2 regions, 4 inter_ticks
 * @brief The CoordGrid class
 * @author beyss
 * @date 26.07.2017
 */
class CoordGrid
{
public:
    /** Creates a CoordGrid with the given number of datasets, regions,
     * interticks and extreme values.
     * @brief CoordGrid
     * @param num_datasets the number of datasets
     * @param num_regions the number of regions
     * @param inter_ticks the number of interticks
     * @param extreme_vals a vector containing the extreme values
     */
    CoordGrid(size_t num_datasets, size_t num_regions, size_t inter_ticks,
              const std::vector< std::pair<double, double> >& extreme_vals);

    virtual ~CoordGrid();

    /** Returns the number of datasets.
     * @brief getnumdatasets
     * @return the number of datasets
     */
    size_t getnumdatasets() const
    {
        return _num_datasets;
    }

    /** Returns the number of regions.
     * @brief getnumregions
     * @return the number of regions
     */
    size_t getnumregions() const
    {
        return _num_regions;
    }

    /** Returns the number of interticks.
     * @brief getinterticks
     * @return the number of interticks
     */
    size_t getinterticks() const
    {
        return _inter_ticks;
    }

private:
    /** The number of datasets, regions and interticks. */
    size_t _num_datasets, _num_regions, _inter_ticks;

    /** The extrem values */
    std::vector<std::pair<double, double>> _extreme_vals;
};

#endif /* COORDGRID_H_ */
