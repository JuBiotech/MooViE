/*
 * CoordGrid.cc
 *
 *  Created on: 26.07.2017
 *      Author: beyss
 */

#include "CoordGrid.h"

CoordGrid::~CoordGrid()
{
	// TODO Auto-generated destructor stub
}

CoordGrid::CoordGrid(size_t num_datasets, size_t num_regions,
		size_t inter_ticks,
		const std::vector<std::pair<double, double> >& extreme_vals)
: _num_datasets {num_datasets}
, _num_regions {num_regions}
, _inter_ticks {inter_ticks}
, _extreme_vals {extreme_vals}
{
}
