/*
 * Configuration.cpp
 *
 *  Created on: 16.01.2018
 *      Author: stratmann
 */

#include "Configuration.h"

const double Configuration::RADIAL_TEXT_FACTOR = 0.3;

const double Configuration::COORDGRID_ADJUSTMENT = 0.5;
const double Configuration::COORDPOINT_ANGLE = 0.005;
const double Configuration::COORDGRID_DESCRIPTION_ANGLE = 0.1;

const double Configuration::END_RADIUS_MAJOR_FACTOR = 0.25;
const double Configuration::END_RADIUS_MINOR_FACTOR = 0.125;
const double Configuration::RADIUS_TICK_LABEL_FACTOR = 0.75;

const double Configuration::DATA_LINK_LINE_WIDTH = 0.1;
const double Configuration::CONNECTOR_ARROW_HEIGHT = 3;

const double Configuration::RADIUS_LABEL_DELTA = 5;
const double Configuration::RADIUS_HISTOGRAM_DELTA = 10;
const double Configuration::CONNECTOR_DELTA = 10;
const double Configuration::TEXT_DELTA = 0.01;
const double Configuration::ANGLE_DELTA_SMALL = 0.001;
const double Configuration::ANGLE_DELTA_LARGE = 0.1;
const double Configuration::RADIUS_DELTA = 10;

std::shared_ptr<Configuration> Configuration::_instance(nullptr);

void Configuration::initialize(const std::string & fname, const std::string & cpath)
{
    _instance = std::shared_ptr<Configuration>(new Configuration(fname, cpath));
}

Configuration::Configuration(const std::string & fname, const std::string & cpath)
: _input_file(fname)
{
	std::string content = Util::read_file(cpath);

	for (std::string line: Util::split(content, "\n"))
	{
		if (line.find_first_not_of(' ') != line.npos
				&& line[line.find_first_not_of(' ')] != '#')
		{
			std::size_t split_pos = line.find_first_of("=");
			const std::string & key = Util::strip(line.substr(0, split_pos));
			const std::string & value = Util::strip(line.substr(split_pos + 1,
					line.size() - split_pos - 1));

			if (key.compare("moovie.width") == 0)
			{
				_width = Util::string_to_int(value);
			}
			else if (key.compare("moovie.height") == 0)
			{
				_height = Util::string_to_int(value);
			}
			else if (key.compare("moovie.output_angle_span") == 0)
			{
				_output_angle_span = Util::string_to_double(value);
			}
			else if (key.compare("moovie.output_inner_radius") == 0)
			{
				_output_inner_radius = Util::string_to_double(value);
			}
			else if (key.compare("moovie.output_thickness") == 0)
			{
				_output_thickness = Util::string_to_double(value);
			}
			else if (key.compare("moovie.grid_size") == 0)
			{
				_grid_size = Util::string_to_double(value);
			}
			else if (key.compare("moovie.num_major_ticks_coordgrid") == 0)
			{
				_num_major_ticks_cg = Util::string_to_int(value);
			}
			else if (key.compare("moovie.num_minor_ticks_coordgrid") == 0)
			{
				_num_minor_ticks_cg = Util::string_to_int(value);
			}
			else if (key.compare("moovie.num_segments") == 0)
			{
				_num_segments = Util::string_to_int(value);
			}
			else if (key.compare("moovie.input_inner_radius") == 0)
			{
				_input_inner_radius = Util::string_to_double(value);
			}
			else if (key.compare("moovie.input_thickness") == 0)
			{
				_input_thickness = Util::string_to_double(value);
			}
			else if (key.compare("moovie.input_separation_angle") == 0)
			{
				_input_separation_angle = Util::string_to_double(value);
			}
			else if (key.compare("moovie.num_major_ticks_varaxis") == 0)
			{
				_num_major_ticks_va = Util::string_to_int(value);
			}
			else if (key.compare("moovie.num_minor_ticks_varaxis") == 0)
			{
				_num_major_ticks_va = Util::string_to_int(value);
			}
			else if (key.compare("moovie.num_histogram_classes") == 0)
			{
				_num_histogram_classes = Util::string_to_int(value);
			}
			else if (key.compare("moovie.histogram_height") == 0)
			{
				_histogram_height = Util::string_to_double(value);
			}
			else if (key.compare("moovie.histogram_background") == 0)
			{
				std::vector<std::string> values = Util::split(value, ",");
				if (values.size() != 3);
				_histogram_background = Color(
						Util::string_to_double(values[0]),
						Util::string_to_double(values[1]),
						Util::string_to_double(values[2]),
						0.1
				);
			}
			else if (key.compare("moovie.histogram_fill") == 0)
			{
				std::vector<std::string> values = Util::split(value, ",");
				if (values.size() != 3);
				_histogram_fill = Color(
						Util::string_to_double(values[0]),
						Util::string_to_double(values[1]),
						Util::string_to_double(values[2]),
						1
				);
			}
			else if (key.compare("moovie.line_width_datalink") == 0)
			{
				_line_width_dl = Util::string_to_double(value);
			}
			else if (key.compare("moovie.ratio_connector_arc") == 0)
			{
				_ratio_connector_arc = Util::string_to_double(value);
			}
			else if (key.compare("moovie.thick_line") == 0)
			{
				_prop_thick.line_width = Util::string_to_double(value);
			}
			else if (key.compare("moovie.thick_line") == 0)
			{
				_prop_thin.line_width = Util::string_to_double(value);
			}
			else if (key.compare("moovie.tick_label_font") == 0)
			{
				_tick_label.font_name = value;
			}
			else if (key.compare("moovie.tick_label_font_size") == 0)
			{
				_tick_label.font_size = Util::string_to_double(value);
			}
			else if (key.compare("moovie.var_label_font") == 0)
			{
				_var_label.font_name = value;
			}
			else if (key.compare("moovie.var_label_font_size") == 0)
			{
				_var_label.font_size = Util::string_to_double(value);
			}
		}
	}

	if (_width == 0 && _height == 0)
	{
		_width = _height = _output_inner_radius + _output_thickness + _grid_size;
	}
	else if (_width == 0)
	{
		_width = _height;
	}
	else if (_height == 0)
	{
		_height = _width;
	}
}

