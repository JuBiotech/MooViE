#include <CairoDrawer.h>

const double CairoDrawer::RADIAL_TEXT_FACTOR = 0.3;

const double CairoDrawer::COORDGRID_ADJUSTMENT = 0.5,
    CairoDrawer::COORDPOINT_ANGLE = 0.005;

const double CairoDrawer::END_RADIUS_MAJOR_FACTOR = 0.25,
    CairoDrawer::END_RADIUS_MINOR_FACTOR = 0.125,
    CairoDrawer::RADIUS_TICK_LABEL_FACTOR = 0.75;

const double CairoDrawer::IO_LINE_WIDTH = 0.1,
    CairoDrawer::CONNECTOR_ARC_RATIO = 0.6,
    CairoDrawer::CONNECTOR_ARROW_HEIGHT = 3;

const double CairoDrawer::INPUT_RADIUS_DELTA = 2.5, CairoDrawer::CONNECTOR_DELTA = 10,
    CairoDrawer::TEXT_DELTA = 0.01, CairoDrawer::ANGLE_DELTA_SMALL = 0.001,
    CairoDrawer::ANGLE_DELTA_MEDIUM = 0.01,
    CairoDrawer::RADIUS_DELTA = 10,
    CairoDrawer::OUTPUT_EXTREME_RADIUS_DELTA = 2,
    CairoDrawer::OUTPUT_LABEL_LINE_END_DELTA = 3,
    CairoDrawer::OUTPUT_LABEL_FONT_FACTOR = 0.1;

const CairoDrawer::TextAlignment CairoDrawer::TextAlignment::LEFT (1),
    CairoDrawer::TextAlignment::CENTERED (0.5),
    CairoDrawer::TextAlignment::RIGHT (0);

CairoDrawer::TextAlignment::TextAlignment (double ratio)
{
  if (0 > ratio)
    {
      ratio = std::abs (ratio);
    }

  if (ratio > 1)
    {
      ratio /= std::floor (std::log10 (ratio));
    }
  this->ratio = ratio;
}

CairoDrawer::CairoDrawer (const std::string& fpath, int width, int height,
			  std::size_t num_inputs) :
    Drawer (width, height, num_inputs)
{
  set_surface (fpath, width, height);
}

