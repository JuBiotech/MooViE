/*
 * DataLink.cpp
 *
 *  Created on: 12.12.2017
 *      Author: IBT\stratmann
 */

#include "DataLink.h"

DataLink::DataLink(const std::vector<Polar> & input_coords, const Polar & connector_coord, const std::vector<Polar> & output_coords)
: _input_coords(input_coords), _connector_coord(connector_coord), _output_coords(output_coords)
{}

