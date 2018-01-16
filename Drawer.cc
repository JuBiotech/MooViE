/*
 * Drawer.cc
 *
 *  Created on: 05.07.2017
 *      Author: beyss
 */

#include "Drawer.h"
#include <iostream>
#include <cmath>

Drawer::Drawer(const Configuration & config)
: _config(config), _pc(config.get_width(), config.get_height())
{
	const Cairo::RefPtr<Cairo::Surface>& ptr = Cairo::SvgSurface::create(config.get_output_file(), config.get_width(), config.get_height());
	_cr = Cairo::Context::create(ptr);
}

void Drawer::draw_coord_grid(const CoordGrid & grid, const DrawerProperties<> & prop_thick,
		const DrawerProperties<> & prop_thin)
{
	draw_split_axis(grid.radius, config::INPUT_THICKNESS, grid.start, grid.end, DrawerProperties<std::array<Color, 10>>(1, Color::BLACK,
			Color::GLOW_10), grid.dir);
	_cr->set_identity_matrix();
	double min_radius = grid.radius + config::INPUT_THICKNESS;
	double max_radius = grid.radius + config::INPUT_THICKNESS + grid.height;

	double span = angle_helper::rad_dist(grid.start.get(), grid.end.get());

	std::size_t NUM_SEGMENTS = grid.major_ticks * grid.minor_ticks;
	std::size_t THICK_LINES = grid.major_ticks;

	for (size_t i = 0; i <= NUM_SEGMENTS; ++i)
	{
		Angle a((grid.start.get() + i * span / NUM_SEGMENTS));
		if (i % THICK_LINES)
			draw_line(Polar(min_radius, a), Polar(max_radius, a), prop_thin);
		else
			draw_line(Polar(min_radius, a), Polar(max_radius, a), prop_thick);
	}

	double y_dist = grid.height / (grid.outputs - 0.5);

	for (size_t i = 1; i < grid.outputs; ++i)
	{
		// Changed max_angle <-> min_angle. Whether fix or not depends on meaning of dir
		draw_arc(min_radius + i * y_dist, grid.start, grid.end, grid.dir);
		_cr->set_source_rgba(prop_thin.line_color.r(),
				prop_thin.line_color.g(), prop_thin.line_color.b(),
				prop_thin.line_color.a());
		_cr->set_line_width(prop_thin.line_width);
		_cr->stroke();
	}
}

void Drawer::draw_var_axis(const VarAxis & axis)
{
	_cr->set_identity_matrix();
	draw_torus_segment(axis.radius, axis.height, axis.start, axis.end, axis.prop, Direction::INCREASING);

	Angle span = axis.end - axis.start;

	double start_radius = axis.radius + axis.height;
	double end_radius_major = start_radius + 0.25 * axis.height;
	double end_radius_minor = start_radius + 0.125 * axis.height;
	double radius_tick_label = end_radius_major + 0.75 * axis.height;
	double radius_label = end_radius_major + 3 * axis.height;

	std::vector<Label> tick_label = axis.ticks.label();
	size_t label_pos = 0;

	size_t num_segments = axis.ticks.ticksmajor() * axis.ticks.ticksminor();

	TextProperties text_prop("Liberation Serif", 12);

	for (size_t i = 0; i <= num_segments; ++i)
	{
		Angle a((axis.start + span * (double(i) / double(num_segments))));
		if (i % axis.ticks.ticksmajor())
			draw_line(Polar(start_radius, a), Polar(end_radius_minor, a),
					axis.prop.half_line_width());
		else
		{
			draw_line(Polar(start_radius, a), Polar(end_radius_major, a), axis.prop);
			draw_text_parallel(tick_label.at(label_pos), Polar(radius_tick_label, a));
			++label_pos;
		}
	}

	draw_text_orthogonal(axis.label, Polar(radius_label, Angle::center(axis.start, axis.end)));
}

void Drawer::draw_data_link(const DataLink & link)
{
	Polar from = link.connector_coord();
	// Subtract INPUT_THICKNESS to not draw into SplitAxis
	Polar target1(from.r(), from.phi() - 0.001),
			target2(from.r(), from.phi() + 0.001); // TODO: Subtract other values (from configuration?)

	Polar origin1(link.input_coords()[0].r(), link.input_coords()[0].phi() - 0.0001),
					origin2(link.input_coords()[0].r(), link.input_coords()[0].phi() + 0.0001);
	std::size_t i = 0;
	// Draw links
	for (Polar in: link.input_coords())
	{
		Polar origin1(in.r() - 2, in.phi() - 0.0001),
				origin2(in.r() - 2, in.phi() + 0.0001); // TODO: Subtract other values (from configuration?)
		draw_link(origin1, origin2, target1, target2, link.get_link_prop(i++));
	}

	// draw line from connector to first input
	Polar mod;
	draw_connector(from, link.output_coords()[0], link.connector_prop());
	from = link.output_coords()[0];
	if (link.output_coords().size() > 1)
	{
		const Polar & to = link.output_coords()[1];
		mod = Util::get_connector_end(from, to);
		draw_connector(from, mod, link.connector_prop());
		from = to;
		draw_coord_point(from, 0.005, (to.r() - mod.r()) * 2, link.connector_prop());
	}
	// Draw connector point on coord grid
	for (size_t i = 2; i < link.output_coords().size(); ++i)
	{
		const Polar out = link.output_coords()[i];
		mod = Util::get_connector_end(from, out);
		draw_connector(Util::get_connector_start(from, out), mod, link.connector_prop());
		from = out;
		draw_coord_point(from, 0.005, (out.r() - mod.r()) * 2, link.connector_prop());
	}
}

