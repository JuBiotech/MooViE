/*
 * DataLink.h
 *
 *  Created on: 12.12.2017
 *      Author: IBT\stratmann
 */

#ifndef DATALINK_H_
#define DATALINK_H_

#include <vector>
#include "PolarCartesian.h"
#include "DrawerProperties.h"

class DataLink
{
public:
	DataLink(const std::vector<Polar> & input_coords, const Polar & connector_coord,
			const std::vector<Polar> & output_coord, const DrawerProperties<> & connector_prop);

	inline const std::vector<Polar> & input_coords() const
	{
		return _input_coords;
	}

	inline const Polar & connector_coord() const
	{
		return _connector_coord;
	}

	inline const std::vector<Polar> & output_coords() const
	{
		return _output_coords;
	}

	inline const DrawerProperties<> & connector_prop() const
	{
		return _connector_prop;
	}

	inline const DrawerProperties<> & get_link_prop(std::size_t i) const
	{
		return _link_props[i];
	}

	inline void add_link_prop(const DrawerProperties<> prop)
	{
		_link_props.push_back(prop);
	}

private:
	std::vector<Polar> _input_coords;
	Polar _connector_coord;
	std::vector<Polar> _output_coords;
	DrawerProperties<> _connector_prop;
	std::vector<DrawerProperties<>> _link_props;
};

#endif /* DATALINK_H_ */
