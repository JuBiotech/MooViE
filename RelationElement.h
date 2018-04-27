/*
 * DataLink.h
 *
 *  Created on: 12.12.2017
 *      Author: IBT\stratmann
 */

#ifndef DATALINK_H_
#define DATALINK_H_

#include <vector>
#include "CodomainGrid.h"
#include "DomainAxis.h"
#include "Coordinates.h"
#include "Mapper.h"

struct Point
{
	const Polar coord;
	const DrawerProperties<> prop;
	Point(Polar&& coord, const DrawerProperties<>& prop)
	: coord(coord), prop(prop)
	{}
};

class RelationElement
{
public:
	static std::size_t num_inputs;

	const Point & operator[](std::size_t i) const
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
	std::vector<Point> points;
};

class RelationElementFactory
{
public:
	RelationElementFactory(std::size_t num_data_rows,
			const CodomainGrid & grid,
			const std::vector<DomainAxis> & axis);
	RelationElement create(const DefDataRow & row) const;
private:
	const Color & get_color(double val) const;
private:
	double _line_width, _line_alpha, _fill_alpha;
	const CodomainGrid & _grid;
	const std::vector<DomainAxis> & _axis;
	std::vector<Mapper> _input_mapper,
						_output_mapper;
};

#endif /* DATALINK_H_ */
