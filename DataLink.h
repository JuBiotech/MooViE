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
	const DrawerProperties<> prop;
	DataPoint(Polar&& coord, const DrawerProperties<>& prop)
	: coord(coord), prop(prop)
	{}
};

class DataLink
{
public:
	static std::size_t num_inputs;

	const DataPoint & operator[](std::size_t i) const
	{
		return points[i];
	}

	inline std::size_t size(void) const
	{
		return points.size();
	}

	template<typename... Arg>
	void emplace_back(Arg&&... args)
	{
		points.emplace_back(std::forward<Arg>(args)...);
	}
private:
	std::vector<DataPoint> points;
};

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
