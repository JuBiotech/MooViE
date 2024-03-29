#ifndef CAIRODRAWER_H_
#define CAIRODRAWER_H_

#include "Drawer.h"
#include <cairommconfig.h>
#include <cairomm/context.h>
#include <cairomm/surface.h>
#include <array>

/** CairoDrawer is a wrapper class for MooViE's basic drawing abilities
 * which are realized using Cairo.
 *
 * @brief SVG surface drawer for MooViE
 *
 * @authors beyss, stratmann
 * @date 05.07.2017
 */
class CairoDrawer : public Drawer
{
public:
  static const double RADIAL_TEXT_FACTOR;

  static const double COORDGRID_ADJUSTMENT, COORDPOINT_ANGLE;

  static const double END_RADIUS_MAJOR_FACTOR, END_RADIUS_MINOR_FACTOR,
      RADIUS_TICK_LABEL_FACTOR;

  static const double IO_LINE_WIDTH, CONNECTOR_ARC_RATIO,
      CONNECTOR_ARROW_HEIGHT, CONNECTOR_ARROW_ANGLE;

  static const double INPUT_RADIUS_DELTA, CONNECTOR_DELTA, TEXT_DELTA,
      ANGLE_DELTA_SMALL, ANGLE_DELTA_MEDIUM, ANGLE_DELTA_LARGE, RADIUS_DELTA,
      OUTPUT_EXTREME_RADIUS_DELTA, OUTPUT_LABEL_LINE_END_DELTA,
      OUTPUT_LABEL_FONT_FACTOR;

private:
  /** Smart pointer for calling Cairo functions */
  Cairo::RefPtr<Cairo::Context> cairo_context;

public:
  CairoDrawer (const std::string & fpath, int width, int height,
	       std::size_t num_inputs_);

  virtual
  ~CairoDrawer ()
  {
    this->finish ();
  }

  virtual void
  change_surface (const std::string& fpath, int width, int height,
		  std::size_t num_inputs_);

  virtual void
  draw_output_grid (const OutputGrid& grid);

  virtual void
  draw_input_axis (const InputAxis& axis);

  virtual void
  draw_io_vector (const IOVector& iov);

  virtual void
  finish ();

protected:
  virtual void
  set_surface (const std::string& fpath, int width, int height);

  virtual void
  draw_histogram (const InputAxis::Histogram& histogram, double radius,
		  const Angle& start, const Angle& end);

  virtual void
  draw_link (const Polar& origin1, const Polar& origin2, const Polar& target1,
	     const Polar& target2, const DrawerProperties<>& prop);

  virtual void
  draw_connector (const Polar& from, const Polar& to,
		  const DrawerProperties<>& prop);

  virtual void
  draw_segment_axis (double inner_radius, double thickness, const Angle& start,
		     const Angle& end,
		     const DrawerProperties<std::array<Color, 10>>& prop,
		     Direction dir);

  virtual void
  draw_output_label (const Label& output_label, double radius_label,
		     double radius_output, const Angle& begin,
		     const Angle& end);

  virtual void
  draw_arrow (const Polar& start, const DrawerProperties<>& prop);

  virtual void
  draw_ring_segment (double radius, double thickness, const Angle& begin,
		     const Angle & end, const DrawerProperties<> & prop,
		     Direction dir);

  virtual void
  draw_connector_segment (double begin_radius, double begin_angle,
			  double end_radius, double end_angle,
			  const DrawerProperties<>& prop);

  virtual void
  draw_line (const Polar& from, const Polar& to,
	     const DrawerProperties<> & prop);

  virtual void
  draw_arc (double inner_radius, const Angle& start, const Angle& end,
	    Direction dir);

  virtual void
  draw_coord_point (const Polar& coord, const Angle& width, double height,
		    const DrawerProperties<> & prop);

  virtual void
  draw_text_parallel (
      const Label& label, const Polar& start, const TextAlignment & alignment =
	  TextAlignment::CENTERED);

  virtual void
  draw_text_orthogonal (const Label& label, const Polar& start,
			const TextAlignment & alignment =
			    TextAlignment::CENTERED);

  /** Sets the font face according to the TextProperties of the given Label.
   *
   * @brief set font style
   *
   * @param label the Label whose properties to set
   */
  void
  set_font_face (const Label& label);

  Cairo::TextExtents
  get_text_extents (const Label& label) const;

  /** Cairo uses an non-standard way to define angles. The angle of 0 is on
   * the positive X axis, but the angle of pi/2 or 90° is on the negative
   * Y axis (the common model uses the positive Y axis).
   *
   * @param angle
   *
   * @return the cairo angle
   */
  inline Angle
  get_cairo_angle (const Angle& angle)
  {
    return Angle (2 * M_PI - angle.value ());
  }
};

#endif /* DRAWER_H_ */
