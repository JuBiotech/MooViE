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

class DataLink
{
public:
	DataLink(const std::vector<Polar> & input_coords,
			const Polar & connector_coord, const std::vector<Polar> & output_coord);

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

private:
	std::vector<Polar> _input_coords;
	Polar _connector_coord;
	std::vector<Polar> _output_coords;
};

#endif /* DATALINK_H_ */
