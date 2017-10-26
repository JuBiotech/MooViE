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


class CoordGrid
{
public:
	CoordGrid(size_t num_datasets, size_t num_regions, size_t inter_ticks,
			const std::vector< std::pair<double, double> >& extreme_vals);

	virtual ~CoordGrid();

	size_t getinterticks() const
	{
		return _inter_ticks;
	}

	size_t getnumdatasets() const
	{
		return _num_datasets;
	}

	size_t getnumregions() const
	{
		return _num_regions;
	}

private:
	size_t _num_datasets;
	size_t _num_regions;
	size_t _inter_ticks;
	std::vector<std::pair<double, double>> _extreme_vals;
};

#endif /* COORDGRID_H_ */
