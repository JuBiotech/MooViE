#include <Configuration.h>
#include <iostream>

// Instance pointer

std::shared_ptr<Configuration> Configuration::instance (nullptr);

// Color constants

const std::array<Color, 10> Configuration::GLOW_10 =
  {
    { Color (242, 165, 44, 255), Color (248, 130, 54, 255), Color (241, 98, 58,
								   255), Color (
	229, 66, 60, 255), Color (216, 14, 64, 255), Color (180, 0, 154, 255),
	Color (117, 0, 222, 255), Color (81, 0, 189, 255), Color (52, 12, 149,
								  255), Color (
	    40, 15, 94, 255) } };

const Color Configuration::SET2_3_1
  { 102, 194, 165 };
const Color Configuration::SET2_3_2
  { 252, 141, 98 };
const Color Configuration::SET2_3_3
  { 141, 160, 203 };

const Triangle<Color, 12> Configuration::SET3
  { std::vector<Color>
    {
//1 (artificial 3_2)
	Color (255, 255, 179, 255),
//2 (artificial 3_1 and 3_3)
	Color (141, 211, 199, 255), Color (190, 186, 218, 255),
//3
	Color (141, 211, 199, 255), Color (255, 255, 179, 255), Color (190, 186,
								       218,
								       255),
//4
	Color (141, 211, 199, 255), Color (255, 255, 179, 255), Color (190, 186,
								       218,
								       255),
	Color (251, 128, 114, 255),
//5
	Color (141, 211, 199, 255), Color (255, 255, 179, 255), Color (190, 186,
								       218,
								       255),
	Color (251, 128, 114, 255), Color (128, 177, 211, 255),
//6
	Color (141, 211, 199, 255), Color (255, 255, 179, 255), Color (190, 186,
								       218,
								       255),
	Color (251, 128, 114, 255), Color (128, 177, 211, 255), Color (253, 180,
								       98, 255),
//7
	Color (141, 211, 199, 255), Color (255, 255, 179, 255), Color (190, 186,
								       218,
								       255),
	Color (251, 128, 114, 255), Color (128, 177, 211, 255), Color (253, 180,
								       98, 255),
	Color (179, 222, 105, 255),
//8
	Color (141, 211, 199, 255), Color (255, 255, 179, 255), Color (190, 186,
								       218,
								       255),
	Color (251, 128, 114, 255), Color (128, 177, 211, 255), Color (253, 180,
								       98, 255),
	Color (179, 222, 105, 255), Color (252, 205, 229, 255),
//9
	Color (141, 211, 199, 255), Color (255, 255, 179, 255), Color (190, 186,
								       218,
								       255),
	Color (251, 128, 114, 255), Color (128, 177, 211, 255), Color (253, 180,
								       98, 255),
	Color (179, 222, 105, 255), Color (252, 205, 229, 255), Color (217, 217,
								       217,
								       255),
//10
	Color (141, 211, 199, 255), Color (255, 255, 179, 255), Color (190, 186,
								       218,
								       255),
	Color (251, 128, 114, 255), Color (128, 177, 211, 255), Color (253, 180,
								       98, 255),
	Color (179, 222, 105, 255), Color (252, 205, 229, 255), Color (217, 217,
								       217,
								       255),
	Color (188, 128, 189, 255),
//11
	Color (141, 211, 199, 255), Color (255, 255, 179, 255), Color (190, 186,
								       218,
								       255),
	Color (251, 128, 114, 255), Color (128, 177, 211, 255), Color (253, 180,
								       98, 255),
	Color (179, 222, 105, 255), Color (252, 205, 229, 255), Color (217, 217,
								       217,
								       255),
	Color (188, 128, 189, 255), Color (204, 235, 197, 255),
//12
	Color (141, 211, 199, 255), Color (255, 255, 179, 255), Color (190, 186,
								       218,
								       255),
	Color (251, 128, 114, 255), Color (128, 177, 211, 255), Color (253, 180,
								       98, 255),
	Color (179, 222, 105, 255), Color (252, 205, 229, 255), Color (217, 217,
								       217,
								       255),
	Color (188, 128, 189, 255), Color (204, 235, 197, 255), Color (255, 237,
								       111, 255)

    } };

// Functions

void
Configuration::initialize (const std::string & fpath, const std::string & cpath)
{
  instance = std::shared_ptr<Configuration> (new Configuration (fpath, cpath));
}

