/*
 * Drawer.cc
 *
 *  Created on: 05.07.2017
 *      Author: beyss
 */

#include "Drawer.h"
#include <iostream>
#include <cmath>

Drawer::Drawer(const std::string & fpath, int width, int height)
: _pc(width, height)
{
	const Cairo::RefPtr<Cairo::Surface> & ptr = Cairo::SvgSurface::create(fpath, width, height);
	_cr = Cairo::Context::create(ptr);
}

void Drawer::draw_coord_grid(const CoordGrid & grid)
{
	_cr->set_identity_matrix();

	// Draw ring with colored segments which are used to color and distinguish the connectors
	draw_segment_axis(
			grid.get_radius(), Configuration::get_instance().get_input_thickness(),
			grid.get_start(), grid.get_end(),
			DrawerProperties<std::array<Color, 10>>(1, Color::BLACK, Color::GLOW_10),
			grid.get_direction()
			);

	// Calculate the inner and outer radius of the CoordGrid
	double min_radius = grid.get_radius() + Configuration::get_instance().get_input_thickness();
	double max_radius = grid.get_radius() + Configuration::get_instance().get_input_thickness() + grid.get_height();

	// Radian distance (absolute!) between start and end angle
	double span = angle_helper::rad_dist(grid.get_start().get(), grid.get_end().get());

	// Calculate how the CoordGrid is separated into thin and thick lines (ticks)
	const std::size_t NUM_SEGMENTS = grid.get_major_ticks() * grid.get_minor_ticks();
	const std::size_t NUM_THICK_LINES = grid.get_major_ticks();

	// Draw the ticks of the CoordGrid
	for (size_t i = 0; i <= NUM_SEGMENTS; ++i)
	{
		Angle a((grid.get_start().get() + i * span / NUM_SEGMENTS));
		if (i % NUM_THICK_LINES)
			draw_line(
					Polar(min_radius, a),
					Polar(max_radius, a),
					Configuration::get_instance().get_prop_thin()
			);
		else
			draw_line(
					Polar(min_radius, a),
					Polar(max_radius, a),
					Configuration::get_instance().get_prop_thick()
			);
	}

	// Adjusted difference between the radial lines of the CoordGrid (outputs)
	double y_dist = grid.get_height() / (grid.get_num_outputs() - Configuration::COORDGRID_ADJUSTMENT);

	// Draw the description of the first output
	draw_text_parallel(
	    Label(grid.get_var(0).name, Configuration::get_instance().get_tick_label()),
	    Polar(min_radius, 0)
	);
	draw_text_orthogonal(
	    Label(std::to_string(grid.get_var(0).max), Configuration::get_instance().get_tick_label()),
	    Polar(min_radius, grid.get_start() - Configuration::TEXT_DELTA)
	    );
	draw_text_orthogonal(
	    Label(std::to_string(grid.get_var(0).min), Configuration::get_instance().get_tick_label()),
	    Polar(min_radius, grid.get_end() + Configuration::TEXT_DELTA)
	    );

	// Draw the output lines of the CoordGrid
	for (size_t i = 1; i < grid.get_num_outputs(); ++i)
	{
		// Draw the description of the i-th output
		draw_text_parallel(
		    Label(grid.get_var(i).name, Configuration::get_instance().get_tick_label()),
		    Polar(min_radius + i * y_dist, 0)
		    );
		draw_text_orthogonal(
		    Label(std::to_string(grid.get_var(i).max), Configuration::get_instance().get_tick_label()),
		    Polar(min_radius + i * y_dist, grid.get_start() - Configuration::TEXT_DELTA)
		    );
		draw_text_orthogonal(
		    Label(std::to_string(grid.get_var(i).min), Configuration::get_instance().get_tick_label()),
		    Polar(min_radius + i * y_dist, grid.get_end() + Configuration::TEXT_DELTA)
		    );

		_cr->begin_new_path();
		draw_arc(min_radius + i * y_dist, grid.get_start(), grid.get_end(), Direction::INCREASING);
		_cr->set_source_rgba(
			Configuration::get_instance().get_prop_thin().line_color.r(),
			Configuration::get_instance().get_prop_thin().line_color.g(),
			Configuration::get_instance().get_prop_thin().line_color.b(),
			Configuration::get_instance().get_prop_thin().line_color.a()
		    );
		_cr->set_line_width(Configuration::get_instance().get_prop_thin().line_width);
		_cr->stroke();
	}
}

