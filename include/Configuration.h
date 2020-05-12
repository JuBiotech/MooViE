#ifndef CONFIGURATION_H_
#define CONFIGURATION_H_

#include <string>
#include <vector>
#include <regex>
#include <memory>
#include <functional>
#include <clocale>
#include <Utils.h>
#include <DrawerProperties.h>
#include <TextProperties.h>
#include <Triangle.h>

#include "libmoovie_export.h"

#define MOOVIE_CONF_LINE(key, value) (("moovie." TO_STRING(key) "=") + (value))

/** A class wrapping the settings and information that is
 * necessary for a MooViE run. Configuration is implemented
 * as a singelton. Before calling Configuration#get_instance
 * to get the singleton instance Configuration#initialize
 * need to be called once.
 *
 * @brief Configuration for a MooViE run
 *
 * @author stratmann
 * @date 16.01.2018
 */
class Configuration
{
public:
  /** An array of Colors */
  static const std::array<Color, 10> GLOW_10;

  /** A Triangular storage which contains i+1
   * matching colors at the i-th index.
   */
  static const Triangle<Color, 12> SET3;

  /** Further color constants */
  static const Color SET2_3_1;
  static const Color SET2_3_2;
  static const Color SET2_3_3;

private:
  /** The singleton instance */
  static LIBMOOVIE_EXPORT std::shared_ptr<Configuration> instance;

  /** Absolute file paths for data (input) and image (output) */
  std::string m_input_file;
  std::string m_output_file = "image.svg";

  /** Width and height of the output image */
  int m_width = 0;
  int m_height = 0;

  /** OutputGrid modification values */
  double m_output_angle_span = 160;
  double m_output_inner_radius = 160;
  double m_output_thickness = 5;
  double m_grid_size = 150;
  int m_num_major_sections_grid = 10;
  int m_num_minor_sections_grid = 10;

  /** InputAxis modification values */
  double m_input_inner_radius = 180;
  double m_input_thickness = 5;
  double m_input_separation_angle = 5;
  int m_num_major_sections_axis = 10;
  int m_num_minor_sections_axis = 10;

  /** Histogram modification values */
  bool m_histograms_enabled = true;
  int m_num_histogram_classes = 10;
  double m_histogram_height = 20;
  Color m_histogram_background =
    { 0, 0, 0, .1 };
  Color m_histogram_fill =
    { .5, .5, .5, 1 };

  /** IOVector modification values */
  int m_relevant_places = 3;

  /** General line and fill styles */
  DrawerProperties<> m_prop_thick =
    { 0.5, Color::BLACK, Color::BLACK };
  DrawerProperties<> m_prop_thin =
    { 0.1, Color::BLACK, Color::BLACK };

  /** General font and font size */
  TextProperties m_prop_scale_label =
    { "Liberation Serif", 5 };
  TextProperties m_prop_axis_label =
    { "Liberation Serif", 10 };

public:
  /** Returns a reference to the singleton instance of
   * Configuration. Configuration#initialize needs to be
   * called at least once before.
   *
   * @return the reference to the Configuration instance
   *
   * @throw bad_function_call if instance was not initialized
   */
  inline static Configuration &
  get_instance ()
  {
    if (instance.get () == nullptr)
      {
	throw std::bad_function_call ();
      }

    return *instance;
  }

  /** Initializes the singleton instance with the given input
   * file path and the information given by the configuration
   * file located under the given configuration file path.
   *
   * @param fname the path to the input file
   * @param cpath the path to the configuration file
   */
  static void
  initialize (const std::string & fname, const std::string & cpath);

  /** Initializes the singleton instance with the given input
   * file path and the standard configuration information.
   *
   * @param fname the path to the input file
   */
  static void
  initialize (const std::string & fname);

  /** Writes the current configuration instance to the specified
   * file path.
   *
   * @param cpath the path to save the configuration file to
   */
  static void
  save_to_file (const std::string & cpath);

  // General

  /** Returns the path to the input file.
   *
   * @return the input file path
   */
  inline const std::string &
  get_input_file () const
  {
    return m_input_file;
  }

  inline void
  set_input_file (const std::string& input_file)
  {
    m_input_file = input_file;
  }

  /** Returns the path to the output file.
   *
   * @return the output file path
   */
  inline const std::string &
  get_output_file () const
  {
    return m_output_file;
  }

  /** Sets the path to the output file.
   *
   * @param output_file the output file path to set
   */
  inline void
  set_output_file (const std::string & output_file)
  {
    m_output_file = output_file;
  }

  /** Returns the width of the MooViE scene
   *
   * @return the width
   */
  inline int
  get_width () const
  {
    return m_width;
  }

  /** Sets the width of a MooViE scene.
   *
   * @param width the width to set
   */
  inline void
  set_width (int width)
  {
    m_width = width;
  }

  /** Returns the height of the MooViE scene
   *
   * @return the height
   */
  inline int
  get_height () const
  {
    return m_height;
  }

  /** Sets the height of a MooViE scene.
   *
   * @param height the height to set
   */
  inline void
  set_height (int height)
  {
    m_height = height;
  }