void
CairoDrawer::draw_output_grid (const OutputGrid& grid)
{
  cairo_context->set_identity_matrix ();

  const Configuration & conf = Configuration::get_instance ();

  // Draw ring with colored segments which are used to color and distinguish the connectors
  draw_segment_axis (
      grid.get_radius (),
      conf.get_output_thickness (),
      grid.get_start (),
      grid.get_end (),
      DrawerProperties<std::array<Color, 10>> (1, Color::BLACK,
					       Configuration::GLOW_10),
      grid.get_direction ());

  // Calculate the inner and outer radius of the OutputGrid
  double min_radius = grid.get_radius () + conf.get_output_thickness ();
  double max_radius = grid.get_radius () + conf.get_output_thickness ()
      + grid.get_height ();

  // Radian distance (absolute!) between start and end angle
  double span = angle_helper::rad_dist (grid.get_start ().value (),
					grid.get_end ().value ());

  // Calculate how the OutputGrid is separated into thin and thick lines (ticks)
  const std::size_t NUM_SEGMENTS = grid.get_scale ().get_major_intersections ()
      * grid.get_scale ().get_minor_intersections ();
  const std::size_t NUM_THICK_LINES =
      grid.get_scale ().get_minor_intersections ();

  // Draw the ticks of the OutputGrid
  for (size_t i = 0; i <= NUM_SEGMENTS; ++i)
    {
      Angle a ((grid.get_start ().value () + i * span / NUM_SEGMENTS));
      if (i % NUM_THICK_LINES)
	draw_line (Polar (min_radius, a), Polar (max_radius, a),
		   conf.get_prop_thin ());
      else
	draw_line (Polar (min_radius, a), Polar (max_radius, a),
		   conf.get_prop_thick ());
    }

  // Adjusted difference between the radial lines of the OutputGrid (outputs)
  double y_dist = grid.get_height ()
      / (grid.get_num_outputs () - COORDGRID_ADJUSTMENT);

  // Draw the description of the first output
  const TextProperties& name_prop = conf.get_prop_axis_label();
  Label first_label (grid.get_var (0).name, name_prop);
  Cairo::TextExtents extends = get_text_extents(first_label);
  draw_output_label (first_label, max_radius,
		     grid.get_radius () + conf.get_output_thickness () / 2,
		     grid.get_end (),
		     M_PI_2);

  const MultiScale& scale = grid.get_scale ();

  // Draw the scale of the OutputGrid
  std::vector<Label> labels = scale.make_labels(0);
  if (grid.get_direction () == Direction::CLOCKWISE)
    {
      std::reverse(labels.begin(), labels.end());
    }
  draw_text_orthogonal (
      labels.front(),
      Polar (min_radius, grid.get_start () - TEXT_DELTA), TextAlignment::RIGHT);
  draw_text_orthogonal (
      labels.back(),
      Polar (min_radius, grid.get_end () + TEXT_DELTA), TextAlignment::LEFT);

  // Draw the output lines of the OutputGrid
  for (size_t i = 1; i < grid.get_num_outputs (); ++i)
    {
      // Draw the description of the i-th output
      draw_output_label (Label (grid.get_var (i).name, name_prop),
			 max_radius + i * extends.height * name_prop.font_size * OUTPUT_LABEL_FONT_FACTOR,
			 min_radius + i * y_dist, grid.get_end (),
			 M_PI_2 - i * 2 * ANGLE_DELTA_MEDIUM);

      labels = scale.make_labels(0);
      if (grid.get_direction () == Direction::CLOCKWISE)
      {
        std::reverse(labels.begin(), labels.end());
      }
      draw_text_orthogonal (
    	 labels.front(),
		 Polar (min_radius + i * y_dist + OUTPUT_EXTREME_RADIUS_DELTA,
		 grid.get_start () - TEXT_DELTA),
		 TextAlignment::RIGHT);
      draw_text_orthogonal (
         labels.back(),
		 Polar (min_radius + i * y_dist + OUTPUT_EXTREME_RADIUS_DELTA,
		 grid.get_end () + TEXT_DELTA),
		 TextAlignment::LEFT);

      cairo_context->begin_new_path ();
      draw_arc (min_radius + i * y_dist, grid.get_start (), grid.get_end (),
		Direction::COUNTER_CLOCKWISE);
      cairo_context->set_source_rgba (conf.get_prop_thin ().line_color.r (),
				      conf.get_prop_thin ().line_color.g (),
				      conf.get_prop_thin ().line_color.b (),
				      conf.get_prop_thin ().line_color.a ());
      cairo_context->set_line_width (conf.get_prop_thin ().line_width);
      cairo_context->stroke ();
    }
}

