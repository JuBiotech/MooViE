Configuration
==========

MooViE has a large amount of configuration values. Some of them are outlined graphically
in the following picture.

<p align="center">
  <img width="500" src="_images/scene_conf_values.png" />
</p>

If you use MooViE on the command line, you might want to create a custom configuration
file. A default that you can use as base can be found at `src/test/resources/moovie.conf`.
A configuration file consists of lines that encode key value pairs. The syntax of such
a line is `moovie.<key> = <value>`. An example for a valid line is

`moovie.width = 500`.

Blank lines and lines that start with **\#** are
ignored.

## Detailed configuration value description

### Setting image dimensions
* **width**: the image width [positive integer]
* **height**: the image height [positive integer]

### Setting the line widths

* **thick_line_width**: line width that is used for thick lines [float], _default_
  = 0.5
* **thin_line_width**: line width that is used for thin lines [float], _default_ =
  0.1

### Setting font properties

* **scale_label_font**: font name of input/output scale descriptions [string], _default_ = "Liberation Serif"
* **scale_label_font_size**: font size of input/output scale descriptions [positive integer], _default_ =
  5
* **axis_label_font**: font name of input/output labels [string], _default_ = "Liberation Serif"
* **axis_label_font_size**: font size of the input/output label [positive integer], _default_ =
  10

### Configuring the output grid

* **output_angle_span**: angle of the output grid in degrees [float], _default_ = 160.0
* **output_inner_radius**: distance from the center of the scene to the begin of the
  output grid [float], _default_ = 160
* **output_thickness**: thickness of the primary output arc in px [float], _default_
  = 5
* **grid_size**: distance from the primary output arc to the end the output grid in px [float],
  _default_ = 150
* **num_major_sections_grid**: number of major ticks on the output scale [positive integer],
  _default_ = 10
* **num_minor_sections_grid**: number of minor ticks between big ticks on the output scale [positive integer],
  _default_ = 10
* **min_grid_fill_ratio**: minimal ratio of variable to axis span [float, between 0 and 1], _default_ = 0.9

### Configuring the input axis

* **input_inner_radius**: distance from the center of the scene to the begin of an
  input axis in px [float], _default_ = 180
* **input_thickness**: thickness of the input arcs in px [float] _default_ = 5
* **input_separation_angle**: angle between two input axis in degrees [float], _default_ = 5
* **num_major_sections_axis**: number of major ticks on the input scale [positive integer],
  _default_ = 10
* **num_minor_sections_axis**: number of minor ticks between big ticks on the input scale [positive integer],
  _default_ = 10

### Configuring the input histograms

* **histograms_enabled**: enables displaying statistical information about the inputs [boolean],
  _default_ = true
* **num_histogram_classes**: number of classes/bins in the histogram [positive integer],
  default_ = 10
* **histogram_height**: height of the histogram in px [float], _default_ = 20.0
* **histogram_background**: RGB values [0...1]  of the histogram background color [float, float, float],
   _default_ = 0.0, 0.0, 0.0
* **histogram_fill**: RGB values [0...1] of the histogram class fill color [float, float, float],
  _default_ = 0.5, 0.5, 0.5

### Configuring data rows

* **relevant_places**: number of decimal places that MooViE will round a table cell
  to [integer],
  _default_ = 3