void Drawer::draw_link(const Polar & origin1, const Polar & origin2,
		const Polar & target1, const Polar & target2,
		const DrawerProperties<>& prop)
{
	_cr->set_identity_matrix();
	Cartesian orig1, orig2, targ1, targ2;
	_pc.convert(origin1, orig1);
	_pc.convert(origin2, orig2);
	_pc.convert(target1, targ1);
	_pc.convert(target2, targ2);

	Cartesian origin1_c = createLinkControlPoint(origin1);
	Cartesian origin2_c = createLinkControlPoint(origin2);
	Cartesian target1_c = createLinkControlPoint(target1);
	Cartesian target2_c = createLinkControlPoint(target2);

	_cr->begin_new_path();

	//move to initial point
	_cr->move_to(orig1.x(), orig1.y());
	//bezier curve from origin1 to target1
	_cr->curve_to(origin1_c.x(), origin1_c.y(), target1_c.x(), target1_c.y(),
			targ1.x(), targ1.y());
	_cr->curve_to(target2_c.x(), target2_c.y(), origin2_c.x(), origin2_c.y(),
			orig2.x(), orig2.y());

	_cr->set_source_rgba(prop.fill_color.r(), prop.fill_color.g(),
			prop.fill_color.b(), prop.fill_color.a());
	_cr->fill_preserve();

	_cr->set_source_rgba(prop.fill_color.r(), prop.fill_color.g(),
			prop.fill_color.b(), prop.fill_color.a());
	_cr->set_line_width(prop.line_width);
	_cr->stroke(); //draw outline, but preserve path
}

void Drawer::draw_connector(const Polar& from, const Polar& to,
		const DrawerProperties<>& prop)
{
	const double p1 = 0.2;
	const double p2 = 0.2;
	const double p3 = 0.6;

	double radial_dist = to.r() - from.r();
	Polar intermediate1 {from.r() + p1 * radial_dist,from.phi() };
	Polar intermediate2 {to.r() - p2 * radial_dist, to.phi() };

	Cartesian real_from_c;
	Cartesian real_to_c;
	Cartesian intermediate1_c;
	Cartesian intermediate2_c;

	_pc.convert(from, real_from_c);
	_pc.convert(to, real_to_c);
	_pc.convert(intermediate1, intermediate1_c);
	_pc.convert(intermediate2, intermediate2_c);

	_cr->set_identity_matrix();
	_cr->begin_new_path();
	_cr->move_to(real_from_c.x(), real_from_c.y());
	_cr->line_to(intermediate1_c.x(), intermediate1_c.y());

	//TODO: nicer bezier solution!
	double r_diff = radial_dist * p3;
	double d0 = angle_helper::rad_dist(from.phi().get(), to.phi().get()), d1 = angle_helper::rad_dist(to.phi().get(), from.phi().get());
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


	_cr->line_to(intermediate2_c.x(), intermediate2_c.y());
	_cr->line_to(real_to_c.x(), real_to_c.y());

	_cr->set_source_rgba(prop.line_color.r(), prop.line_color.g(), prop.line_color.b(),
			prop.line_color.a());
	_cr->set_line_width(prop.line_width);

	_cr->stroke();
}

void Drawer::draw_arc(double radius, const Angle& start, const Angle& end,
		Direction dir)
{
	_cr->set_identity_matrix();
	switch (dir)
	{
	case Direction::INCREASING:
		_cr->arc(_pc.center().x(), _pc.center().y(), radius, start.get(),
				end.get());
		break;
	case Direction::DECREASING:
		_cr->arc_negative(_pc.center().x(), _pc.center().y(), radius,
				start.get(), end.get());
		break;
	}
}

void Drawer::draw_split_axis(double inner_radius, double thickness,
		const Angle& begin, const Angle& end,
		const DrawerProperties<std::array<Color, 10>>& prop, Direction dir)
{
	_cr->set_identity_matrix();
	size_t num_of_splits = 10;
	Angle segment_size = angle_helper::rad_dist(begin.get(), end.get()) / num_of_splits;
	for (size_t i = 0; i < num_of_splits; ++i)
	{
		DrawerProperties<> inner_prop(prop.line_width, prop.line_color, prop.fill_color.at(i));
		draw_torus_segment(inner_radius, thickness, begin + segment_size * i,
				begin + segment_size * (i + 1), inner_prop, dir);
	}
}

