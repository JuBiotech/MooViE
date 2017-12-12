/*
 * Drawer.cc
 *
 *  Created on: 05.07.2017
 *      Author: beyss
 */

#include "Drawer.h"
#include <iostream>

void Drawer::draw_coord_grid(const CoordGrid & grid, double radius,
		const DrawerProperties<> & prop_thick, const DrawerProperties<> & prop_thin)
{
	_cr->set_identity_matrix();
	double min_radius = radius;
	double max_radius = radius + grid.height;

	Angle span = grid.end - grid.start;

	static const size_t NUM_SEGMENTS = 100;
	static const size_t THICK_LINES = 10;

	for (size_t i = 0; i <= NUM_SEGMENTS; ++i)
	{
		Angle a((grid.start.get() + i * span.get() / NUM_SEGMENTS));
		if (i % THICK_LINES)
			drawLine(Polar(min_radius, a), Polar(max_radius, a), prop_thin);
		else
			drawLine(Polar(min_radius, a), Polar(max_radius, a), prop_thick);
	}

	double y_dist = (max_radius - min_radius) / (grid.outputs + 0.5);

	for (size_t i = 1; i <= grid.outputs; ++i)
	{
		// Changed max_angle <-> min_angle. Whether fix or not depends on meaning of dir
		drawArc(min_radius + i * y_dist, grid.end, grid.start, grid.dir);
		_cr->set_source_rgba(prop_thin.lineColor().r(),
				prop_thin.lineColor().g(), prop_thin.lineColor().b(),
				prop_thin.lineColor().a());
		_cr->set_line_width(prop_thin.lineWidth());
		_cr->stroke();
	}
}

void Drawer::draw_var_axis(const VarAxis & axis, double radius,
		const DrawerProperties<std::array<Color, 10>> & prop_var)
{
	_cr->set_identity_matrix();
	size_t num_of_splits = 10;
	Angle segment_size = (axis.start - axis.end) / num_of_splits;
	for (size_t i = 0; i < num_of_splits; ++i)
	{
		DrawerProperties<> inner_prop(prop_var.lineWidth(), prop_var.lineColor(),
				prop_var.fillColor().at(i));
		drawWegdeSegment(radius, axis.height, axis.start + segment_size * i,
				axis.start + segment_size * (i + 1), inner_prop, Direction::INCREASING);
	}
}