void Drawer::draw_var_axis(const VarAxis & axis)
{
	_cr->set_identity_matrix();

	// Draw the base of the VarAxis: a filled ring segment
	draw_ring_segment(
	    axis.get_radius(), axis.get_height(),
	    axis.get_start(), axis.get_end(),
	    axis.get_prop(),
	    Direction::INCREASING
	    );

	// Radian distance (absolute!) between start and end angle
	double span = angle_helper::rad_dist(axis.get_start().get(), axis.get_end().get());

	// TODO: Calculate using predefined constants
	// Calculate radii for ticks and labels
	double start_radius = axis.get_radius() + axis.get_height();
	double end_radius_major = start_radius + 0.25 * axis.get_height();
	double end_radius_minor = start_radius + 0.125 * axis.get_height();
	double radius_tick_label = end_radius_major + 0.75 * axis.get_height();
	double radius_label = end_radius_major + 3 * axis.get_height();
	double radius_histogram = radius_label + 10;

	// Tick values as strings
	std::vector<Label> tick_labels = axis.get_ticks().get_labels();
	std::size_t label_pos = 0;

	// Calculate how the VarAxis' ticks is separated into thin and thick lines (ticks)
	const std::size_t NUM_SEGMENTS = axis.get_ticks().get_major_ticks() * axis.get_ticks().get_minor_ticks();
	const std::size_t NUM_THICK_LINES = axis.get_ticks().get_major_ticks();

	// Draw the ticks and the associated values
	for (size_t i = 0; i <= NUM_SEGMENTS; ++i)
	{
		Angle a((axis.get_start() + span * (double(i) / double(NUM_SEGMENTS))));
		if (i % NUM_THICK_LINES)
		{
			draw_line(
			    Polar(start_radius, a),
			    Polar(end_radius_minor, a),
			    axis.get_prop().half_line_width()
			    );
		}
		else
		{
			const Label & tick_label = tick_labels[label_pos++];
			draw_line(Polar(start_radius, a), Polar(end_radius_major, a), axis.get_prop());

			double dep_distance = (tick_label.text().length() / 2)
					* tick_label.prop().fontsize() * Configuration::RADIAL_TEXT_FACTOR;

			draw_text_parallel(
			    tick_label,
			    Polar(radius_tick_label + dep_distance, a)
			);
		}
	}

	// TODO: Adjust VarAxis label radius
	// Draw the name of the Variable
	draw_text_orthogonal(
	    axis.get_label(),
	    Polar(radius_label, Angle::center(axis.get_start(), axis.get_end()))
	    );

	draw_histogram(axis.get_histogram(), radius_histogram, axis.get_start(), axis.get_end());
}

