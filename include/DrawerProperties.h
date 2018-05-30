/*
 * DrawerProperties.h
 *
 *  Created on: 05.07.2017
 *      Author: beyss
 */

#ifndef DRAWERPROPERTIES_H_
#define DRAWERPROPERTIES_H_

#include <algorithm>
#include "Color.h"

/** DrawerProperties can be used to control the line thinkness, stroke and
 * fill color of a Drawer.
 * @brief The DrawerProperties class
 * @author beyss
 * @date 05.07.2017
 */
template<typename FillT = Color>
struct DrawerProperties
{
	/** The line width */
	double line_width;
	/** Line color */
	Color line_color;
	/** Fill color(s) */
	FillT fill_color;

    /** Creates a DrawerProperties instance storing the given line thinkness,
     * stroke and fill color of a Drawer.
     * @brief DrawerProperties
     * @param _line_width the line width
     * @param _line_color the line color
     * @param _fill_color the fill color
     */
    DrawerProperties(double _line_width, const Color & _line_color, const FillT& _fill_color)
    : line_width(_line_width), line_color(_line_color), fill_color(_fill_color)
    {
    }
};

#endif /* DRAWERPROPERTIES_H_ */
