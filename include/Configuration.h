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
#include <Utils.h>
#include <DrawerProperties.h>
#include <TextProperties.h>
#include <Triangle.h>

/** A class wrapping the settings and information that is
 * necessary for a MooViE run. Configuration is implemented
 * as a singelton. Before calling Configuration#get_instance
 * to get the singleton instance Configuration#initialize
 * need to be called once.
 *
 * @author stratmann
 * @date 16.01.2018
 */
class Configuration
{
public:
	/** An array of Colors */
	static const std::array<Color, 10> 	GLOW_10;

	/** A Triangular storage which contains i+1
	 * matching colors at the i-th index.
	 */
	static const Triangle<Color, 12> 	SET3;

	/** Further color constants */
	static const Color 					SET2_3_1;
	static const Color 					SET2_3_2;
	static const Color 					SET2_3_3;

private:
	/** The singleton instance */
	static std::shared_ptr<Configuration> _instance;

public:
	/** Returns a reference to the singleton instance of
	 * Configuration. Configuration#initialize needs to be
	 * called at least once before.
	 *
	 * @return the reference to the Configuration instance
	 *
	 * @throw bad_function_call if instance was not initialized
	 */
	inline static Configuration & get_instance()
	{
		if (_instance.get() == nullptr)
		{
			throw std::bad_function_call();
		}

		return *_instance;
	}

	/** Initializes the singleton instance with the given input
	 * file path and the information given by the configuration
	 * file located under the given configuration file path.
	 *
	 * @param fname the path to the input file
	 * @param cpath the path to the configuration file
	 */
	static void initialize(const std::string & fname, const std::string & cpath);

	/** Initializes the singleton instance with the given input
	 * file path and the standard configuration information.
	 *
	 * @param fname the path to the input file
	 */
	static void initialize(const std::string & fname);


	// General

	/** Returns the path to the input file.
	 *
	 * @return the input file path
	 */
	inline const std::string & get_input_file() const
	{
		return input_file;
	}

	/** Returns the path to the output file.
	 *
	 * @return the output file path
	 */
	inline const std::string & get_output_file() const
	{
		return output_file;
	}

	/** Sets the path to the output file.
	 *
	 * @param output_file the output file path to set
	 */
	inline void set_output_file(const std::string & _output_file)
	{
		output_file = _output_file;
	}

	/** Returns the width of the MooViE scene
	 *
	 * @return the width
	 */
	inline int get_width() const {
		return width;
	}

	/** Sets the width of a MooViE scene.
	 *
	 * @param width the width to set
	 */
	inline void set_width(int _width) {
		width = _width;
	}

	/** Returns the height of the MooViE scene
	 *
	 * @return the height
	 */
	inline int get_height() const {
		return height;
	}

	/** Sets the height of a MooViE scene.
	 *
	 * @param height the height to set
	 */
	inline void set_height(int _height) {
		height = _height;
	}


	// CoordGrid


	/** Returns the output angle span, the angle span
	 * for the CodomainGrid.
	 *
	 * @return the output angle span
	 */
	double get_output_angle_span () const
	{
	  return output_angle_span;
	}

	/** Sets the output angle span, the angle span
	 * for the CodomainGrid.
	 *
	 * @param output_angle_span the output angle span to set
	 */
	void set_output_angle_span (double _output_angle_span)
	{
	    output_angle_span = _output_angle_span;
	}

	/** Returns the inner radius of the output, the radius
	 * at which the CodomainGrid starts.
	 *
	 * @return the output inner radius
	 */
	double get_output_inner_radius() const
	{
		return output_inner_radius;
	}

	/** Sets the inner radius of the output, the radius
	 * at which the CodomainGrid starts.
	 *
	 * @param output_inner_radius the output inner radius to set
	 */
	void set_output_inner_radius(double _output_inner_radius)
	{
		output_inner_radius = _output_inner_radius;
	}

	/** Returns the thickness of the outputs colored
	 * segmented ring.
	 *
	 * @return the output thickness
	 */
	double get_output_thickness() const {
		return output_thickness;
	}

	/** Sets the thickness of the outputs colored
	 * segmented ring.
	 *
	 * @param output_thickness the output_thickness to set
	 */
	void set_output_thickness(double _output_thickness)
	{
		output_thickness = _output_thickness;
	}

	/** Returns the size of actual grid that is a part
	 * of the CodomainGrid.
	 *
	 * @return the grid_size
	 */
	double get_grid_size() const
	{
		return grid_size;
	}

	/** Sets the size of actual grid that is a part
	 * of the CodomainGrid.
	 *
	 * @param grid_size the grid_size to set
	 */
	void set_grid_size(double _grid_size)
	{
		grid_size = _grid_size;
	}