  // OutputGrid

  /** Returns the output angle span, the angle span
   * for the OutputGrid.
   *
   * @return the output angle span
   */
  double
  get_output_angle_span () const
  {
    return m_output_angle_span;
  }

  /** Sets the output angle span, the angle span
   * for the OutputGrid.
   *
   * @param output_angle_span the output angle span to set
   */
  void
  set_output_angle_span (double output_angle_span)
  {
    m_output_angle_span = output_angle_span;
  }

  /** Returns the inner radius of the output, the radius
   * at which the OutputGrid starts.
   *
   * @return the output inner radius
   */
  double
  get_output_inner_radius () const
  {
    return m_output_inner_radius;
  }

  /** Sets the inner radius of the output, the radius
   * at which the OutputGrid starts.
   *
   * @param output_inner_radius the output inner radius to set
   */
  void
  set_output_inner_radius (double output_inner_radius)
  {
    m_output_inner_radius = output_inner_radius;
  }

  /** Returns the thickness of the outputs colored
   * segmented ring.
   *
   * @return the output thickness
   */
  double
  get_output_thickness () const
  {
    return m_output_thickness;
  }

  /** Sets the thickness of the outputs colored
   * segmented ring.
   *
   * @param output_thickness the output_thickness to set
   */
  void
  set_output_thickness (double output_thickness)
  {
    m_output_thickness = output_thickness;
  }

  /** Returns the size of actual grid that is a part
   * of the OutputGrid.
   *
   * @return the m_grid_size
   */
  double
  get_grid_size () const
  {
    return m_grid_size;
  }

  /** Sets the size of actual grid that is a part
   * of the OutputGrid.
   *
   * @param grid_size the m_grid_size to set
   */
  void
  set_grid_size (double grid_size)
  {
    m_grid_size = grid_size;
  }

  /** Returns the number of bold sections of
   * the scale of the OutputGrid.
   *
   * @return the number of major sections
   */
  int
  get_num_major_sections_grid () const
  {
    return m_num_major_sections_grid;
  }

  /** Sets the number of bold sections of
   * the scale of the OutputGrid.
   *
   * @param major_sections the number of major sections to set
   */
  void
  set_num_major_sections_grid (int major_sections)
  {
    m_num_major_sections_grid = major_sections;
  }

  /** Returns the number of narrow sections of
   * the scale of the OutputGrid.
   *
   * @return the number of minor sections
   */
  int
  get_num_minor_sections_grid () const
  {
    return m_num_minor_sections_grid;
  }

  /** Sets the number of narrow sections of
   * the scale of the OutputGrid.
   *
   * @param minor_sections the number of minor sections to set
   */
  void
  set_num_minor_sections_grid (int minor_sections)
  {
    m_num_minor_sections_grid = minor_sections;
  }

  // InputAxis

  /** Returns the inner radius of an input, the radius
   * where the InputAxis start.
   *
   * @return the input inner radius
   */
  double
  get_input_inner_radius () const
  {
    return m_input_inner_radius;
  }

  /** Sets the inner radius of an input, the radius
   * where the InputAxis start.
   *
   * @param input_inner_radius the input inner radius to set
   */
  void
  set_input_inner_radius (double input_inner_radius)
  {
    m_input_inner_radius = input_inner_radius;
  }

  /** Returns the seperation angle between inputs.
   *
   * @return the input separation angle
   */
  double
  get_input_separation_angle () const
  {
    return m_input_separation_angle;
  }

  /** Sets the seperation angle between inputs.
   *
   * @param input_separation_angle the input separation angle to set
   */
  void
  set_input_separation_angle (double input_separation_angle)
  {
    m_input_separation_angle = input_separation_angle;
  }

  /** Returns the thickness of the colored ring of the
   * InputAxis.
   *
   * @return the input thickness
   */
  double
  get_input_thickness () const
  {
    return m_input_thickness;
  }

  /** Sets the thickness of the colored ring of the
   * InputAxis.
   *
   * @param input_thickness the input thickness to set
   */
  void
  set_input_thickness (double input_thickness)
  {
    m_input_thickness = input_thickness;
  }

  /** Returns the number of bold sections of
   * the scale of the InputAxis.
   *
   * @return the number of major sections
   */
  int
  get_num_major_sections_axis () const
  {
    return m_num_major_sections_axis;
  }

  /** Sets the number of bold sections of
   * the scale of the InputAxis.
   *
   * @param major_sections the number of major sections to set
   */
  void
  set_num_major_sections_axis (int major_sections)
  {
    m_num_major_sections_axis = major_sections;
  }

  /** Returns the number of narrow sections of
   * the scale of the InputAxis.
   *
   * @return the number of minor sections
   */
  int
  get_num_minor_sections_axis () const
  {
    return m_num_minor_sections_axis;
  }

  /** Sets the number of narrow sections of
   * the scale of the InputAxis.
   *
   * @param minor_sections the number minor sections to set
   */
  void
  set_num_minor_sections_axis (int minor_sections)
  {
    m_num_minor_sections_axis = minor_sections;
  }

