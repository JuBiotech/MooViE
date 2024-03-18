<img src="docs/source/images/logo.png" width="500"/>

# Multi-objective optimization Visualization Engine

The Multi-objective optimization Visualization Engine (MooViE) is developed at 
the Institute of Bio- and Geosciences 1 (IBG-1) of the Forschungszentrum Jülich. MooViE 
is an easy-to-use tool to display multidimensional data. It is designed for 
pareto optima with up to eight optimization criteria.
 
MooViE comes with a simple graphical user interface that allows the user to interactively 
change which data is displayed and configure the style.

### Prerequisites and Dependencies
These prerequisites are only necessary if you want to install MooViE natively. This is currently only supported for 
Ubuntu (>= 20.04). For other systems, see below section about how to install MooViE using Docker.

Required tools:
* GNU C++ compiler
* CMake (>= 3.7, recommended cmake-curses-gui or cmake-qt-gui)

Required Libraries:
- libfreetype-dev
- libsigc++-2.0-dev
- libcairo2-dev
- libcairomm-1.0-dev
- Either Qt5 libraries (qtbase5-dev, qttools5-dev, libqt5svg5-dev, libgl1-mesa-dev) or Qt6 libraries (qt6-base-dev, qt6-tools-dev, libqt6svg6-dev, libgl1-mesa-dev)

### How to install MooViE
There are two ways to install MooViE for your operating system. The recommended and more generic way is to use _Docker_
in combination with X11. For Ubuntu operating systems (>= 20.04), MooViE can also be installed manually.

#### Docker
To simplify the installation procedure we supply two scripts that install and run Docker containers in which the 
graphical user interface of MooViE runs. It can be displayed on the host machine via X11 connection. The scripts are 
located in the project directory root. Prior to installing and running MooViE with the scripts, you need to install
Docker (for instance by following this
[instruction](https://docs.docker.com/engine/install/ubuntu/#install-docker-engine)).

On Linux systems with X11 server installed and running you just need to open a bash console and run the 
installation/runner script with
```shell script
./moovie-desktop-docker.sh [-d Dockerfile location] [-v Volume location]
```
On Windows systems, you additionally need to install an Xserver 
(check out [vcxsrv](https://sourceforge.net/projects/vcxsrv/)) and run it with disabled access control 
([helpful tutorial](https://medium.com/@potatowagon/how-to-use-gui-apps-in-linux-docker-container-from-windows-host-485d3e1c64a3)).
Being set up, you can now open a Powershell console and run the Windows installation/runner script with
```powershell
./moovie-desktop-docker.ps1 [-d Dockerfile location] [-v Volume to mount]
```

Both scripts will build the Docker image and run it afterward. For later runs, the script will check if the image is 
already installed and just run it directly. 

#### Manual
After installing the dependencies from above using `apt-get`, you can simply follow the installation steps for MooViE from the Dockerfile.

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

- **-o/\-\-output-file** path of the result file [string]

- **-x/\-\-width** width of the result image [positive integer]

- **-y/\-\-height** height of the result image [positive integer]

- **-c/\-\-configuration-file** path of the configuration file [string]

A valid call would be for instance

```shell
moovie -x 750 -y 750 -o ./output.svg -c ./moovie.conf input.csv
```



