#ifndef DRAWER_H_
#define DRAWER_H_

#include "RelationElement.h"
#include <cairommconfig.h>
#include <cairomm/context.h>
#include <cairomm/surface.h>
#include <array>
#include <iostream>

/** CairoDrawer is a wrapper class for MooViE's basic drawing abilities
 * which are realized using Cairo.
 * @brief CairoDrawer draws on a SVG surface and stores it to a file.
 * @author beyss
 * @date 05.07.2017
 */
class CairoDrawer
{
public:
	static const double RADIAL_TEXT_FACTOR;

	static const double COORDGRID_ADJUSTMENT,
						COORDPOINT_ANGLE,
						COORDGRID_DESCRIPTION_ANGLE;

	static const double END_RADIUS_MAJOR_FACTOR,
						END_RADIUS_MINOR_FACTOR,
						RADIUS_TICK_LABEL_FACTOR;

	static const double DATA_LINK_LINE_WIDTH,
						CONNECTOR_ARROW_HEIGHT;

	static const double RADIUS_LABEL_DELTA,
						RADIUS_HISTOGRAM_DELTA,
						CONNECTOR_DELTA,
						TEXT_DELTA,
						ANGLE_DELTA_SMALL,
						ANGLE_DELTA_LARGE,
						RADIUS_DELTA;

	struct TextAlignment
	{
		const static TextAlignment LEFT, HALF_LEFT, CENTERED, HALF_RIGHT, RIGHT;
		double ratio;
		TextAlignment(double ratio);
	};

    /** Creates a CairoDrawer which draws to a file with the given path on
     * a surface from (0,0) with the stored configuration width and
     * height.
     * CairoDrawer uses polar coordinate inputs which are transformed into
     * Cartesian coordinates. The Cartesian center of its coordinate
     * system is (width/2, height/2).
     * @brief CairoDrawer
     */
    CairoDrawer(const std::string & fpath, int width, int height);

    /** Writes and closes file correctly on destruction of this CairoDrawer.
     * @brief ~CairoDrawer
     */
    ~CairoDrawer() { this->finish(); }

    /** Draws a CoordGrid.
     * @brief draw_coord_grid
     * @param grid the CoordGrid to draw
    */
    void draw_coord_grid(const CodomainGrid & grid);

    /** Draws a VarAxis.
     * @brief draw_var_axis
     * @param the VarAxis to draw
     */
    void draw_var_axis(const DomainAxis & axis);

    /** Draws a DataLink.
     * @brief draw_data_link
     * @param the DataLink to draw
     */
    void draw_data_link(const RelationElement & link);

    /**
     *
     */
    void change_surface(const std::string & fpath, int width, int height);


    /** Save and show the CairoDrawer's result.
     * @brief finish
     */
    void finish();

private:
    /**
     *
     */
    void draw_histogram(const DomainAxis::Histogram & histogram,
			double radius, const Angle & begin, const Angle & end);

    /** Draws a bold line between the lines origin1-origin2
     * and target1-target2. This is realized by drawing bezier
     * curves from origin1 to target1 and from origin2 to target2
     * and filling the so created surface.
     * @brief draw_link
     * @param origin1 first origin coordinate
     * @param origin2 second origin coordinate
     * @param target1 first target coordinate
     * @param target2 second target coordinate
     * @param prop DrawerProperties for the link
     */
    void draw_link(const Polar & origin1, const Polar & origin2,
			const Polar & target1, const Polar & target2,
			const DrawerProperties<>& prop);

	/** Draws a connection between to given polar coordinates.
	 * The connection is a bezier curve which is controlled by
	 * automatically generated control points.
	 * @brief draw_connection
	 * @param from the start Polar
	 * @param to the end Polar
	 * @param prop the CairoDrawer properties
	 */
	void draw_connector(const Polar & from, const Polar & to,
			const DrawerProperties<> & prop);

	/** Draws a circle segment which is itself divided in colored
	 * segments.
	 * @brief draw_split_axis
	 * @param inner_radius inner radius of the split axis
	 * @param thickness width of the split axis
	 * @param begin angle of the segments begin
	 * @param end angle of the segments end
	 * @param prop color
	 * @param dir direction of the split axis' colors
	 */
	void draw_segment_axis(double inner_radius, double thickness,
			const Angle & begin, const Angle & end,
			const DrawerProperties<std::array<Color, 10>> & prop, Direction dir);

	/** Draws a filled ring segment around the center of its
	 * coordinate system between the two given Angles and with
	 * the given radius.
	 * @brief draw_ring_segment
	 * @param radius the radius
	 * @param thickness the thinkness of the edge segment
	 * @param begin the begin Angle
	 * @param end the end Angle
	 * @param prop the CairoDrawer properties
	 * @param dir the direction
	 */
	void draw_ring_segment(double radius, double thickness, const Angle& begin,
			const Angle & end, const DrawerProperties<> & prop, Direction dir);

	void draw_connector_segment(double begin_radius, double begin_angle,
			double end_radius, double end_angle,
			const DrawerProperties<> & prop);

	/** Draws a arrow head from a given start pointing.
	 * @brief
	 * @param start the start of the arrow head
	 * @param prop DrawerProperties for the arrow head
	 */
	void draw_arrow(const Polar & start, const DrawerProperties<> & prop);

	/** Draws a line from a given starting vertice to a given end vertice.
	 * @brief draw_line
	 * @param from the starting coordinates
	 * @param to the end coordinates
	 * @param prop the DrawerProperties to use
	 */
	void draw_line(const Polar & from, const Polar & to,
			const DrawerProperties<> & prop);

	/** Draws a simple edge segment around the center of its coordinate system between
	 * the two given Angles and with the given radius.
	 * @brief draw_arc
	 * @param inner_radius the inner radius
	 * @param start the start Angle
	 * @param end the end Angle
	 * @param dir the direction
	 */
	void draw_arc(double inner_radius, const Angle & start, const Angle & end,
			Direction dir);

	/** Draws a coordinate point with given height and with.
	 * @brief draw_coord_point
	 * @param coord the polar coordinate to draw
	 * @param width the width
	 * @param height the height
	 * @param prop the DrawerProperties
	 */
	void draw_coord_point(const Polar & coord, const Angle & width, double height,
					const DrawerProperties<> & prop);

	/** Draws the given label with the same angle like the given coordinate.
	 * @brief draw_text_orthogonal
	 * @param label the label to draw
	 * @param start the coordinate to adjust to
	 */
	void draw_text_parallel(const Label & label, const Polar & start,
			const TextAlignment & alignment = TextAlignment::CENTERED);

	/** Draws the given label orthogonal to the angle of the given
	 * coordinate's angle.
	 * @brief draw_text_orthogonal
	 * @param label the label to draw
	 * @param start the coordinate to adjust to
	 */
	void draw_text_orthogonal(const Label & label, const Polar & start,
			const TextAlignment & alignment = TextAlignment::CENTERED);

	void set_font_face(const Label & label);

	Cairo::TextExtents get_text_extents(const Label & label) const;

	/** ???
	 * @brief createLinkControlPoint
	 * @param point
	 * @return
	 */
	Cartesian create_control_point(const Polar & point) const;

	/**
	 *
	 */
	void set_surface(const std::string & fpath, int width, int height);

private:
    /** Polar-Cartesian converting */
    const PolarCartesian 				_pc;

    /** Smart pointer for calling Cairo functions */
    Cairo::RefPtr<Cairo::Context> 		_cr;

    /** ??? */
    double 								_link_control_strength 	= 100.0;

};

#endif /* DRAWER_H_ */