void
Configuration::initialize (const std::string & fpath)
{
  instance = std::shared_ptr<Configuration> (new Configuration (fpath));
}

void
Configuration::adjust_height ()
{
  if (m_width == 0 && m_height == 0)
    {
      m_width = m_height = 2
	  * (m_output_inner_radius + m_output_thickness + m_grid_size) + 100;
    }
  else if (m_width == 0)
    {
      m_width = m_height;
    }
  else if (m_height == 0)
    {
      m_height = m_width;
    }
}

Configuration::Configuration (const std::string & fpath,
			      const std::string & cpath) :
    m_input_file (fpath)
{
  std::string content = Util::read_file (cpath);

  for (std::string line : Util::split (content, "\n"))
    {
      if (line.find_first_not_of (' ') != line.npos
	  && line[line.find_first_not_of (' ')] != '#')
	{
	  std::size_t split_pos = line.find_first_of ("=");
	  const std::string & key = Util::strip (line.substr (0, split_pos));
	  const std::string & value = Util::strip (
	      line.substr (split_pos + 1, line.size () - split_pos - 1));

	  if (key.compare ("moovie.width") == 0)
	    {
	      m_width = std::stoi (value);

	      if (m_width <= 0)
		{
		  throw std::out_of_range ("\"width\" cannot be set <= 0");
		}
	    }
	  else if (key.compare ("moovie.height") == 0)
	    {
	      m_height = std::stoi (value);

	      if (m_height <= 0)
		{
		  throw std::out_of_range ("\"height\" cannot be set <= 0");
		}
	    }
	  else if (key.compare ("moovie.output_angle_span") == 0)
	    {
	      m_output_angle_span = std::stod (value);

	      if (m_output_angle_span <= 0 || m_output_angle_span > 175)
		{
		  throw std::out_of_range (
		      "\"output_angle_span\" exceeded range (0, 175)");
		}
	    }
	  else if (key.compare ("moovie.output_inner_radius") == 0)
	    {
	      m_output_inner_radius = std::stod (value);

	      if (m_output_inner_radius <= 0)
		{
		  throw std::out_of_range (
		      "\"output_inner_radius\" cannot be <= 0");
		}
	    }
	  else if (key.compare ("moovie.output_thickness") == 0)
	    {
	      m_output_thickness = std::stod (value);

	      if (m_output_thickness <= 0)
		{
		  throw std::out_of_range (
		      "\"output_thickness\" cannot be <= 0");
		}
	    }
	  else if (key.compare ("moovie.grid_size") == 0)
	    {
	      m_grid_size = std::stod (value);

	      if (m_grid_size <= 0)
		{
		  throw std::out_of_range ("\"grid_size\" cannot be <= 0");
		}
	    }
	  else if (key.compare ("moovie.num_major_sections_grid") == 0)
	    {
	      m_num_major_sections_grid = std::stoi (value);

	      if (m_num_major_sections_grid <= 0)
		{
		  throw std::out_of_range (
		      "\"num_major_sections_grid\" cannot be <= 0");
		}
	    }
	  else if (key.compare ("moovie.num_minor_sections_grid") == 0)
	    {
	      m_num_minor_sections_grid = std::stoi (value);

	      if (m_num_minor_sections_grid <= 0)
		{
		  throw std::out_of_range (
		      "\"num_minor_sections_grid\" cannot be <= 0");
		}
	    }
	  else if (key.compare ("moovie.input_inner_radius") == 0)
	    {
	      m_input_inner_radius = std::stod (value);

	      if (m_input_inner_radius <= 0)
		{
		  throw std::out_of_range (
		      "\"input_inner_radius\" cannot be <= 0");
		}
	    }
	  else if (key.compare ("moovie.input_thickness") == 0)
	    {
	      m_input_thickness = std::stod (value);

	      if (m_input_thickness <= 0)
		{
		  throw std::out_of_range (
		      "\"input_thickness\" cannot be <= 0");
		}
	    }
	  else if (key.compare ("moovie.input_separation_angle") == 0)
	    {
	      m_input_separation_angle = std::stod (value);

	      if (m_input_separation_angle <= 0
		  || m_input_separation_angle >= 180)
		{
		  throw std::out_of_range (
		      "\"input_separation_angle\" cannot be <= 0");
		}
	    }
	  else if (key.compare ("moovie.num_major_sections_axis") == 0)
	    {
	      m_num_major_sections_axis = std::stoi (value);

	      if (m_num_major_sections_axis <= 0)
		{
		  throw std::out_of_range (
		      "\"num_major_sections_axis\" cannot be <= 0");
		}
	    }
	  else if (key.compare ("moovie.num_minor_sections_axis") == 0)
	    {
	      m_num_minor_sections_axis = std::stoi (value);

	      if (m_num_minor_sections_axis <= 0)
		{
		  throw std::out_of_range (
		      "\"num_minor_sections_axis\" cannot be <= 0");
		}
	    }
	  else if (key.compare ("moovie.histograms_enabled") == 0)
	    {
	      if (value == "true")
		{
		  m_histograms_enabled = true;
		}
	      else if (value == "false")
		{
		  m_histograms_enabled = false;
		}
	      else
		{
		  throw std::invalid_argument (
		      "\"histograms_enabled\" expects \"true\" or \"false\"");
		}
	    }
	  else if (key.compare ("moovie.num_histogram_classes") == 0)
	    {
	      m_num_histogram_classes = std::stoi (value);

	      if (m_num_histogram_classes <= 0)
		{
		  throw std::out_of_range (
		      "\"num_histogram_classes\" cannot be <= 0");
		}
	    }
	  else if (key.compare ("moovie.histogram_height") == 0)
	    {
	      m_histogram_height = std::stod (value);

	      if (m_histogram_height <= 0)
		{
		  throw std::out_of_range (
		      "\"histogram_height\" cannot be <= 0");
		}
	    }
	  else if (key.compare ("moovie.histogram_background") == 0)
	    {
	      std::vector<std::string> values = Util::split (value, ",");

	      if (values.size () != 3)
		{
		  throw std::length_error (
		      "histogram_background should be defined with 3 comma-separated values ("
			  + std::to_string (values.size ())
			  + " given) which represent RGB values");
		}

	      m_histogram_background = Color (std::stod (values[0]),
					      std::stod (values[1]),
					      std::stod (values[2]), 0.1);
	    }
	  else if (key.compare ("moovie.histogram_fill") == 0)
	    {
	      std::vector<std::string> values = Util::split (value, ",");

	      if (values.size () != 3)
		{
		  throw std::length_error (
		      "histogram_background should be defined with 3 comma-separated values ("
			  + std::to_string (values.size ())
			  + " given) which represent RGB values");
		}

	      m_histogram_fill = Color (std::stod (values[0]),
					std::stod (values[1]),
					std::stod (values[2]), 1);
	    }
	  else if (key.compare ("moovie.connector_arc_ratio") == 0)
	    {
	      m_connector_arc_ratio = std::stod (value);

	      if (m_connector_arc_ratio < 0 || m_connector_arc_ratio > 1)
		{
		  throw std::out_of_range (
		      "\"connector_arc_ratio\" exceeds range [0,1]");
		}
	    }
	  else if (key.compare ("moovie.thick_line_width") == 0)
	    {
	      m_prop_thick.line_width = std::stod (value);

	      if (m_prop_thick.line_width <= 0)
		{
		  throw std::out_of_range (
		      "\"thick_line_width\" cannot be <= 0");
		}
	    }
	  else if (key.compare ("moovie.thick_line_width") == 0)
	    {
	      m_prop_thin.line_width = std::stod (value);

	      if (m_prop_thin.line_width <= 0)
		{
		  throw std::out_of_range (
		      "\"thick_line_width\" cannot be <= 0");
		}
	    }
	  else if (key.compare ("moovie.scale_label_font") == 0)
	    {
	      m_prop_scale_label.font_name = value;
	    }
	  else if (key.compare ("moovie.scale_label_font_size") == 0)
	    {
	      m_prop_scale_label.font_size = std::stod (value);

	      if (m_prop_scale_label.font_size <= 0)
		{
		  throw std::out_of_range (
		      "\"scale_label_font_size\" cannot be <= 0");
		}
	    }
	  else if (key.compare ("moovie.axis_label_font") == 0)
	    {
	      m_prop_axis_label.font_name = value;
	    }
	  else if (key.compare ("moovie.axis_label_font_size") == 0)
	    {
	      m_prop_axis_label.font_size = std::stod (value);

	      if (m_prop_axis_label.font_size <= 0)
		{
		  throw std::out_of_range (
		      "\"axis_label_font_size\" cannot be <= 0");
		}
	    }
	}
    }

  adjust_height ();
}

Configuration::Configuration (const std::string & fname) :
    m_input_file (fname)
{
  adjust_height ();
}

