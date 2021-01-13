/* M_PI is defined in math.h in the case of Microsoft Visual C++, Solaris,
 * et. al.
 */

#include <string>
#include <iostream>
#include "lib/Scene.h"
#include "lib/Configuration.h"
#include <CmdLine.h>

using namespace TCLAP;

// Runs the MooViE application from command line arguments
int
run_moovie (int argc, const char * argv[])
{
  CmdLine cmd (
      "MooViE is a tool to display multi-dimensional data (R^n -> R^m) using a "
      "clear circular chart.\n");

  UnlabeledValueArg<std::string> input ("input", "path to the input file", true,
					"", "string");
  cmd.add (input);

  ValueArg<int> width ("x", "width", "width of the resulting svg", false, 0,
		       "positive integer");
  cmd.add (width);

  ValueArg<int> height ("y", "height", "height of the resulting svg", false, 0,
			"positive integer");
  cmd.add (height);

  ValueArg<std::string> output ("o", "output-file", "path to the output file",
				false, "", "string");
  cmd.add (output);

  ValueArg<std::string> config ("c", "configuration-file",
				"path to a moovie config file", false, "",
				"string");
  cmd.add (config);

  if (input.getValue ().empty ())
    {
      try
	{
	  cmd.parse (argc, argv);

	  if (not config.getValue ().empty ())
	    {
	      Configuration::initialize (input.getValue (), config.getValue ());
	    }
	  else
	    {
	      Configuration::initialize (input.getValue ());
	    }

	  Configuration& conf = Configuration::get_instance ();

	  if (width.getValue () != 0)
	    conf.set_width (width.getValue ());
	  if (height.getValue () != 0)
	    conf.set_height (height.getValue ());
	  if (not output.getValue ().empty ())
	    conf.set_output_file (output.getValue ());

	  Scene main;
	}
      catch (const std::exception& e)
	{
	  std::cout << "MooViE execution failed: " << e.what () << std::endl;
	  return EXIT_FAILURE;
	}
    }

  return EXIT_SUCCESS;
}

int
main (int argc, char const * argv[])
{
#ifdef CAIRO_HAS_SVG_SURFACE
  return run_moovie (argc, argv);
#else
  std::cout << "You must compile cairo with SVG support for MooViE to work." << std::endl;
  return 1;
#endif
}


