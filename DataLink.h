/*
 * DataLink.h
 *
 *  Created on: 12.12.2017
 *      Author: IBT\stratmann
 */

#ifndef DATALINK_H_
#define DATALINK_H_

#include <vector>
#include "CoordGrid.h"
#include "VarAxis.h"
#include "DataLink.h"
#include "PolarCartesian.h"
#include "DrawerProperties.h"

struct DataPoint
{
	const Polar coord;
	DrawerProperties<> prop;
	DataPoint(Polar&& coord, const DrawerProperties<>& prop)
	: coord(coord), prop(prop)
	{}
};

typedef std::vector<DataPoint> DataLink;

class DataLinkFactory
{
public:
	DataLinkFactory(const CoordGrid & grid, const std::vector<VarAxis> & axis);
	DataLink create(const DefDataRow & row) const;
private:
	const Color & get_color(double val) const;
private:
	const CoordGrid & _grid;
	const std::vector<VarAxis> & _axis;
	std::vector<Mapper> _input_mapper,
						_output_mapper;
};

#endif /* DATALINK_H_ */