void Drawer::draw_data_link(const DataLink & link)
{
	// Calculate target from connector coordinate
	Polar from = link.get_connector_coord();
	Polar target1(from.r() - 5, from.phi() - Configuration::ANGLE_DELTA_SMALL),
			target2(from.r() - 5, from.phi() + Configuration::ANGLE_DELTA_SMALL);

	// Draw links
	std::size_t i = 0;
	for (Polar in: link.get_input_coords())
	{
		Polar origin1(in.r() - 10, in.phi() - Configuration::ANGLE_DELTA_SMALL),
				origin2(in.r() - 10, in.phi() + Configuration::ANGLE_DELTA_SMALL);
		draw_link(origin1, origin2, target1, target2, link.get_link_prop(i++));
	}

	// Draw line from connector to first output
	Polar mod;
	draw_connector(from, link.get_output_coords()[0], link.get_connector_prop());
	draw_arrow(from, link.get_connector_prop());
	from = link.get_output_coords()[0];
	if (link.get_output_coords().size() > 1)
	{
		const Polar & to = link.get_output_coords()[1];
		mod = Util::get_connector_end(from, to);
		draw_connector(from, mod, link.get_connector_prop());
		from = to;
		draw_coord_point(from, 0.005, (to.r() - mod.r()) * 2, link.get_connector_prop());
	}

	// Draw connector on CoordGrid
	for (size_t i = 2; i < link.get_output_coords().size(); ++i)
	{
		const Polar out = link.get_output_coords()[i];
		mod = Util::get_connector_end(from, out);
		draw_connector(Util::get_connector_start(from, out), mod, link.get_connector_prop());
		from = out;
		draw_coord_point(from, 0.005, (out.r() - mod.r()) * 2, link.get_connector_prop());
	}
}

void Drawer::draw_histogram(const VarAxis::Histogram & histogram,
			double radius, const Angle & start, const Angle & end)
{
	_cr->set_identity_matrix();

	DrawerProperties<> histogram_background(0.1, Color(0,0,0,0.1), Color(0,0,0,0.1)),
	    histogram_lines(0.1, Color(0,0,0,0.3), Color(0,0,0,0.3));
	// TODO: use configuration values

	// Draw background
	draw_ring_segment(
	    radius,
	    20,
	    start, end,
	    histogram_background,
	    Direction::INCREASING
	);

	// Draw thin lines for histogram background
	for (std::size_t i = 1; i < 6; ++i)
	{
	    _cr->begin_new_path();
	    draw_arc(
	    		radius + 20 * (i / 6.),
				start, end,
				Direction::INCREASING
	    );
	    _cr->set_source_rgba(
	    		histogram_lines.line_color.r(),
				histogram_lines.line_color.g(),
				histogram_lines.line_color.b(),
				histogram_lines.line_color.a()
	    );
	    _cr->set_line_width(histogram_lines.line_width);
	    _cr->stroke();
	}

	// Draw the histogram graph
	_cr->begin_new_path();
	double span = angle_helper::rad_dist(start.get(), end.get());
	for (std::size_t i = 0; i < histogram.get_num_intervals(); ++i)
	{
	    draw_arc(
		radius + 20 * histogram.get_section_frequency(i),
		start + (span / histogram.get_num_intervals()) * i,
		start + (span / histogram.get_num_intervals()) * (i + 1),
		Direction::DECREASING
	    );
	}
	_cr->set_source_rgb(0,0,0);
	_cr->set_line_width(0.5);
	_cr->stroke();
}

void Drawer::draw_link(const Polar & origin1, const Polar & origin2,
		const Polar & target1, const Polar & target2,
		const DrawerProperties<>& prop)
{
	_cr->set_identity_matrix();

	// Convert given Polar to Cartesian coordinates
	Cartesian origin1_c, origin2_c, target1_c, target2_c;
	_pc.convert(origin1, origin1_c);
	_pc.convert(origin2, origin2_c);
	_pc.convert(target1, target1_c);
	_pc.convert(target2, target2_c);

	// Calculate control points for Bezier curve
	Cartesian CTRL_ORIG1 = create_control_point(origin1);
	Cartesian CTRL_ORIG2 = create_control_point(origin2);
	Cartesian CTRL_TARG1 = create_control_point(target1);
	Cartesian CTRL_TARG2 = create_control_point(target2);

	_cr->begin_new_path();
	_cr->move_to(origin1_c.x(), origin1_c.y());

	// Draw first Bezier curve from origin to target
	_cr->curve_to(CTRL_ORIG1.x(), CTRL_ORIG1.y(), CTRL_TARG1.x(), CTRL_TARG1.y(),
			target1_c.x(), target1_c.y());
	// Draw second Bezier curve from target to origin
	_cr->curve_to(CTRL_TARG2.x(), CTRL_TARG2.y(), CTRL_ORIG2.x(), CTRL_ORIG2.y(),
			origin2_c.x(), origin2_c.y());

	// Set line and fill style and apply drawing
	_cr->set_source_rgba(prop.fill_color.r(), prop.fill_color.g(),
			prop.fill_color.b(), prop.fill_color.a());
	_cr->fill_preserve();
	_cr->set_source_rgba(prop.fill_color.r(), prop.fill_color.g(),
			prop.fill_color.b(), prop.fill_color.a());
	_cr->set_line_width(prop.line_width);
	_cr->stroke();
}

