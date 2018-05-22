#ifndef DRAWER_H_
#define DRAWER_H_

#include "RelationElement.h"

/** An abstract Drawer class that can be used to draw
 * MooViE elements. Drawer is supposed to cover the strategy that is used to
 * actually draw an image with a MooViE scene. It provides the implementation
 * with a CoordinateConverter, TextAlignment wrapper and basic calculation functions
 * for points.
 *
 * @brief an abstract MooViE Drawer
 *
 * @author stratmann
 * @date 27.04.2018
 */
class Drawer
{
public:
	/* Constant affecting the distance of the control points of a link Bezier curve */
	static constexpr double LINK_CONTROL_STRENGTH = 100;

	/** TextAlignment represents the alignment of MooViE Labels. It can be
	 * used for both horizontal and vertical alignment.
	 *
	 * @brief an text alignment representation
	 */
	struct TextAlignment
	{
		const static TextAlignment LEFT, HALF_LEFT, CENTERED, HALF_RIGHT, RIGHT;
		double ratio;
		TextAlignment(double ratio);
	};

	/** Creates a Drawer which draws on a surface with the given width and height.
	 *
	 * @brief Drawer constructor
	 *
	 * @param width the surface width
	 * @param height the surface height
	 */
	Drawer(int width, int height, std::size_t _num_inputs)
	: coord_converter(width, height), num_inputs(_num_inputs)
	{}

	virtual ~Drawer()
	{}

	/** Alters the surface of this Drawer in with, height and storage path. All unsafed
	 * changes will be stored and all kept resources freed correctly.
	 *
	 * @brief changes the underlying surface by the given parameters
	 *
	 * @param fpath a string containing an valid existing or accessible not existing path
	 * @param width an integer between 0 and MAX_INT
	 * @param height an integer between 0 and MAX_INT
	 */
	virtual void change_surface(const std::string& fpath, int width, int height) = 0;

    /** Draws a CodomainGrid using its radius and angles. For thin or thick lines
     * the properties given by the Configuration instance are used. On
     *
     * @brief draws a CodomainGrid
     *
     * @param grid the CodomainGrid to draw
    */
    virtual void draw_codomain_grid(const CodomainGrid& grid) = 0;

    /** Draws a DomainAxis using its radius and angles. For thin or thick lines
     * the properties given by the Configuration instance are used.
     *
     * @brief draws a DomainAxis
     *
     * @param axis the DomainAxis to draw
     */
    virtual void draw_domain_axis(const DomainAxis& axis) = 0;

    /** Draws a RelationElement using its coordinates.
     *
     * @brief draws a RelationElement
     *
     * @param elem the RelationElement to draw
     */
    virtual void draw_relation_element(const RelationElement& elem) = 0;


    /** Save the Drawer's result to the given file.
     *
     * @brief save results
     */
    virtual void finish() = 0;

protected:
    /** Alters the surface of this Drawer in with, height and storage path.
     *
     * @brief hard-sets the underlying surface by the given parameters
     *
     * @param fpath a string containing an valid or accessible path
	 * @param width an integer between 0 and MAX_INT
	 * @param height an integer between 0 and MAX_INT
     */
    virtual void set_surface(const std::string& fpath, int width, int height) = 0;

    /** Draws a Histogram from the given radius, between begin and end Angle.
     * For the histogram height, thin or thick lines the properties given by
     * the Configuration instance are used.
     *
     * @brief draws a Histogram
     *
     * @param histogram the Histogram to draw
     * @param radius the start radius of the Histogram
     * @param start the starting angle of the Histogram
     * @param end the end angle of the Histogram
     */
    virtual void draw_histogram(const DomainAxis::Histogram& histogram,
			double radius, const Angle& start, const Angle& end) = 0;

    /** Draws a bold line between the lines origin1-origin2
     * and target1-target2. This is realized by drawing Bezier
     * curves from origin1 to target1 and from origin2 to target2
     * and filling the so created surface.
     *
     * @brief draws a link
     *
     * @param origin1 first origin coordinate
     * @param origin2 second origin coordinate
     * @param target1 first target coordinate
     * @param target2 second target coordinate
     * @param prop DrawerProperties for the link
     */
    virtual void draw_link(const Polar& origin1, const Polar& origin2,
			const Polar& target1, const Polar& target2,
			const DrawerProperties<>& prop) = 0;

	/** Draws a connection between to given polar coordinates.
	 * The connection is a bezier curve which is controlled by
	 * automatically generated control points.
	 *
	 * @brief draws a connector
	 *
	 * @param from the start Polar
	 * @param to the end Polar
	 * @param prop the DrawerProperties
	 */
	virtual void draw_connector(const Polar& from, const Polar& to,
			const DrawerProperties<>& prop) = 0;

	/** Draws a circle segment which is itself divided in colored
	 * segments.
	 *
	 * @brief draws a split axis
	 *
	 * @param inner_radius inner radius of the split axis
	 * @param thickness width of the split axis
	 * @param begin angle of the segments begin
	 * @param end angle of the segments end
	 * @param prop color
	 * @param dir direction of the split axis' colors
	 */
	virtual void draw_segment_axis(double inner_radius, double thickness,
			const Angle& begin, const Angle& end,
			const DrawerProperties<std::array<Color, 10>>& prop, Direction dir) = 0;

