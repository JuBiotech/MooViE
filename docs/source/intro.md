The Multi-objective optimization Visualization Engine (MooViE) is developed at
the Institute of Bio- and Geosciences 1 (IBG-1) of the Forschungszentrum Jülich. MooViE
is an easy-to-use tool to display multidimensional data. It is designed for
pareto optima with up to eight optimization criteria.

MooViE comes with a simple graphical user interface that allows the user to interactively
change which data is displayed and configure the style.

### Quick start with the Command Line Tool
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