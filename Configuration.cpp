/*
 * Configuration.cpp
 *
 *  Created on: 16.01.2018
 *      Author: stratmann
 */

#include "Configuration.h"

const double Configuration::RADIAL_TEXT_FACTOR = 0.5;

const double Configuration::COORDGRID_ADJUSTMENT = 0.5;

const double Configuration::DATA_LINK_LINE_WIDTH = 0.1;

const double Configuration::CONNECTOR_DELTA = 10;
const double Configuration::TEXT_DELTA = 0.05;
const double Configuration::ANGLE_DELTA_SMALL = 0.001;
const double Configuration::ANGLE_DELTA_LARGE = 0.1;

std::shared_ptr<Configuration> Configuration::_instance;

void Configuration::initialize(const std::string & fname, std::size_t inputs, const std::string & cpath)
{
    _instance = std::shared_ptr<Configuration>(new Configuration(fname, inputs, cpath));
}

Configuration::Configuration()
: _num_inputs(0)
{}

Configuration::Configuration(const std::string & fname, std::size_t inputs, const std::string & cpath)
: _input_file(fname), _num_inputs(inputs),
  mooviec_int("moovie\\.\\w+=\\d+"),
  mooviec_dbl("moovie\\.\\w+=(\\d+(\\.\\d+)?|\\.\\d+)"),
  mooviec_name("moovie\\.\\w+=[a-zA-Z ]+")
{
	std::string content = Util::read_file(cpath);

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
					_width = Util::string_to_int(definition[1]);
				}
				else if (definition[0].compare("moovie.height") == 0)
				{
					_height = Util::string_to_int(definition[1]);
				}
				else if (definition[0].compare("moovie.input_inner_radius") == 0)
				{
					_input_inner_radius = Util::string_to_double(definition[1]);
				}
				else if (definition[0].compare("moovie.input_thickness") == 0)
				{
					_input_thickness = Util::string_to_double(definition[1]);
				}
				else if (definition[0].compare("moovie.output_angle_span") == 0)
				{
					_output_angle_span = Util::string_to_double(definition[1]);
				}
				else if (definition[0].compare("moovie.output_inner_radius") == 0)
				{
					_output_inner_radius = Util::string_to_double(definition[1]);
				}
				else if (definition[0].compare("moovie.output_thickness") == 0)
				{
					_output_thickness = Util::string_to_double(definition[1]);
				}
				else if (definition[0].compare("moovie.grid_size") == 0)
				{
					_grid_size = Util::string_to_double(definition[1]);
				}
				else if (definition[0].compare("moovie.tick_label_font_size") == 0)
				{
					_tick_label = TextProperties(_tick_label.fontname(), Util::string_to_double(definition[1]));
				}
				else if (definition[0].compare("moovie.var_label_font_size") == 0)
				{
					_var_label = TextProperties(_var_label.fontname(), Util::string_to_double(definition[1]));
				}
				else if (definition[0].compare("moovie.thick_line") == 0)
				{
					_prop_thick.line_width = Util::string_to_double(definition[1]);
				}
				else if (definition[0].compare("moovie.thick_line") == 0)
				{
					_prop_thin.line_width = Util::string_to_double(definition[1]);
				}
			}
			else if (std::regex_match(stripped_line, mooviec_dbl))
			{
				const std::vector<std::string> & definition = Util::split(stripped_line, "=");

				if (definition[0].compare("moovie.input_inner_radius") == 0)
				{
					_input_inner_radius = Util::string_to_double(definition[1]);
				}
				else if (definition[0].compare("moovie.input_thickness") == 0)
				{
					_input_thickness = Util::string_to_double(definition[1]);
				}
				else if (definition[0].compare("moovie.output_angle_span") == 0)
				{
					_output_angle_span = Util::string_to_double(definition[1]);
				}
				else if (definition[0].compare("moovie.output_inner_radius") == 0)
				{
					_output_inner_radius = Util::string_to_double(definition[1]);
				}
				else if (definition[0].compare("moovie.output_thickness") == 0)
				{
					_output_thickness = Util::string_to_double(definition[1]);
				}
				else if (definition[0].compare("moovie.grid_size") == 0)
				{
					_grid_size = Util::string_to_double(definition[1]);
				}
				else if (definition[0].compare("moovie.tick_label_font_size") == 0)
				{
					_tick_label = TextProperties(_tick_label.fontname(), Util::string_to_double(definition[1]));
				}
				else if (definition[0].compare("moovie.var_label_font_size") == 0)
				{
					_var_label = TextProperties(_var_label.fontname(), Util::string_to_double(definition[1]));
				}
				else if (definition[0].compare("moovie.thick_line") == 0)
				{
					_prop_thick.line_width = Util::string_to_double(definition[1]);
				}
				else if (definition[0].compare("moovie.thick_line") == 0)
				{
					_prop_thin.line_width = Util::string_to_double(definition[1]);
				}
			}
			else if (std::regex_match(stripped_line, mooviec_name))
			{
				const std::vector<std::string> & definition = Util::split(stripped_line, "=");
				if (definition[0].compare("moovie.tick_label_font") == 0)
				{
					_tick_label = TextProperties(definition[1], _tick_label.fontsize());
				}
				else if (definition[0].compare("moovie.var_label_font") == 0)
				{
					_var_label = TextProperties(definition[1], _var_label.fontsize());
				}
			}
		}
	}
}

