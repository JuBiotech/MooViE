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
private:
	std::size_t _coord;
public:
	DrawerProperties<> prop;

	DataPoint(std::size_t coord, const DrawerProperties<> _prop)
	: _coord(coord), prop(_prop) {}

	const Polar & coord() const;
};

typedef std::vector<DataPoint> DataLink;

class DataLinkFactory
{
private:
	friend struct DataPoint;

	class CoordinateStorage
	{
	public:
		std::size_t add_unique(Polar && coord);
		inline const Polar & get(std::size_t location)
		{
			return _coordinates[location];
		}
	private:
		std::vector<Polar> _coordinates;
	};

	static CoordinateStorage _coordinate_storage;

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