void
CairoDrawer::draw_input_axis (const InputAxis& axis)
{
  cairo_context->set_identity_matrix ();

  const Configuration& conf = Configuration::get_instance ();

  // Draw the base of the InputAxis: a filled ring segment
  draw_ring_segment (axis.get_radius (), axis.get_height (), axis.get_start (),
		     axis.get_end (), axis.get_prop (),
		     Direction::COUNTER_CLOCKWISE);

  // Radian distance (absolute!) between start and end angle
  double span = angle_helper::rad_dist (axis.get_start ().value (),
					axis.get_end ().value ());

  // Tick values as strings
  std::vector<Label> tick_labels = axis.get_scale ().make_labels ();
  std::size_t label_pos = 0;

  // Calculate radii for axis and ticks
  double start_radius = axis.get_radius () + axis.get_height ();
  double end_radius_major = start_radius
      + END_RADIUS_MAJOR_FACTOR * axis.get_height ();
  double end_radius_minor = start_radius
      + END_RADIUS_MINOR_FACTOR * axis.get_height ();

  // Get width of longest tick description
  std::size_t max_tick_label_pos = 0;
  const Label& longestTickDiscr = *std::max_element(tick_labels.begin(), tick_labels.end(),
      [](const Label& l0, const Label& l1) {
              return l0.get_text().length() < l1.get_text().length();
  });
  set_font_face (longestTickDiscr);
  Cairo::TextExtents tick_ext = get_text_extents (longestTickDiscr);
  set_font_face (axis.make_label (conf.get_prop_axis_label ()));
  Cairo::TextExtents label_ext = get_text_extents (
      axis.make_label (conf.get_prop_axis_label ()));

  // Calculate radii at that tick labels, axis label and histogram can start
  double radius_tick_label = end_radius_major + tick_ext.width
      + RADIUS_TICK_LABEL_FACTOR * axis.get_height ();
  double radius_label = radius_tick_label + label_ext.height + INPUT_RADIUS_DELTA;
  double radius_histogram = radius_label + label_ext.height
      + INPUT_RADIUS_DELTA;

  // Calculate how the InputAxis' ticks is separated into thin and thick lines (ticks)
  const std::size_t NUM_SEGMENTS = axis.get_scale ().get_major_intersections ()
      * axis.get_scale ().get_minor_intersections ();
  const std::size_t NUM_THICK_LINES =
      axis.get_scale ().get_major_intersections ();

  // Draw the ticks and the associated values labels
  for (size_t i = 0; i <= NUM_SEGMENTS; ++i)
    {
      Angle a (axis.get_start () + span * (double (i) / double (NUM_SEGMENTS)));
      if (i % NUM_THICK_LINES)
	{
	  draw_line (
	      Polar (start_radius, a),
	      Polar (end_radius_minor, a),
	      DrawerProperties<> (axis.get_prop ().line_width / 2,
				  axis.get_prop ().line_color,
				  axis.get_prop ().fill_color));
	}
      else
	{
	  const Label & tick_label = tick_labels[label_pos++];
	  draw_line (Polar (start_radius, a), Polar (end_radius_major, a),
		     axis.get_prop ());

	  draw_text_parallel (tick_label, Polar (radius_tick_label, a),
			      TextAlignment::RIGHT);
	}
    }

  // Draw the name of the Variable
  draw_text_orthogonal (
      axis.make_label (conf.get_prop_axis_label ()),
      Polar (radius_label, Angle::center (axis.get_start (), axis.get_end ())));

  if (conf.is_histograms_enabled ())
    {
      draw_histogram (axis.get_histogram (), radius_histogram,
		      axis.get_start (), axis.get_end ());
    }
}

void
CairoDrawer::draw_io_vector (const IOVector& iov)
{
  // Calculate target from connector coordinate
  std::size_t connector_pos = m_num_inputs;
  const Point from = iov[connector_pos];

  Polar target1 (from.coord.radius () - CONNECTOR_ARROW_HEIGHT,
		 from.coord.angle () - ANGLE_DELTA_SMALL), target2 (
      from.coord.radius () - CONNECTOR_ARROW_HEIGHT,
      from.coord.angle () + ANGLE_DELTA_SMALL);

  // Draw links
  for (std::size_t i = 0; i < m_num_inputs; ++i)
    {
      Polar origin1 (iov[i].coord.radius () - RADIUS_DELTA,
		     iov[i].coord.angle () - ANGLE_DELTA_SMALL), origin2 (
	  iov[i].coord.radius () - RADIUS_DELTA,
	  iov[i].coord.angle () + ANGLE_DELTA_SMALL);
      draw_link (origin1, origin2, target1, target2, iov[i].prop);
    }

  // Draw line from connector to first output
  double connector_distance = (iov[connector_pos + 1].coord.radius ()
      - from.coord.radius ()) * 0.1
      + Configuration::get_instance ().get_output_thickness ();
	if (iov.size() > connector_pos + 2)
	{
		draw_line(from.coord,
				get_connector_start(iov[connector_pos + 1].coord,
						iov[connector_pos + 2].coord), from.prop);
	}
	else
	{
		draw_line(from.coord, iov[connector_pos + 1].coord, from.prop);
	}
  draw_arrow (from.coord, from.prop);

  // Draw connector on OutputGrid
  for (size_t i = connector_pos + 1; i < iov.size () - 1; ++i)
    {
      Polar from = iov[i].coord, to = iov[i + 1].coord;
      draw_connector (get_connector_start (from, to),
		      get_connector_end (from, to), iov[i].prop);
      draw_coord_point (to, COORDPOINT_ANGLE,
			(to.radius () - from.radius ()) * 0.2, iov[i].prop);
    }
}

void
CairoDrawer::change_surface (const std::string& fpath, int width, int height,
			     std::size_t num_inputs_)
{
  finish ();
  set_surface (fpath, width, height);
  m_coord_converter = CoordinateConverter(width, height);
  m_num_inputs = num_inputs_;
}

void
CairoDrawer::finish ()
{
  cairo_context->get_target ()->finish ();
}