void Drawer::draw_connector(const Polar & from, const Polar & to,
		const DrawerProperties<> & prop)
{
	_cr->set_identity_matrix();
  	_cr->begin_new_path();

	// Only use 0.2 as distance factor
	const static double dist_factor = 0.2;

	// Calculate to intermediate coordinates to draw the arc from
	double radial_dist = to.r() - from.r();
	Polar intermediate1 {from.r() + dist_factor * radial_dist, from.phi() };
	Polar intermediate2 {to.r() - dist_factor * radial_dist, to.phi() };

	// Convert to Cartesian coordinates
	Cartesian real_from_c;
	Cartesian real_to_c;
	Cartesian intermediate1_c;
	Cartesian intermediate2_c;
	_pc.convert(from, real_from_c);
	_pc.convert(to, real_to_c);
	_pc.convert(intermediate1, intermediate1_c);
	_pc.convert(intermediate2, intermediate2_c);

	// Line from start to first intermediate
	_cr->move_to(real_from_c.x(), real_from_c.y());
	_cr->line_to(intermediate1_c.x(), intermediate1_c.y());


	// Draw arc by approximating circle segments linearly:
	//TODO: nicer bezier solution!
	double r_diff = radial_dist * 0.6;
	double d0 = angle_helper::rad_dist(from.phi().get(), to.phi().get()),
	    d1 = angle_helper::rad_dist(to.phi().get(), from.phi().get());
	double phi_diff = d0 <= d1 ? d0 : -d1;

	size_t steps = 10;

	for (size_t i = 0; i < steps - 1; ++i)
	{
		double r = intermediate1.r() + i * r_diff / steps;
		double phi = intermediate1.phi().get() + i * phi_diff / steps;
		Polar next(r,phi);
		Cartesian next_c;
		_pc.convert(next,next_c);
		_cr->line_to(next_c.x(), next_c.y());
	}

	// Line to second intermediate to from there to end
	_cr->line_to(intermediate2_c.x(), intermediate2_c.y());
	_cr->line_to(real_to_c.x(), real_to_c.y());

	// Set line style and apply drawing
	_cr->set_source_rgba(prop.line_color.r(), prop.line_color.g(), prop.line_color.b(),
			prop.line_color.a());
	_cr->set_line_width(prop.line_width);
	_cr->stroke();
}

void Drawer::draw_segment_axis(double inner_radius, double thickness,
		const Angle & begin, const Angle & end,
		const DrawerProperties<std::array<Color, 10>> & prop, Direction dir)
{
	_cr->set_identity_matrix();

	// Only draw axis with ten segments
	const static std::size_t NUM_SPLITS = 10;

	// Calculate segment size
	double segment_size = angle_helper::rad_dist(begin.get(), end.get()) / NUM_SPLITS;

	// Draw segments
	for (size_t i = 0; i < NUM_SPLITS; ++i)
	{
		DrawerProperties<> inner_prop(prop.line_width, prop.line_color, prop.fill_color.at(i));
		draw_ring_segment(inner_radius, thickness, begin + segment_size * i,
				begin + segment_size * (i + 1), inner_prop, dir);
	}
}

