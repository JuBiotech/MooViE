#ifndef CAIRODRAWER_H_
#define CAIRODRAWER_H_

#include "Drawer.h"
#include <cairommconfig.h>
#include <cairomm/context.h>
#include <cairomm/surface.h>
#include <array>
#include <iostream>

/** CairoDrawer is a wrapper class for MooViE's basic drawing abilities
 * which are realized using Cairo.
 *
 * @brief CairoDrawer draws on a SVG surface and stores it to a file.
 *
 * @author beyss
 * @date 05.07.2017
 */
class CairoDrawer : public Drawer
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

    CairoDrawer(const std::string & fpath, int width, int height);

    virtual ~CairoDrawer() { this->finish(); }

    virtual void change_surface(const std::string& fpath, int width, int height);

    virtual void draw_codomain_grid(const CodomainGrid& grid);

    virtual void draw_domain_axis(const DomainAxis& axis);

    virtual void draw_relation_element(const RelationElement& link);

    virtual void finish();

protected:
    virtual void set_surface(const std::string& fpath, int width, int height);

    virtual void draw_histogram(const DomainAxis::Histogram& histogram,
			double radius, const Angle& start, const Angle& end);

    virtual void draw_link(const Polar& origin1, const Polar& origin2,
			const Polar& target1, const Polar& target2,
			const DrawerProperties<>& prop);

    virtual void draw_connector(const Polar& from, const Polar& to,
			const DrawerProperties<>& prop);

    virtual void draw_segment_axis(double inner_radius, double thickness,
			const Angle& start, const Angle& end,
			const DrawerProperties<std::array<Color, 10>>& prop, Direction dir);

    virtual void draw_ring_segment(double radius, double thickness, const Angle& begin,
			const Angle & end, const DrawerProperties<> & prop, Direction dir);

    virtual void draw_connector_segment(double begin_radius, double begin_angle,
			double end_radius, double end_angle,
			const DrawerProperties<>& prop);

    virtual void draw_arrow(const Polar& start, const DrawerProperties<>& prop);

    virtual void draw_line(const Polar& from, const Polar& to,
			const DrawerProperties<> & prop);

    virtual void draw_arc(double inner_radius, const Angle& start, const Angle& end,
			Direction dir);

    virtual void draw_coord_point(const Polar& coord, const Angle& width, double height,
					const DrawerProperties<> & prop);

    virtual void draw_text_parallel(const Label& label, const Polar& start,
			const TextAlignment & alignment = TextAlignment::CENTERED);

    virtual void draw_text_orthogonal(const Label& label, const Polar& start,
			const TextAlignment & alignment = TextAlignment::CENTERED);

    /** Sets the font face according to the TextProperties of the given Label.
     *
     * @brief set font style
     *
     * @param label the Label whose properties to set
     */
    void set_font_face(const Label& label);

	Cairo::TextExtents get_text_extents(const Label& label) const;

	/** Cairo uses an non-standard way to define angles. The angle of 0 is on
	 * the positive X axis, but the angle of pi/2 or 90° is on the negative
	 * Y axis (the common model uses the positive Y axis).
	 *
	 * @param angle
	 *
	 * @return the cairo angle
	 */
	inline Angle get_cairo_angle(const Angle& angle)
	{
		return Angle(2 * M_PI - angle.value());
	}

private:
    /** Smart pointer for calling Cairo functions */
    Cairo::RefPtr<Cairo::Context> _cr;

};

#endif /* DRAWER_H_ */