void
CairoDrawer::draw_histogram (const InputAxis::Histogram& histogram,
			     double radius, const Angle& start,
			     const Angle& end)
{
  cairo_context->set_identity_matrix ();

  const Configuration & conf = Configuration::get_instance ();

  // Create properties from Configuration
  DrawerProperties<> histogram_background (conf.get_prop_thin ().line_width,
					   conf.get_histogram_background (),
					   conf.get_histogram_background ());
  DrawerProperties<> histogram_fill (conf.get_prop_thin ().line_width,
				     conf.get_histogram_fill (),
				     conf.get_histogram_fill ());
  const DrawerProperties<> & prop_thin = conf.get_prop_thin ();

  // Draw background
  draw_ring_segment (radius, conf.get_histogram_height (), start, end,
		     histogram_background, Direction::COUNTER_CLOCKWISE);

  // Draw thin lines for histogram background
  cairo_context->set_line_width (prop_thin.line_width);
  for (std::size_t i = 1; i < 6; ++i)
    {
      cairo_context->begin_new_path ();
      draw_arc (radius + conf.get_histogram_height () * (i / 6.), start, end,
		Direction::COUNTER_CLOCKWISE);
      cairo_context->stroke ();
    }

  // Draw the histogram graph filling
  cairo_context->begin_new_path ();
  double span = angle_helper::rad_dist (start.value (), end.value ());
  for (std::size_t i = 0; i < histogram.get_num_intervals (); ++i)
    {
      draw_ring_segment (
	  radius,
	  conf.get_histogram_height () * histogram.get_section_frequency (i),
	  start + (span / histogram.get_num_intervals ()) * i,
	  start + (span / histogram.get_num_intervals ()) * (i + 1),
	  histogram_fill, Direction::COUNTER_CLOCKWISE);
    }
  cairo_context->stroke ();

  // Draw the histogram graph outline
  Cartesian start_point;
  m_coord_converter.convert (Polar (radius, start), start_point);
  cairo_context->begin_new_path ();
  cairo_context->set_source_rgba (prop_thin.line_color.r (),
				  prop_thin.line_color.g (),
				  prop_thin.line_color.b (),
				  prop_thin.line_color.a ());
  cairo_context->move_to (start_point.x (), start_point.y ());
  for (std::size_t i = 0; i < histogram.get_num_intervals (); ++i)
    {
      // Create the lower right and upper left coordinates of the histogram column
      Polar right_down (
	  radius, start + (span / histogram.get_num_intervals ()) * (i + 1)),
	  left_up (
	      radius
		  + conf.get_histogram_height ()
		      * histogram.get_section_frequency (i),
	      start + (span / histogram.get_num_intervals ()) * i);
      Cartesian right_down_c, left_up_c;
      m_coord_converter.convert (right_down, right_down_c);
      m_coord_converter.convert (left_up, left_up_c);

      // Draw the histogram column
      cairo_context->line_to (left_up_c.x (), left_up_c.y ());
      draw_arc (left_up.radius (), left_up.angle (), right_down.angle (),
		Direction::CLOCKWISE);
      cairo_context->line_to (right_down_c.x (), right_down_c.y ());
    }
  cairo_context->stroke ();
}

void
CairoDrawer::draw_link (const Polar& origin1, const Polar& origin2,
			const Polar& target1, const Polar& target2,
			const DrawerProperties<>& prop)
{
  cairo_context->set_identity_matrix ();

  // Convert given Polar to Cartesian coordinates
  Cartesian origin1_c, origin2_c, target1_c, target2_c;
  m_coord_converter.convert (origin1, origin1_c);
  m_coord_converter.convert (origin2, origin2_c);
  m_coord_converter.convert (target1, target1_c);
  m_coord_converter.convert (target2, target2_c);

  // Calculate control points for Bezier curve
  Cartesian CTRL_ORIG1 = create_link_control_point (origin1);
  Cartesian CTRL_ORIG2 = create_link_control_point (origin2);
  Cartesian CTRL_TARG1 = create_link_control_point (target1);
  Cartesian CTRL_TARG2 = create_link_control_point (target2);

  cairo_context->begin_new_path ();
  cairo_context->move_to (origin1_c.x (), origin1_c.y ());

  // Draw first Bezier curve from origin to target
  cairo_context->curve_to (CTRL_ORIG1.x (), CTRL_ORIG1.y (), CTRL_TARG1.x (),
			   CTRL_TARG1.y (), target1_c.x (), target1_c.y ());
  // Draw second Bezier curve from target to origin
  cairo_context->curve_to (CTRL_TARG2.x (), CTRL_TARG2.y (), CTRL_ORIG2.x (),
			   CTRL_ORIG2.y (), origin2_c.x (), origin2_c.y ());

  // Set line and fill style and apply drawing
  cairo_context->set_source_rgba (prop.fill_color.r (), prop.fill_color.g (),
				  prop.fill_color.b (), prop.fill_color.a ());
  cairo_context->fill_preserve ();
  cairo_context->set_source_rgba (prop.fill_color.r (), prop.fill_color.g (),
				  prop.fill_color.b (), prop.fill_color.a ());
  cairo_context->set_line_width (prop.line_width);
  cairo_context->stroke ();
}