	/** Returns the number of bold sections of
	 * the scale of the CodomainGrid.
	 *
	 * @return the number of major sections
	 */
	int get_num_major_sections_grid() const
	{
		return num_major_sections_grid;
	}

	/** Sets the number of bold sections of
	 * the scale of the CodomainGrid.
	 *
	 * @param major_sections the number of major sections to set
	 */
	void set_num_major_sections_grid(int major_sections)
	{
		num_major_sections_grid = major_sections;
	}

	/** Returns the number of narrow sections of
	 * the scale of the CodomainGrid.
	 *
	 * @return the number of minor sections
	 */
	int get_num_minor_sections_grid() const
	{
		return num_minor_sections_grid;
	}

	/** Sets the number of narrow sections of
	 * the scale of the CodomainGrid.
	 *
	 * @param minor_sections the number of minor sections to set
	 */
	void set_num_minor_sections_grid(int minor_sections)
	{
		num_minor_sections_grid = minor_sections;
	}


	// DomainAxis


	/** Returns the inner radius of an input, the radius
	 * where the DomainAxis start.
	 *
	 * @return the input inner radius
	 */
	double get_input_inner_radius() const
	{
		return input_inner_radius;
	}

	/** Sets the inner radius of an input, the radius
	 * where the DomainAxis start.
	 *
	 * @param input_inner_radius the input inner radius to set
	 */
	void set_input_inner_radius(double _input_inner_radius)
	{
		input_inner_radius = _input_inner_radius;
	}

	/** Returns the seperation angle between inputs.
	 *
	 * @return the input separation angle
	 */
	double get_input_separation_angle() const
	{
		return input_separation_angle;
	}

	/** Sets the seperation angle between inputs.
	 *
	 * @param input_separation_angle the input separation angle to set
	 */
	void set_input_separation_angle(double _input_separation_angle)
	{
		input_separation_angle = _input_separation_angle;
	}

	/** Returns the thickness of the colored ring of the
	 * DomainAxis.
	 *
	 * @return the input thickness
	 */
	double get_input_thickness() const
	{
		return input_thickness;
	}

	/** Sets the thickness of the colored ring of the
	 * DomainAxis.
	 *
	 * @param _input_thickness the input thickness to set
	 */
	void set_input_thickness(double _input_thickness)
	{
		input_thickness = _input_thickness;
	}

	/** Returns the number of bold sections of
	 * the scale of the DomainAxis.
	 *
	 * @return the number of major sections
	 */
	int get_num_major_sections_axis() const
	{
		return num_major_sections_axis;
	}

	/** Sets the number of bold sections of
	 * the scale of the DomainAxis.
	 *
	 * @param major_sections the number of major sections to set
	 */
	void set_num_major_sections_axis(int major_sections)
	{
		num_major_sections_grid = major_sections;
	}

	/** Returns the number of narrow sections of
	 * the scale of the DomainAxis.
	 *
	 * @return the number of minor sections
	 */
	int get_num_minor_sections_axis() const
	{
		return num_minor_sections_axis;
	}

	/** Sets the number of narrow sections of
	 * the scale of the DomainAxis.
	 *
	 * @param minor_sections the number minor sections to set
	 */
	void set_num_minor_sections_axis(int minor_sections)
	{
		num_minor_sections_axis = minor_sections;
	}

	/** Returns the number of classes that each histogram
	 * consists of.
	 *
	 * @return the number of histogram classes
	 */
	int get_num_histogram_classes() const
	{
		return num_histogram_classes;
	}

	/** Sets the number of classes that each histogram
	 * consists of.
	 *
	 * @param _num_histogram_classes the number of histogram classes to set
	 */
	void set_num_histogram_classes(int _num_histogram_classes)
	{
		num_histogram_classes = _num_histogram_classes;
	}

	/** Returns the height that each histogram has.
	 *
	 * @return the histogram height
	 */
	double get_histogram_height() const
	{
		return histogram_height;
	}

	/** Sets the height that each histogram has.
	 *
	 * @param _histogram_height the histogram height to set
	 */
	void set_histogram_height(double _histogram_height)
	{
		histogram_height = _histogram_height;
	}

	/** Returns the background color that each histogram
	 * has.
	 *
	 * @return the histogram background color
	 */
	const Color& get_histogram_background() const
	{
		return histogram_background;
	}

	/** Sets the background color that each histogram
	 * has.
	 *
	 * @param _histogram_background the histogram background color to set
	 */
	void set_histogram_background(const Color& _histogram_background)
	{
		histogram_background = _histogram_background;
	}

	/** Returns the fill color of each histogram's bars.
	 *
	 * @return the histogram fill color
	 */
	const Color& get_histogram_fill() const
	{
		return histogram_fill;
	}

