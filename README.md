<img src="doc/images/logo.png" width="500"/>

# Multi-objective optimization Visualization Engine

 
The Multi-objective optimization Visualization Engine (MooViE) is developed at 
the Institute of Bio- and Geosciences 1 (IBG-1) of the Forschungszentrum Jülich. MooViE 
is an easy-to-use tool to display multidimensional data. It is designed for 
pareto optima with up to eight optimization criteria
 
MooViE comes with a simple graphical user interface that allows the user to interactively 
change which data is displayed and configure the style.

### Prerequisites and Dependencies
MooViE currently supports Linux.

Required tools:
* A C++11 capable compiler
* [CMake](http://cmake.org) >= 3.1

Required Libraries:
* _freetype2_
* _sigc++-2.0_
* _cairo_ and _cairomm-1.0_
* _Qt4_ with _QtWebKit_

### How to install MooViE
Clone or download this repository. Generate Makefile using _CMake_:
```shell
cmake <MooViE directory>
```
You can set the install directory using `-DCMAKE_INSTALL_PREFIX`. Finally, MooViE is 
installed using _Make_:
```shell
make install
```

### Input Format
The MooViE input file needs to be in CSV format using **commas** as column delimiters. 
Comments begin with **\#**. The first line that is neither a blank line and nor a comment 
is the column header line. Column headers specify the name of the component, its unit 
and if it contains input or criteria (output) values.

The syntax is `i#<input name>[<unit>]` for input headers and `o#<output name>[<unit>]` 
for outputs. If a column name should contain commas or square brackets, it can be masked by 
quotes. Square brackets and units can be omitted. 

It is required that all input columns are followed by all output columns. The table 
cells must not be empty.

### How to use the Command Line Tool
If installed, the `moovie` should be available from the command line. The syntax for 
the command line tool is
```shell
moovie [[OPTION <arg>]...] <input file>
```
When calling MooViE from the command line, an input file _must_ be specified. MooViE 
generates an SVG file that is by default `image.svg` in your current path. The command 
line tool has the following options:

**-o/\-\-output-file** path of the result file [string]

**-x/\-\-width** width of the result image [positive integer]

**-y/\-\-height** height of the result image [positive integer]

**-c/\-\-configuration-file** path of the configuration file [string]

A valid call would be for instance
```shell
moovie -x 750 -y 750 -o ./output.svg -c ./moovie.conf input.csv
```

### How to use the GUI
With MooViE's graphical user interface you can easily configure MooViE and display 
the results.

For running a MooViE scene, an input file (1) and an output (2) need to be specified. 
You can now render the scene with a simple click (3). If the output does not satisfy 
your wishes, you can edit the configuration for the MooViE scene (4). By using the 
column control section (5), you can now alter how and what data is displayed.

You can enable and disable inputs and outputs by a toggle button and enter new boundaries 
for the values in the selected column. The order of columns can also be changed by 
drag-and-drop.

The configuration dialog simplifies editing the configuration for the MooViE scene. 
Configurations also be saved to a file for later and loaded from a file directly 
into the current Scene.

### How to configure MooViE
MooViE has a large amount of configuration values. Their meaning is outlined graphically
in the following picture.

If you use MooViE on the command line, you might want to create a custom configuration 
file. A default that you can use as base can be found at `test/files/moovie.conf`. 
A configuration file consists of lines that encode key value pairs. The syntax of such 
a line is `moovie.<key> = <value>`. An example for a valid line is

`moovie.width = 500`.

Blank lines and lines that start with **\#** are 
ignored.

### Detailed configuration value description