void Drawer::draw_coord_point(const Polar & coord, const Angle & width,
		double height, const DrawerProperties<> & prop)
{
	_cr->set_identity_matrix();

	// Calculate the radius and the angles between the box should be drawn
	double inner_radius = coord.r() - 0.5 * height;
	Angle begin = coord.phi() - width * 0.5;
	Angle end = coord.phi() + width * 0.5;

	// Draw segment
	draw_ring_segment(inner_radius, height, begin, end, prop, Direction::INCREASING);
}

void Drawer::draw_arc(double radius, const Angle & start, const Angle & end,
		Direction dir)
{
	_cr->set_identity_matrix();

	// Draw arc begin->end or end->begin depending on direction
	switch (dir)
	{
	case Direction::INCREASING:
		_cr->arc(
		    _pc.center().x(),
		    _pc.center().y(),
		    radius,
		    Util::get_cairo_angle(end).get(),
		    Util::get_cairo_angle(start).get()
		    );
		break;
	case Direction::DECREASING:
		_cr->arc_negative(
		    _pc.center().x(),
		    _pc.center().y(),
		    radius,
		    Util::get_cairo_angle(start).get(),
		    Util::get_cairo_angle(end).get()
		    );
		break;
	}
}

void Drawer::draw_ring_segment(double inner_radius, double thickness,
		const Angle & start, const Angle & end, const DrawerProperties<> & prop,
		Direction dir)
{
	_cr->set_identity_matrix();
	_cr->begin_new_path();

	// Draw first arc
	draw_arc(inner_radius, start, end, Direction::INCREASING);

	// Draw second arc depending on first one
	draw_arc(inner_radius + thickness, start, end,
		 dir == Direction::INCREASING ? Direction::DECREASING : Direction::INCREASING);

	_cr->close_path();

	// Set line and fill color and apply drawing
	_cr->set_source_rgba(prop.fill_color.r(), prop.fill_color.g(),
			prop.fill_color.b(), prop.fill_color.a());
	_cr->fill_preserve();
	_cr->set_source_rgba(prop.line_color.r(), prop.line_color.g(),
			prop.line_color.b(), prop.line_color.a());
	_cr->set_line_width(prop.line_width);
	_cr->stroke();
}

void Drawer::draw_arrow(const Polar & start, const DrawerProperties<> & prop)
{
	_cr->set_identity_matrix();
	_cr->begin_new_path();

	// Only draw arrows with height of 5
	const static double height = 5;

	// Calculate arrow coordinates
	Polar start_help(start.r() - height, start.phi()),
			direction_help(start.r() - height / 2, start.phi()),
			left_help(start.r() - height, start.phi() - height / 500),
			right_help(start.r() - height, start.phi() + height / 500);

	// Convert arrow coordinates into Cartesian coordinates
	Cartesian start_c, direction_c, left, right;
	_pc.convert(start_help, start_c);
	_pc.convert(direction_help, direction_c);
	_pc.convert(left_help, left);
	_pc.convert(right_help, right);

	// Calculate head coordinate h = p + height * (d - p) / ||d-p||
	double p_x = start_c.x(), p_y = start_c.y(), d_x = direction_c.x(), d_y = direction_c.y();
	double diff_len = std::sqrt(std::pow(d_x - p_x, 2) + std::pow(d_y - p_y, 2));
	Cartesian head(p_x + height * (d_x - p_x) / diff_len, p_y + height * (d_y - p_y) / diff_len);

	// Draw path and apply after setting line and fill style
	_cr->move_to(head.x(), head.y());
	_cr->line_to(right.x(), right.y());
	_cr->line_to(left.x(), left.y());
	_cr->set_source_rgba(prop.line_color.r(), prop.line_color.g(),
				prop.line_color.b(), prop.line_color.a());
	_cr->set_line_width(Configuration::DATA_LINK_LINE_WIDTH);
	_cr->fill_preserve();
	_cr->stroke();
}