void
CairoDrawer::draw_connector (const Polar& from, const Polar& to,
			     const DrawerProperties<>& prop)
{
  cairo_context->set_identity_matrix ();
  cairo_context->begin_new_path ();

  // Calculate distance factor
  static const double dist_factor = (1 - CONNECTOR_ARC_RATIO) / 2;

  // Calculate intermediate coordinates to draw the arc from
  double radial_dist = to.radius () - from.radius ();
  Polar curve_begin
    { from.radius () + dist_factor * radial_dist, from.angle () };
  Polar curve_end
    { to.radius () - dist_factor * radial_dist, to.angle () };

  // Convert to Cartesian coordinates
  Cartesian from_c;
  Cartesian to_c;
  Cartesian curve_begin_c;
  Cartesian curve_end_c;
  m_coord_converter.convert (from, from_c);
  m_coord_converter.convert (to, to_c);
  m_coord_converter.convert (curve_begin, curve_begin_c);
  m_coord_converter.convert (curve_end, curve_end_c);

  // Line from start to the curve begin
  cairo_context->move_to (from_c.x (), from_c.y ());

  cairo_context->line_to (curve_begin_c.x (), curve_begin_c.y ());

  // Adjust angles so that their difference is lower than PI
  double begin_angle = curve_begin.angle ().value (), end_angle =
      curve_end.angle ().value ();
  double phi_diff_unadjusted = end_angle - begin_angle;
  if (phi_diff_unadjusted > M_PI)
    {
      begin_angle += 2 * M_PI;
    }
  else if (phi_diff_unadjusted < -M_PI)
    {
      end_angle += 2 * M_PI;
    }

  // Decide wether to draw one or to connector segments
  double phi_diff = end_angle - begin_angle;
  if (std::abs (phi_diff) > M_PI_2)
    {
      // Calculate coordinate between the curve begin and the curve end
      double mid_angle = (begin_angle + end_angle) / 2.0;
      double mid_radius = curve_begin.radius ()
	  + (curve_end.radius () - curve_begin.radius ()) / phi_diff
	      * (mid_angle - begin_angle);

      draw_connector_segment (curve_begin.radius (), begin_angle, mid_radius,
			      mid_angle, prop);
      draw_connector_segment (mid_radius, mid_angle, curve_end.radius (),
			      end_angle, prop);
    }
  else
    {
      draw_connector_segment (curve_begin.radius (), begin_angle,
			      curve_end.radius (), end_angle, prop);
    }

  // Line from the curve end to end
  cairo_context->line_to (to_c.x (), to_c.y ());

  // Set line style and apply drawing
  cairo_context->set_source_rgba (prop.line_color.r (), prop.line_color.g (),
				  prop.line_color.b (), prop.line_color.a ());
  cairo_context->set_line_width (prop.line_width);
  cairo_context->stroke ();
}

void
CairoDrawer::draw_segment_axis (
    double inner_radius, double thickness, const Angle& start, const Angle& end,
    const DrawerProperties<std::array<Color, 10>>& prop, Direction dir)
{
  cairo_context->set_identity_matrix ();

  // Only draw axis with ten segments
  const static std::size_t NUM_SPLITS = 10;

  // Calculate segment size
  double segment_size = angle_helper::rad_dist (start.value (), end.value ())
      / NUM_SPLITS;

  // Draw segments
  for (size_t i = 0; i < NUM_SPLITS; ++i)
    {
      DrawerProperties<> inner_prop (prop.line_width, prop.line_color,
				     prop.fill_color.at (i));
      draw_ring_segment (inner_radius, thickness, start + segment_size * i,
			 start + segment_size * (i + 1), inner_prop,
			 Direction::COUNTER_CLOCKWISE);
    }
}

