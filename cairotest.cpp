/* M_PI is defined in math.h in the case of Microsoft Visual C++, Solaris,
 * et. al.
 */
#if defined(_MSC_VER)
#define _USE_MATH_DEFINES
#endif

#include <string>
#include <iostream>
#include <array>
#include "cairommconfig.h"
#include "cairomm/context.h"
#include "cairomm/surface.h"

#include <cmath>
#include <sstream>

#include "Scene.h"
#include "PolarCartesian.h"
#include "Mapper.h"
#include "Drawer.h"
#include "DrawerProperties.h"
#include "Config.h"
#include "MooViEArgs.h"

int cairo_test_01(void)
{
	std::string filename = "/home/stratmann/MooViE/image.svg";
	double width = 800;
	double height = 800;
	//	Cairo::RefPtr<Cairo::SvgSurface> surface = Cairo::SvgSurface::create(
	//			filename, width, height);
	//
	//	Cairo::RefPtr<Cairo::Context> cr = Cairo::Context::create(surface);

	Drawer drawer(filename, width, height);

	Polar origin1(180, angle_helper::deg_to_rad(168.0));
	Polar origin2(180, angle_helper::deg_to_rad(167.0));
	for (ssize_t i = -16; i < 19; ++i) {
		Polar target1(180, angle_helper::deg_to_rad(-10.0 * i - 5.0));
		Polar target2(180, angle_helper::deg_to_rad(-10.0 * i));
		Link link(origin1, origin2, target1, target2);

		Color strokeColor(102, 194, 165, 255);
		Color fillColor(strokeColor.r(), strokeColor.g(), strokeColor.b(), 0.5);

		DrawerProperties<> prop(0.5, strokeColor, fillColor);

		drawer.drawLink(link, prop);
	}

	DrawerProperties<std::array<Color, 10>> properteis(1, Color::BLACK,
			Color::GLOW_10);

	drawer.drawSplitAxis(200, 20, Angle(angle_helper::deg_to_rad(-80.0)),
			Angle(angle_helper::deg_to_rad(80.0)), properteis,
			Drawer::Direction::INCREASING);

	//	cr->set_line_width(2.0);
	//	cr->set_source_rgba(black.r(), black.g(), black.b(), black.a());
	//	for (size_t i = 1; i < 180; i += 2)
	//	{
	//
	//		drawer.drawArc(200, Angle(double(2*i)/360.0 * CIRCLE), Angle(double(2*i+1.5)/360.0 * CIRCLE),Drawer::Direction::INCREASING);
	//		cr->stroke();
	//		drawer.drawArc(210, Angle(double(2*i)/360.0 * CIRCLE), Angle(double(2*i-1.5)/360.0 * CIRCLE),Drawer::Direction::DECREASING);
	//		cr->stroke();
	//	}

	DrawerProperties<> prop1 { 1, Color::BLACK, Color::SET3.at(2, 0) };
	DrawerProperties<> prop2 { 1, Color::BLACK, Color::SET3.at(2, 1) };
	DrawerProperties<> prop3 { 1, Color::BLACK, Color::SET3.at(2, 2) };

	Ticks tick(10, 10, std::make_pair(0.0, 100.0),
			TextProperties("Liberation Serif", 8), "%");
	TextProperties label_prop("Liberation Serif", 20);

	drawer.drawAxis(180, 20, Angle(angle_helper::deg_to_rad(-93.0)),
			Angle(angle_helper::deg_to_rad(-149.0)), prop1,
			Drawer::Direction::DECREASING, tick, Label("var1", label_prop));
	drawer.drawAxis(180, 20, Angle(angle_helper::deg_to_rad(-152.0)),
			Angle(angle_helper::deg_to_rad(152.0)), prop2,
			Drawer::Direction::DECREASING, tick, Label("var2", label_prop));
	drawer.drawAxis(180, 20, Angle(angle_helper::deg_to_rad(149.0)),
			Angle(angle_helper::deg_to_rad(93.0)), prop3,
			Drawer::Direction::DECREASING, tick, Label("var3", label_prop));

	double min_radius = 220;
	double max_radius = 375;

	DrawerProperties<> thin_line { 0.5, Color::BLACK, Color::BLACK };
	DrawerProperties<> thick_line { 1, Color::BLACK, Color::BLACK };

	drawer.drawCoordGrid(Polar(min_radius, angle_helper::deg_to_rad(-80.0)),
			Polar(max_radius, angle_helper::deg_to_rad(80.0)),
			Drawer::Direction::INCREASING, 2, thin_line, thick_line);
	//grids at r=282 and r=344

	DrawerProperties<> prop4 { 1, Color::GLOW_10[3],
			Color::GLOW_10[3].set_alpha(100) };
	drawer.drawCoordPoint(Polar(282, angle_helper::deg_to_rad(-20.0)),
			angle_helper::deg_to_rad(4), 10, prop4);

	Polar start(282, angle_helper::deg_to_rad(-20));
	Polar end(344, angle_helper::deg_to_rad(20));
	drawer.drawConnector(start, end, prop4);

	srand(1000);
	for (size_t i = 0; i < 100; ++i) {
		double f1 = double(rand()) / RAND_MAX;
		double f2 = double(rand()) / RAND_MAX;
		double angle1 = -80.0 + f1 * 160;
		double angle2 = -80.0 + f2 * 160;

		drawer.drawConnector(
				Polar(282, Angle(angle_helper::deg_to_rad(angle1))),
				Polar(375, Angle(angle_helper::deg_to_rad(angle2))), prop4);

	}

	drawer.finish();
	return 0;
}

int cairo_test_02(int argc, char const * argv[])
{
	try
	{
		const MooViEArgs & args = MooViEArgs::parse_from_commandline(argc,
				argv);

		/** TODO: implement CSV parser */
		std::vector<Var> ivars = { Var(0, 100, "Usage of production capacity") };
		std::vector<Var> ovars = { Var(0, 1000000, "Total production"), Var(0,
				500, "Employees needed"), Var(-10000, 10000000, "Profit") };

		Drawer drawer(args.output_file(), args.width(), args.height());
		Scene mainScene(drawer, ivars, ovars);

		return 0;
	} catch (MooViEArgs::ParseException & e)
	{
		std::cout << e.what() << std::endl;
		return 1;
	}
}


int main(int argc, char const * argv[])
{
#ifdef CAIRO_HAS_SVG_SURFACE
	return cairo_test_02(argc, argv);
#else
	std::cout << "You must compile cairo with SVG support for this example to work." << std::endl;
	return 1;

#endif
}

//const TextProperties config::TICK_LABEL = TextProperties("Liberation Serif", 8);
//const TextProperties config::VAR_LABEL = TextProperties("Liberation Serif", 20);