	/** Draws the given Label output_label with the radius radius_label
	 * and a descriptive path that connects the output label with the
	 * associated output. The path consists of an arc segment and a line.
	 *
	 * @brief draws an output label
	 *
	 * @param output_label the output label to draw
	 * @param radius_label the radius of the output label
	 * @param radius_output the radius of the associated output
	 * @param begin the angle at which the output ends
	 * @param end the angle at which the arc ends
	 */
	virtual void draw_output_label(const Label& output_label,
			double radius_label, double radius_output,
			const Angle& begin, const Angle& end) = 0;

	/** Draws a arrow head from a given start pointing.
	 *
	 * @brief draws arrow
     *
     * @param start the start of the arrow head
	 * @param prop DrawerProperties for the arrow head
	 */
	virtual void draw_arrow(const Polar& start, const DrawerProperties<>& prop) = 0;

	/** Draws a filled ring segment around the center of its
	 * coordinate system between the two given Angles and with
	 * the given radius.
	 *
	 * @brief draws a ring segment
	 *
	 * @param radius the radius
	 * @param thickness the thinkness of the edge segment
	 * @param begin the begin Angle
	 * @param end the end Angle
	 * @param prop the CairoDrawer properties
	 * @param dir the direction
	 */
	virtual void draw_ring_segment(double radius, double thickness,
			const Angle& start, const Angle& end, const DrawerProperties<>& prop,
			Direction dir) = 0;

	/** Draws a Bezier curve from Polar(start_radius, start_angle) to
	 * Polar(end_radius, end_angle) which approximately behaves like Archimedean spiral.
	 * If the smaller difference angle between start_angle and end_angle is bigger than
	 * PI, the spiral will be approximated by two Bezier curves.
	 *
	 * @brief draws a connector Bezier curve
	 *
	 * @param start_radius the radius of the starting point
	 * @param start_angle the angle of the starting point
	 * @param end_radius the radius of the end point
	 * @param end_angle the angle of the end point
	 * @param prop the DrawerProperties for the segment
	 */
	virtual void draw_connector_segment(double start_radius, double start_angle,
			double end_radius, double end_angle,
			const DrawerProperties<>& prop) = 0;

	/** Draws a line from a given starting vertice to a given end vertice.
	 *
	 * @brief draws a simple line
	 *
	 * @param from the starting coordinates
	 * @param to the end coordinates
	 * @param prop the DrawerProperties to use
	 */
	virtual void draw_line(const Polar& from, const Polar& to,
			const DrawerProperties<>& prop) = 0;

	/** Draws a simple edge segment around the center of its coordinate system between
	 * the two given Angles and with the given radius.
	 *
	 * @brief draws an arc
	 *
	 * @param inner_radius the inner radius
	 * @param start the start Angle
	 * @param end the end Angle
	 * @param dir the direction
	 */
	virtual void draw_arc(double inner_radius, const Angle& start, const Angle& end,
			Direction dir) = 0;

	/** Draws a coordinate point with given height and with.
	 *
	 * @brief draws an error box
	 *
	 * @param coord the polar coordinate to draw
	 * @param width the width
	 * @param height the height
	 * @param prop the DrawerProperties
	 */
	virtual void draw_coord_point(const Polar& coord, const Angle& width, double height,
					const DrawerProperties<>& prop) = 0;

	/** Draws the given label with the same angle like the given coordinate.
	 *
	 * @brief draws a Label on a line to the middle
	 *
	 * @param label the label to draw
	 * @param start the coordinate to adjust to
	 */
	virtual void draw_text_parallel(const Label& label, const Polar & start,
			const TextAlignment& alignment = TextAlignment::CENTERED) = 0;

	/** Draws the given label orthogonal to the angle of the given
	 * coordinate's angle.
	 *
	 * @brief draws a Label orthogonal to a line to the middle
	 *
	 * @param label the label to draw
	 * @param start the coordinate to adjust to
	 */
	virtual void draw_text_orthogonal(const Label& label, const Polar& start,
			const TextAlignment& alignment = TextAlignment::CENTERED) = 0;

	/** Calculates a Polar coordinate for the beginning of a connector
	 * between 'from' and 'to'. If the resulting coordinate is passed to
	 * a connector drawing function, the connector does not immediately
	 * start at from.
	 *
	 * @param from the Polar coordinate to start the connector from
	 * @param from the Polar coordinate to draw the connector to
	 *
	 * @return the modified connector start coordinate
	 */
	inline Polar get_connector_start(const Polar& from, const Polar& to)
	{
		return Polar(from.radius() + 0.1 * (to.radius() - from.radius()), from.angle());
	}

	/** Calculates a Polar coordinate for the end of a connector between
	 * 'from' and 'to'. If the resulting coordinate is passed to a connector
	 * drawing function, the connector does not immediately end at to.
	 *
	 * @param from the Polar coordinate to start the connector from
	 * @param from the Polar coordinate to draw the connector to
	 *
	 * @return the modified connector end coordinate
	 */
	inline Polar get_connector_end(const Polar& from, const Polar& to)
	{
		return Polar(to.radius() - 0.1 * (to.radius() - from.radius()), to.angle());
	}

	/** Creates a control point for a Bezier curve approximating a link.
	 *
	 * @brief creates link control point
	 *
	 * @param point coordinate to which the control point will be created
	 *
	 * @return the control point
	 */
	inline Cartesian create_link_control_point(const Polar& point) const
	{
		Polar control(point);
		control.radius() -= LINK_CONTROL_STRENGTH;

		Cartesian control_c;
		coord_converter.convert(control, control_c);

		return control_c;
	}

protected:
    /** Polar-Cartesian converting */
    const CoordinateConverter 	coord_converter;
    /** Number of input variables of the multi-objective data to draw */
    std::size_t 				num_inputs;
};



#endif /* DRAWER_H_ */