void
CairoDrawer::draw_output_label (const Label& output_label, double radius_label,
				double radius_output, const Angle& begin,
				const Angle& end)
{
  cairo_context->set_identity_matrix ();
  cairo_context->begin_new_path ();

  draw_arc (radius_output, begin, end, Direction::CLOCKWISE);

  Cartesian tmp;
  m_coord_converter.convert (Polar (radius_output, end), tmp);
  Cartesian line_end (
      tmp.x (),
      tmp.y () - radius_label + radius_output - OUTPUT_LABEL_LINE_END_DELTA);

  cairo_context->line_to (line_end.x (), line_end.y ());
  cairo_context->line_to (m_coord_converter.get_center_x (), line_end.y ());

  cairo_context->set_line_width (
      Configuration::get_instance ().get_prop_thin ().line_width);
  cairo_context->stroke ();

  draw_text_orthogonal (output_label,
			Polar (radius_label, M_PI_2 + 3 * ANGLE_DELTA_SMALL),
			TextAlignment::LEFT);
}

void
CairoDrawer::draw_arrow (const Polar& start, const DrawerProperties<>& prop)
{
  cairo_context->set_identity_matrix ();
  cairo_context->begin_new_path ();

  // Only draw arrows with height of 5
  double height = CONNECTOR_ARROW_HEIGHT;

  // Calculate arrow coordinates
  Polar start_help (start.radius () - height, start.angle ()), direction_help (
      start.radius () - height / 2, start.angle ()), left_help (
      start.radius () - height, start.angle () - height / 500), right_help (
      start.radius () - height, start.angle () + height / 500);

  // Convert arrow coordinates into Cartesian coordinates
  Cartesian start_c, direction_c, left, right;
  m_coord_converter.convert (start_help, start_c);
  m_coord_converter.convert (direction_help, direction_c);
  m_coord_converter.convert (left_help, left);
  m_coord_converter.convert (right_help, right);

  // Calculate head coordinate h = p + height * (d - p) / ||d-p||
  double p_x = start_c.x (), p_y = start_c.y (), d_x = direction_c.x (), d_y =
      direction_c.y ();
  double diff_len = std::sqrt (
      std::pow (d_x - p_x, 2) + std::pow (d_y - p_y, 2));
  Cartesian head (p_x + height * (d_x - p_x) / diff_len,
		  p_y + height * (d_y - p_y) / diff_len);

  // Draw path and apply after setting line and fill style
  cairo_context->move_to (head.x (), head.y ());
  cairo_context->line_to (right.x (), right.y ());
  cairo_context->line_to (left.x (), left.y ());
  cairo_context->set_source_rgba (prop.line_color.r (), prop.line_color.g (),
				  prop.line_color.b (), 1);
  cairo_context->set_line_width (IO_LINE_WIDTH);
  cairo_context->fill_preserve ();
  cairo_context->stroke ();
}

void
CairoDrawer::draw_coord_point (const Polar& coord, const Angle& width,
			       double height, const DrawerProperties<>& prop)
{
  cairo_context->set_identity_matrix ();

  // Calculate the radius and the angles between the box should be drawn
  double inner_radius = coord.radius () - 0.5 * height;
  Angle begin = coord.angle () - width * 0.5;
  Angle end = coord.angle () + width * 0.5;

  // Draw segment
  draw_ring_segment (inner_radius, height, begin, end, prop,
		     Direction::COUNTER_CLOCKWISE);
}