void Drawer::draw_line(const Polar& from, const Polar& to,
		const DrawerProperties<>& prop)
{
	_cr->set_identity_matrix();
	_cr->begin_new_path();

	// Convert to Cartesian coordinates
	Cartesian from_c, to_c;
	_pc.convert(from, from_c);
	_pc.convert(to, to_c);

	// Draw path and apply after setting line style
	_cr->move_to(from_c.x(), from_c.y());
	_cr->line_to(to_c.x(), to_c.y());
	_cr->set_source_rgba(prop.line_color.r(), prop.line_color.g(),
			prop.line_color.b(), prop.line_color.a());
	_cr->set_line_width(prop.line_width);
	_cr->stroke();

}

void Drawer::draw_text_parallel(const Label& label, const Polar & start)
{
	_cr->set_identity_matrix();

	// Set font styles
	Cairo::RefPtr<Cairo::ToyFontFace> font = Cairo::ToyFontFace::create(
			label.prop().fontname(),
			label.prop().italic() ? Cairo::FONT_SLANT_ITALIC : Cairo::FONT_SLANT_NORMAL,
					label.prop().bold() ? Cairo::FONT_WEIGHT_BOLD : Cairo::FONT_WEIGHT_NORMAL);
	_cr->set_font_face(font);
	_cr->set_font_size(label.prop().fontsize());
	_cr->set_source_rgba(label.prop().color().r(), label.prop().color().g(), label.prop().color().b(),
			label.prop().color().a());

	// Create cairo label
	Cairo::TextExtents t_exts;
	std::string message { label.text() };
	_cr->get_text_extents(message, t_exts);

	// Calculate cairo angle
	Angle cairo_angle = M_PI_2 - start.phi();

	// Set cairo user-space origin and rotation
	_cr->begin_new_path();
	_cr->translate(_pc.center().x(), _pc.center().y());
	_cr->rotate(cairo_angle.get());
	_cr->translate(0, -start.r());
	if (start.phi().get() > M_PI_2 && start.phi().get() < 3 * M_PI_2)
	  _cr->rotate_degrees(90);
	else
	  _cr->rotate_degrees(270);
	_cr->translate(-0.5 * t_exts.width, 0.5 * t_exts.height);

	_cr->close_path();
	_cr->show_text(message);
}

void Drawer::draw_text_orthogonal(const Label & label, const Polar & start)
{
	_cr->set_identity_matrix();

	// Set font styles
	Cairo::RefPtr<Cairo::ToyFontFace> font = Cairo::ToyFontFace::create(
			label.prop().fontname(),
			label.prop().italic() ? Cairo::FONT_SLANT_ITALIC : Cairo::FONT_SLANT_NORMAL,
					label.prop().bold() ? Cairo::FONT_WEIGHT_BOLD : Cairo::FONT_WEIGHT_NORMAL);
	_cr->set_font_face(font);
	_cr->set_font_size(label.prop().fontsize());
	_cr->set_source_rgba(label.prop().color().r(), label.prop().color().g(), label.prop().color().b(),
			label.prop().color().a());

	// Create cairo label
	Cairo::TextExtents t_exts;
	std::string message { label.text() };
	_cr->get_text_extents(message, t_exts);

	// Create cairo angle
	Angle cairo_angle = M_PI_2 - start.phi();

	// Set cairo user-space origin and rotation
	_cr->begin_new_path();
	_cr->translate(_pc.center().x(), _pc.center().y());
	_cr->rotate(cairo_angle.get());
	_cr->translate(0, -start.r());
	_cr->translate(-0.5 * t_exts.width, 0.5 * t_exts.height);

	_cr->close_path();
	_cr->show_text(message);
}

void Drawer::finish()
{
	// Save the state of the context
	_cr->save();
	_cr->show_page();
}

Cartesian Drawer::create_control_point(const Polar & point)
{
	Polar control(point);
	control.r() -= _link_control_strength;

	Cartesian control_c;
	_pc.convert(control, control_c);

	return control_c;
}