	/** Sets the fill color of each histogram's bars.
	 *
	 * @param _histogram_fill the histogram fill color to set
	 */
	void set_histogram_fill(const Color& _histogram_fill)
	{
		histogram_fill = _histogram_fill;
	}


	// RelationElement

	/** Returns the ratio of the radial distance between two data
	 * points that will be drawn as connector.
	 *
	 * @return the connector arc ratio
	 */
	double get_connector_arc_ratio() const
	{
		return connector_arc_ratio;
	}

	/** Sets the ratio of the radial distance between two data
	 * points that will be drawn as connector.
	 *
	 * @param _ratio_connector_arc the connector arc ratio to set
	 */
	void set_connector_arc_ratio(double _connector_arc_ratio)
	{
		connector_arc_ratio = _connector_arc_ratio;
	}


	// Standard properties and labels


	/** Returns MooViEs DrawerProperties for thick black
	 * lines.
	 *
	 * @return the DrawerProperties for thick lines
	 */
	const DrawerProperties<> & get_prop_thick() const
	{
		return prop_thick;
	}

	/** Sets MooViEs DrawerProperties for thick black
	 * lines.
	 *
	 * @param _prop_thick the DrawerProperties to set
	 */
	void set_prop_thick(const DrawerProperties<> & _prop_thick)
	{
		prop_thick = _prop_thick;
	}

	/** Returns MooViEs DrawerProperties for thin black
	 * lines.
	 *
	 * @return the DrawerProperties for thin lines
	 */
	const DrawerProperties<> & get_prop_thin() const {
		return prop_thin;
	}

	/** Sets MooViEs DrawerProperties for thin black
	 * lines.
	 *
	 * @param _prop_thin the DrawerProperties to set
	 */
	void set_prop_thin(const DrawerProperties<> & _prop_thin) {
		prop_thin = _prop_thin;
	}

	/** Returns MooViEs TextProperties for Scale labels.
	 *
	 * @return the TextProperties for Scale labels
	 */
	const TextProperties & get_prop_scale_label() const {
		return prop_scale_label;
	}

	/** Sets MooViEs TextProperties for Scale labels.
	 *
	 * @param _prop_scale_label the TextProperties to set
	 */
	void set_prop_scale_label(const TextProperties & _prop_scale_label)
	{
		prop_scale_label = _prop_scale_label;
	}

	/** Returns MooViEs TextProperties for DomainAxis
	 * labels.
	 *
	 * @return the TextProperties for DomainAxis labels
	 */
	const TextProperties & get_prop_axis_label() const
	{
		return prop_axis_label;
	}

	/** Sets MooViEs TextProperties for DomainAxis
	 * labels.
	 *
	 * @param _prop_axis_label the TextProperties to set
	 */
	void set_prop_axis_label(const TextProperties& _prop_axis_label)
	{
		prop_axis_label = _prop_axis_label;
	}

private:
	/** Tries to guess the height and width of the MooViE scene
	 * using the
	 */
	void adjust_height();

private:
	Configuration(const std::string & fname, const std::string & cpath);

	Configuration(const std::string & fname);

	/* Absolute file paths for data (input) and image (output) */
	std::string 		input_file;
	std::string			output_file 			= "image.svg";

	/* Width and height of the output image */
	int 				width 					= 0;
	int 				height 					= 0;

	/* CodomainGrid modification values */
	double				output_angle_span		= 160;
	double 				output_inner_radius 	= 160;
	double 				output_thickness 		= 5;
	double 				grid_size 				= 150;
	int					num_major_sections_grid	= 10;
	int					num_minor_sections_grid	= 10;

	/* DomainAxis modification values */
	double 				input_inner_radius 		= 180;
	double 				input_thickness 		= 5;
	double 				input_separation_angle 	= 5;
	int					num_major_sections_axis	= 10;
	int					num_minor_sections_axis	= 10;

	/* Histogram modification values */
	int					num_histogram_classes	= 10;
	double				histogram_height		= 20;
	Color				histogram_background	= {0, 0, 0, .1};
	Color				histogram_fill			= {.5, .5, .5, 1};

	/* RelationElement modification values */
	double				connector_arc_ratio		= 0.6;

	/* General line and fill styles */
	DrawerProperties<> 	prop_thick 				= {0.5, Color::BLACK, Color::BLACK};
	DrawerProperties<> 	prop_thin 				= {0.1, Color::BLACK, Color::BLACK};

	/* General font and font size */
	TextProperties 		prop_scale_label 		= {"Liberation Serif", 5};
	TextProperties 		prop_axis_label 		= {"Liberation Serif", 10};
};

#endif /* CONFIGURATION_H_ */