void
CairoDrawer::draw_connector_segment (double begin_radius, double begin_angle,
				     double end_radius, double end_angle,
				     const DrawerProperties<> & prop)
{
  // Calculate the Cartesian coordinates of start and end
  Cartesian P0, P3;
  m_coord_converter.convert (Polar (begin_radius, begin_angle), P0);
  m_coord_converter.convert (Polar (end_radius, end_angle), P3);

  double phi_diff = end_angle - begin_angle, r_diff = end_radius - begin_radius;

  // Calculate the derivative vectors
  double P1_x, P1_y, P2_x, P2_y;
  if (std::abs (phi_diff) < DBL_MIN)
    {
      P1_x = 0;
      P1_y = 0;
      P2_x = 0;
      P2_y = 0;
    }
  else
    {
      P1_x = 1;
      P1_y = (begin_radius * std::cos (begin_angle)
	  + (r_diff / phi_diff) * std::sin (begin_angle))
	  / (begin_radius * std::sin (begin_angle)
	      - (r_diff / phi_diff) * std::cos (begin_angle));
      P2_x = 1;
      P2_y = (end_radius * std::cos (end_angle)
	  + (r_diff / phi_diff) * std::sin (end_angle))
	  / (end_radius * std::sin (end_angle)
	      - (r_diff / phi_diff) * std::cos (end_angle));

      double norm_p1 = std::sqrt (1 + std::pow (P1_y, 2)), norm_p3 = std::sqrt (
	  1 + std::pow (P2_y, 2));
      P1_x /= norm_p1;
      P1_y /= norm_p1;
      P2_x /= norm_p3;
      P2_y /= norm_p3;
    }

  // Factor to scale the derivative vector
  double k = 70 * std::abs (phi_diff);

  // Calculate in which direction the derivative vector should be added
  double phi_p1 = std::atan2 (
      -(P0.y () + k * P1_y - m_coord_converter.get_center_y ()),
      P0.x () + k * P1_x - m_coord_converter.get_center_x ());
  if (phi_p1 < 0)
    {
      phi_p1 += 2 * M_PI;
    }
  if (phi_p1 < begin_angle && phi_p1 < end_angle)
    {
      phi_p1 += 2 * M_PI;
    }

  double phi_p2 = std::atan2 (
      -(P3.y () + k * P2_y - m_coord_converter.get_center_y ()),
      P3.x () + k * P2_x - m_coord_converter.get_center_x ());
  if (phi_p2 < 0)
    {
      phi_p2 += 2 * M_PI;
    }
  if (phi_p2 < begin_angle && phi_p2 < end_angle)
    {
      phi_p2 += 2 * M_PI;
    }

  double sign_1 =
      (begin_angle < phi_p1 && end_angle > phi_p1)
	  || (begin_angle > phi_p1 && end_angle < phi_p1) ? 1 : -1;
  double sign_2 =
      (begin_angle < phi_p2 && end_angle > phi_p2)
	  || (begin_angle > phi_p2 && end_angle < phi_p2) ? 1 : -1;

  // Calculate the control points of the Bezier curve
  Cartesian P1 (P0.x () + k * P1_x * sign_1, P0.y () + k * P1_y * sign_1), P2 (
      P3.x () + k * P2_x * sign_2, P3.y () + k * P2_y * sign_2);

  cairo_context->curve_to (P1.x (), P1.y (), P2.x (), P2.y (), P3.x (),
			   P3.y ());
}

void
CairoDrawer::draw_ring_segment (double inner_radius, double thickness,
				const Angle& start, const Angle& end,
				const DrawerProperties<>& prop, Direction dir)
{
  cairo_context->set_identity_matrix ();
  cairo_context->begin_new_path ();

  // Draw first arc
  draw_arc (inner_radius, start, end, Direction::COUNTER_CLOCKWISE);

  // Draw second arc depending on first one
  draw_arc (
      inner_radius + thickness,
      start,
      end,
      dir == Direction::COUNTER_CLOCKWISE ?
	  Direction::CLOCKWISE : Direction::COUNTER_CLOCKWISE);

  cairo_context->close_path ();

  // Set line and fill color and apply drawing
  cairo_context->set_source_rgba (prop.fill_color.r (), prop.fill_color.g (),
				  prop.fill_color.b (), prop.fill_color.a ());
  cairo_context->fill_preserve ();
  cairo_context->set_source_rgba (prop.line_color.r (), prop.line_color.g (),
				  prop.line_color.b (), prop.line_color.a ());
  cairo_context->set_line_width (prop.line_width);
  cairo_context->stroke ();
}

void
CairoDrawer::draw_arc (double radius, const Angle& start, const Angle& end,
		       Direction dir)
{
  cairo_context->set_identity_matrix ();

  // Draw arc begin->end or end->begin depending on direction
  switch (dir)
    {
    case Direction::COUNTER_CLOCKWISE:
      cairo_context->arc (m_coord_converter.get_center_x (),
			  m_coord_converter.get_center_y (), radius,
			  get_cairo_angle (end).value (),
			  get_cairo_angle (start).value ());
      break;
    case Direction::CLOCKWISE:
      cairo_context->arc_negative (m_coord_converter.get_center_x (),
				   m_coord_converter.get_center_y (), radius,
				   get_cairo_angle (start).value (),
				   get_cairo_angle (end).value ());
      break;
    }
}