void Drawer::draw_line(const Polar& from, const Polar& to,
		const DrawerProperties<>& prop)
{
	_cr->set_identity_matrix();
	_cr->begin_new_path();
	Cartesian from_c, to_c;
	_pc.convert(from, from_c);
	_pc.convert(to, to_c);
	_cr->move_to(from_c.x(), from_c.y());
	_cr->line_to(to_c.x(), to_c.y());
	_cr->set_source_rgba(prop.line_color.r(), prop.line_color.g(),
			prop.line_color.b(), prop.line_color.a());
	_cr->set_line_width(prop.line_width);
	_cr->stroke();

}

void Drawer::draw_text_orthogonal(const Label& label, const Polar& start)
{
	_cr->set_identity_matrix();
	Cairo::RefPtr<Cairo::ToyFontFace> font = Cairo::ToyFontFace::create(
			label.prop().fontname(),
			label.prop().italic() ? Cairo::FONT_SLANT_ITALIC : Cairo::FONT_SLANT_NORMAL,
					label.prop().bold() ? Cairo::FONT_WEIGHT_BOLD : Cairo::FONT_WEIGHT_NORMAL);
	_cr->set_font_face(font);
	_cr->set_font_size(label.prop().fontsize());
	_cr->set_source_rgba(label.prop().color().r(), label.prop().color().g(), label.prop().color().b(),
			label.prop().color().a());

	Cairo::TextExtents t_exts;
	std::string message { label.text() };
	_cr->get_text_extents(message, t_exts);

	Angle cairo_angle = M_PI_2 - start.phi();

	_cr->set_identity_matrix();
	_cr->begin_new_path();
	_cr->translate(_pc.center().x(), _pc.center().y());
	_cr->rotate(cairo_angle.get());
	_cr->translate(0, -start.r());
	if (start.phi().get() > M_PI)
		_cr->rotate_degrees(180);
	_cr->translate(-0.5 * t_exts.width, 0.5 * t_exts.height);

	_cr->show_text(message);
}

void Drawer::draw_coord_point(const Polar& coord, const Angle& width,
		double height, const DrawerProperties<>& prop)
{
	_cr->set_identity_matrix();
	double inner_radius = coord.r() - 0.5 * height;
	Angle begin = coord.phi() - width * 0.5;
	Angle end = coord.phi() + width * 0.5;
	draw_torus_segment(inner_radius, height, begin, end, prop,
			Direction::INCREASING);
}

void Drawer::draw_torus_segment(double inner_radius, double thickness,
		const Angle& begin, const Angle& end, const DrawerProperties<>& prop,
		Direction dir)
{
	_cr->set_identity_matrix();
	_cr->begin_new_path();

	const Angle beginn = 2 * M_PI - end;
	const Angle endn = 2 * M_PI - begin;

	draw_arc(inner_radius, beginn, endn, dir);
	switch (dir)
	{
	case Direction::INCREASING:
		draw_arc(inner_radius + thickness, endn, beginn, Direction::DECREASING);
		break;
	case Direction::DECREASING:
		draw_arc(inner_radius + thickness, endn, beginn, Direction::INCREASING);
		break;
	}

	_cr->close_path();

	_cr->set_source_rgba(prop.fill_color.r(), prop.fill_color.g(),
			prop.fill_color.b(), prop.fill_color.a());
	_cr->fill_preserve(); //fill, but preserve path

	_cr->set_source_rgba(prop.line_color.r(), prop.line_color.g(),
			prop.line_color.b(), prop.line_color.a());
	_cr->set_line_width(prop.line_width);
	_cr->stroke();
}

void Drawer::draw_text_parallel(const Label& label, const Polar& start)
{
	_cr->set_identity_matrix();
	Cairo::RefPtr<Cairo::ToyFontFace> font = Cairo::ToyFontFace::create(
			label.prop().fontname(),
			label.prop().italic() ? Cairo::FONT_SLANT_ITALIC : Cairo::FONT_SLANT_NORMAL,
					label.prop().bold() ? Cairo::FONT_WEIGHT_BOLD : Cairo::FONT_WEIGHT_NORMAL);
	_cr->set_font_face(font);
	_cr->set_font_size(label.prop().fontsize());
	_cr->set_source_rgba(label.prop().color().r(), label.prop().color().g(), label.prop().color().b(),
			label.prop().color().a());

	Cairo::TextExtents t_exts;
	std::string message { label.text() };
	_cr->get_text_extents(message, t_exts);

	Angle cairo_angle = M_PI_2 - start.phi();

	_cr->set_identity_matrix();
	_cr->begin_new_path();
	_cr->translate(_pc.center().x(), _pc.center().y());
	_cr->rotate(cairo_angle.get());
	_cr->translate(0, -start.r());
	_cr->rotate_degrees(90);
	if ((M_PI_2 - start.phi()).get() > 0)
		_cr->rotate_degrees(180);
	_cr->translate(-0.5 * t_exts.width, 0.5 * t_exts.height);

	_cr->show_text(message);
}

void Drawer::finish()
{
	_cr->save(); // save the state of the context
	_cr->show_page();
}

Cartesian Drawer::createLinkControlPoint(const Polar& point)
{
	Polar p_control { point };
	Cartesian c_control;
	p_control.r() -= _linkControlStrength;
	_pc.convert(p_control, c_control);
	return c_control;
}
