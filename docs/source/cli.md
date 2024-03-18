Command Line Interface
======================

If installed, the `moovie` is available from the command line. The syntax for
the command line tool is
```shell
moovie [[OPTION <arg>]...] <input file>
```
When calling MooViE from the command line, an input file _must_ be specified. MooViE
generates an SVG file that is by default `image.svg` in your current path. The command
line tool has the following options:

- **-o/\-\-output-file** path of the result file [string]

- **-x/\-\-width** width of the result image [positive integer]

- **-y/\-\-height** height of the result image [positive integer]

- **-c/\-\-configuration-file** path of the configuration file [string]

A valid call would be for instance
```shell
moovie -x 750 -y 750 -o ./output.svg -c ./moovie.conf input.csv
```