void Drawer::draw_data_link(const DataLink & link, const CoordGrid & grid,
		double radius, const DrawerProperties<> & prop_link)
{
	Polar from = link.connector_coord();
	Polar target1(radius, from.phi() - 0.5),
			target2(radius, from.phi() + 0.5); // TODO: Subtract other values
	// Draw links
	for (Polar in: link.input_coords())
	{
		Polar origin1(radius, in.phi() - 0.5),
				origin2(radius, in.phi() + 0.5); // TODO: Subtract other values
		draw_link(origin1, origin2, target1, target2, prop_link);
	}

	// Draw connector on coord grid
	for (Polar out: link.output_coords())
	{
		drawConnector(from, out, prop_link);
		from = out;
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
	//circle segment from target1 to target2
	drawArc(target1.r(), target1.phi(), target2.phi(),
			Direction::INCREASING);
	//bezier curve from target2 back to origin2
	_cr->curve_to(target2_c.x(), target2_c.y(), origin2_c.x(), origin2_c.y(),
			orig2.x(), orig2.y());
	//circle segment from origin2 to origin1
	drawArc(origin1.r(), origin2.phi(), origin1.phi(),
			Direction::INCREASING);

	_cr->set_source_rgba(prop.fillColor().r(), prop.fillColor().g(),
			prop.fillColor().b(), prop.fillColor().a());
	_cr->fill_preserve();

	_cr->set_source_rgba(prop.lineColor().r(), prop.lineColor().g(),
			prop.lineColor().b(), prop.lineColor().a());
	_cr->set_line_width(prop.lineWidth());
	_cr->stroke(); //draw outline, but preserve path
}

void Drawer::drawLink(const Link& link, const DrawerProperties<>& prop)
{
	_cr->set_identity_matrix();
	Cartesian origin1, origin2, target1, target2;
	_pc.convert(link.origin1(), origin1);
	_pc.convert(link.origin2(), origin2);
	_pc.convert(link.target1(), target1);
	_pc.convert(link.target2(), target2);

	Cartesian origin1_c = createLinkControlPoint(link.origin1());
	Cartesian origin2_c = createLinkControlPoint(link.origin2());
	Cartesian target1_c = createLinkControlPoint(link.target1());
	Cartesian target2_c = createLinkControlPoint(link.target2());

	_cr->begin_new_path();

	//move to initial point
	_cr->move_to(origin1.x(), origin1.y());
	//bezier curve from origin1 to target1
	_cr->curve_to(origin1_c.x(), origin1_c.y(), target1_c.x(), target1_c.y(),
			target1.x(), target1.y());
	//circle segment from target1 to target2
	drawArc(link.target1().r(), link.target1().phi(), link.target2().phi(),
			Direction::INCREASING);
	//bezier curve from target2 back to origin2
	_cr->curve_to(target2_c.x(), target2_c.y(), origin2_c.x(), origin2_c.y(),
			origin2.x(), origin2.y());
	//circle segment from origin2 to origin1
	drawArc(link.origin1().r(), link.origin2().phi(), link.origin1().phi(),
			Direction::INCREASING);

	_cr->set_source_rgba(prop.fillColor().r(), prop.fillColor().g(),
			prop.fillColor().b(), prop.fillColor().a());
	_cr->fill_preserve();

	_cr->set_source_rgba(prop.lineColor().r(), prop.lineColor().g(),
			prop.lineColor().b(), prop.lineColor().a());
	_cr->set_line_width(prop.lineWidth());
	_cr->stroke(); //draw outline, but preserve path
}

void Drawer::drawArc(double radius, const Angle& start, const Angle& end,
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

void Drawer::drawSplitAxis(double inner_radius, double thickness,
		const Angle& begin, const Angle& end,
		const DrawerProperties<std::array<Color, 10>>& prop, Direction dir)
{
	_cr->set_identity_matrix();
	size_t num_of_splits = 10;
	Angle segment_size = (end - begin) / num_of_splits;
	for (size_t i = 0; i < num_of_splits; ++i)
	{
		DrawerProperties<> inner_prop(prop.lineWidth(), prop.lineColor(), prop.fillColor().at(i));
		drawWegdeSegment(inner_radius, thickness, begin + segment_size * i,
				begin + segment_size * (i + 1), inner_prop, dir);
	}
}

void Drawer::drawLine(const Polar& from, const Polar& to,
		const DrawerProperties<>& prop)
{
	_cr->set_identity_matrix();
	_cr->begin_new_path();
	Cartesian from_c, to_c;
	_pc.convert(from, from_c);
	_pc.convert(to, to_c);
	_cr->move_to(from_c.x(), from_c.y());
	_cr->line_to(to_c.x(), to_c.y());
	_cr->set_source_rgba(prop.lineColor().r(), prop.lineColor().g(),
			prop.lineColor().b(), prop.lineColor().a());
	_cr->set_line_width(prop.lineWidth());
	_cr->stroke();

}

void Drawer::drawCoordGrid(const Polar& lower_left, const Polar& upper_right,
		Direction dir, size_t ys, const DrawerProperties<>& prop_thin,
		const DrawerProperties<>& prop_thick)
{
	_cr->set_identity_matrix();
	double min_radius = lower_left.r();
	double max_radius = upper_right.r();

	Angle min_angle = lower_left.phi();
	Angle max_angle = upper_right.phi();

	Angle span = max_angle - min_angle;

	// warum nach Direction abfragen?
	/**
	if ((max_angle < min_angle && dir == Direction::DECREASING)
			|| (min_angle > max_angle && dir == Direction::INCREASING))
	{
		span = min_angle - max_angle;
	}
	*/

	static const size_t NUM_SEGMENTS = 100;
	static const size_t THICK_LINES = 10;

	for (size_t i = 0; i <= NUM_SEGMENTS; ++i)
	{
		Angle a((min_angle.get() + i * span.get() / NUM_SEGMENTS));
		if (i % THICK_LINES)
			drawLine(Polar(min_radius, a), Polar(max_radius, a), prop_thin);
		else
			drawLine(Polar(min_radius, a), Polar(max_radius, a), prop_thick);
	}

	double y_dist = (max_radius - min_radius) / (ys + 0.5);

	for (size_t i = 1; i <= ys; ++i)
	{
		// Changed max_angle <-> min_angle. Whether fix or not depends on meaning of dir
		drawArc(min_radius + i * y_dist, max_angle, min_angle, dir);
		_cr->set_source_rgba(prop_thin.lineColor().r(),
				prop_thin.lineColor().g(), prop_thin.lineColor().b(),
				prop_thin.lineColor().a());
		_cr->set_line_width(prop_thin.lineWidth());
		_cr->stroke();
	}
}

void Drawer::drawTextOrthogonal(const Label& label, const Polar& start)
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

	Angle cairo_angle = start.phi() + M_PI_2;

	_cr->set_identity_matrix();
	_cr->begin_new_path();
	_cr->translate(_pc.center().x(), _pc.center().y());
	_cr->rotate(cairo_angle.get());
	_cr->translate(0, -start.r());
	if (start.phi().get() > 0)
		_cr->rotate_degrees(180);
	_cr->translate(-0.5 * t_exts.width, 0.5 * t_exts.height);

	_cr->show_text(message);
}

void Drawer::drawCoordPoint(const Polar& coord, const Angle& width,
		double height, const DrawerProperties<>& prop)
{
	_cr->set_identity_matrix();
	double inner_radius = coord.r() - 0.5 * height;
	Angle begin = coord.phi() - width * 0.5;
	Angle end = coord.phi() + width * 0.5;
	drawWegdeSegment(inner_radius, height, begin, end, prop,
			Direction::INCREASING);
}

void Drawer::drawWegdeSegment(double inner_radius, double thickness,
		const Angle& begin, const Angle& end, const DrawerProperties<>& prop,
		Direction dir)
{
	_cr->set_identity_matrix();
	_cr->begin_new_path();

	drawArc(inner_radius, begin, end, dir);
	switch (dir)
	{
	case Direction::INCREASING:
		drawArc(inner_radius + thickness, end, begin, Direction::DECREASING);
		break;
	case Direction::DECREASING:
		drawArc(inner_radius + thickness, end, begin, Direction::INCREASING);
		break;
	}

	_cr->close_path();

	_cr->set_source_rgba(prop.fillColor().r(), prop.fillColor().g(),
			prop.fillColor().b(), prop.fillColor().a());
	_cr->fill_preserve(); //fill, but preserve path

	_cr->set_source_rgba(prop.lineColor().r(), prop.lineColor().g(),
			prop.lineColor().b(), prop.lineColor().a());
	_cr->set_line_width(prop.lineWidth());
	_cr->stroke();
}

void Drawer::drawTextParallel(const Label& label, const Polar& start)
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

	Angle cairo_angle = start.phi() + M_PI_2;

	_cr->set_identity_matrix();
	_cr->begin_new_path();
	_cr->translate(_pc.center().x(), _pc.center().y());
	_cr->rotate(cairo_angle.get());
	_cr->translate(0, -start.r());
	_cr->rotate_degrees(90);
	if ((start.phi() + M_PI_2).get() > 0)
		_cr->rotate_degrees(180);
	_cr->translate(-0.5 * t_exts.width, 0.5 * t_exts.height);

	_cr->show_text(message);
}

