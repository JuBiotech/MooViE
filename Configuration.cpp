/*
 * Configuration.cpp
 *
 *  Created on: 16.01.2018
 *      Author: stratmann
 */

#include "Configuration.h"

Configuration::Configuration(const std::string & fpath)
: mooviec_int("moovie\\.\\w+=\\d+"),
  mooviec_dbl("moovie\\.\\w+=(\\d+(\\.\\d+)?|\\.\\d+)"),
  mooviec_name("moovie\\.\\w+=[a-zA-Z ]+")
{
	std::string content = Util::read_file(fpath);

	for (std::string line: Util::split(content, "\n"))
	{
		if (line.find_first_not_of(' ') != line.npos
				&& line[line.find_first_not_of(' ')] != '#')
		{
			std::string stripped_line = Util::strip(line);

			if (std::regex_match(stripped_line, mooviec_int))
			{
				const std::vector<std::string> & definition = Util::split(stripped_line, "=");

				if (definition[0].compare("moovie.width") == 0)
				{
					width = std::stoi(definition[1]);
				}
				else if (definition[0].compare("moovie.height") == 0)
				{
					height = std::stoi(definition[1]);
				}
			}
			else if (std::regex_match(stripped_line, mooviec_dbl))
			{
				const std::vector<std::string> & definition = Util::split(stripped_line, "=");

				if (definition[0].compare("moovie.input_inner_radius") == 0)
				{
					input_inner_radius = std::stod(definition[1]);
				}
				else if (definition[0].compare("moovie.input_thickness") == 0)
				{
					input_thickness = std::stod(definition[1]);
				}
				else if (definition[0].compare("moovie.output_inner_radius") == 0)
				{
					output_inner_radius = std::stod(definition[1]);
				}
				else if (definition[0].compare("moovie.output_thickness") == 0)
				{
					output_thickness = std::stod(definition[1]);
				}
				else if (definition[0].compare("moovie.grid_size") == 0)
				{
					grid_size = std::stod(definition[1]);
				}
				else if (definition[0].compare("moovie.tick_label_font_size") == 0)
				{
					tick_label = TextProperties(tick_label.fontname(), std::stoi(definition[1]));
				}
				else if (definition[0].compare("moovie.var_label_font_size") == 0)
				{
					var_label = TextProperties(var_label.fontname(), std::stoi(definition[1]));
				}
				else if (definition[0].compare("moovie.thick_line") == 0)
				{
					prop_thick.line_width = std::stod(definition[1]);
				}
				else if (definition[0].compare("moovie.thick_line") == 0)
				{
					prop_thin.line_width = std::stod(definition[1]);
				}
			}
			else if (std::regex_match(stripped_line, mooviec_name))
			{
				const std::vector<std::string> & definition = Util::split(stripped_line, "=");
				if (definition[0].compare("moovie.tick_label_font") == 0)
				{
					tick_label = TextProperties(definition[1], tick_label.fontsize());
				}
				else if (definition[0].compare("moovie.var_label_font") == 0)
				{
					var_label = TextProperties(definition[1], var_label.fontsize());
				}
			}
		}
	}
}

