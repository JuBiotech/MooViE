/*
 * Drawer.h
 *
 *  Created on: 05.07.2017
 *      Author: beyss
 */

#ifndef DRAWER_H_
#define DRAWER_H_

#include "PolarCartesian.h"
#include "DrawerProperties.h"
#include "Link.h"
#include "Ticks.h"
#include <cairommconfig.h>
#include <cairomm/context.h>
#include <cairomm/surface.h>
#include <array>

class Drawer
{
public:
	enum Direction
	{
		INCREASING, DECREASING
	};
	Drawer(const std::string& filename, size_t width, size_t height)
			: _pc {width, height}
	{
		_cr = Cairo::Context::create(Cairo::SvgSurface::create(
				filename, width, height));
	}

	///Draws a Link in coord diagram
	void drawLink(const Link& link, const DrawerProperties<>& prop);
	//Draws an axis in choord diagram
	void drawAxis(double radius, double thickness, const Angle& begin,
			const Angle& end, const DrawerProperties<>& prop, Direction dir, const Ticks& ticks, const Label& label);
	//draws an axis composed of sub axis in a choord diagram
	void drawSplitAxis(double inner_radius, double thickness,
			const Angle& begin, const Angle& end,
			const DrawerProperties<std::array<Color, 10>>& prop, Direction dir);
	//draws a polar coordinate grid
	void drawCoordGrid(const Polar& lower_left, const Polar& upper_right, Direction dir, size_t ys,
			const DrawerProperties<>& prop_thin, const DrawerProperties<>& prop_thick);
	void drawTextOrthogonal(const Label& label, const Polar& start);
	void drawTextParallel(const Label& label, const Polar& start);
	//draws a straigh line
	void drawLine(const Polar& from, const Polar& to,
			const DrawerProperties<>& prop);
	void drawCoordPoint(const Polar& coord, const Angle& width, double height, DrawerProperties<>& prop);
	void drawConnector(const Polar& from, const Polar& to, DrawerProperties<>& prop);
	void finish();
private:
	void drawArc(double inner_radius, const Angle& start, const Angle& end,
			Direction dir);
	void drawWegdeSegment(double radius, double thickness, const Angle& begin,
			const Angle& end, const DrawerProperties<>& prop, Direction dir);
	Cartesian createLinkControlPoint(const Polar& point);
	const PolarCartesian _pc;
	Cairo::RefPtr<Cairo::Context> _cr;
	double _linkControlStrength = 100.0;

};

#endif /* DRAWER_H_ */