void Drawer::drawConnector(const Polar& from, const Polar& to,
		const DrawerProperties<>& prop)
{
	const double p1 = 0.1;
	const double p2 = 0.1;
	const double p3 = 0.6;
	const double p4 = 0.1;
	const double p5 = 0.1;

	double radial_dist = to.r() - from.r();
	Polar real_from {from.r() + p1 * radial_dist, from.phi()};
	Polar real_to {to.r() - p5 * radial_dist, to.phi()};
	Polar intermediate1 {real_from.r() + p2 * radial_dist, real_from.phi() };
	Polar intermediate2 {real_to.r() - p4 * radial_dist, real_to.phi() };


	Cartesian real_from_c;
	Cartesian real_to_c;
	Cartesian intermediate1_c;
	Cartesian intermediate2_c;

	_pc.convert(real_from, real_from_c);
	_pc.convert(real_to, real_to_c);
	_pc.convert(intermediate1, intermediate1_c);
	_pc.convert(intermediate2, intermediate2_c);

	_cr->set_identity_matrix();
	_cr->begin_new_path();
	_cr->move_to(real_from_c.x(), real_from_c.y());
	_cr->line_to(intermediate1_c.x(), intermediate1_c.y());

	//TODO: nicer bezier solution!
	double r_diff = radial_dist * p3;
	double phi_diff = (to.phi() - from.phi()).get();
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

	_cr->set_source_rgba(prop.lineColor().r(), prop.lineColor().g(), prop.lineColor().b(),
			prop.lineColor().a());
	_cr->set_line_width(prop.lineWidth());

	_cr->stroke();
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

void Drawer::drawAxis(double inner_radius, double thickness, const Angle& begin,
		const Angle& end, const DrawerProperties<>& prop, Direction dir, const Ticks& ticks, const Label& label)
{
	_cr->set_identity_matrix();
	drawWegdeSegment(inner_radius, thickness, begin, end, prop, dir);


	Angle span = end - begin;
	std::cout << "Begin: " << begin << " End: " << end << " Span: " << span << std::endl;

	if ((end < begin && dir == Direction::DECREASING)
			|| (begin > end && dir == Direction::INCREASING))
	{
		span = end - begin;
	}


	double start_radius = inner_radius + thickness;
	double end_radius_major = start_radius + 0.25 * thickness;
	double end_radius_mimor = start_radius + 0.125 * thickness;
	double radius_tick_label = end_radius_major + 0.25 * thickness;
	double radius_label = end_radius_major + 1 * thickness;

	std::vector<Label> tick_label = ticks.label();
	size_t label_pos = 0;

	size_t num_segments = ticks.ticksmajor() * ticks.ticksminor();

	TextProperties text_prop("Liberation Serif",12);

	for (size_t i = 0; i <= num_segments; ++i)
	{
		Angle a((begin + span * (double(i) / double(num_segments))));
		if (i % ticks.ticksmajor())
			drawLine(Polar(start_radius, a), Polar(end_radius_mimor, a), prop.halfLineWidth());
		else
		{
			drawLine(Polar(start_radius, a), Polar(end_radius_major, a), prop);
			drawTextParallel(tick_label.at(label_pos),Polar(radius_tick_label, a));
			++label_pos;
		}
	}

	drawTextOrthogonal(label, Polar(radius_label, Angle::center(begin,end)));


}
