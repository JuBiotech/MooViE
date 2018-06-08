/*
 * Configuration.cpp
 *
 *  Created on: 16.01.2018
 *      Author: stratmann
 */

#include <Configuration.h>
#include <iostream>

// Instance pointer


std::shared_ptr<Configuration> Configuration::_instance(nullptr);


// Color constants


const std::array<Color, 10> Configuration::GLOW_10 = {{
		Color(242, 165, 44, 255), Color(248, 130, 54, 255),
		Color(241, 98, 58, 255), Color(229, 66, 60, 255),
		Color(216, 14, 64, 255), Color(180, 0, 154, 255),
		Color(117, 0, 222, 255), Color(81, 0, 189, 255),
		Color(52, 12, 149, 255), Color(40, 15, 94, 255) }};

const Color Configuration::SET2_3_1 { 102, 194, 165 };
const Color Configuration::SET2_3_2 { 252, 141, 98 };
const Color Configuration::SET2_3_3 { 141, 160, 203 };

const Triangle<Color, 12> Configuration::SET3 {std::vector<Color>{
//1 (artificial 3_2)
Color(255, 255, 179, 255),
//2 (artificial 3_1 and 3_3)
Color(141, 211, 199, 255), Color(190, 186, 218, 255),
//3
Color(141, 211, 199, 255), Color(255, 255, 179, 255), Color(190, 186, 218, 255),
//4
Color(141, 211, 199, 255), Color(255, 255, 179, 255), Color(190, 186, 218, 255),
Color(251, 128, 114, 255),
//5
Color(141, 211, 199, 255), Color(255, 255, 179, 255), Color(190, 186, 218, 255),
Color(251, 128, 114, 255), Color(128, 177, 211, 255),
//6
Color(141, 211, 199, 255), Color(255, 255, 179, 255), Color(190, 186, 218, 255),
Color(251, 128, 114, 255), Color(128, 177, 211, 255), Color(253, 180, 98, 255),
//7
Color(141, 211, 199, 255), Color(255, 255, 179, 255), Color(190, 186, 218, 255),
Color(251, 128, 114, 255), Color(128, 177, 211, 255), Color(253, 180, 98, 255),
Color(179, 222, 105, 255),
//8
Color(141, 211, 199, 255), Color(255, 255, 179, 255), Color(190, 186, 218, 255),
Color(251, 128, 114, 255), Color(128, 177, 211, 255), Color(253, 180, 98, 255),
Color(179, 222, 105, 255), Color(252, 205, 229, 255),
//9
Color(141, 211, 199, 255), Color(255, 255, 179, 255), Color(190, 186, 218, 255),
Color(251, 128, 114, 255), Color(128, 177, 211, 255), Color(253, 180, 98, 255),
Color(179, 222, 105, 255), Color(252, 205, 229, 255), Color(217, 217, 217, 255),
//10
Color(141, 211, 199, 255), Color(255, 255, 179, 255), Color(190, 186, 218, 255),
Color(251, 128, 114, 255), Color(128, 177, 211, 255), Color(253, 180, 98, 255),
Color(179, 222, 105, 255), Color(252, 205, 229, 255), Color(217, 217, 217, 255),
Color(188, 128, 189, 255),
//11
Color(141, 211, 199, 255), Color(255, 255, 179, 255), Color(190, 186, 218, 255),
Color(251, 128, 114, 255), Color(128, 177, 211, 255), Color(253, 180, 98, 255),
Color(179, 222, 105, 255), Color(252, 205, 229, 255), Color(217, 217, 217, 255),
Color(188, 128, 189, 255), Color(204, 235, 197, 255),
//12
Color(141, 211, 199, 255), Color(255, 255, 179, 255), Color(190, 186, 218, 255),
Color(251, 128, 114, 255), Color(128, 177, 211, 255), Color(253, 180, 98, 255),
Color(179, 222, 105, 255), Color(252, 205, 229, 255), Color(217, 217, 217, 255),
Color(188, 128, 189, 255), Color(204, 235, 197, 255), Color(255, 237, 111, 255)

}};


// Functions


void Configuration::initialize(const std::string & fname, const std::string & cpath)
{
    _instance = std::shared_ptr<Configuration>(new Configuration(fname, cpath));
}

void Configuration::initialize(const std::string & fname)
{
	_instance = std::shared_ptr<Configuration>(new Configuration(fname));
}

void Configuration::adjust_height()
{
	if (_width == 0 && _height == 0)
	{
		_width = _height = 2 * (_output_inner_radius + _output_thickness + _grid_size) + 100;
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

				if (values.size() != 3)
				{
					throw std::length_error(
							"histogram_background should be defined with 3 comma-separated values ("
							+ std::to_string(values.size()) + " given) which represent RGB values"
					);
				}

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

				if (values.size() != 3)
				{
					throw std::length_error(
							"histogram_background should be defined with 3 comma-separated values ("
							+ std::to_string(values.size()) + " given) which represent RGB values"
					);
				}

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

	adjust_height();
}

Configuration::Configuration(const std::string & fname)
: _input_file(fname)
{
	adjust_height();
}

