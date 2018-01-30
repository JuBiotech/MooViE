#ifndef DRAWER_H_
#define DRAWER_H_

#include "PolarCartesian.h"
#include "DrawerProperties.h"
#include "Link.h"
#include "Ticks.h"
#include "CoordGrid.h"
#include "VarAxis.h"
#include "DataLink.h"
#include "Config.h"
#include "Configuration.h"
#include <cairommconfig.h>
#include <cairomm/context.h>
#include <cairomm/surface.h>
#include <array>

/** Drawer is a wrapper class for MooViE's basic drawing abilities
 * which are realized using Cairo.
 * @brief Drawer draws on a SVG surface and stores it to a file.
 * @author beyss
 * @date 05.07.2017
 */
class Drawer
{
public:
    /** Creates a Drawer wich draws to a file with the given path on
     * a surface from (0,0) with the given width and height.
     * Drawer uses polar coordinate inputs which are transformed into
     * cartesian coordinates. The cartesian center of its coordinate 
     * system is (width/2, height/2).
     * @brief Drawer
     * @param filename the file path
     * @param width the drawing surface width
     * @param height the drawing surface height
     */
    Drawer(const Configuration & config);

    /** Writes and closes file correctly on destruction of this Drawer.
     * @brief ~Drawer
     */
    ~Drawer() { this->finish(); }

    /** Draws a coordinate grid from two given coordinates. Direction of the values, number of
     * segments and thin/thick line style are specifiable.
     * @brief drawCoordGrid
     * @param lower_left the lower left coordinate of the grid
     * @param upper_right the upper right coordinate of the grid
     * @param dir direction of the grid's value
     * @param ys segments of the grid
     * @param prop_thin thin line properties
     * @param prop_thick thick line properties
    */
    void draw_coord_grid(const CoordGrid & grid, const DrawerProperties<> & prop_thick,
    		const DrawerProperties<> & prop_thin);

    void draw_var_axis(const VarAxis & axis);

    void draw_data_link(const DataLink & link);

    /** Save and show the Drawer's result.
     * @brief finish
     */
    void finish();

private:
	void draw_link(const Polar & origin1, const Polar & origin2,
			const Polar & target1, const Polar & target2,
			const DrawerProperties<>& prop);

	/** Draws a connection between to given polar coordinates. The connection is a bezier curve
	 * which is controlled by automatically generated control points.
	 * @brief drawConnection
	 * @param from the start Polar
	 * @param to the end Polar
	 * @param prop the Drawer properties
	 */
	void draw_connector(const Polar& from, const Polar& to,
			const DrawerProperties<>& prop);

	/** Draws a circle segment which is itself divided in colored segments.
	 * @brief drawSplitAxis
	 * @param inner_radius inner radius of the split axis
	 * @param thickness width of the split axis
	 * @param begin angle of the segments begin
	 * @param end angle of the segments end
	 * @param prop color
	 * @param dir direction of the split axis' colors
	 */
	void draw_split_axis(double inner_radius, double thickness,
			const Angle& begin, const Angle& end,
			const DrawerProperties<std::array<Color, 10>>& prop, Direction dir);

	/** Draws a filled edge segment around the center of its coordinate system between
	 * the two given Angles and with the given radius.
	 * @brief drawWegdeSegment
	 * @param radius the radius
	 * @param thickness the thinkness of the edge segment
	 * @param begin the begin Angle
	 * @param end the end Angle
	 * @param prop the Drawer properties
	 * @param dir the direction
	 */
	void draw_torus_segment(double radius, double thickness, const Angle& begin,
			const Angle& end, const DrawerProperties<>& prop, Direction dir);

	/** Draws a arrow head from a given center coordinates pointing to the other
	 * given coordinates.
	 * @brief draw_torus_segment
	 *
	 */
	void draw_arrow(const Polar & center, const Polar direction,
			const DrawerProperties<> prop);

	/** Draws a line from a given starting vertice to a given end vertice.
	 * @brief drawLine
	 * @param from the starting coordinates
	 * @param to the end coordinates
	 * @param prop the Drawer properties to use
	 */
	void draw_line(const Polar& from, const Polar& to,
			const DrawerProperties<>& prop);

	/** Draws a simple edge segment around the center of its coordinate system between
	 * the two given Angles and with the given radius.
	 * @brief drawArc
	 * @param inner_radius the inner radius
	 * @param start the start Angle
	 * @param end the end Angle
	 * @param dir the direction
	 */
	void draw_arc(double inner_radius, const Angle& start, const Angle& end,
			Direction dir);

	/** Draws a coordinate point with given height and with.
	 * @brief drawCoordPoint
	 * @param coord the polar coordinate to draw
	 * @param width the width
	 * @param height the height
	 * @param prop the drawer properties
	 */
	void draw_coord_point(const Polar& coord, const Angle& width, double height,
					const DrawerProperties<>& prop);

	/** Draws the given label with the same angle like the given coordinate.
	 * @brief drawTextOrthogonal
	 * @param label the label to draw
	 * @param start the coordinate to adjust to
	 */
	void draw_text_parallel(const Label& label, const Polar& start);

	/** Draws the given label orthogonal to the angle of the given
	 * coordinate's angle.
	 * @brief drawTextOrthogonal
	 * @param label the label to draw
	 * @param start the coordinate to adjust to
	 */
	void draw_text_orthogonal(const Label& label, const Polar& start);

	/** ???
	 * @brief createLinkControlPoint
	 * @param point
	 * @return
	 */
	Cartesian createLinkControlPoint(const Polar& point);

private:
    /** MooViE configuration */
    const Configuration & _config;

    /** Polar-Cartesian converting */
    const PolarCartesian _pc;
    /** Cairo reference pointer, the interface for calling Cairo functions. */
    Cairo::RefPtr<Cairo::Context> _cr;

    /** ??? */
    double _linkControlStrength = 100.0;

};

#endif /* DRAWER_H_ */