  /** Returns whether or not histograms should be drawn.
   *
   * @return histograms enabled or not
   */
  bool
  is_histograms_enabled () const
  {
    return m_histograms_enabled;
  }

  /** Sets whether or not histograms should be drawn.
   *
   * @param histograms_enabled histograms enabled or not
   */
  void
  set_histograms_enabled (bool histograms_enabled)
  {
    m_histograms_enabled = histograms_enabled;
  }

  /** Returns the number of classes that each histogram
   * consists of.
   *
   * @return the number of histogram classes
   */
  int
  get_num_histogram_classes () const
  {
    return m_num_histogram_classes;
  }

  /** Sets the number of classes that each histogram
   * consists of.
   *
   * @param num_histogram_classes the number of histogram classes to set
   */
  void
  set_num_histogram_classes (int num_histogram_classes)
  {
    m_num_histogram_classes = num_histogram_classes;
  }

  /** Returns the height that each histogram has.
   *
   * @return the histogram height
   */
  double
  get_histogram_height () const
  {
    return m_histogram_height;
  }

  /** Sets the height that each histogram has.
   *
   * @param histogram_height the histogram height to set
   */
  void
  set_histogram_height (double histogram_height)
  {
    m_histogram_height = histogram_height;
  }

  /** Returns the background color that each histogram
   * has.
   *
   * @return the histogram background color
   */
  const Color&
  get_histogram_background () const
  {
    return m_histogram_background;
  }

  /** Sets the background color that each histogram
   * has.
   *
   * @param histogram_background the histogram background color to set
   */
  void
  set_histogram_background (const Color& histogram_background)
  {
    m_histogram_background = histogram_background;
  }

  /** Returns the fill color of each histogram's bars.
   *
   * @return the histogram fill color
   */
  const Color&
  get_histogram_fill () const
  {
    return m_histogram_fill;
  }

  /** Sets the fill color of each histogram's bars.
   *
   * @param histogram_fill the histogram fill color to set
   */
  void
  set_histogram_fill (const Color& histogram_fill)
  {
    m_histogram_fill = histogram_fill;
  }

  // IOVector

  /** Returns the decimal place that is every column cell
   * is rounded to.
   *
   * @return the decimal place
   */
  int
  get_relevant_places () const
  {
    return m_relevant_places;
  }

  /** Sets the decimal place that is every column cell
   * is rounded to.
   *
   * @param relevant_places the epsilon places to set
   */
  void
  set_relevant_places (int relevant_places)
  {
    m_relevant_places = relevant_places;
  }

  // Standard properties and labels

  /** Returns MooViEs DrawerProperties for thick black
   * lines.
   *
   * @return the DrawerProperties for thick lines
   */
  const DrawerProperties<> &
  get_prop_thick () const
  {
    return m_prop_thick;
  }

  /** Sets MooViEs DrawerProperties for thick black
   * lines.
   *
   * @param prop_thick the DrawerProperties to set
   */
  void
  set_prop_thick (const DrawerProperties<> & prop_thick)
  {
    m_prop_thick = prop_thick;
  }

  /** Returns MooViEs DrawerProperties for thin black
   * lines.
   *
   * @return the DrawerProperties for thin lines
   */
  const DrawerProperties<> &
  get_prop_thin () const
  {
    return m_prop_thin;
  }

  /** Sets MooViEs DrawerProperties for thin black
   * lines.
   *
   * @param prop_thin the DrawerProperties to set
   */
  void
  set_prop_thin (const DrawerProperties<> & prop_thin)
  {
    m_prop_thin = prop_thin;
  }

  /** Returns MooViEs TextProperties for Scale labels.
   *
   * @return the TextProperties for Scale labels
   */
  const TextProperties &
  get_prop_scale_label () const
  {
    return m_prop_scale_label;
  }

  /** Sets MooViEs TextProperties for Scale labels.
   *
   * @param prop_scale_label the TextProperties to set
   */
  void
  set_prop_scale_label (const TextProperties & prop_scale_label)
  {
    m_prop_scale_label = prop_scale_label;
  }

  /** Returns MooViEs TextProperties for InputAxis
   * labels.
   *
   * @return the TextProperties for InputAxis labels
   */
  const TextProperties &
  get_prop_axis_label () const
  {
    return m_prop_axis_label;
  }

  /** Sets MooViEs TextProperties for InputAxis
   * labels.
   *
   * @param prop_axis_label the TextProperties to set
   */
  void
  set_prop_axis_label (const TextProperties& prop_axis_label)
  {
    m_prop_axis_label = prop_axis_label;
  }

private:
  /** Creates a configuration with the given input file path and
   * other configuration data from the given path.
   *
   * @param fname the input file path
   * @param cpath the configuration file path
   */
  Configuration (const std::string& fpath, const std::string& cpath);

  /** Creates a configuration with the given input file path.
   *
   * @param fname the input file path
   */
  Configuration (const std::string& fpath);

  /** Tries to guess the height and width of the MooViE scene
   * using the
   */
  void
  adjust_height ();
};

#endif /* CONFIGURATION_H_ */
