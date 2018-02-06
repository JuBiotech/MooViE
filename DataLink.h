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

/** A DataLink is the visualization of a DataRow. It consists of links, a connector start coordinate and a
 * connector. Links which are curves starting at the VarAxis representing the input of the associated variable.
 * A connector is a curve on the CoordGrid representing the outputs of the associated input value tuple.
 * @author stratmann
 * @date 12.12.2017
 */
class DataLink
{
public:
	/** Creates a new DataLink, a connection from the different inputs to their output values.
	 * @param input_coords coordinates of the different VarAxis
	 * @param connector_coord coordinate of the connector begin
	 * @param output_coords coordinates of the CoordGrid
	 * @param connector_prop DrawerProperties for the connector
	 */
	DataLink(const std::vector<Polar> & input_coords, const Polar & connector_coord,
			const std::vector<Polar> & output_coord, const DrawerProperties<> & connector_prop);

	/** Returns a vector with the Polar coordinates which are placed at the position
	 * of the VarAxis.
	 * @return coordinates of the different VarAxis
	 */
	inline const std::vector<Polar> & get_input_coords() const
	{
		return _input_coords;
	}

	/** Returns a Polar coordinate which is placed at the beginning of CoordGrid and used to
	 * as a starting point for drawing the connector.
	 * @return coordinates of the different VarAxis
	 */
	inline const Polar & get_connector_coord() const
	{
		return _connector_coord;
	}

	/** Returns a vector with the Polar coordinates which are placed at the position
	 * of the CoordGrid.
	 * @return coordinates of the different VarAxis
	 */
	inline const std::vector<Polar> & get_output_coords() const
	{
		return _output_coords;
	}

	/** Returns a DrawerProperties instance holding information about how to draw
	 * the connector on the CoordGrid.
	 * It should have the color of the section it entered the CoordGrid.
	 * @return DrawerProperties for drawing the connector
	 */
	inline const DrawerProperties<> & get_connector_prop() const
	{
		return _connector_prop;
	}

	/** Returns a DrawerProperties instance holding information about how to draw
	 * the link from the (i+1)-th VarAxis to the connector coordinate.
	 * It should have the color of the VarAxis filling.
	 * @return DrawerProperties for drawing the (i+1)-th link
	 */
	inline const DrawerProperties<> & get_link_prop(std::size_t i) const
	{
		return _link_props[i];
	}

	/** Adds a DrawerProperties instance which is used to determine the color
	 * of the next link.
	 * It should have the color of the next VarAxis filling.
	 * @param DrawerProperties for drawing the next link
	 */
	inline void add_link_prop(const DrawerProperties<> prop)
	{
		_link_props.push_back(prop);
	}

private:
	/* Coordinates for drawing the DataLink */
	std::vector<Polar> 		_input_coords, _output_coords;
	Polar 				_connector_coord;

	/* DrawerProperties for coloring the DataLink */
	DrawerProperties<> 		_connector_prop;
	std::vector<DrawerProperties<>>	_link_props;
};

#endif /* DATALINK_H_ */
