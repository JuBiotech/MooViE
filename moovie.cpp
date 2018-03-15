
/* M_PI is defined in math.h in the case of Microsoft Visual C++, Solaris,
 * et. al.
 */
#if defined(_MSC_VER)
#define _USE_MATH_DEFINES
#endif

#include <string>
#include <iostream>
#include "Scene.h"
#include "Args.h"
#include "Configuration.h"
#include <chrono>

// Runs the MooViE application from command line arguments
int run_moovie(int argc, const char * argv[])
{
	std::chrono::time_point<std::chrono::system_clock> start, end;
	start = std::chrono::system_clock::now();
	try
	{
		const Args & args = Args::parse(argc, argv);

		if (args.help())
		{
			std::cout << Args::HELP_STRING << std::endl;
		}
		else if (args.has_config_file())
		{
			Configuration::initialize(
			    args.get_input_file(),
			    args.get_config_file()
			);
			if (args.has_output_file())
			  Configuration::get_instance().set_output_file(args.get_output_file());
			Scene main;
		}
		else
		{
			Configuration::initialize(args.get_input_file());
			Scene main;
		}
		end = std::chrono::system_clock::now();
		std::cout << std::chrono::duration_cast<std::chrono::microseconds>(end -start).count() << std::endl;
		return EXIT_SUCCESS;
	} catch (ParseException & e)
	{
		std::cout << e.what() << std::endl;
		return EXIT_FAILURE;
	}
}

int main(int argc, char const * argv[])
{
#ifdef CAIRO_HAS_SVG_SURFACE
	return run_moovie(argc, argv);
#else
	std::cout << "You must compile cairo with SVG support for this example to work." << std::endl;
	return 1;
#endif
}


