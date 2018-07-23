#ifndef DRAWERPROPERTIES_H_
#define DRAWERPROPERTIES_H_

#include <algorithm>
#include <Color.h>

/** DrawerProperties can be used to control the line thinkness, stroke and
 * fill color of a Drawer.
 *
 * @brief Properties to modify a MooViE drawers behavior
 *
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
     *
     * @param _line_width the line width
     * @param _line_color the line color
     * @param _fill_color the fill color
     */
    DrawerProperties (double line_width_, const Color& line_color_,
		      const FillT& fill_color_) :
	line_width (line_width_), line_color (line_color_), fill_color (
	    fill_color_)
    {
    }
};

#endif /* DRAWERPROPERTIES_H_ */
