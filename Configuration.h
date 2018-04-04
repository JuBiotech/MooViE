/*
 * Configuration.h
 *
 *  Created on: 16.01.2018
 *      Author: stratmann
 */

#ifndef CONFIGURATION_H_
#define CONFIGURATION_H_

#include <string>
#include <vector>
#include <regex>
#include <memory>
#include "Utils.h"
#include "DrawerProperties.h"
#include "TextProperties.h"

/**
 *
 */
class Configuration {
public:
	static const double RADIAL_TEXT_FACTOR;

	static const double COORDGRID_ADJUSTMENT;
	static const double COORDPOINT_ANGLE;
	static const double COORDGRID_DESCRIPTION_ANGLE;

	static const double END_RADIUS_MAJOR_FACTOR;
	static const double END_RADIUS_MINOR_FACTOR;
	static const double RADIUS_TICK_LABEL_FACTOR;

	static const double DATA_LINK_LINE_WIDTH;
	static const double CONNECTOR_ARROW_HEIGHT;

	static const double RADIUS_LABEL_DELTA;
	static const double RADIUS_HISTOGRAM_DELTA;
	static const double CONNECTOR_DELTA;
	static const double TEXT_DELTA;
	static const double ANGLE_DELTA_SMALL;
	static const double ANGLE_DELTA_LARGE;
	static const double RADIUS_DELTA;
private:
	static std::shared_ptr<Configuration> _instance;
public:
	inline static Configuration & get_instance()
	{
	  return *_instance; // TODO: throw exception if empty
	}

	static void initialize(const std::string & fname, const std::string & cpath = ".");


	// Generell


	inline const std::string & get_input_file() const
	{
		return _input_file;
	}

	inline const std::string & get_output_file() const
	{
		return _output_file;
	}

	inline void set_output_file(const std::string & output_file)
	{
		_output_file = output_file;
	}

	inline int get_width() const {
		return _width;
	}

	inline int get_height() const {
		return _height;
	}


	// CoordGrid


	double get_output_angle_span () const
	{
	  return _output_angle_span;
	}

	void set_output_angle_span (double output_angle_span)
	{
	    _output_angle_span = output_angle_span;
	}

	double get_output_inner_radius() const
	{
		return _output_inner_radius;
	}

	void set_output_inner_radius(double output_inner_radius)
	{
		_output_inner_radius = output_inner_radius;
	}

	double get_output_thickness() const {
		return _output_thickness;
	}

	void set_output_thickness(double output_thickness)
	{
		_output_thickness = output_thickness;
	}

	double get_grid_size() const
	{
		return _grid_size;
	}

	void set_grid_size(double grid_size)
	{
		_grid_size = grid_size;
	}

	int get_num_major_ticks_cg() const
	{
		return _num_major_ticks_cg;
	}

	void set_num_major_ticks_cg(int num_major_ticks_cg)
	{
		_num_major_ticks_cg = num_major_ticks_cg;
	}

	int get_num_minor_ticks_cg() const
	{
		return _num_minor_ticks_cg;
	}

	void set_num_minor_ticks_cg(int num_minor_ticks_cg)
	{
		_num_minor_ticks_cg = num_minor_ticks_cg;
	}

	int get_num_segments() const
	{
		return _num_segments;
	}

	void set_num_segments(int num_segments)
	{
		_num_segments = num_segments;
	}


	// VarAxis


	double get_input_inner_radius() const
	{
		return _input_inner_radius;
	}

	void set_input_inner_radius(double input_inner_radius)
	{
		_input_inner_radius = input_inner_radius;
	}

	double get_input_separation_angle() const
	{
		return _input_separation_angle;
	}

	void set_input_separation_angle(double input_separation_angle)
	{
		_input_separation_angle = input_separation_angle;
	}

	double get_input_thickness() const
	{
		return _input_thickness;
	}

	void set_input_thickness(double input_thickness)
	{
		_input_thickness = input_thickness;
	}

	int get_num_major_ticks_va() const
	{
		return _num_major_ticks_va;
	}

