
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
#include <fstream>

#include "Scene.h"
#include "PolarCartesian.h"
#include "Mapper.h"
#include "Drawer.h"
#include "DrawerProperties.h"
#include "Config.h"
#include "Args.h"
#include "Utils.h"
#include "Configuration.h"

int Args_test(int argc, char const * argv[])
{
	try
	{
		const Args & args =
				Args::parse_from_commandline(argc, argv);

		if (args.help())
			std::cout << Args::HELP_STRING << std::endl;
		else
			std::cout << "Given MooViE arguments:" << std::endl <<
			"Width: " << args.width() << ", Height: " << args.height() << std::endl <<
			"Inputs: " << args.inputs() << std::endl <<
			"Output file: " << args.output_file() << ", input file: " << args.input_file() << std::endl <<
			"Input file format: " << args.file_type() << std::endl;
		return 0;
	} catch (ParseException & e)
	{
		std::cout << e.what() << std::endl;
		return 1;
	}
}

int DefDataSet_test(void)
{
	DefDataSet set = DefDataSet::parse_from_csv(Util::read_file("/home/stratmann/MooViE/testfiles/input.csv"), 3);

	for (DefDataSet::Var var : set.input_variables())
	{
		std::cout << var.name << ": min(" << var.min << "), max(" << var.max << ")" << std::endl;
	}
	for (DefDataSet::Var var : set.output_variables())
	{
		std::cout << var.name << ": min(" << var.min << "), max(" << var.max << ")" << std::endl;
	}
	std::cout << "Values: " << std::endl;
	for (DefDataRow row : set)
	{
		for (DefCell cell : row)
		{
			std::cout << cell.value << ", ";
		}
		std::cout << std::endl;
	}

	return 0;
}

int Scene_test(void)
{
	Configuration config("/home/stratmann/MooViE/testfiles/input.csv", 3);
	config.set_output_file("/home/stratmann/MooViE/image.svg");
	Scene mainScene(config);

	return 0;
}

int Configuration_test(void)
{
	Configuration conf("/home/stratmann/MooViE/testfiles/input.csv", 3, "/home/stratmann/MooViE/testfiles/moovie.conf");

	std::cout << "fname: " << conf.get_input_file() << std::endl
			<< "output file: " << conf.get_output_file() << std::endl
			<< "width: " << conf.get_width() << std::endl
			<< "height: " << conf.get_width() << std::endl
			<< "input inner radius: " << conf.get_input_inner_radius() << std::endl
			<< "output thickness: " << conf.get_input_thickness() << std::endl
			<< "output inner radius: " << conf.get_output_inner_radius() << std::endl
			<< "output thickness: " << conf.get_output_thickness() << std::endl
			<< "grid size: " << conf.get_grid_size() << std::endl;

	return 0;
}

int All_test(int argc, const char * argv[])
{
	try
	{
		const Args & args = Args::parse_from_commandline(argc, argv);

		if (args.help())
		{
			std::cout << Args::HELP_STRING << std::endl;
		}
		else if (args.has_config_file())
		{
			Configuration config(args.input_file(), args.inputs(), args.config_file());
			if (args.has_output_file())
				config.set_output_file(args.output_file());
			Scene main(config);
		}
		else
		{
			Configuration config(args.input_file(), args.inputs());
			Scene main(config);
		}
		return 0;
	} catch (ParseException & e)
	{
		std::cout << e.what() << std::endl;
		return 1;
	}
}

int main(int argc, char const * argv[])
{
#ifdef CAIRO_HAS_SVG_SURFACE
	return All_test(argc, argv);
#else
	std::cout << "You must compile cairo with SVG support for this example to work." << std::endl;
	return 1;
#endif
}