void
CairoDrawer::draw_line (const Polar& from, const Polar& to,
			const DrawerProperties<>& prop)
{
  cairo_context->set_identity_matrix ();
  cairo_context->begin_new_path ();

  // Convert to Cartesian coordinates
  Cartesian from_c, to_c;
  m_coord_converter.convert (from, from_c);
  m_coord_converter.convert (to, to_c);

  // Draw path and apply after setting line style
  cairo_context->move_to (from_c.x (), from_c.y ());
  cairo_context->line_to (to_c.x (), to_c.y ());
  cairo_context->set_source_rgba (prop.line_color.r (), prop.line_color.g (),
				  prop.line_color.b (), prop.line_color.a ());
  cairo_context->set_line_width (prop.line_width);
  cairo_context->stroke ();

}

void
CairoDrawer::draw_text_parallel (const Label& label, const Polar& start,
				 const TextAlignment& alignment)
{
  cairo_context->set_identity_matrix ();

  // Set font style
  set_font_face (label);

  // Calculate the width and height of the textbox
  const Cairo::TextExtents & t_exts = get_text_extents (label);

  // Calculate cairo angle
  Angle cairo_angle = M_PI_2 - start.angle ().value ();

  // Set cairo user-space origin and rotation
  cairo_context->begin_new_path ();
  cairo_context->translate (m_coord_converter.get_center_x (),
			    m_coord_converter.get_center_y ());
  cairo_context->rotate (cairo_angle.value ());
  cairo_context->translate (0, -start.radius ());
  if (start.angle ().value () > M_PI_2 && start.angle ().value () < 3 * M_PI_2)
    cairo_context->rotate_degrees (90);
  else
    cairo_context->rotate_degrees (270);
  cairo_context->translate (-alignment.ratio * t_exts.width,
			    0.5 * t_exts.height);

  cairo_context->close_path ();
  cairo_context->show_text (label.get_text ());
}

void
CairoDrawer::draw_text_orthogonal (const Label& label, const Polar& start,
				   const TextAlignment & alignment)
{
  cairo_context->set_identity_matrix ();

  // Set font style
  set_font_face (label);

  // Calculate the width and height of the textbox
  Cairo::TextExtents t_exts = get_text_extents (label);

  // Create cairo angle
  Angle cairo_angle = M_PI_2 - start.angle ().value ();

  // Set cairo user-space origin and rotation
  cairo_context->begin_new_path ();
  cairo_context->translate (m_coord_converter.get_center_x (),
			    m_coord_converter.get_center_y ());
  cairo_context->rotate (cairo_angle.value ());
  cairo_context->translate (0, -start.radius ());
  cairo_context->translate (-alignment.ratio * t_exts.width,
			    (1 - alignment.ratio) * t_exts.height);

  cairo_context->close_path ();
  cairo_context->show_text (label.get_text ());
}

void
CairoDrawer::set_font_face (const Label& label)
{
  const TextProperties & prop = label.get_properties ();

  // Set font styles
  Cairo::RefPtr<Cairo::ToyFontFace> font = Cairo::ToyFontFace::create (
      prop.font_name,
      prop.italic ? Cairo::FONT_SLANT_ITALIC : Cairo::FONT_SLANT_NORMAL,
      prop.bold ? Cairo::FONT_WEIGHT_BOLD : Cairo::FONT_WEIGHT_NORMAL);
  cairo_context->set_font_face (font);
  cairo_context->set_font_size (label.get_properties ().font_size);
  cairo_context->set_source_rgba (prop.color.r (), prop.color.g (),
				  prop.color.b (), prop.color.a ());
}

Cairo::TextExtents
CairoDrawer::get_text_extents (const Label& label) const
{
  // Calculate the width and height of the textbox
  Cairo::TextExtents t_exts;
  std::string message
    { label.get_text () };
  cairo_context->get_text_extents (message, t_exts);

  return t_exts;
}

void
CairoDrawer::set_surface (const std::string& fpath, int width, int height)
{
  Cairo::RefPtr<Cairo::Surface> ptr = Cairo::SvgSurface::create (fpath,
								       width,
								       height);
  cairo_context = Cairo::Context::create (ptr);
}