	void set_num_major_ticks_va(int num_major_ticks_va)
	{
		_num_major_ticks_va = num_major_ticks_va;
	}

	int get_num_minor_ticks_va() const
	{
		return _num_minor_ticks_va;
	}

	void set_num_minor_ticks_va(int num_minor_ticks_va)
	{
		_num_minor_ticks_va = num_minor_ticks_va;
	}

	int get_num_histogram_classes() const
	{
		return _num_histogram_classes;
	}

	void set_num_histogram_classes(int num_histogram_classes)
	{
		_num_histogram_classes = num_histogram_classes;
	}

	double get_histogram_height() const
	{
		return _histogram_height;
	}

	void set_histogram_height(double histogram_height)
	{
		_histogram_height = histogram_height;
	}

	const Color& get_histogram_background() const
	{
		return _histogram_background;
	}

	void set_histogram_background(const Color& histogram_background)
	{
		_histogram_background = histogram_background;
	}

	const Color& get_histogram_fill() const
	{
		return _histogram_fill;
	}

	void set_histogram_fill(const Color& histogram_fill)
	{
		_histogram_fill = histogram_fill;
	}


	// DataLink


	double get_line_with_dl() const
	{
		return _line_width_dl;
	}

	void set_line_with_dl(double line_with_dl = 0.1)
	{
		_line_width_dl = line_with_dl;
	}

	double get_ratio_connector_arc() const
	{
		return _ratio_connector_arc;
	}

	void set_ratio_connector_arc(double ratio_connector_arc)
	{
		_ratio_connector_arc = ratio_connector_arc;
	}


	// Standard properties and labels


	const DrawerProperties<> & get_prop_thick() const
	{
		return _prop_thick;
	}

	void set_propthick(const DrawerProperties<> & prop_thick)
	{
		_prop_thick = prop_thick;
	}

	const DrawerProperties<> & get_prop_thin() const {
		return _prop_thin;
	}

	void set_prop_thin(const DrawerProperties<> & prop_thin) {
		_prop_thin = prop_thin;
	}

	const TextProperties & get_tick_label() const {
		return _tick_label;
	}

	void set_ticklabel(const TextProperties & tick_label)
	{
		_tick_label = tick_label;
	}

	const TextProperties & get_var_label() const
	{
		return _var_label;
	}

	void set_var_label(const TextProperties& var_label)
	{
		_var_label = var_label;
	}

private:
	Configuration(const std::string & fname, const std::string & cpath);

	/* Absolute file paths for data (input) and image (output) */
	std::string 		_input_file;
	std::string			_output_file 			= "image.svg";

	/* Width and height of the output image */
	int 				_width 					= 0;
	int 				_height 				= 0;

	/* CoordGrid modification values */
	double				_output_angle_span		= 100;
	double 				_output_inner_radius 	= 160;
	double 				_output_thickness 		= 10;
	double 				_grid_size 				= 150;
	int					_num_major_ticks_cg		= 10;
	int					_num_minor_ticks_cg		= 10;
	int					_num_segments			= 10;

	/* VarAxis modification values */
	double 				_input_inner_radius 	= 150;
	double 				_input_thickness 		= 10;
	double 				_input_separation_angle = 5;
	int					_num_major_ticks_va		= 10;
	int					_num_minor_ticks_va		= 10;

	/* Histogram modification values */
	int					_num_histogram_classes	= 10;
	double				_histogram_height		= 20;
	Color				_histogram_background	= {0, 0, 0, .1};
	Color				_histogram_fill			= {.5, .5, .5, 1};

	/* DataLink modification values */
	double				_line_width_dl			= 0.1;
	double				_ratio_connector_arc	= 0.6;

	/* General line and fill styles */
	DrawerProperties<> 	_prop_thick 			= {0.5, Color::BLACK, Color::BLACK};
	DrawerProperties<> 	_prop_thin 				= {0.2, Color::BLACK, Color::BLACK};

	/* General font and font size */
	TextProperties 		_tick_label 			= {"Sans Serif", 8};
	TextProperties 		_var_label 				= {"Sans Serif", 20};
};

#endif /* CONFIGURATION_H_ */
