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

/** Drawer is a wrapper class for MooViE's basic drawing abilities
 * which are realized using Cairo.
 * @brief Drawer draws on a SVG surface and stores it to a file.
 * @author beyss
 * @date 05.07.2017
 */
class Drawer
{
public:
    /** A enum for drawer direction */
    enum Direction
    {
        INCREASING, DECREASING
    };

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
    Drawer(const std::string& filename, size_t width, size_t height)
    : _pc {width, height}
    {
    	const Cairo::RefPtr<Cairo::Surface>& ptr = Cairo::SvgSurface::create(filename, width, height); // TODO: find error
        _cr = Cairo::Context::create(ptr);
    }

    /** Draws a given link on the surface.
     * @brief drawLink
     * @param link the link to draw
     * @param prop the Drawer properties to use
     */
    void drawLink(const Link& link, const DrawerProperties<>& prop);

    //Draws an axis in choord diagram
    void drawAxis(double radius, double thickness, const Angle& begin, 
		  const Angle& end, const DrawerProperties<>& prop, 
		  Direction dir, const Ticks& ticks, const Label& label);
	//draws an axis composed of sub axis in a choord diagram
    void drawSplitAxis(double inner_radius, double thickness,
			const Angle& begin, const Angle& end,
			const DrawerProperties<std::array<Color, 10>>& prop, Direction dir);
	//draws a polar coordinate grid
    void drawCoordGrid(const Polar& lower_left, const Polar& upper_right, Direction dir, size_t ys,
			const DrawerProperties<>& prop_thin, const DrawerProperties<>& prop_thick);

    /** Draws the given label orthogonal to the angle of the given
     * coordinate's angle.
     * @brief drawTextOrthogonal
     * @param label the label to draw
     * @param start the coordinate to adjust to
     */
    void drawTextOrthogonal(const Label& label, const Polar& start);

    /** Draws the given label with the same angle like the given coordinate.
     * @brief drawTextOrthogonal
     * @param label the label to draw
     * @param start the coordinate to adjust to
     */
    void drawTextParallel(const Label& label, const Polar& start);

    /** Draws a line from a given starting vertice to a given end vertice.
     * @brief drawLine
     * @param from the starting coordinates
     * @param to the end coordinates
     * @param prop the Drawer properties to use
     */
    void drawLine(const Polar& from, const Polar& to, const DrawerProperties<>& prop);

    /** Draws a coordinate point with given height and with.
     * @brief drawCoordPoint
     * @param coord the polar coordinate to draw
     * @param width the width
     * @param height the height
     * @param prop the drawer properties
     */
    void drawCoordPoint(const Polar& coord, const Angle& width, double height, DrawerProperties<>& prop);

    /** Draws a connection between to given polar coordinates. The connection is a bezier curve
     * which is controlled by automatically generated control points.
     * @brief drawConnection
     * @param from the start Polar
     * @param to the end Polar
     * @param prop the Drawer properties
     */
    void drawConnector(const Polar& from, const Polar& to, DrawerProperties<>& prop);

    /** Save and show the Drawer's result.
     * @brief finish
     */
    void finish();
private:
    /** Draws a simple edge segment around the center of its coordinate system between
     * the two given Angles and with the given radius.
     * @brief drawArc
     * @param inner_radius the inner radius
     * @param start the start Angle
     * @param end the end Angle
     * @param dir the direction
     */
    void drawArc(double inner_radius, const Angle& start, const Angle& end,
			Direction dir);

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
    void drawWegdeSegment(double radius, double thickness, const Angle& begin,
                        const Angle& end, const DrawerProperties<>& prop, Direction dir);

    /** ???
     * @brief createLinkControlPoint
     * @param point
     * @return
     */
    Cartesian createLinkControlPoint(const Polar& point);

    /** Polar-Cartesian converting */
    const PolarCartesian _pc;
    /** Cairo reference pointer, the interface for calling Cairo functions. */
    Cairo::RefPtr<Cairo::Context> _cr;
    /** ??? */
    double _linkControlStrength = 100.0;

};

#endif /* DRAWER_H_ */
